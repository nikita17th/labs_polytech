#include <boost/test/unit_test.hpp>
#include <stdexcept>

#include "matrix.hpp"
#include "shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "base-types.hpp"

const double EPS = 10e-7;

BOOST_AUTO_TEST_SUITE(Matrix)

  BOOST_AUTO_TEST_CASE(DefultConsructionMatrix_CorrectObjekts_CorrectWork)
  {
    dergunov::Matrix matrix;
    BOOST_CHECK_EQUAL(matrix.getLines(), 0);
    BOOST_CHECK_EQUAL(matrix.getRows(), 0);
  }

  BOOST_AUTO_TEST_CASE(ConsructionMatrix_CorrectObjekts_CorrectWork)
  {
    double radius = 100.7;
    dergunov::point_t circlePosition{1000.56, -2000.3};
    dergunov::Shape::ShapePtr newCircle =
        std::make_shared<dergunov::Circle>(dergunov::Circle(radius,  circlePosition));
    double width = 200.7;
    double height = 440.65;
    dergunov::point_t rectPosition = {10.3, -0.8};
    dergunov::Shape::ShapePtr newRect =
        std::make_shared<dergunov::Rectangle>(dergunov::Rectangle(width,  height, rectPosition));

    dergunov::Matrix matrix({newCircle, newRect});
    size_t rowsRight = 2;
    size_t linesRight = 1;

    BOOST_CHECK_EQUAL(matrix.getLines(), linesRight);
    BOOST_CHECK_EQUAL(matrix.getRows(), rowsRight);
  }

  BOOST_AUTO_TEST_CASE(ConsructionMatrix_EmptyArgument_CorrectWork)
  {
    dergunov::Matrix matrix({});
    BOOST_CHECK_EQUAL(matrix.getLines(), 0);
    BOOST_CHECK_EQUAL(matrix.getRows(), 0);
  }

  BOOST_AUTO_TEST_CASE(ConsructionMatrix_HeveNullPtrObject_CorrectWork)
  {
    double radius = 7.4;
    dergunov::point_t startPosition = {40.3, 50.8};
    dergunov::Shape::ShapePtr pCircle =
        std::make_shared<dergunov::Circle>(dergunov::Circle(radius, startPosition));

    dergunov::Matrix matrix({nullptr, pCircle});
    BOOST_CHECK_EQUAL(matrix.getLines(), 1);
    BOOST_CHECK_EQUAL(matrix.getRows(), 1);
  }

  BOOST_AUTO_TEST_CASE(CopyConsructionMatrix_MatrixForCopy_CorrectWork)
  {
    double width = 4.5;
    double height = 14.3;
    dergunov::point_t startPosition = {40.3, 50.8};
    dergunov::Shape::ShapePtr pRectangle =
        std::make_shared<dergunov::Rectangle>(dergunov::Rectangle(width, height, startPosition));

    dergunov::Matrix matrixForCopy({pRectangle});
    dergunov::Matrix matrix(matrixForCopy);

    BOOST_CHECK_EQUAL(matrix.getLines(), matrixForCopy.getLines());
    BOOST_CHECK_EQUAL(matrix.getRows(), matrixForCopy.getRows());
  }

  BOOST_AUTO_TEST_CASE(MovingConsructionMatrix_MatrixForMoving_CorrectWork)
  {
    double width = 4.5;
    double height = 14.3;
    dergunov::point_t startPosition = {40.3, 50.8};
    dergunov::Shape::ShapePtr pRectangle =
        std::make_shared<dergunov::Rectangle>(dergunov::Rectangle(width, height, startPosition));

    dergunov::Matrix matrix(dergunov::Matrix({pRectangle}));

    BOOST_CHECK_EQUAL(matrix.getLines(), 1);
    BOOST_CHECK_EQUAL(matrix.getRows(), 1);
  }

  BOOST_AUTO_TEST_CASE(OperatorIndexMatrix_CorrectIndex_CorrectWork)
  {
    double radius = 7.4;
    dergunov::point_t startPosition = {40.3, 50.8};
    dergunov::Shape::ShapePtr pCircle =
        std::make_shared<dergunov::Circle>(dergunov::Circle(radius, startPosition));

    dergunov::Matrix matrix({pCircle});
    BOOST_CHECK_EQUAL(matrix[0].getSize(), 1);
  }

  BOOST_AUTO_TEST_CASE(OperatorIndexMatrix_MoreThanSize_CatchError)
  {
    double radius = 7.4;
    dergunov::point_t startPosition = {40.3, 50.8};
    dergunov::Shape::ShapePtr pCircle =
        std::make_shared<dergunov::Circle>(dergunov::Circle(radius, startPosition));

    dergunov::Matrix matrix({pCircle});
    BOOST_CHECK_THROW(matrix[1], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(OperatorIndexMatrix_IndexEqualZeroAndEmptyMatrix_CatchError)
  {
    dergunov::Matrix matrix;
    BOOST_CHECK_THROW(matrix[0];, std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(OperatorIndexMatrix_LessThanZero_CatchError)
  {
    double radius = 7.4;
    dergunov::point_t startPosition = {40.3, 50.8};
    dergunov::Shape::ShapePtr pCircle =
        std::make_shared<dergunov::Circle>(dergunov::Circle(radius, startPosition));

    dergunov::Matrix matrix({pCircle});
    BOOST_CHECK_THROW(matrix[-1];, std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(OperatorIndexMatrix_MatrixEmpty_CatchError)
  {
    dergunov::Matrix matrix({});
    BOOST_CHECK_THROW(matrix[0];, std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(OperatorIndexMatrixLayer_CorrectIndexes_CorrectWork)
  {
    double radius = 7.4;
    dergunov::point_t startPosition = {40.3, 50.8};
    dergunov::Shape::ShapePtr pCircle =
        std::make_shared<dergunov::Circle>(dergunov::Circle(radius, startPosition));

    dergunov::Matrix matrix({pCircle});
    BOOST_CHECK_CLOSE(matrix[0][0]->getArea(), pCircle->getArea(), EPS);
    BOOST_CHECK_CLOSE(matrix[0][0]->getCenter().x, pCircle->getCenter().x, EPS);
    BOOST_CHECK_CLOSE(matrix[0][0]->getCenter().y, pCircle->getCenter().y, EPS);
  }

  BOOST_AUTO_TEST_CASE(OperatorIndexMatrixLayer_MoreThanSize_CatchError)
  {
    double radius = 7.4;
    dergunov::point_t startPosition = {40.3, 50.8};
    dergunov::Shape::ShapePtr pCircle =
        std::make_shared<dergunov::Circle>(dergunov::Circle(radius, startPosition));

    dergunov::Matrix matrix({pCircle});
    BOOST_CHECK_THROW(matrix[0][1], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(OperatorIndexMatrixLayer_IndexEqualZeroAndEmptyMatrix_CatchError)
  {
    dergunov::Matrix matrix;
    BOOST_CHECK_THROW(matrix[0][0];, std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(OperatorIndexMatrixLayer_LessThanZero_CatchError)
  {
    double radius = 7.4;
    dergunov::point_t startPosition = {40.3, 50.8};
    dergunov::Shape::ShapePtr pCircle =
        std::make_shared<dergunov::Circle>(dergunov::Circle(radius, startPosition));

    dergunov::Matrix matrix({pCircle});
    BOOST_CHECK_THROW(matrix[0][-1];, std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(MatrixAddShape_CorrectObject_CorrectWork)
  {
    double radius = 7.4;
    dergunov::point_t startPosition = {40.3, 50.8};
    dergunov::Shape::ShapePtr pCircle =
        std::make_shared<dergunov::Circle>(dergunov::Circle(radius, startPosition));

    dergunov::Matrix matrix({});
    matrix.addShape(pCircle);
    BOOST_CHECK_EQUAL(matrix.getLines(), 1);
    BOOST_CHECK_EQUAL(matrix.getRows(), 1);
  }

  BOOST_AUTO_TEST_CASE(MatrixAddShape_NullPtr_CorrectWork)
  {
    double radius = 7.4;
    dergunov::point_t startPosition = {40.3, 50.8};
    dergunov::Shape::ShapePtr pCircle =
        std::make_shared<dergunov::Circle>(dergunov::Circle(radius, startPosition));

    dergunov::Matrix matrix({pCircle});
    matrix.addShape(nullptr);
    BOOST_CHECK_EQUAL(matrix.getLines(), 1);
    BOOST_CHECK_EQUAL(matrix.getRows(), 1);
  }
BOOST_AUTO_TEST_SUITE_END()
