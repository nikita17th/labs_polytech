#ifndef B3_EXCEPTIONS_COMMANDS_HPP
#define B3_EXCEPTIONS_COMMANDS_HPP

#include <exception>
#include <string>

class InvalidBookmark: public std::exception
{
public:
  InvalidBookmark();
  explicit InvalidBookmark(const std::string & error);
  const char* what() const noexcept override;
private:
  std::string error_;
};

class InvalidStep: public std::exception
{
public:
  InvalidStep();
  explicit InvalidStep(const std::string & error);
  const char* what() const noexcept override;
private:
  std::string error_;
};

class InvalidCommand: public std::exception
{
public:
  InvalidCommand();
  explicit InvalidCommand(const std::string & error);
  const char* what() const noexcept override;
private:
  std::string error_;
};

class Empty: public std::exception
{
public:
  Empty();
  explicit Empty(const std::string & error);
  const char* what() const noexcept override;
private:
  std::string error_;
};

#endif
