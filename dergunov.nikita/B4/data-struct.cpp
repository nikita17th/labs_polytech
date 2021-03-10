#include "data-struct.hpp"

#include <iostream>
#include <string>
#include <boost/io/ios_state.hpp>
#include <array>
#include <cmath>

#include "common-functions.hpp"

const char DELIMITER_COMMA = ',';

bool operator==(const DataStruct &left, const DataStruct &right)
{
  return (left.key1_ == left.key2_) && (left.key2_ == right.key2_) && (left.str_ == right.str_);
}

bool operator!=(const DataStruct &left, const DataStruct &right)
{
  return !(right == left);
}

bool operator<(DataStruct const & left, DataStruct const & right)
{
  if (left.key1_ != right.key1_)
  {
    return left.key1_ < right.key1_;
  }

  if (left.key2_ != right.key2_)
  {
    return left.key2_ < right.key2_;
  }

  return left.str_.size() < right.str_.size();
}

bool operator>(const DataStruct &left, const DataStruct &right)
{
  return right < left;
}

std::istream &operator>>(std::istream & is, DataStruct &dataStruct)
{
  boost::io::ios_flags_saver ifs(is);
  std::skipws(is);
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }

  std::array<int, 2> keys {6, 6};
  std::string str;

  std::noskipws(is);

  for (int & key : keys)
  {
    is >> detail::skipBlanks >> key >> detail::skipBlanks;
    detail::skipSymbol(DELIMITER_COMMA, is);
    if (std::abs(key) > 5)
    {
      is.setstate(std::istream::failbit);
    }
    if (is.fail())
    {
      return is;
    }
  }

  std::getline(is >> detail::skipBlanks, str);
  if (str.empty())
  {
    is.setstate(std::istream::failbit);
    return is;
  }

  dataStruct.key1_ = keys[0];
  dataStruct.key2_ = keys[1];
  dataStruct.str_ = std::move(str);

  return is;
}

std::ostream &operator<<(std::ostream &os, DataStruct const &dataStruct)
{
  std::ostream::sentry sentry(os);
  if (sentry)
  {
    os << dataStruct.key1_ << DELIMITER_COMMA << dataStruct.key2_ << DELIMITER_COMMA << dataStruct.str_;
  }

  return os;
}
