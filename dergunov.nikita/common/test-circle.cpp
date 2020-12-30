#include <boost/test/unit_test.hpp>
#include <stdexcept>

#include "circle.hpp"
#include "rectangle.hpp"
#include "base-types.hpp"

const double EPS = 10e-7;

BOOST_AUTO_TEST_SUITE(Circle)

  BOOST_AUTO_TEST_CASE(ConstructorCircle_RadiusMoreZero_ObjectCreation)
  {
    double originalRadius = 5.3;
    dergunov::point_t originalCoordinatesCenter = {4.3, -6.3};
    dergunov::Circle circle(originalRadius, originalCoordinatesCenter);

    BOOST_CHECK_CLOSE(circle.getRadius(), originalRadius, EPS);
    BOOST_CHECK_CLOSE(circle.getCenter().x, originalCoordinatesCenter.x, EPS);
    BOOST_CHECK_CLOSE(circle.getCenter().y, originalCoordinatesCenter.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(ConstructorCircle_RadiusEqualZero_ObjectCreation)
  {
    double originalRadius = 0;
    dergunov::point_t originalCoordinatesCenter = {4.3, -6.3};
    dergunov::Circle circle(originalRadius, originalCoordinatesCenter);

    BOOST_CHECK_CLOSE(circle.getRadius(), originalRadius, EPS);
    BOOST_CHECK_CLOSE(circle.getCenter().x, originalCoordinatesCenter.x, EPS);
    BOOST_CHECK_CLOSE(circle.getCenter().y, originalCoordinatesCenter.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(ConstructorCircle_RadiusLessZero_CatchError)
  {
    double radius = -6.1;
    dergunov::point_t coordinatesCenter = {17.5, -43.7};
    BOOST_CHECK_THROW(dergunov::Circle(radius, coordinatesCenter), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MoveCircle_MoveInPoint_CorectWorkMethod)
  {
    double originalRadius = 3.5;
    dergunov::point_t coordinatesCenter = {3.4, -4.6};
    dergunov::Circle circle(originalRadius, coordinatesCenter);
    double areaBeforeMoving = circle.getArea();

    dergunov::point_t newCoordinatesCenter = {4.5, 10.3};
    circle.move(newCoordinatesCenter);

    BOOST_CHECK_CLOSE(circle.getRadius(), originalRadius, EPS);
    BOOST_CHECK_CLOSE(circle.getArea(), areaBeforeMoving, EPS);
    BOOST_CHECK_CLOSE(circle.getCenter().x, newCoordinatesCenter.x, EPS);
    BOOST_CHECK_CLOSE(circle.getCenter().y, newCoordinatesCenter.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(MoveCircle_XandYoffset_CoreectWorkMethod)
  {
    double originalRadius = 2.6;
    dergunov::point_t coordinatesCenter = {13.5, -11.6};
    dergunov::Circle circle(originalRadius, coordinatesCenter);
    double areaBeforeMoving = circle.getArea();

    double dx = -6.2;
    double dy = 5.7;
    circle.move(dx, dy);

    BOOST_CHECK_CLOSE(circle.getRadius(), originalRadius, EPS);
    BOOST_CHECK_CLOSE(circle.getArea(), areaBeforeMoving, EPS);
    BOOST_CHECK_CLOSE(circle.getCenter().x, coordinatesCenter.x + dx, EPS);
    BOOST_CHECK_CLOSE(circle.getCenter().y, coordinatesCenter.y + dy, EPS);
  }

  BOOST_AUTO_TEST_CASE(ScaleCircle_FactorMoreZero_CorrectWorkMethod)
  {
    double radius = 8.6;
    dergunov::point_t coordinatesCenter = {13.5, -11.6};
    dergunov::Circle circle(radius, coordinatesCenter);
    double areaCircleBeforeScale = circle.getArea();
    dergunov::Rectangle frameRectBeforeScale(circle.getFrameRect());
    double areaFrameRectBeforeScale =frameRectBeforeScale.getArea();

    double factor = 5.5;
    circle.scale(factor);
    dergunov::Rectangle frameRectAfterScale(circle.getFrameRect());

    BOOST_CHECK_CLOSE(circle.getArea(), areaCircleBeforeScale * factor * factor, EPS);
    BOOST_CHECK_CLOSE(frameRectAfterScale.getArea(), areaFrameRectBeforeScale * factor * factor, EPS);
  }

  BOOST_AUTO_TEST_CASE(ScaleCircle_FacroEqualZero_CorrectWorkMethod)
  {
    double radius = 14.7;
    dergunov::point_t coordinatesCenter = {5.3, -7.4};
    dergunov::Circle circle(radius, coordinatesCenter);
    dergunov::Rectangle frameRectBeforeScale(circle.getFrameRect());

    double factor = 0;
    circle.scale(factor);
    dergunov::Rectangle frameRectAfterScale(circle.getFrameRect());

    BOOST_CHECK_CLOSE(circle.getArea(), 0, EPS);
    BOOST_CHECK_CLOSE(frameRectAfterScale.getArea(), 0, EPS);
  }

  BOOST_AUTO_TEST_CASE(ScaleCircle_FactorLessZero_CatchError)
  {
    double radius = 14.7;
    dergunov::point_t coordinatesCenter = {5.3, -7.4};
    dergunov::Circle circle(radius, coordinatesCenter);

    double factor = -9.6;
    BOOST_CHECK_THROW(circle.scale(factor), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(RotateCircle_ArbitraryDegree_NoChange)
  {
    double radius = 14.7;
    double degree = 578;
    dergunov::point_t coordinatesCenter = {5.3, -7.4};
    dergunov::Circle circle(radius, coordinatesCenter);

    circle.rotate(degree);

    BOOST_CHECK_CLOSE(circle.getRadius(), radius, EPS);
    BOOST_CHECK_CLOSE(circle.getCenter().x, coordinatesCenter.x, EPS);
    BOOST_CHECK_CLOSE(circle.getCenter().y, coordinatesCenter.y, EPS);
  }
BOOST_AUTO_TEST_SUITE_END()

