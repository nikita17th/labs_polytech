#ifndef B4_DATASTRUCT_HPP
#define B4_DATASTRUCT_HPP

#include <iostream>
#include <vector>
#include <string>

namespace dergunov
{
  namespace B4
  {
    namespace errorMessages
    {
      const std::string INCORRECT_INPUT = "Incorrect input, expected sequence of records view <integer>,<integer>,<string>"
          ",integer from -5 to 5, string not empty, which end EOF!";
    }

    const char DELIMITER = ',';

    class DataStruct
    {
    public:
      DataStruct();

      friend bool operator==(DataStruct const & left , DataStruct const & right);
      friend bool operator!=(DataStruct const & left , DataStruct const & right);
      friend bool operator<(DataStruct const & left , DataStruct const & right);
      friend bool operator>(DataStruct const & left , DataStruct const & right);

      friend std::istream &operator>>(std::istream &in, DataStruct &dataStruct);
      friend std::ostream &operator<<(std::ostream &out, DataStruct const &dataStruct);
    private:
      int key1_;
      int key2_;
      std::string str_;
      static  const int MAX_VALUE = 5;
      static  const int MIN_VALUE = -5;
      static  const int DEFAULT_KEY_VALUE = 0;
      static void readKey(int &key, std::istream &in = std::cin, std::ostream &out = std::cout);
    };

    bool operator==(DataStruct const & left , DataStruct const & right);
    bool operator!=(DataStruct const & left , DataStruct const & right);
    bool operator<(DataStruct const & left , DataStruct const & right);
    bool operator>(DataStruct const & left , DataStruct const & right);
    std::istream &operator>>(std::istream &in, DataStruct &dataStruct);
    std::ostream &operator<<(std::ostream &out, DataStruct const &dataStruct);
  }
}
#endif
