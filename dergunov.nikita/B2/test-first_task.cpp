#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>
#include "functions.hpp"

BOOST_AUTO_TEST_SUITE(FIRST_TASK)

  BOOST_AUTO_TEST_CASE(ACCELERATE)
  {

    std::stringstream nowInOut;
    std::string in = "add normal hi\nadd low bye\naccelerate\nget";
    std::istringstream nowIn(in);
    std::string example = "bye";

    dergunov::executeFirstTask(nowIn, nowInOut);

    std::string out;
    std::getline(nowInOut, out);
    BOOST_CHECK(out == example);
  }

  BOOST_AUTO_TEST_CASE(ADD_SINGLE_ELEMENT_WITH_HIGH_PRIORITY)
  {

    std::stringstream nowInOut;
    std::string in = "add high hello\nget";
    std::istringstream nowIn(in);
    std::string example = "hello";

    dergunov::executeFirstTask(nowIn, nowInOut);

    std::string out;
    std::getline(nowInOut, out);
    BOOST_CHECK(out == example);
  }

  BOOST_AUTO_TEST_CASE(ADD_SINGLE_ELEMENT_WITH_INVALID_PRIORITY)
  {

    std::stringstream nowInOut;
    std::string in = "add error hello";
    std::istringstream nowIn(in);
    std::string example = "<INVALID COMMAND>";
    
    dergunov::executeFirstTask(nowIn, nowInOut);

    std::string out;
    std::getline(nowInOut, out);
    BOOST_CHECK(out == example);

  }

  BOOST_AUTO_TEST_CASE(ADD_SINGLE_ELEMENT_WITH_LOW_PRIORITY)
  {

    std::stringstream nowInOut;
    std::string in = "add low hello\nget";
    std::istringstream nowIn(in);
    std::string example = "hello";

    dergunov::executeFirstTask(nowIn, nowInOut);

    std::string out;
    std::getline(nowInOut, out);
    BOOST_CHECK(out == example);

  }

  BOOST_AUTO_TEST_CASE(ADD_SINGLE_ELEMENT_WITH_NORMAL_PRIORITY)
  {

    std::stringstream nowInOut;
    std::string in = "add normal hello\nget";
    std::istringstream nowIn(in);
    std::string example = "hello";

    dergunov::executeFirstTask(nowIn, nowInOut);

    std::string out;
    std::getline(nowInOut, out);
    BOOST_CHECK(out == example);
  }

  BOOST_AUTO_TEST_CASE(ADD_SINGLE_ELEMENT_WITHOUT_DATA)
  {

    std::stringstream nowInOut;
    std::string in = "add low ";
    std::istringstream nowIn(in);
    std::string example = "<INVALID COMMAND>";

    dergunov::executeFirstTask(nowIn, nowInOut);

    std::string out;
    std::getline(nowInOut, out);
    BOOST_CHECK(out == example);

  }

  BOOST_AUTO_TEST_CASE(ELEMENT_WITH_MIXED_SEPARATORS)
  {

    std::stringstream nowInOut;
    std::string in = "add low hello world !\nget";
    std::istringstream nowIn(in);
    std::string example = "hello world !";

    dergunov::executeFirstTask(nowIn, nowInOut);

    std::string out;
    std::getline(nowInOut, out);
    BOOST_CHECK(out == example);

  }

  BOOST_AUTO_TEST_CASE(ELEMENT_WITH_MULTIPLE_SEPARATORS)
  {

    std::stringstream nowInOut;
    std::string in = "add low hello     world   !\nget";
    std::istringstream nowIn(in);
    std::string example = "hello     world   !";

    dergunov::executeFirstTask(nowIn, nowInOut);

    std::string out;
    std::getline(nowInOut, out);
    BOOST_CHECK(out == example);

  }

  BOOST_AUTO_TEST_CASE(ELEMENTS_WITH_VARIOUS_PRIORITIES)
  {

    std::stringstream nowInOut;
    std::string in = "add low hello \nadd normal world \nadd high ! \nget\nget\nget";
    size_t countWords = 3;
    std::istringstream nowIn(in);
    std::string example = "! \nworld \nhello \n";

    dergunov::executeFirstTask(nowIn, nowInOut);

    std::string out;
    std::string inputForOut;
    for (size_t i = 0; i < countWords; i++) {
      std::getline(nowInOut, inputForOut);
      out += inputForOut + "\n";
    }

    BOOST_CHECK(out == example);

  }

  BOOST_AUTO_TEST_CASE(EMPTY_INPUT_OUTPUT)
  {

    std::stringstream nowInOut;
    std::string in;
    std::istringstream nowIn(in);
    std::string example;

    dergunov::executeFirstTask(nowIn, nowInOut);

    std::string out;
    std::getline(nowInOut, out);
    BOOST_CHECK(out == example);

  }

  BOOST_AUTO_TEST_CASE(SINGLE_ELEMENT_WITH_SPACES)
  {

    std::stringstream nowInOut;
    std::string in = "add low               ";
    std::istringstream nowIn(in);
    std::string example = "<INVALID COMMAND>";

    dergunov::executeFirstTask(nowIn, nowInOut);

    std::string out;
    std::getline(nowInOut, out);
    BOOST_CHECK(out == example);

  }

BOOST_AUTO_TEST_SUITE_END()
