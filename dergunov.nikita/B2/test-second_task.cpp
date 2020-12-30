#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>
#include <stdexcept>

#include "functions.hpp"

BOOST_AUTO_TEST_SUITE(SECOND_TASK)

  BOOST_AUTO_TEST_CASE(TWO_VALUE_LIST)
  {
  
    std::stringstream nowInOut;
    std::string in = "14 6";
    std::istringstream nowIn(in);
    std::string example = "14 6";

    dergunov::executeSecondTask(nowIn, nowInOut);

    std::string out;
    std::getline(nowInOut, out);
    BOOST_CHECK(out == example);
  }

  BOOST_AUTO_TEST_CASE(TWENTY_VALUE_LIST)
  {

    std::stringstream nowInOut;
    std::string in = "1 20 6 6 19 15 11 8 6 11 7 1 7 8 18 20 7 11 9 17";
    std::istringstream nowIn(in);
    std::string example = "1 17 20 9 6 11 6 7 19 20 15 18 11 8 8 7 6 1 11 7";

    dergunov::executeSecondTask(nowIn, nowInOut);

    std::string out;
    std::getline(nowInOut, out);
    BOOST_CHECK(out == example);

  }

  BOOST_AUTO_TEST_CASE(THREE_VALUE_LIST)
  {

    std::stringstream nowInOut;
    std::string in = "15 20 16";
    std::istringstream nowIn(in);
    std::string example = "15 16 20";

    dergunov::executeSecondTask(nowIn, nowInOut);

    std::string out;
    std::getline(nowInOut, out);
    BOOST_CHECK(out == example);

  }

  BOOST_AUTO_TEST_CASE(EMPTY_INPUT)
  {

    std::stringstream nowInOut;
    std::string in;
    std::istringstream nowIn(in);
    std::string example;

    dergunov::executeSecondTask(nowIn, nowInOut);

    std::string out;
    std::getline(nowInOut, out);
    BOOST_CHECK(out == example);

  }


  BOOST_AUTO_TEST_CASE(INVALID_NUMBER)
  {

    std::stringstream nowInOut;
    std::string in = "f";
    std::istringstream nowIn(in);

    BOOST_CHECK_THROW(dergunov::executeSecondTask(nowIn, nowInOut), std::invalid_argument);

  }

  BOOST_AUTO_TEST_CASE(INVALID_NUMBER_IN_A_MIDDLE)
  {

    std::stringstream nowInOut;
    std::string in = "19 16 3 17 20 9 18 a 8 14 7 17 17 12 6 11 16 8 20";
    std::istringstream nowIn(in);

    BOOST_CHECK_THROW(dergunov::executeSecondTask(nowIn, nowInOut), std::invalid_argument);

  }

  BOOST_AUTO_TEST_CASE(MAX_VALUES_MINUS_1)
  {

    std::stringstream nowInOut;
    std::string in = "19 16 3 17 20 9 18 20 8 14 7 17 17 12 6 11 16 8 20";
    std::istringstream nowIn(in);
    std::string example = "19 20 16 8 3 16 17 11 20 6 9 12 18 17 20 17 8 7 14";

    dergunov::executeSecondTask(nowIn, nowInOut);

    std::string out;
    std::getline(nowInOut, out);
    BOOST_CHECK(out == example);

  }

  BOOST_AUTO_TEST_CASE(RATIONAL_NUMBER)
  {

    std::stringstream nowInOut;
    std::string in = "8.6";
    std::istringstream nowIn(in);

    BOOST_CHECK_THROW(dergunov::executeSecondTask(nowIn, nowInOut), std::invalid_argument);

  }

  BOOST_AUTO_TEST_CASE(RATIONAL_NUMBER_IN_A_MIDDLE)
  {

    std::stringstream nowInOut;
    std::string in = "16 1.7 11";
    std::istringstream nowIn(in);

    BOOST_CHECK_THROW(dergunov::executeSecondTask(nowIn, nowInOut), std::invalid_argument);

  }

  BOOST_AUTO_TEST_CASE(SINGLE_VALUE_LIST)
  {

    std::stringstream nowInOut;
    std::string in = "16";
    std::istringstream nowIn(in);
    std::string example = "16";

    dergunov::executeSecondTask(nowIn, nowInOut);

    std::string out;
    std::getline(nowInOut, out);
    BOOST_CHECK(out == example);

  }

  BOOST_AUTO_TEST_CASE(TOO_MANY_VALUES)
  {

    std::stringstream nowInOut;
    std::string in = "1 20 6 6 19 15 11 8 6 11 7 1 7 8 18 20 7 11 9 17 1";
    std::istringstream nowIn(in);

    BOOST_CHECK_THROW(dergunov::executeSecondTask(nowIn, nowInOut), std::invalid_argument);

  }

  BOOST_AUTO_TEST_CASE(VALUE_TOO_BIG)
  {

    std::stringstream nowInOut;
    std::string in = "1 20 6 6 19 15 11 8 6 71 7 1 7 8 18 20 7 11 9 17";
    std::istringstream nowIn(in);

    BOOST_CHECK_THROW(dergunov::executeSecondTask(nowIn, nowInOut), std::invalid_argument);

  }


  BOOST_AUTO_TEST_CASE(VALUE_TOO_SMALL)
  {

    std::stringstream nowInOut;
    std::string in = "1 20 6 6 19 -1 11 8 6 20 7 1 7 8 18 20 7 11 9 17";
    std::istringstream nowIn(in);

    BOOST_CHECK_THROW(dergunov::executeSecondTask(nowIn, nowInOut), std::invalid_argument);

  }

BOOST_AUTO_TEST_SUITE_END()
