#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

class Date
{
private:
  int year_, month_, day_;
public:
  Date(int year, int month, int day)
  {
    setDate(year, month, day);
  }

  std::string to_string()
  {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(4) << year_  << '.'
       << std::setfill('0') << std::setw(2) << month_ << '.'
       << std::setfill('0') << std::setw(2) << day_;
    return ss.str();
  }

  void setDate(int year, int month, int day)
  {
    year_ = year;
    month_ = month;
    day_ = day;
  }
};

class Person
{
private:
  std::string firstname_, lastname_;
  Date birthdate_;
public:
  Person(std::string firstname, std::string lastname, Date birthdate) :
    birthdate_(birthdate)
  {
    firstname_ = firstname;
    lastname_ = lastname;
  }

  std::string to_string()
  {
    std::stringstream ss;
    ss << firstname_ << ' ' << lastname_ << '\n'
       << "birthdate:\t" << birthdate_.to_string();
    return ss.str();
  }
};

class Employee : private Person
{
private:
  Date hiredate_;
public:
  Employee(std::string firstname, std::string lastname,
           Date birthdate, Date hiredate) :
    Person(firstname, lastname, birthdate), hiredate_(hiredate)
  {
  }

  std::string to_string()
  {
    std::stringstream ss;
    ss << Person::to_string() << '\n'
       << "hiredate:\t" << hiredate_.to_string();
    return ss.str();
  }

  void setHiredate(int year, int month, int day)
  {
    hiredate_.setDate(year, month, day);
  }
};

int main(int argc, char *argv[])
{
  Date b(1998, 2, 18);
  Date h(2012, 9, 1);
  Employee anst("Kalle", "Anka", b, h);
  std::cout << anst.to_string() << '\n'
            << h.to_string() << '\n' << '\n';

  anst.setHiredate(2013, 10, 21);
  std::cout << anst.to_string() << '\n'
            << h.to_string() << '\n';
  return 0;
}
