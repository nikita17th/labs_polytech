#include <boost/test/unit_test.hpp>
#include <stdexcept>

#include "shape.hpp"
#include "base-types.hpp"
#include "polygon.hpp"

const double EPS = 10e-7;

BOOST_AUTO_TEST_SUITE(Polygon)

  BOOST_AUTO_TEST_CASE(ConstructorPolygon_CorrectData_CorrectWork)
  {
    dergunov::point_t firstPoint {-10, -10};
    dergunov::point_t secondPoint {-10, 0};
    dergunov::point_t thirdPoint {0, 0};
    dergunov::point_t forthPoint {0, -10};

    dergunov::Polygon polygon {firstPoint, secondPoint, thirdPoint, forthPoint};

    dergunov::rectangle_t frameRect{polygon.getFrameRect()};

    BOOST_CHECK_CLOSE(polygon.getCenter().x, -5, EPS);
    BOOST_CHECK_CLOSE(polygon.getCenter().y, -5, EPS);
    BOOST_CHECK_CLOSE(polygon.getArea(), 100, EPS);
    BOOST_CHECK_CLOSE(frameRect.pos.x, -5, EPS);
    BOOST_CHECK_CLOSE(frameRect.pos.y, -5, EPS);
    BOOST_CHECK_CLOSE(frameRect.width, 10, EPS);
    BOOST_CHECK_CLOSE(frameRect.height, 10, EPS);
  }

  BOOST_AUTO_TEST_CASE(ConstructorPolygon_LessThreeCorrectPoint_CatchError)
  {
    dergunov::point_t firstPoint {-10, -10};
    dergunov::point_t secondPoint {-10, 0};

    BOOST_CHECK_THROW(dergunov::Polygon polygon({firstPoint, secondPoint}),
        std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ConstructorPolygon_EmptyParameters_CatchError)
  {
    BOOST_CHECK_THROW(dergunov::Polygon polygon {}, std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ConstructorPolygon_ZeroArea_CatchError)
  {
    dergunov::point_t firstPoint {0, 0};
    dergunov::point_t secondPoint {2.6, 3.6};
    dergunov::point_t thirdPoint {5.2, 7.2};
    BOOST_CHECK_THROW(dergunov::Polygon polygon({firstPoint, secondPoint, thirdPoint}),
        std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ConstructorPolygon_NotConvexShape_CorrecrWork)
  {
    dergunov::point_t firstPoint {0, 0};
    dergunov::point_t secondPoint {10, 0};
    dergunov::point_t thirdPoint {0, 10};
    dergunov::point_t forthPoint {0, 10};
    dergunov::Polygon polygon {firstPoint, secondPoint, thirdPoint, forthPoint};
    
    BOOST_CHECK_CLOSE(polygon.getCenter().x, 2.5, EPS);
    BOOST_CHECK_CLOSE(polygon.getCenter().y, 5, EPS);
  }

  BOOST_AUTO_TEST_CASE(MovePolygon_InPoint_CorrectWork)
  {
    dergunov::point_t firstPoint {-10, -10};
    dergunov::point_t secondPoint {-10, 0};
    dergunov::point_t thirdPoint {0, 0};
    dergunov::point_t forthPoint {0, -10};
    dergunov::Polygon polygon {firstPoint, secondPoint, thirdPoint, forthPoint};

    double areaBeforeMove = polygon.getArea();
    dergunov::rectangle_t frameRectBeforeMove {polygon.getFrameRect()};
    dergunov::point_t newCenter {5.5, 5.5};
    polygon.move(newCenter);
    dergunov::rectangle_t frameRectAfterMove {polygon.getFrameRect()};

    BOOST_CHECK_CLOSE(polygon.getCenter().x, newCenter.x, EPS);
    BOOST_CHECK_CLOSE(polygon.getCenter().y, newCenter.y, EPS);
    BOOST_CHECK_CLOSE(polygon.getArea(), areaBeforeMove, EPS);
    BOOST_CHECK_CLOSE(frameRectAfterMove.width, frameRectBeforeMove.width, EPS);
    BOOST_CHECK_CLOSE(frameRectAfterMove.height, frameRectBeforeMove.height, EPS);
  }

  BOOST_AUTO_TEST_CASE(MovePolygon_XandYoffset_CorrectWork)
  {
    dergunov::point_t firstPoint {-10, -10};
    dergunov::point_t secondPoint {-10, 0};
    dergunov::point_t thirdPoint {0, 0};
    dergunov::point_t forthPoint {0, -10};
    dergunov::Polygon polygon {firstPoint, secondPoint, thirdPoint, forthPoint};

    double areaBeforeMove = polygon.getArea();
    dergunov::rectangle_t frameRectBeforeMove {polygon.getFrameRect()};
    dergunov::point_t newCenter {5.5, 5.5};
    polygon.move(newCenter);
    dergunov::rectangle_t frameRectAfterMove {polygon.getFrameRect()};

    BOOST_CHECK_CLOSE(polygon.getCenter().x, newCenter.x, EPS);
    BOOST_CHECK_CLOSE(polygon.getCenter().y, newCenter.y, EPS);
    BOOST_CHECK_CLOSE(polygon.getArea(), areaBeforeMove, EPS);
    BOOST_CHECK_CLOSE(frameRectAfterMove.width, frameRectBeforeMove.width, EPS);
    BOOST_CHECK_CLOSE(frameRectAfterMove.height, frameRectBeforeMove.height, EPS);
  }

  BOOST_AUTO_TEST_CASE(ScalePolygon_FactorMoreZero_CorrectWork)
  {
    dergunov::point_t firstPoint {-10, -10};
    dergunov::point_t secondPoint {-10, 0};
    dergunov::point_t thirdPoint {0, 0};
    dergunov::point_t forthPoint {0, -10};
    dergunov::Polygon polygon({firstPoint, secondPoint, thirdPoint, forthPoint});

    double areaBeforeMove = polygon.getArea();
    double scaleFactor = 5.4;
    dergunov::rectangle_t frameRectBeforeMove {polygon.getFrameRect()};
    dergunov::point_t centerBeforeScale {polygon.getCenter()};
    polygon.scale(scaleFactor);
    dergunov::rectangle_t frameRectAfterMove {polygon.getFrameRect()};

    BOOST_CHECK_CLOSE(polygon.getCenter().x, centerBeforeScale.x, EPS);
    BOOST_CHECK_CLOSE(polygon.getCenter().y, centerBeforeScale.y, EPS);
    BOOST_CHECK_CLOSE(polygon.getArea(), areaBeforeMove * scaleFactor * scaleFactor, EPS);
    BOOST_CHECK_CLOSE(frameRectAfterMove.width, frameRectBeforeMove.width * scaleFactor, EPS);
    BOOST_CHECK_CLOSE(frameRectAfterMove.height, frameRectBeforeMove.height * scaleFactor, EPS);
  }

  BOOST_AUTO_TEST_CASE(ScalePolygon_FactorEqualZero_CatchError)
  {
    dergunov::point_t firstPoint {-10, -10};
    dergunov::point_t secondPoint {-10, 0};
    dergunov::point_t thirdPoint {0, 0};
    dergunov::Polygon polygon {firstPoint, secondPoint, thirdPoint};

    BOOST_CHECK_THROW(polygon.scale(0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ScalePolygon_FactorLessZero_CatchError)
  {
    dergunov::point_t firstPoint {-10, -10};
    dergunov::point_t secondPoint {-10, 0};
    dergunov::point_t thirdPoint {0, 0};
    dergunov::Polygon polygon {firstPoint, secondPoint, thirdPoint};

    BOOST_CHECK_THROW(polygon.scale(-7.6), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(RotatePolygon_DegreeMoreZero_CorrectWork)
  {
    dergunov::point_t firstPoint {-10, -5};
    dergunov::point_t secondPoint {-10, 0};
    dergunov::point_t thirdPoint {0, 0};
    dergunov::point_t forthPoint {0, -5};
    dergunov::Polygon polygon {firstPoint, secondPoint, thirdPoint, forthPoint};

    double areaBeforeMove = polygon.getArea();
    dergunov::rectangle_t frameRectBeforeMove {polygon.getFrameRect()};
    dergunov::point_t centerBeforeScale {polygon.getCenter()};
    polygon.rotate(450);
    dergunov::rectangle_t frameRectAfterMove {polygon.getFrameRect()};

    BOOST_CHECK_CLOSE(polygon.getCenter().x, centerBeforeScale.x, EPS);
    BOOST_CHECK_CLOSE(polygon.getCenter().y, centerBeforeScale.y, EPS);
    BOOST_CHECK_CLOSE(polygon.getArea(), areaBeforeMove, EPS);
    BOOST_CHECK_CLOSE(frameRectAfterMove.width, frameRectBeforeMove.height, EPS);
    BOOST_CHECK_CLOSE(frameRectAfterMove.height, frameRectBeforeMove.width, EPS);
  }

  BOOST_AUTO_TEST_CASE(RotatePolygon_DegreeEqualZero_CorrectWork)
  {
    dergunov::point_t firstPoint {-10, -5};
    dergunov::point_t secondPoint {-10, 0};
    dergunov::point_t thirdPoint {0, 0};
    dergunov::point_t forthPoint {0, -5};
    dergunov::Polygon polygon {firstPoint, secondPoint, thirdPoint, forthPoint};

    double areaBeforeMove = polygon.getArea();
    dergunov::rectangle_t frameRectBeforeMove {polygon.getFrameRect()};
    dergunov::point_t centerBeforeScale {polygon.getCenter()};
    polygon.rotate(0);
    dergunov::rectangle_t frameRectAfterMove {polygon.getFrameRect()};

    BOOST_CHECK_CLOSE(polygon.getCenter().x, centerBeforeScale.x, EPS);
    BOOST_CHECK_CLOSE(polygon.getCenter().y, centerBeforeScale.y, EPS);
    BOOST_CHECK_CLOSE(polygon.getArea(), areaBeforeMove, EPS);
    BOOST_CHECK_CLOSE(frameRectAfterMove.width, frameRectBeforeMove.width, EPS);
    BOOST_CHECK_CLOSE(frameRectAfterMove.height, frameRectBeforeMove.height, EPS);
  }
  
  BOOST_AUTO_TEST_CASE(RotatePolygon_DegreeLessZero_CorrectWork)
  {
    dergunov::point_t firstPoint {-10, -5};
    dergunov::point_t secondPoint {-10, 0};
    dergunov::point_t thirdPoint {0, 0};
    dergunov::point_t forthPoint {0, -5};
    dergunov::Polygon polygon {firstPoint, secondPoint, thirdPoint, forthPoint};

    double areaBeforeMove = polygon.getArea();
    dergunov::rectangle_t frameRectBeforeMove {polygon.getFrameRect()};
    dergunov::point_t centerBeforeScale {polygon.getCenter()};
    polygon.rotate(-450);
    dergunov::rectangle_t frameRectAfterMove {polygon.getFrameRect()};

    BOOST_CHECK_CLOSE(polygon.getCenter().x, centerBeforeScale.x, EPS);
    BOOST_CHECK_CLOSE(polygon.getCenter().y, centerBeforeScale.y, EPS);
    BOOST_CHECK_CLOSE(polygon.getArea(), areaBeforeMove, EPS);
    BOOST_CHECK_CLOSE(frameRectAfterMove.width, frameRectBeforeMove.height, EPS);
    BOOST_CHECK_CLOSE(frameRectAfterMove.height, frameRectBeforeMove.width, EPS);
  }
  
BOOST_AUTO_TEST_SUITE_END()
