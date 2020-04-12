#include "stdafx.h"

#include <GameBackbone/Util/SFUtil.h>

#include <SFML/Graphics.hpp>

#define _USE_MATH_DEFINES
#include <math.h>


using namespace GB;

// Contains all of the tests for SFUtils
BOOST_AUTO_TEST_SUITE(SFUtilTests)

BOOST_AUTO_TEST_SUITE(stepTowardsPointTests)

// Test that a single sprite can reach its destination when given a movement length greater than the distance to its destination.
BOOST_AUTO_TEST_CASE(stepTowardsPoint_Large_Step) {
	sf::Sprite sprite;
	sf::Vector2f destination{ 0, 10 };
	stepTowardsPoint(sprite, destination, 11);

	BOOST_CHECK(sprite.getPosition() == destination);
}

// Test that a single sprite can reach its destination
BOOST_AUTO_TEST_CASE(stepTowardsPoint_Small_Step) {
	sf::Sprite sprite;
	const float DIST_FROM_SPRITE = 10;
	sf::Vector2f destination{ 0, DIST_FROM_SPRITE };

	// Move 1 more time than should be required to account for floating point error
	for (unsigned int i = 0; i < DIST_FROM_SPRITE + 1; i++) {
		stepTowardsPoint(sprite, destination, 1);
	}

	BOOST_CHECK(sprite.getPosition() == destination);
}


// Test that a single sprite is rotated correctly.
BOOST_AUTO_TEST_CASE(stepTowardsPointTests_Rotation) {
	sf::Sprite sprite;
	sf::Vector2f destination{ 0, 10 };
	sf::Vector2f currentPos = sprite.getPosition();

	stepTowardsPoint(sprite, destination, 11);

	float angleToDestination = (fmodf(360.0f + atan2f(destination.y - currentPos.y, destination.x - currentPos.x) * 180.0f / (float)M_PI, 360.0f));

	BOOST_CHECK_CLOSE(sprite.getRotation(), angleToDestination, 0.01);
}

// Test that a single sprite is not rotated when the option is off.
BOOST_AUTO_TEST_CASE(stepTowardsPointTests_No_Rotation) {
	sf::Sprite sprite;
	sf::Vector2f destination{ 0, 10 };
	sf::Vector2f currentPos = sprite.getPosition();
	const float originalRotation = sprite.getRotation();

	stepTowardsPoint(sprite, destination, 11, false);

	BOOST_CHECK_EQUAL(sprite.getRotation(), originalRotation);
}


// Test that a single sprite does not rotate if it is already at its destination.
BOOST_AUTO_TEST_CASE(stepTowardsPointTests_No_Movement_No_Rotation) {
	sf::Sprite sprite;
	const float SPECIAL_ROTATION = 12.345f;
	sprite.setRotation(SPECIAL_ROTATION);
	sf::Vector2f destination = sprite.getPosition();

	stepTowardsPoint(sprite, destination, 11);

	BOOST_CHECK_EQUAL(sprite.getRotation(), SPECIAL_ROTATION);
}

BOOST_AUTO_TEST_SUITE_END() // end stepTowardsPointTests

BOOST_AUTO_TEST_SUITE_END() // end SFUtilTests