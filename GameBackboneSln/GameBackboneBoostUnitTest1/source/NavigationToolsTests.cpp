#include "stdafx.h"
#include <Navigation\NavigationTools.h>

#include <SFML\Graphics.hpp>

#include <vector>

using namespace GB;


/// <summary>
/// Moves all passed sprites a number of steps towards the destination of the same index then checks to see if they have reached
/// their intended destination.
/// </summary>
/// <param name="sprites">The sprites.</param>
/// <param name="destinations">The destinations.</param>
/// <param name="maxStepLengths">The maximum distances to move the sprites.</param>
/// <param name="orientSpritesToDestination">Orients sprites towards their destination if true. Does not orient sprites otherwise.</param>
/// <param name="NUM_STEPS">The number of movements to make towards the destination.</param>
static bool checkBulkStepsToDestinations(std::vector<sf::Sprite*>& sprites, std::vector<sf::Vector2f>& destinations, std::vector<float>& maxMovementDistances, bool orientSpritesToDestination, const unsigned int NUM_STEPS) {
	//move the sprites
	for (unsigned int i = 0; i < NUM_STEPS; i++) {
		bulkMoveSpriteStepTowardsPoint(sprites, destinations, maxMovementDistances, orientSpritesToDestination);
	}

	//ensure that all sprites reached their destinations
	bool missedTarget = false;
	for (unsigned int i = 0; i < sprites.size(); i++) {
		if (sprites[i]->getPosition() != destinations[i]) {
			missedTarget = true;
		}
	}
	return !missedTarget;
}

// Contains all of the tests for Navigation Tools
BOOST_AUTO_TEST_SUITE(NavigationToolsTests)

/// <summary>
/// Struct to store objects that can be reused for all or nearly all 
/// of the unit tests in this file. This struct is meant to be used with fixtures
/// at the unit test level.
/// </summary>
struct ReusableObjects
{
	ReusableObjects() {
		// add sprites
		for (unsigned int i = 0; i < NUM_SPRITES; i++) {
			sprites.push_back(new sf::Sprite());
			destinations.push_back(sf::Vector2f(sinf((float)i), sinf((float)(i+1)))); // should cover all quadrants. Max distance should be below 1.25.
			//TODO (Ryan Lavin): initialize paths 
		}
	}

	~ReusableObjects() {
		for (sf::Sprite* sprite : sprites) {
			delete sprite;
		}
	}

	const unsigned int NUM_SPRITES = 100;
	std::vector<sf::Sprite*> sprites;
	std::vector<sf::Vector2f> destinations;
	std::vector<std::list<Point2D<int>>*> paths;
};

// Test moving a large number of sprites to their destinations by taking small steps
BOOST_FIXTURE_TEST_CASE(bulkMoveSpriteStepTowardsPoint_Large_Batch_Small_Step, ReusableObjects) {
	
	//create the vector of movement lengths
	std::vector<float> maxMovementDistances;
	const float MAX_MOVEMENT_DISTANCE = 0.1f;
	for (unsigned int  i = 0; i < NUM_SPRITES; i++) {
		maxMovementDistances.push_back(MAX_MOVEMENT_DISTANCE);
	}
	
	//move the sprites
	const int NUM_STEPS = 13;
	BOOST_CHECK(checkBulkStepsToDestinations(sprites, destinations, maxMovementDistances, false, NUM_STEPS));
}

// Test moving a large number of sprites to their destinations by taking medium steps
BOOST_FIXTURE_TEST_CASE(bulkMoveSpriteStepTowardsPoint_Large_Batch_Medium_Step, ReusableObjects) {

	//create the vector of movement lengths
	std::vector<float> maxMovementDistances;
	
	const float MAX_MOVEMENT_DISTANCE = 0.5f;
	for (unsigned int i = 0; i < NUM_SPRITES; i++) {
		maxMovementDistances.push_back(MAX_MOVEMENT_DISTANCE);
	}

	//move the sprites
	const int NUM_STEPS = 3; 
	BOOST_CHECK(checkBulkStepsToDestinations(sprites, destinations, maxMovementDistances, false, NUM_STEPS));
}

// Test moving a large number of sprites to their destinations by taking large steps
BOOST_FIXTURE_TEST_CASE(bulkMoveSpriteStepTowardsPoint_Large_Batch_large_Step, ReusableObjects) {

	//create the vector of movement lengths
	std::vector<float> maxMovementDistances;
	const float MAX_MOVEMENT_DISTANCE = 1000.0f;
	for (unsigned int i = 0; i < NUM_SPRITES; i++) {
		maxMovementDistances.push_back(MAX_MOVEMENT_DISTANCE);
	}

	//move the sprites
	const int NUM_STEPS = 1;
	BOOST_CHECK(checkBulkStepsToDestinations(sprites, destinations, maxMovementDistances, false, NUM_STEPS));
}

// TODO (Ryan Lavin): add test for having 0 move distance 


// Test that without any movement distance the sprite does not reach its destination.
BOOST_FIXTURE_TEST_CASE(bulkMoveSpriteStepTowardsPoint_Large_Batch_Zero_Size_Step, ReusableObjects) {

	//create the vector of movement lengths
	std::vector<float> maxMovementDistances;
	const float MAX_MOVEMENT_DISTANCE = 0.0f;
	for (unsigned int i = 0; i < NUM_SPRITES; i++) {
		maxMovementDistances.push_back(MAX_MOVEMENT_DISTANCE);
	}

	//move the sprites
	const int NUM_STEPS = 100;
	BOOST_CHECK(!checkBulkStepsToDestinations(sprites, destinations, maxMovementDistances, false, NUM_STEPS));
}

// Test that all sprites are rotated towards their destination with a large step
BOOST_FIXTURE_TEST_CASE(bulkMoveSpriteStepTowardsPoint_Large_Batch_Large_Size_Step_Rotation, ReusableObjects) {

	//create the vector of movement lengths
	std::vector<float> maxMovementDistances;
	const float MAX_MOVEMENT_DISTANCE = 1000.0f;
	for (unsigned int i = 0; i < NUM_SPRITES; i++) {
		maxMovementDistances.push_back(MAX_MOVEMENT_DISTANCE);
	}

	std::vector<float> angleToDestinations;
	for (unsigned int i = 0; i < NUM_SPRITES; i++) {
		sf::Vector2f currentPos = sprites[i]->getPosition();
		sf::Vector2f destination = destinations[i];
		angleToDestinations.push_back(atan2f(destination.y - currentPos.y, destination.x - currentPos.x));
	}

	//move the sprites
	const int NUM_STEPS = 1;
	checkBulkStepsToDestinations(sprites, destinations, maxMovementDistances, true, NUM_STEPS);

	int wrongRotatedSprites = 0;
	for (unsigned int i = 0; i < NUM_SPRITES; i++) {
		if (abs(angleToDestinations[i] - sprites[i]->getRotation()) > 0.01) {
			wrongRotatedSprites++;
		}
	}
	BOOST_CHECK_EQUAL(wrongRotatedSprites, 0);
}

// keep at end of file
BOOST_AUTO_TEST_SUITE_END() // end NavigationToolsTests