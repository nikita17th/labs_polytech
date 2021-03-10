#include "common-functions.hpp"

#include <iostream>

bool detail::skipSymbol(char symbol, std::istream &is, std::ostream &)
{
  std::istream::sentry sentry(is);
  if (sentry && is.peek() == symbol && is.get())
  {
    return true;
  }
  is.setstate(std::istream::failbit);
  return false;
}
