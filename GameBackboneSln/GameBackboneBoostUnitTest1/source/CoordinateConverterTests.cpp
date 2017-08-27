#include "stdafx.h"

#include <Navigation/CoordinateConverter.h>
#include <Util/Point.h>

#include <SFML/Graphics.hpp>

using namespace GB;

// Contains all of the tests for CoordinateConverter
BOOST_AUTO_TEST_SUITE(CoordinateConverter_Tests)

BOOST_AUTO_TEST_SUITE(CoordinateConverter_Offsets)

// Tests the functions with a negative offset
BOOST_AUTO_TEST_CASE(CoordinateConverter_NegativeOffset) {
	CoordinateConverter TestConverter(50, Point2D<float>{-1500, -1500});

	Point2D<int> ngOrigin = {0, 0};
	sf::Vector2f sfOrigin = TestConverter.convertCoordToWindow(ngOrigin);
	// Ensure that the sf coordinate is correct
	BOOST_CHECK_CLOSE(sfOrigin.x, -1475.f, 0.001);
	BOOST_CHECK_CLOSE(sfOrigin.y, -1475.f, 0.001);
	Point2D<int> originalOrigin = TestConverter.convertCoordToNavGrid(sfOrigin);
	// Ensure that the original coordinate is the same as the navigation grid coordinate
	BOOST_CHECK(originalOrigin == ngOrigin);

	Point2D<int> ngPoint = {43, 12};
	sf::Vector2f sfPoint = TestConverter.convertCoordToWindow(ngPoint);
	// Ensure that the sf coordinate is correct
	BOOST_CHECK_CLOSE(sfPoint.x, 675.f, 0.001);
	BOOST_CHECK_CLOSE(sfPoint.y, -875.f, 0.001);
	Point2D<int> originalPoint = TestConverter.convertCoordToNavGrid(sfPoint);
	// Ensure that the original coordinate is the same as the navigation grid coordinate
	BOOST_CHECK(originalPoint == ngPoint);
}

// Tests the functions with a positive offset
BOOST_AUTO_TEST_CASE(CoordinateConverter_PositiveOffset) {
	CoordinateConverter TestConverter(50, Point2D<float>{1500, 1500});

	Point2D<int> ngOrigin = {0, 0};
	sf::Vector2f sfOrigin = TestConverter.convertCoordToWindow(ngOrigin);
	// Ensure that the sf coordinate is correct
	BOOST_CHECK_CLOSE(sfOrigin.x, 1525.f, 0.001);
	BOOST_CHECK_CLOSE(sfOrigin.y, 1525.f, 0.001);
	Point2D<int> originalOrigin = TestConverter.convertCoordToNavGrid(sfOrigin);
	BOOST_CHECK(originalOrigin == ngOrigin);

	Point2D<int> ngPoint = {43, 12};
	sf::Vector2f sfPoint = TestConverter.convertCoordToWindow(ngPoint);
	// Ensure that the sf coordinate is correct
	BOOST_CHECK_CLOSE(sfPoint.x, 3675.f, 0.001);
	BOOST_CHECK_CLOSE(sfPoint.y, 2125.f, 0.001);
	Point2D<int> originalPoint = TestConverter.convertCoordToNavGrid(sfPoint);
	// Ensure that the original coordinate is the same as the navigation grid coordinate
	BOOST_CHECK(originalPoint == ngPoint);
}

// Tests the functions with no offset
BOOST_AUTO_TEST_CASE(CoordinateConverter_ZeroOffset) {
	CoordinateConverter TestConverter(50, Point2D<float>{0, 0});

	Point2D<int> ngOrigin = {0, 0};
	sf::Vector2f sfOrigin = TestConverter.convertCoordToWindow(ngOrigin);
	// Ensure that the sf coordinate is correct
	BOOST_CHECK_CLOSE(sfOrigin.x, 25.f, 0.001);
	BOOST_CHECK_CLOSE(sfOrigin.y, 25.f, 0.001);
	Point2D<int> originalOrigin = TestConverter.convertCoordToNavGrid(sfOrigin);
	// Ensure that the original coordinate is the same as the navigation grid coordinate
	BOOST_CHECK(originalOrigin == ngOrigin);

	Point2D<int> ngPoint = {43, 12};
	sf::Vector2f sfPoint = TestConverter.convertCoordToWindow(ngPoint);
	// Ensure that the sf coordinate is correct
	BOOST_CHECK_CLOSE(sfPoint.x, 2175.f, 0.001);
	BOOST_CHECK_CLOSE(sfPoint.y, 625.f, 0.001);
	Point2D<int> originalPoint = TestConverter.convertCoordToNavGrid(sfPoint);
	// Ensure that the original coordinate is the same as the navigation grid coordinate
	BOOST_CHECK(originalPoint == ngPoint);
}

BOOST_AUTO_TEST_SUITE_END() // end CoordinateConverter_Offsets

BOOST_AUTO_TEST_SUITE(CoordinateConverter_Locations)

// Checks that the edge cases act as we expect
BOOST_AUTO_TEST_CASE(CoordinateConverter_BottomRightEdge) {
	CoordinateConverter TestConverter(50, Point2D<float>{0, 0});

	sf::Vector2f sfPoint = {49.999f, 49.999f};
	Point2D<int> ngPoint = TestConverter.convertCoordToNavGrid(sfPoint);
	// Ensures that the navigation grid point is contained in the first square
	BOOST_CHECK(ngPoint.x == 0 && ngPoint.y == 0);

	sfPoint = {50, 50};
	ngPoint = TestConverter.convertCoordToNavGrid(sfPoint);
	// Ensures that the navigation grid point is contained in the second square
	BOOST_CHECK(ngPoint.x == 1 && ngPoint.y == 1);
}

// Checks that our general case works as we expect
BOOST_AUTO_TEST_CASE(CoordinateConverter_MidPoint) {
	CoordinateConverter TestConverter(50, Point2D<float>{0, 0});

	sf::Vector2f sfPoint = {25, 25};
	Point2D<int> ngPoint = TestConverter.convertCoordToNavGrid(sfPoint);
	// Ensures that the navigation grid point is contained in the first square
	BOOST_CHECK(ngPoint.x == 0 && ngPoint.y == 0);

	sfPoint = {75, 75};
	ngPoint = TestConverter.convertCoordToNavGrid(sfPoint);
	// Ensures that the navigation grid point is contained in the second square
	BOOST_CHECK(ngPoint.x == 1 && ngPoint.y == 1);
}

BOOST_AUTO_TEST_SUITE_END() // end CoordinateConverter_Locations

// Keep at end of file
BOOST_AUTO_TEST_SUITE_END()