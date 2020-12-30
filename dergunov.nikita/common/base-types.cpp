#include "base-types.hpp"

#include <cmath>
#include <string>
#include <iostream>

namespace dergunov
{
  bool checkIntersection(const rectangle_t &frameRectFirstShape, const rectangle_t &frameRectSecondShape)
  {
    double dCenterX = fabs(frameRectFirstShape.pos.x - frameRectSecondShape.pos.x);
    double dCenterY = fabs(frameRectFirstShape.pos.y - frameRectSecondShape.pos.y);

    double sumHalfWidth = frameRectFirstShape.width / 2 + frameRectSecondShape.width / 2;
    double sumHalHeight = frameRectFirstShape.height / 2 + frameRectSecondShape.height / 2;

    return (dCenterX <= sumHalfWidth) && (dCenterY <= sumHalHeight);
  }

  bool details::skipSymbol(char symbol, std::istream &in, std::ostream &)
  {
    std::istream::sentry sentry(in);
    if (sentry && in.peek() == symbol && in.get()) {
      return true;
    }
    in.setstate(std::istream::failbit);
    return false;
  }
}
