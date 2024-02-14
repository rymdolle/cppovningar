#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Smart pointers

class Item
{
private:
  std::string name_;
  int price_;

public:
  Item(std::string name, int price)
  {
    std::cout << "Create " << name << '\n';
    name_ = name;
    price_ = price;
  }
  ~Item()
  {
    std::cout << "Delete " << name_ << '\n';
  }

  void print()
  {
    std::cout << name_ << ": " << price_ << '\n';
  }
};

class Inventory
{
private:
  std::vector<std::shared_ptr<Item>> items_;

public:
  void add(std::string name, int price)
  {
    auto ptr = std::make_shared<Item>(name, price);
    std::cout << "Count before push: " << name << ' '
              << ptr.use_count() << ' ' << ptr.get() << '\n';
    items_.push_back(ptr);
    std::cout << "Count after  push: " << name << ' '
              << ptr.use_count() << ' ' << ptr.get() << '\n';
  }

  void print_all()
  {
    for (const auto& i : items_) {
      std::cout << i.use_count() << ' ';
      i->print();
    }
  }
};

int main(int argc, char *argv[])
{
  Inventory inv;
  inv.add("Apple", 12);
  inv.add("Banana", 11);
  inv.add("Pear", 13);
  inv.add("Strawberry", 10);
  inv.add("Ananas", 22);

  inv.print_all();
  return 0;
}
