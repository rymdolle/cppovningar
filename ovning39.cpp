#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdint>
#include <cmath>
#include <bitset>
#include <Magick++.h>
#include <MagickCore/quantum.h>
#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <unistd.h>
#include <filesystem>

// Encrypt/decrypt files with aes_256_cbc.
// Embed/extract data in lossless images.

// Embed data in the least significant bits (default 3 LSB) so the
// image still look as close to original as possible. Embed in red
// green and blue channels.

// Encrypt data in blocks for the whole image so not just a portion is
// changed.

// Compile with:
// g++ ovning39.cpp $(Magick++-config --cxxflags --libs) -lcrypto

typedef std::vector<uint8_t> AES_key;
typedef std::vector<uint8_t> AES_iv;
typedef std::vector<uint8_t> data_t;

void encode(data_t data, data_t &dst, int depth)
{
  if (depth > 8 || depth < 1) {
    std::cerr << "Invalid depth " << depth << "\n";
    exit(1);
  }

  int mask = 0;
  for (int b = 0; b < depth; ++b)
    mask |= 1 << b;
  for (int i = 0; i * depth < data.size() * 8; ++i) {
    dst[i] &= ~mask;
    int offset = i * depth;
    int p = data[offset/8];
    if (offset % 8 + depth < 8)
      p >>= (8 - ((offset + depth) % 8));
    if (offset % 8 + depth > 8) {
      p <<= (offset % 8 + depth) - 8;
      p |= data[offset/8+1] >> (8 - ((offset + depth) % 8));
    }
    p &= mask;
    dst[i] |= p;
  }
}

data_t decode(data_t src, int depth)
{
  if (depth > 8 || depth < 1) {
    std::cerr << "Invalid depth " << depth << "\n";
    exit(1);
  }

  data_t data;
  int p = 0;
  int offset = 0;
  int mask = 0;

  for (int b = 0; b < depth; ++b)
    mask |= 1 << b;
  for (auto it : src) {
    p <<= depth;
    p |= it & mask;
    if (offset % 8 + depth >= 8) {
      data.push_back(p >> ((offset + depth) % 8));
    }
    offset += depth;
  }
  return data;
}

void encrypt(data_t &data, const AES_key &key)
{
  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
  const EVP_CIPHER *cipher = EVP_aes_256_cbc();
  if (int ks = EVP_CIPHER_key_length(cipher); key.size() < ks) {
    std::cerr << "Key size mismatch (" << key.size()
              << " < " << ks << ").\n";
    exit(1);
  }
  int bs = EVP_CIPHER_block_size(cipher);
  if (data.size() % bs != 0) {
    std::cerr << "Data block mismatch (" << data.size() % bs << ").\n";
    exit(1);
  }
  data_t tmp(bs, 0);
  EVP_EncryptInit(ctx, cipher, key.data(), nullptr);
  for (int i = 0; i < data.size() / bs; ++i) {
    EVP_Cipher(ctx, tmp.data(), data.data() + i * bs, bs);

    // Copy tmp to data
    std::copy(tmp.begin(), tmp.end(), data.begin() + i * bs);
  }

  EVP_CIPHER_CTX_free(ctx);
}

void decrypt(data_t &data, const AES_key &key)
{
  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
  const EVP_CIPHER *cipher = EVP_aes_256_cbc();
  if (int ks = EVP_CIPHER_key_length(cipher); key.size() < ks) {
    std::cerr << "Key size mismatch (" << key.size()
              << " < " << ks << ").\n";
    exit(1);
  }
  int bs = EVP_CIPHER_block_size(cipher);
  if (data.size() % bs != 0) {
    std::cerr << "Data block mismatch (" << data.size() % bs << ").\n";
    exit(1);
  }
  data_t tmp(bs, 0);
  EVP_DecryptInit(ctx, cipher, key.data(), nullptr);
  for (int i = 0; i < data.size() / bs; ++i) {
    EVP_Cipher(ctx, tmp.data(), data.data() + i * bs, bs);

    // Copy tmp to data
    std::copy(tmp.begin(), tmp.end(), data.begin() + i * bs);
  }

  EVP_CIPHER_CTX_free(ctx);
}

void print(data_t data)
{
  auto flags = std::cout.flags();
  for (int i = 0; i < data.size(); ++i) {
    if (i % 16 == 0 && i > 0)
      std::cout << '\n';
    std::cout << std::setw(2) << std::hex << std::setfill('0')
              << static_cast<int>(data[i]) << ' ';
  }
  std::cout << '\n' << '\n';
  std::cout.flags(flags);
}

data_t read_file(std::filesystem::path filename)
{
  if (!std::filesystem::exists(filename)) {
    std::cerr << "File " << filename << " does not exist." << '\n';
    exit(1);
  }
  std::ifstream file(filename, std::ios::binary);
  file.seekg(0, std::ios::end);
  size_t size = file.tellg();
  data_t data(size);
  file.seekg(0, std::ios::beg);
  file.read(reinterpret_cast<char*>(data.data()), size);
  return data;
}

void write_file(std::filesystem::path filename, data_t data)
{
  std::ofstream file(filename, std::ios::binary);
  file.write(reinterpret_cast<char*>(data.data()), data.size());
}

int data_depth(const data_t data, const data_t pixels)
{
  for (int i = 1; i <= 8; ++i)
    if (pixels.size() * i >= data.size() * 8)
      return i;

  return 0;
}

void help(char *argv[])
{
  std::cout << "Usage: " << *argv << " [options...] COMMAND [<input>]\n"
            << " -d <depth>        Depth to embed data in bits\n"
            << " -k <file>         Key file for encrypt/decrypt\n"
            << " -o <file>         Write to file\n"
            << " -i <file>         Read from file\n"
            << " -h                Show this help\n"
            << '\n'
            << "Commands:" << '\n'
            << "  embed <image>    Embed data in image\n"
            << "  extract <image>  Extract data from image\n"
            << "  encrypt          Encrypt data\n"
            << "  decrypt          Decrypt data\n"
            << "  help             Show this help\n"
            << '\n';
  const EVP_CIPHER *cipher = EVP_aes_256_cbc();
  int bs = EVP_CIPHER_block_size(cipher);
  int ks = EVP_CIPHER_key_length(cipher);
  int is = EVP_CIPHER_iv_length(cipher);
  std::cout << "size block:\t" << bs << '\n';
  std::cout << "size key:\t"   << ks << '\n';
  std::cout << "size iv:\t"    << is << '\n';
  std::cout << '\n';
}

int main(int argc, char *argv[])
{
  std::filesystem::path file_in;
  std::filesystem::path file_out;
  std::filesystem::path file_key;
  std::filesystem::path file_image;
  int depth = 0;

  for (char c; (c = getopt(argc, argv, "hd:o:i:k:")) != -1;) {
    switch (c) {
    case 'd': {
      depth = std::strtol(optarg, nullptr, 10);
      if (depth > 8) {
        std::cerr << "Invalid depth (" << depth << ").\n";
        help(argv);
        exit(1);
      }
      break;
    }
    case 'o': {
      file_out = optarg;
      break;
    }
    case 'i': {
      file_in = optarg;
      break;
    }
    case 'k': {
      file_key = optarg;
      break;
    }
    case '?': {
      help(argv);
      exit(1);
    }
    default:
      break;
    }
  }

  if (optind >= argc) {
    std::cerr << "Missing command.\n";
    help(argv);
    exit(1);
  }

  std::string cmd = argv[optind];
  ++optind;
  if (cmd == "help") {
    help(argv);
  } else if (cmd == "extract") {
    if (optind >= argc) {
      std::cerr << "Missing image file." << '\n';
      exit(1);
    }
    file_image = argv[optind];
    Magick::InitializeMagick(*argv);
    Magick::Image img(file_image);
    if (depth <= 0) {
      std::cerr << "Depth must be set.\n";
      help(argv);
      exit(1);
    }

    data_t pixels(img.columns() * img.rows() * 3);
    img.getPixels(0, 0, img.columns(), img.rows());
    img.writePixels(Magick::RGBQuantum, pixels.data());
    data_t data = decode(pixels, depth);
    if (!file_key.empty()) {
      AES_key key = read_file(file_key);
      decrypt(data, key);
    }
    if (file_out.empty()) {
      std::cout.write(reinterpret_cast<const char*>(data.data()), data.size());
    } else {
      write_file(file_out, data);
    }

  } else if (cmd == "embed") {
    if (optind >= argc) {
      std::cerr << "Missing image file." << '\n';
      exit(1);
    }
    if (file_in.empty()) {
      std::cerr << "Missing input file." << '\n';
      exit(1);
    }
    if (file_out.empty()) {
      std::cerr << "Missing output file." << '\n';
      exit(1);
    }
    file_image = argv[optind];
    Magick::InitializeMagick(*argv);
    Magick::Image img(file_image);

    data_t pixels(img.columns() * img.rows() * 3);
    data_t data = read_file(file_in);
    int original_size = data.size();

    if (depth <= 0) {
      depth = data_depth(data, pixels);
    }
    std::cout << "Using data depth of " << depth << '\n';

    if (data.size() * 8 > pixels.size() * depth) {
      std::cerr << "Data is too big (" << data.size() << "). Max "
                << (pixels.size() * depth) / 8 << " bytes "
                << "for supplied image."
                << '\n';
      exit(1);
    }
    // Add padding to fill whole image
    int padding_bits = pixels.size() * depth - data.size() * 8;
    data.resize(data.size() + padding_bits / 8, 0);

    img.getPixels(0, 0, img.columns(), img.rows());
    img.writePixels(Magick::RGBQuantum, pixels.data());
    if (!file_key.empty()) {
      std::cout << "Encrypting data using keyfile " << file_key << '\n';
      AES_key key = read_file(file_key);
      encrypt(data, key);
    }
    encode(data, pixels, depth);
    img.readPixels(Magick::RGBQuantum, pixels.data());
    img.syncPixels();
    img.write(file_out);
    std::cout << "Wrote to " << file_out << '\n';
    std::cout << "Original size:\t" << original_size << '\n';
    std::cout << "Padded size:\t" << data.size() << '\n';

  } else if (cmd == "encrypt") {
    if (file_key.empty()) {
      std::cerr << "Missing key file." << '\n';
      exit(1);
    }
    if (file_in.empty()) {
      std::cerr << "Missing input file." << '\n';
      exit(1);
    }
    if (file_out.empty()) {
      std::cerr << "Missing output file." << '\n';
      exit(1);
    }
    AES_key key = read_file(file_key);
    data_t data = read_file(file_in);
    int padding = 0;
    const EVP_CIPHER *cipher = EVP_aes_256_cbc();
    if (int bs = EVP_CIPHER_block_size(cipher); data.size() % bs > 0)
      padding = bs - (data.size() % bs);
    data.resize(data.size() + padding, 0);
    encrypt(data, key);
    write_file(file_out, data);
    std::cout << "Wrote encrypted data to " << file_out
              << " using " << file_key << '\n';

  } else if (cmd == "decrypt") {
    if (file_key.empty()) {
      std::cerr << "Missing key file." << '\n';
      exit(1);
    }
    if (file_in.empty()) {
      std::cerr << "Missing input file." << '\n';
      exit(1);
    }
    AES_key key = read_file(file_key);
    data_t data = read_file(file_in);
    decrypt(data, key);
    if (file_out.empty()) {
      std::cout.write(reinterpret_cast<const char*>(data.data()), data.size());
    } else {
      std::cout << "Wrote decrypted data to " << file_out
                << " using " << file_key << '\n';
      write_file(file_out, data);
    }

  } else {
    std::cerr << "Invalid command." << '\n';
    help(argv);
  }
  return 0;
}
