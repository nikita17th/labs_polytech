#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include <cmath>

#include "rectangle.hpp"
#include "base-types.hpp"

const double EPS = 10e-7;


BOOST_AUTO_TEST_SUITE(Rectangle)
 BOOST_AUTO_TEST_CASE(ConstructorRectangle_HieghtAndWidthMoreZeroDefaultAngle_CreateObject)
  {
    double originalWidth = 12.5;
    double originalHeight = 5.3;
    dergunov::point_t originalCoordinatesCenter = {-4.3, 6.3};
    dergunov::Rectangle rectangle(originalWidth, originalHeight, originalCoordinatesCenter);

    BOOST_CHECK_CLOSE(rectangle.getWidth(), originalWidth, EPS);
    BOOST_CHECK_CLOSE(rectangle.getHeight(), originalHeight, EPS);
    BOOST_CHECK_CLOSE(rectangle.getCenter().x, originalCoordinatesCenter.x, EPS);
    BOOST_CHECK_CLOSE(rectangle.getCenter().y, originalCoordinatesCenter.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(ConstructorRectangle_HieghtAndWidthMoreZeroAngleMoreZero_CreateObject)
  {
    double originalWidth = 12.5;
    double originalHeight = 5.3;
    dergunov::point_t originalCoordinatesCenter = {-4.3, 6.3};
    dergunov::Rectangle rectangle(originalWidth, originalHeight, originalCoordinatesCenter, 450);

    dergunov::rectangle_t frameRect {rectangle.getFrameRect()};
    BOOST_CHECK_CLOSE(frameRect.width, originalHeight, EPS);
    BOOST_CHECK_CLOSE(frameRect.height, originalWidth, EPS);
    BOOST_CHECK_CLOSE(rectangle.getCenter().x, originalCoordinatesCenter.x, EPS);
    BOOST_CHECK_CLOSE(rectangle.getCenter().y, originalCoordinatesCenter.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(ConstructorRectangle_HieghtAndWidthMoreZeroAngleLessZero_CreateObject)
  {
    double originalWidth = 12.5;
    double originalHeight = 5.3;
    dergunov::point_t originalCoordinatesCenter = {-4.3, 6.3};
    dergunov::Rectangle rectangle(originalWidth, originalHeight, originalCoordinatesCenter, -450);

    dergunov::rectangle_t frameRect {rectangle.getFrameRect()};
    BOOST_CHECK_CLOSE(frameRect.width, originalHeight, EPS);
    BOOST_CHECK_CLOSE(frameRect.height, originalWidth, EPS);
    BOOST_CHECK_CLOSE(rectangle.getCenter().x, originalCoordinatesCenter.x, EPS);
    BOOST_CHECK_CLOSE(rectangle.getCenter().y, originalCoordinatesCenter.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(ConstructorRectangle_WidthAndHeightEqualZero_CreateObject)
  {
    double originalWidth = 0;
    double originalHeight = 0;
    dergunov::point_t originalCoordinatesCenter = {-4.3, 6.3};
    dergunov::Rectangle rectangle(originalWidth, originalHeight, originalCoordinatesCenter);

    BOOST_CHECK_CLOSE(rectangle.getWidth(), originalWidth, EPS);
    BOOST_CHECK_CLOSE(rectangle.getHeight(), originalHeight, EPS);
    BOOST_CHECK_CLOSE(rectangle.getCenter().x, originalCoordinatesCenter.x, EPS);
    BOOST_CHECK_CLOSE(rectangle.getCenter().y, originalCoordinatesCenter.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(ConstructorRectangle_WidthLessZero_CreateObject)
  {
    double width = -10.3;
    double height = 8.1;
    dergunov::point_t coordinatesCenter = {17.5, -43.7};
    BOOST_CHECK_THROW(dergunov::Rectangle(width, height, coordinatesCenter), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ConstructorRectangle_HeightLessZero_CrateObject)
  {
    double width = 10.3;
    double height = -8.1;
    dergunov::point_t coordinatesCenter = {17.5, -43.7};
    BOOST_CHECK_THROW(dergunov::Rectangle(width, height, coordinatesCenter), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(CoorectConstructorStructure_WidthAndHeightMoreZeri_CreateObject)
  {
    double originalWidth = 12.5;
    double originalHeight = 5.3;
    dergunov::point_t originalCoordinatesCenter = {-4.3, 6.3};
    dergunov::Rectangle rectangle(dergunov::rectangle_t{originalWidth, originalHeight,
        originalCoordinatesCenter});

    BOOST_CHECK_CLOSE(rectangle.getWidth(), originalWidth, EPS);
    BOOST_CHECK_CLOSE(rectangle.getHeight(), originalHeight, EPS);
    BOOST_CHECK_CLOSE(rectangle.getCenter().x, originalCoordinatesCenter.x, EPS);
    BOOST_CHECK_CLOSE(rectangle.getCenter().y, originalCoordinatesCenter.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(ConstructorRectangleStructure_WidthAndHeightEqualZero_CreateObject)
  {
    double originalWidth = 0;
    double originalHeight = 0;
    dergunov::point_t originalCoordinatesCenter = {-4.3, 6.3};
    dergunov::Rectangle rectangle(dergunov::rectangle_t{originalWidth, originalHeight,
        originalCoordinatesCenter});

    BOOST_CHECK_CLOSE(rectangle.getWidth(), originalWidth, EPS);
    BOOST_CHECK_CLOSE(rectangle.getHeight(), originalHeight, EPS);
    BOOST_CHECK_CLOSE(rectangle.getCenter().x, originalCoordinatesCenter.x, EPS);
    BOOST_CHECK_CLOSE(rectangle.getCenter().y, originalCoordinatesCenter.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(ConstructorRectangleStructure_WidthLessZero_CatchError)
  {
    double width = -10.3;
    double height = 8.1;
    dergunov::point_t coordinatesCenter = {17.5, -43.7};
    BOOST_CHECK_THROW(dergunov::Rectangle(dergunov::rectangle_t{width, height,
        coordinatesCenter}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ConstructorRectangleStructure_HeightLessZero_CatchError)
  {
    double width = 10.3;
    double height = -8.1;
    dergunov::point_t coordinatesCenter = {17.5, -43.7};
    BOOST_CHECK_THROW(dergunov::Rectangle(dergunov::rectangle_t{width, height,
        coordinatesCenter}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MoveRectangle_InPoint_CorrectWorkMethod)
  {
    double originalWidth = 7.6;
    double originalHeight = 3.5;
    dergunov::point_t coordinatesCenter = {3.4, -4.6};
    dergunov::Rectangle rectangle(originalWidth, originalHeight, coordinatesCenter);
    double areaBeforeMoving = rectangle.getArea();

    dergunov::point_t newCoordinatesCenter = {12.8, 23.6};
    rectangle.move(newCoordinatesCenter);

    BOOST_CHECK_CLOSE(rectangle.getWidth(), originalWidth, EPS);
    BOOST_CHECK_CLOSE(rectangle.getHeight(), originalHeight, EPS);
    BOOST_CHECK_CLOSE(rectangle.getArea(), areaBeforeMoving, EPS);
    BOOST_CHECK_CLOSE(rectangle.getCenter().x, newCoordinatesCenter.x, EPS);
    BOOST_CHECK_CLOSE(rectangle.getCenter().y, newCoordinatesCenter.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(MoveRectangle_XandYoffset_CorrectWorkMethod)
  {
    double originalWidth = 7.6;
    double originalHeight = 3.5;
    dergunov::point_t coordinatesCenter = {3.4, -4.6};
    dergunov::Rectangle rectangle(originalWidth, originalHeight, coordinatesCenter);
    double areaBeforeMoving = rectangle.getArea();

    double dx = 34.2;
    double dy = -15.1;
    rectangle.move(dx, dy);

    BOOST_CHECK_CLOSE(rectangle.getWidth(), originalWidth, EPS);
    BOOST_CHECK_CLOSE(rectangle.getHeight(), originalHeight, EPS);
    BOOST_CHECK_CLOSE(rectangle.getArea(), areaBeforeMoving, EPS);
    BOOST_CHECK_CLOSE(rectangle.getCenter().x, coordinatesCenter.x + dx, EPS);
    BOOST_CHECK_CLOSE(rectangle.getCenter().y, coordinatesCenter.y + dy, EPS);
  }

  BOOST_AUTO_TEST_CASE(ScaleRectangle_FactorMoreZero_CorrectWorkMethod)
  {
    double width = 7.7;
    double height = 6.5;
    dergunov::point_t coordinatesCenter = {4.3, -6.4};
    dergunov::Rectangle rectangle(width, height, coordinatesCenter);
    double areaBeforeScale = rectangle.getArea();
    dergunov::Rectangle frameRectBeforeScale(rectangle.getFrameRect());
    double areaFrameRectBeforeScale =frameRectBeforeScale.getArea();

    double factor = 4.5;
    rectangle.scale(factor);
    dergunov::Rectangle frameRectAfterScale(rectangle.getFrameRect());

    BOOST_CHECK_CLOSE(rectangle.getArea(), areaBeforeScale * factor * factor, EPS);
    BOOST_CHECK_CLOSE(frameRectAfterScale.getArea(), areaFrameRectBeforeScale * factor * factor, EPS);

  }

  BOOST_AUTO_TEST_CASE(ScaleRectangle_FactorEqualZero_CorrectWorkMethod)
  {
    double width = 7.7;
    double height = 6.5;
    dergunov::point_t coordinatesCenter = {4.3, -6.4};
    dergunov::Rectangle rectangle(width, height, coordinatesCenter);
    dergunov::Rectangle frameRectBeforeScale(rectangle.getFrameRect());

    double factor = 0;
    rectangle.scale(factor);
    dergunov::Rectangle frameRectAfterScale(rectangle.getFrameRect());

    BOOST_CHECK_CLOSE(rectangle.getArea(), 0, EPS);
    BOOST_CHECK_CLOSE(frameRectAfterScale.getArea(), 0, EPS);
  }

  BOOST_AUTO_TEST_CASE(ScaleRectangle_FactorLessZero_CatchError)
  {
    double width = 7.7;
    double height = 6.5;
    dergunov::point_t coordinatesCenter = {4.3, -6.4};
    dergunov::Rectangle rectangle(width, height, coordinatesCenter);

    double factor = -5.6;
    BOOST_CHECK_THROW(rectangle.scale(factor), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(RotateRectangle_DegreeMoreZero_CorrectWork)
  {
    double width = 7.7;
    double height = 6.5;
    double degree = 740;
    dergunov::point_t coordinatesCenter = {4.3, -6.4};
    dergunov::Rectangle rectangle(width, height, coordinatesCenter);

    rectangle.rotate(degree);
    BOOST_CHECK_CLOSE(rectangle.getCenter().x, coordinatesCenter.x, EPS);
    BOOST_CHECK_CLOSE(rectangle.getCenter().y, coordinatesCenter.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(RotateRectangle_DegreeLessZero_CorrectWork)
  {
    double width = 7.7;
    double height = 6.5;
    double degree = -740;
    dergunov::point_t coordinatesCenter = {4.3, -6.4};
    dergunov::Rectangle rectangle(width, height, coordinatesCenter);

    rectangle.rotate(degree);
    BOOST_CHECK_CLOSE(rectangle.getCenter().x, coordinatesCenter.x, EPS);
    BOOST_CHECK_CLOSE(rectangle.getCenter().y, coordinatesCenter.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(GetFrameRectangle_AfterRotate_CorrectWork)
  {
    double width = 700;
    double height = 600;
    double degree = 90;
    dergunov::point_t coordinatesCenter = {4.3, -6.4};
    dergunov::Rectangle rectangle(width, height, coordinatesCenter);

    rectangle.rotate(degree);
    dergunov::rectangle_t frameRect{rectangle.getFrameRect()};

    BOOST_CHECK_CLOSE(frameRect.width, height, EPS);
    BOOST_CHECK_CLOSE(frameRect.height, width, EPS);
    BOOST_CHECK_CLOSE(rectangle.getCenter().x, coordinatesCenter.x, EPS);
    BOOST_CHECK_CLOSE(rectangle.getCenter().y, coordinatesCenter.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(GetFrameRectangle_AfterRotateFortyFiveDegree_CorrectWork)
  {
    double width = 600;
    double height = 600;
    double degree = 45;
    dergunov::point_t coordinatesCenter = {4.3, -6.4};
    dergunov::Rectangle rectangle(width, height, coordinatesCenter);

    rectangle.rotate(degree);
    dergunov::rectangle_t frameRect{rectangle.getFrameRect()};
    double rightSideFrameRectangle = sqrt(width * width + height * height);

    BOOST_CHECK_CLOSE(frameRect.width, rightSideFrameRectangle, EPS);
    BOOST_CHECK_CLOSE(frameRect.height, rightSideFrameRectangle, EPS);
    BOOST_CHECK_CLOSE(rectangle.getCenter().x, coordinatesCenter.x, EPS);
    BOOST_CHECK_CLOSE(rectangle.getCenter().y, coordinatesCenter.y, EPS);
  }
BOOST_AUTO_TEST_SUITE_END()
