#ifndef B4_DATA_STRUCT_HPP
#define B4_DATA_STRUCT_HPP

#include <iostream>
#include <string>

struct DataStruct
{
  int key1_;
  int key2_;
  std::string str_;
};

bool operator==(DataStruct const & left, DataStruct const & right);
bool operator!=(DataStruct const & left, DataStruct const & right);
bool operator<(DataStruct const & left, DataStruct const & right);
bool operator>(DataStruct const & left, DataStruct const & right);
std::istream &operator>>(std::istream &is, DataStruct &dataStruct);
std::ostream &operator<<(std::ostream &os, DataStruct const &dataStruct);

#endif
