#include "data-struct.hpp"

#include <iostream>
#include <string>

#include "base-types.hpp"

dergunov::B4::DataStruct::DataStruct():
  key1_(DEFAULT_KEY_VALUE),
  key2_(DEFAULT_KEY_VALUE),
  str_()
{}

bool dergunov::B4::operator==(const dergunov::B4::DataStruct &left, const dergunov::B4::DataStruct &right)
{
  return (left.key1_ == left.key2_) && (left.key2_ == right.key2_) && (left.str_ == right.str_);
}

bool dergunov::B4::operator!=(const dergunov::B4::DataStruct &left, const dergunov::B4::DataStruct &right)
{
  return !(right == left);
}

bool dergunov::B4::operator<(DataStruct const & left, DataStruct const & right)
{
  if (left.key1_ != right.key1_) {
    return left.key1_ < right.key1_;
  }

  if (left.key2_ != right.key2_) {
    return left.key2_ < right.key2_;
  }

  return left.str_.size() < right.str_.size();
}

bool dergunov::B4::operator>(const dergunov::B4::DataStruct &left, const dergunov::B4::DataStruct &right)
{
  return right < left;
}

std::istream &dergunov::B4::operator>>(std::istream & in, dergunov::B4::DataStruct &dataStruct)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  int key1 = 0;
  int key2 = 0;
  std::string str;

  std::noskipws(in);
  DataStruct::readKey(key1, in);
  in >> details::skipBlanks;
  details::skipSymbol(DELIMITER, in);
  in >> details::skipBlanks;
  DataStruct::readKey(key2, in);
  in >> details::skipBlanks;
  details::skipSymbol(DELIMITER, in);
  std::getline(in, str);
  if (str.empty()) {
    in.setstate(std::istream::failbit);
  }
  std::skipws(in);
  if (!sentry){
    return in;
  }

  dataStruct.key1_ = key1;
  dataStruct.key2_ = key2;
  dataStruct.str_ = std::move(str);

  return in;
}

void dergunov::B4::DataStruct::readKey(int & key, std::istream & in, std::ostream &)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return;
  }
  in >> key;
  if (in.eof()|| key > MAX_VALUE || key < MIN_VALUE) {
    in.setstate(std::istream::failbit);
  }
}

std::ostream &dergunov::B4::operator<<(std::ostream &out, dergunov::B4::DataStruct const &dataStruct)
{
  std::ostream::sentry sentry(out);
  if (sentry) {
    out << dataStruct.key1_ << DELIMITER << dataStruct.key2_ << DELIMITER << dataStruct.str_;
  }

  return out;
}
