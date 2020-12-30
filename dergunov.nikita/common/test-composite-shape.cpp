#include <boost/test/unit_test.hpp>
#include <stdexcept>

#include "shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "base-types.hpp"

const double EPS = 10e-7;

BOOST_AUTO_TEST_SUITE(CompositeShape)

  BOOST_AUTO_TEST_CASE(ConsructionCompositeShapeListInitialization_CorrectObjekt_CorrectWork)
  {
    double originalRadius = 3.5;
    dergunov::point_t coordinatesCenterOfCircle = {3.4, -4.6};
    dergunov::Shape::ShapePtr pCircle =
        std::make_shared<dergunov::Circle>(dergunov::Circle(originalRadius, coordinatesCenterOfCircle));
    double originalWidth = 4.7;
    double originalHeight = 5.6;
    dergunov::point_t coordinatesCenterOfRectangle = {-13.4, 14.6};
    dergunov::Shape::ShapePtr pRect =
        std::make_shared<dergunov::Rectangle> (dergunov::Rectangle(originalWidth, originalHeight, coordinatesCenterOfRectangle));

    dergunov::CompositeShape compositeShape({pCircle, pRect});
    BOOST_CHECK_EQUAL(compositeShape.getCountOfShapes(), 2);
    BOOST_CHECK_EQUAL(compositeShape.getSize(), 4);
  }

  BOOST_AUTO_TEST_CASE(ConsructionCompositeShapeListInitialization_NullPtr_CatchError)
  {
    double originalWidth = 4.7;
    double originalHeight = 5.6;
    dergunov::point_t coordinatesCenterOfRectangle = {-13.4, 14.6};
    dergunov::Shape::ShapePtr pRect =
        std::make_shared<dergunov::Rectangle> (dergunov::Rectangle(originalWidth, originalHeight, coordinatesCenterOfRectangle));
    BOOST_CHECK_THROW(dergunov::CompositeShape compositeShape({pRect, nullptr}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ConsructionCompositeShapeListInitialization_EmptyList_CatchError)
  {

    BOOST_CHECK_THROW(dergunov::CompositeShape compositeShape({}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ConsructionCopyCompositeShape_CorrectObjekt_CorrectWork)
  {
    double originalRadius = 3.5;
    dergunov::point_t coordinatesCenterOfCircle = {3.4, -4.6};
    dergunov::Circle circle(originalRadius, coordinatesCenterOfCircle);
    dergunov::Shape::ShapePtr pShape = std::make_shared<dergunov::Circle>(circle);
    dergunov::CompositeShape compositeShapeForCopy({pShape});

    dergunov::CompositeShape compositeShape(compositeShapeForCopy);
    BOOST_CHECK_EQUAL(compositeShape.getCountOfShapes(), compositeShapeForCopy.getCountOfShapes());
    BOOST_CHECK_EQUAL(compositeShape.getSize(), compositeShapeForCopy.getSize());
    BOOST_CHECK_CLOSE(compositeShape.getCenter().x, compositeShapeForCopy.getCenter().x, EPS);
    BOOST_CHECK_CLOSE(compositeShape.getCenter().y, compositeShapeForCopy.getCenter().y, EPS);
  }

  BOOST_AUTO_TEST_CASE(ConsructionMovingCompositeShape_NewObjekt_CorrectWork)
  {
    double originalRadius = 3.5;
    dergunov::point_t coordinatesCenterOfCircle = {3.4, -4.6};
    dergunov::Shape::ShapePtr pShape =
        std::make_shared<dergunov::Circle>(dergunov::Circle(originalRadius, coordinatesCenterOfCircle));
    dergunov::CompositeShape compositeShapeForMove({pShape});
    size_t correctCountOfShapes = compositeShapeForMove.getCountOfShapes();
    size_t correctSize = compositeShapeForMove.getSize();
    dergunov::point_t correctCenter = compositeShapeForMove.getCenter();

    dergunov::CompositeShape compositeShape(std::move(compositeShapeForMove));

    BOOST_CHECK_EQUAL(compositeShape.getCountOfShapes(), correctCountOfShapes);
    BOOST_CHECK_EQUAL(compositeShape.getSize(), correctSize);
    BOOST_CHECK_CLOSE(compositeShape.getCenter().x, correctCenter.x, EPS);
    BOOST_CHECK_CLOSE(compositeShape.getCenter().y, correctCenter.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(OperatorIndexCompositeShape_CorrectIndex_CorrectWork)
  {
    double originalRadius = 3.5;
    dergunov::point_t coordinatesCenterOfCircle = {3.4, -4.6};
    dergunov::Shape::ShapePtr pShapeBeforeAdd  =
        std::make_shared<dergunov::Circle>(dergunov::Circle(originalRadius, coordinatesCenterOfCircle));
    dergunov::CompositeShape compositeShape({pShapeBeforeAdd});

    dergunov::Shape::ShapePtr pShapeAfterAdd (compositeShape[0]);

    BOOST_CHECK_CLOSE(pShapeAfterAdd->getArea(), pShapeBeforeAdd->getArea(), EPS);
    BOOST_CHECK_CLOSE(pShapeAfterAdd->getCenter().x, pShapeBeforeAdd->getCenter().x, EPS);
    BOOST_CHECK_CLOSE(pShapeAfterAdd->getCenter().y, pShapeBeforeAdd->getCenter().y, EPS);
  }

  BOOST_AUTO_TEST_CASE(OperatorIndexCompositeShape_LessThanZeroIndex_CatchError)
  {
    double originalRadius = 3.5;
    dergunov::point_t coordinatesCenterOfCircle = {3.4, -4.6};
    dergunov::Shape::ShapePtr pShape =
        std::make_shared<dergunov::Circle>(dergunov::Circle(originalRadius, coordinatesCenterOfCircle));
    dergunov::CompositeShape compositeShape({pShape});

    BOOST_CHECK_THROW(compositeShape[-10], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(OperatorIndexCompositeShape_MoreThanCountOfShapesIndex_CatchError)
  {
    double originalRadius = 3.5;
    dergunov::point_t coordinatesCenterOfCircle = {3.4, -4.6};
    dergunov::Shape::ShapePtr pShape =
        std::make_shared<dergunov::Circle>(dergunov::Circle(originalRadius, coordinatesCenterOfCircle));
    dergunov::CompositeShape compositeShape({pShape});

    BOOST_CHECK_THROW(compositeShape[1], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(PushBackShapeCompositeShapw_CoorectShapeAdd_CorrerctWork)
  {
    size_t size = 2;

    double originalRadius = 3.5;
    dergunov::point_t coordinatesCenterOfCircle = {3.4, -4.6};
    dergunov::Shape::ShapePtr pCircle =
        std::make_shared<dergunov::Circle>(dergunov::Circle(originalRadius, coordinatesCenterOfCircle));
    double areaCircle = pCircle->getArea();
    dergunov::CompositeShape compositeShape({pCircle});

    double originalWidth = 4.7;
    double originalHeight = 5.6;
    dergunov::point_t coordinatesCenterOfRectangle = {-13.4, 14.6};
    dergunov::Shape::ShapePtr pRect =
        std::make_shared<dergunov::Rectangle> (dergunov::Rectangle(originalWidth, originalHeight, coordinatesCenterOfRectangle));
    double areaRectangle = pRect->getArea();
    compositeShape.pushBackShape(pRect);

    BOOST_CHECK_EQUAL(compositeShape.getCountOfShapes(), size);

    BOOST_CHECK_CLOSE(compositeShape[0]->getArea(), areaCircle, EPS);
    BOOST_CHECK_CLOSE(compositeShape[0]->getCenter().x, coordinatesCenterOfCircle.x, EPS);
    BOOST_CHECK_CLOSE(compositeShape[0]->getCenter().y, coordinatesCenterOfCircle.y, EPS);

    BOOST_CHECK_CLOSE(compositeShape[1]->getArea(), areaRectangle, EPS);
    BOOST_CHECK_CLOSE(compositeShape[1]->getCenter().x, coordinatesCenterOfRectangle.x, EPS);
    BOOST_CHECK_CLOSE(compositeShape[1]->getCenter().y, coordinatesCenterOfRectangle.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(PushBackShapeCompositeShapw_NullptrAdd_CatchError)
  {
    double originalWidth = 4.7;
    double originalHeight = 5.6;
    dergunov::point_t coordinatesCenterOfRectangle = {-13.4, 14.6};
    dergunov::Shape::ShapePtr pRect =
        std::make_shared<dergunov::Rectangle> (dergunov::Rectangle(originalWidth, originalHeight, coordinatesCenterOfRectangle));
    dergunov::CompositeShape compositeShape({pRect});
    dergunov::Shape::ShapePtr noneShape(nullptr);
    BOOST_CHECK_THROW(compositeShape.pushBackShape(noneShape), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(DeleteShapeCompositrShape_CorrectIndex_CorrectWork)
  {
    double originalWidth = 4.7;
    double originalHeight = 5.6;
    dergunov::point_t coordinatesCenterOfRectangle = {-13.4, 14.6};
    dergunov::Shape::ShapePtr pRect =
        std::make_shared<dergunov::Rectangle> (dergunov::Rectangle(originalWidth, originalHeight, coordinatesCenterOfRectangle));
    dergunov::CompositeShape compositeShape({pRect});

    double originalRadius = 3.5;
    dergunov::point_t coordinatesCenterOfCircle = {3.4, -4.6};
    dergunov::Shape::ShapePtr pCircle =
        std::make_shared<dergunov::Circle>(dergunov::Circle(originalRadius, coordinatesCenterOfCircle));
    compositeShape.pushBackShape(pCircle);

    compositeShape.deleteShape(0);

    BOOST_CHECK_EQUAL(compositeShape.getCountOfShapes(), 1);
  }

  BOOST_AUTO_TEST_CASE(DeleteShapeCompositrShape_CompositeShapeIsEmpty_CatchError)
  {
    size_t exceptionIndex = 0;

    double originalWidth = 4.7;
    double originalHeight = 5.6;
    dergunov::point_t coordinatesCenterOfRectangle = {-13.4, 14.6};
    dergunov::Shape::ShapePtr pRect =
        std::make_shared<dergunov::Rectangle> (dergunov::Rectangle(originalWidth, originalHeight, coordinatesCenterOfRectangle));
    dergunov::CompositeShape compositeShape({pRect});

    BOOST_CHECK_THROW(compositeShape.deleteShape(exceptionIndex), std::logic_error);
  }

  BOOST_AUTO_TEST_CASE(DeleteShapeCompositrShape_IndexMoreThanCountOfShapes_CatchError)
  {
    size_t exceptionIndex = 2;

    double originalWidth = 4.7;
    double originalHeight = 5.6;
    dergunov::point_t coordinatesCenterOfRectangle = {-13.4, 14.6};
    dergunov::Shape::ShapePtr pRect =
        std::make_shared<dergunov::Rectangle> (dergunov::Rectangle(originalWidth, originalHeight, coordinatesCenterOfRectangle));
    dergunov::CompositeShape compositeShape({pRect});

    double originalRadius = 3.5;
    dergunov::point_t coordinatesCenterOfCircle = {3.4, -4.6};
    dergunov::Shape::ShapePtr pCircle =
        std::make_shared<dergunov::Circle>(dergunov::Circle(originalRadius, coordinatesCenterOfCircle));
    compositeShape.pushBackShape(pCircle);

    BOOST_CHECK_THROW(compositeShape.deleteShape(exceptionIndex), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(GetFrameRectCompositeShape_ArrayHasShapes_CorrectWork)
  {
    double originalRadius = 1;
    dergunov::point_t coordinatesCenterOfCircle = {1, 1};
    dergunov::Shape::ShapePtr pCircle =
        std::make_shared<dergunov::Circle>(dergunov::Circle(originalRadius, coordinatesCenterOfCircle));
    dergunov::CompositeShape compositeShape({pCircle});

    double originalWidth = 2;
    double originalHeight = 2;
    dergunov::point_t coordinatesCenterOfRectangle = {-1, -1};
    dergunov::Shape::ShapePtr pRect =
        std::make_shared<dergunov::Rectangle>(dergunov::Rectangle(originalWidth, originalHeight, coordinatesCenterOfRectangle));
    compositeShape.pushBackShape(pRect);

    dergunov::Rectangle methodFrameRect(compositeShape.getFrameRect());
    dergunov::Rectangle originalFrameRect(4, 4, {0, 0});

    BOOST_CHECK_CLOSE(methodFrameRect.getCenter().x, originalFrameRect.getCenter().x, EPS);
    BOOST_CHECK_CLOSE(methodFrameRect.getCenter().y, originalFrameRect.getCenter().y, EPS);
    BOOST_CHECK_CLOSE(methodFrameRect.getWidth(), originalFrameRect.getWidth(), EPS);
    BOOST_CHECK_CLOSE(methodFrameRect.getHeight(), originalFrameRect.getHeight(), EPS);
  }

  BOOST_AUTO_TEST_CASE(MoveCompositeShape_MoveInPoint_CorectWorkMethod)
  {
    double originalRadius = 3.5;
    dergunov::point_t coordinatesCenterOfCircle = {3.4, -4.6};
    dergunov::Shape::ShapePtr pShape =
        std::make_shared<dergunov::Circle>(dergunov::Circle(originalRadius, coordinatesCenterOfCircle));
    dergunov::Rectangle frameCircleRectBeforeAdd(pShape->getFrameRect());
    dergunov::CompositeShape compositeShape({pShape});
    double areaBeforeMoving = compositeShape.getArea();

    dergunov::point_t newCoordinatesCenter = {4.5, 10.3};
    compositeShape.move(newCoordinatesCenter);

    BOOST_CHECK_CLOSE(compositeShape.getArea(), areaBeforeMoving, EPS);
    BOOST_CHECK_CLOSE(compositeShape.getCenter().x, newCoordinatesCenter.x, EPS);
    BOOST_CHECK_CLOSE(compositeShape.getCenter().y, newCoordinatesCenter.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(MoveCompositeShape_XandYoffset_CoreectWorkMethod)
  {
    double originalRadius = 3.5;
    dergunov::point_t coordinatesCenter = {3.4, -4.6};
    dergunov::Shape::ShapePtr pShape =
        std::make_shared<dergunov::Circle>(dergunov::Circle(originalRadius, coordinatesCenter));
    dergunov::Rectangle frameCircleRectBeforeAdd(pShape->getFrameRect());
    dergunov::CompositeShape compositeShape({pShape});
    double areaBeforeMoving = compositeShape.getArea();

    double dx = -6.2;
    double dy = 5.7;
    compositeShape.move(dx, dy);

    BOOST_CHECK_CLOSE(compositeShape.getArea(), areaBeforeMoving, EPS);
    BOOST_CHECK_CLOSE(compositeShape.getCenter().x, coordinatesCenter.x + dx, EPS);
    BOOST_CHECK_CLOSE(compositeShape.getCenter().y, coordinatesCenter.y + dy, EPS);
  }

  BOOST_AUTO_TEST_CASE(ScaleCompositeShape_FactorMoreOne_CorrectWork)
  {
    double originalRadius = 1.5;
    dergunov::point_t coordinatesCenterOfCircle = {50.7, 60.8};
    dergunov::Shape::ShapePtr pCircle =
        std::make_shared<dergunov::Circle>(dergunov::Circle(originalRadius, coordinatesCenterOfCircle));
    dergunov::Rectangle frameCircleRectBeforeAdd(pCircle->getFrameRect());
    dergunov::CompositeShape compositeShape({pCircle});

    double originalWidth = 4.2;
    double originalHeight = 2.3;
    dergunov::point_t coordinatesCenterOfRectangle = {-25.6, -57.8};
    dergunov::Shape::ShapePtr pRect =
        std::make_shared<dergunov::Rectangle>(dergunov::Rectangle(originalWidth, originalHeight, coordinatesCenterOfRectangle));
    compositeShape.pushBackShape(pRect);
    dergunov::point_t centerOfCompositeShapeBeforeScale = compositeShape.getCenter();

    double areaCompositeShapeBeforeScale = compositeShape.getArea();
    double factor = 5.5;
    compositeShape.scale(factor);
    dergunov::point_t centerOfCompositeShapeAfterScale = compositeShape.getCenter();

    BOOST_CHECK_CLOSE(compositeShape.getArea(), areaCompositeShapeBeforeScale * factor * factor, EPS);
    BOOST_CHECK_CLOSE(centerOfCompositeShapeAfterScale.x, centerOfCompositeShapeBeforeScale.x, EPS);
    BOOST_CHECK_CLOSE(centerOfCompositeShapeAfterScale.y, centerOfCompositeShapeBeforeScale.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(ScaleCompositeShape_FacroEqualOne_CorrectWork)
  {
    double originalWidth = 4.7;
    double originalHeight = 5.6;

    dergunov::point_t coordinatesCenterOfRectangle = {-13.4, 14.6};
    dergunov::Shape::ShapePtr pRect =
        std::make_shared<dergunov::Rectangle>(dergunov::Rectangle(originalWidth, originalHeight, coordinatesCenterOfRectangle));
    dergunov::CompositeShape compositeShape({pRect});
    dergunov::point_t centerOfCompositeShapeBeforeScale = compositeShape.getCenter();

    double factor = 1;
    compositeShape.scale(factor);
    dergunov::point_t centerOfCompositeShapeAfterScale = compositeShape.getCenter();

    BOOST_CHECK_CLOSE(compositeShape.getArea(), pRect->getArea(), EPS);
    BOOST_CHECK_CLOSE(centerOfCompositeShapeAfterScale.x, centerOfCompositeShapeBeforeScale.x, EPS);
    BOOST_CHECK_CLOSE(centerOfCompositeShapeAfterScale.y, centerOfCompositeShapeBeforeScale.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(ScaleCompositeShape_FacroEqualZero_CorrectWork)
  {
    double originalWidth = 4.7;
    double originalHeight = 5.6;
    dergunov::point_t coordinatesCenterOfRectangle = {-13.4, 14.6};
    dergunov::Shape::ShapePtr pRect =
        std::make_shared<dergunov::Rectangle>(dergunov::Rectangle(originalWidth, originalHeight, coordinatesCenterOfRectangle));
    dergunov::CompositeShape compositeShape({pRect});
    dergunov::point_t centerOfCompositeShapeBeforeScale = compositeShape.getCenter();

    double factor = 0;
    compositeShape.scale(factor);
    dergunov::point_t centerOfCompositeShapeAfterScale = compositeShape.getCenter();

    BOOST_CHECK_CLOSE(compositeShape.getArea(), 0, EPS);
    BOOST_CHECK_CLOSE(centerOfCompositeShapeAfterScale.x, centerOfCompositeShapeBeforeScale.x, EPS);
    BOOST_CHECK_CLOSE(centerOfCompositeShapeAfterScale.y, centerOfCompositeShapeBeforeScale.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(ScaleCompositeShape_FactorLessZero_CatchError)
  {
    double originalWidth = 4.7;
    double originalHeight = 5.6;
    dergunov::point_t coordinatesCenterOfRectangle = {-13.4, 14.6};
    dergunov::Shape::ShapePtr pRect =
        std::make_shared<dergunov::Rectangle>(dergunov::Rectangle(originalWidth, originalHeight, coordinatesCenterOfRectangle));
    dergunov::CompositeShape compositeShape({pRect});

    double factor = -1;
    BOOST_CHECK_THROW(compositeShape.scale(factor), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(RotateCompositeShape_DegreeMoreZero_CorrectWork)
  {
    double originalRadius = 1.5;
    dergunov::point_t coordinatesCenterOfCircle = {50.7, 60.8};
    dergunov::Shape::ShapePtr pCircle =
        std::make_shared<dergunov::Circle>(dergunov::Circle(originalRadius, coordinatesCenterOfCircle));
    dergunov::Rectangle frameCircleRectBeforeAdd(pCircle->getFrameRect());
    dergunov::CompositeShape compositeShape({pCircle});

    double originalWidth = 4.2;
    double originalHeight = 2.3;
    dergunov::point_t coordinatesCenterOfRectangle = {-25.6, -57.8};
    dergunov::Shape::ShapePtr pRect =
        std::make_shared<dergunov::Rectangle>(dergunov::Rectangle(originalWidth, originalHeight, coordinatesCenterOfRectangle));
    compositeShape.pushBackShape(pRect);

    double degree = 450;
    dergunov::rectangle_t frameRectBeforeRotate{compositeShape.getFrameRect()};
    compositeShape.rotate(degree);
    dergunov::rectangle_t frameRectAfterRotate{compositeShape.getFrameRect()};

    BOOST_CHECK_CLOSE(frameRectBeforeRotate.width, frameRectAfterRotate.height, EPS);
    BOOST_CHECK_CLOSE(frameRectBeforeRotate.height, frameRectAfterRotate.width, EPS);
  }

  BOOST_AUTO_TEST_CASE(RotateCompositeShape_DegreeEqualZero_CorrectWork)
  {
    double originalRadius = 1.5;
    dergunov::point_t coordinatesCenterOfCircle = {50.7, 60.8};
    dergunov::Shape::ShapePtr pCircle =
        std::make_shared<dergunov::Circle>(dergunov::Circle(originalRadius, coordinatesCenterOfCircle));
    dergunov::Rectangle frameCircleRectBeforeAdd(pCircle->getFrameRect());
    dergunov::CompositeShape compositeShape({pCircle});

    double originalWidth = 4.2;
    double originalHeight = 2.3;
    dergunov::point_t coordinatesCenterOfRectangle = {-25.6, -57.8};
    dergunov::Shape::ShapePtr pRect =
        std::make_shared<dergunov::Rectangle>(dergunov::Rectangle(originalWidth, originalHeight, coordinatesCenterOfRectangle));
    compositeShape.pushBackShape(pRect);

    double degree = 0;
    dergunov::rectangle_t frameRectBeforeRotate{compositeShape.getFrameRect()};
    compositeShape.rotate(degree);
    dergunov::rectangle_t frameRectAfterRotate{compositeShape.getFrameRect()};

    BOOST_CHECK_CLOSE(frameRectBeforeRotate.width, frameRectAfterRotate.width, EPS);
    BOOST_CHECK_CLOSE(frameRectBeforeRotate.height, frameRectAfterRotate.height, EPS);
  }
  BOOST_AUTO_TEST_CASE(RotateCompositeShape_DegreeLessZero_CorrectWork)
  {
    double originalRadius = 1.5;
    dergunov::point_t coordinatesCenterOfCircle = {50.7, 60.8};
    dergunov::Shape::ShapePtr pCircle =
        std::make_shared<dergunov::Circle>(dergunov::Circle(originalRadius, coordinatesCenterOfCircle));
    dergunov::Rectangle frameCircleRectBeforeAdd(pCircle->getFrameRect());
    dergunov::CompositeShape compositeShape({pCircle});

    double originalWidth = 4.2;
    double originalHeight = 2.3;
    dergunov::point_t coordinatesCenterOfRectangle = {-25.6, -57.8};
    dergunov::Shape::ShapePtr pRect =
        std::make_shared<dergunov::Rectangle>(dergunov::Rectangle(originalWidth, originalHeight, coordinatesCenterOfRectangle));
    compositeShape.pushBackShape(pRect);

    double degree = -450;
    dergunov::rectangle_t frameRectBeforeRotate{compositeShape.getFrameRect()};
    compositeShape.rotate(degree);
    dergunov::rectangle_t frameRectAfterRotate{compositeShape.getFrameRect()};

    BOOST_CHECK_CLOSE(frameRectBeforeRotate.width, frameRectAfterRotate.height, EPS);
    BOOST_CHECK_CLOSE(frameRectBeforeRotate.height, frameRectAfterRotate.width, EPS);
  }

BOOST_AUTO_TEST_SUITE_END()
