#include "stdafx.h"
#include <Backbone\BackboneBaseExceptions.h>
#include <Navigation\NavigationTools.h>
#include <util\DebugIncludes.h>

#include <SFML\Graphics.hpp>

#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>
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
		for (unsigned int ii = 0; ii < NUM_SPRITES; ++ii) {
			sprites.push_back(new sf::Sprite());
			destinations.push_back(sf::Vector2f(sinf((float)ii), sinf((float)(ii + 1)))); // should cover all quadrants. Max distance should be below 1.25.
			
			// initialize paths 
			for (unsigned int jj = 0; jj < NUM_SPRITES; ++jj) {
				std::list<sf::Vector2f>* path = new std::list<sf::Vector2f>;

				for (unsigned int kk = 0; kk < jj; ++kk) {
					path->push_back(sf::Vector2f(sinf((float)kk), sinf((float)(kk + kk)))); // should cover all quadrants. Max distance should be below 1.25.
				}
				paths.push_back(path);
			}

		}
	}

	~ReusableObjects() {
		for (sf::Sprite* sprite : sprites) {
			delete sprite;
		}
		for (auto path : paths) {
			delete path;
		}
	}

	const unsigned int NUM_SPRITES = 100;
	std::vector<sf::Sprite*> sprites;
	std::vector<sf::Vector2f> destinations;
	std::vector<std::list<sf::Vector2f>*> paths;
};

/// <summary>
/// Test fixture for moving sprites along paths
/// </summary>
struct ReusablePathfindingObjects
{
	ReusablePathfindingObjects() {

		//create sprites
		for (unsigned int ii = 0; ii < NUM_SPRITES; ii++) {
			sprites.push_back(new sf::Sprite());
		}

		//fill the path for each sprite
		for (unsigned int ii = 0; ii < NUM_SPRITES; ii++) {

			//each sprite gets a longer path
			std::shared_ptr<std::list<sf::Vector2f>> path = std::make_shared<std::list<sf::Vector2f>>();
			std::shared_ptr<std::list<sf::Vector2f>> backupPath = std::make_shared<std::list<sf::Vector2f>>();
			for (unsigned int jj = 0; jj < ii * BASE_PATH_LENGTH; jj++) {
				path->push_back({ (float)ii, (float)jj });
				backupPath->push_back({ (float)ii, (float)jj });
			}
			paths.push_back(path);
			backupPaths.push_back(backupPath);
		}

	}

	~ReusablePathfindingObjects()
	{
		for (sf::Sprite* sprite : sprites) {
			delete sprite;
		}
	}

	std::vector<sf::Sprite*> sprites;
	std::vector<std::shared_ptr<std::list<sf::Vector2f>>> paths;
	std::vector<std::shared_ptr<std::list<sf::Vector2f>>> backupPaths;

	const unsigned int NUM_SPRITES = 3;
	const unsigned int BASE_PATH_LENGTH = 3;
};

BOOST_AUTO_TEST_SUITE(bulkMoveSpriteStepTowardsPointTests)

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
		angleToDestinations.push_back(fmodf(360.0f + atan2f(destination.y - currentPos.y, destination.x - currentPos.x) * 180.0f / (float)M_PI, 360.0f));
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

// Test that sprites are only rotated if they are not already at their destination.
BOOST_FIXTURE_TEST_CASE(bulkMoveSpriteStepTowardsPoint_Large_Batch_No_Movement_No_Rotation, ReusableObjects) {

	//create the vector of movement lengths
	std::vector<float> maxMovementDistances;
	const float MAX_MOVEMENT_DISTANCE = 1000.0f;
	for (unsigned int i = 0; i < NUM_SPRITES; i++) {
		maxMovementDistances.push_back(MAX_MOVEMENT_DISTANCE);
	}

	//set the destinations of the first two sprites to their current positions.
	destinations[0] = sprites[0]->getPosition();
	destinations[1] = sprites[1]->getPosition();

	//set the rotation of the first two sprites to a non-default angle.
	const float SPECIAL_ROTATION = 12.345f;
	sprites[0]->setRotation(SPECIAL_ROTATION);
	sprites[1]->setRotation(SPECIAL_ROTATION);

	std::vector<float> angleToDestinations;
	for (unsigned int i = 0; i < NUM_SPRITES; i++) {
		sf::Vector2f currentPos = sprites[i]->getPosition();
		sf::Vector2f destination = destinations[i];
		angleToDestinations.push_back(fmodf(360.0f + atan2f(destination.y - currentPos.y, destination.x - currentPos.x) * 180.0f / (float)M_PI, 360.0f));
	}

	//move the sprites
	const int NUM_STEPS = 1;
	checkBulkStepsToDestinations(sprites, destinations, maxMovementDistances, true, NUM_STEPS);

	//ensure all sprites except the first two get the correct rotation.
	int wrongRotatedSprites = 0;
	for (unsigned int i = 2; i < NUM_SPRITES; i++) {
		if (abs(angleToDestinations[i] - sprites[i]->getRotation()) > 0.01) {
			wrongRotatedSprites++;
		}
	}
	BOOST_CHECK_EQUAL(wrongRotatedSprites, 0);

	//ensure that the first two sprites have their custom rotation
	BOOST_CHECK_EQUAL(sprites[0]->getRotation(), SPECIAL_ROTATION);
	BOOST_CHECK_EQUAL(sprites[1]->getRotation(), SPECIAL_ROTATION);
}

// Test that without any movement distance the sprite does not reach its destination.
BOOST_FIXTURE_TEST_CASE(bulkMoveSpriteStepTowardsPoint_Large_Batch_Incorrect_Sizes, ReusableObjects) {

	//create the vector of movement lengths
	std::vector<float> maxMovementDistances;
	const float MAX_MOVEMENT_DISTANCE = 0.0f;
	for (unsigned int i = 0; i < 1; i++) {
		maxMovementDistances.push_back(MAX_MOVEMENT_DISTANCE);
	}

	//move the sprites
	BOOST_CHECK_THROW( bulkMoveSpriteStepTowardsPoint(sprites, destinations, maxMovementDistances), Error::NavigationTools_MismatchedNavigationSizes);
}

BOOST_AUTO_TEST_SUITE_END() // end bulkMoveSpriteStepTowardsPointTests

BOOST_AUTO_TEST_SUITE(moveSpriteStepTowardsPointTests)

// Test that a single sprite can reach its destination when given a movement length greater than the distance to its destination.
BOOST_AUTO_TEST_CASE(moveSpriteStepTowardsPointTests_Large_Step) {
	sf::Sprite sprite;
	sf::Vector2f destination{ 0, 10 };
	moveSpriteStepTowardsPoint(sprite, destination, 11);

	BOOST_CHECK(sprite.getPosition() == destination);
}

// Test that a single sprite can reach its destination 
BOOST_AUTO_TEST_CASE(moveSpriteStepTowardsPoint_Small_Step) {
	sf::Sprite sprite;
	const float DIST_FROM_SPRITE = 10;
	sf::Vector2f destination{ 0, DIST_FROM_SPRITE };

	//move 1 more time than should be required to account for floating point error
	for (unsigned int i = 0; i < DIST_FROM_SPRITE + 1; i++) {
		moveSpriteStepTowardsPoint(sprite, destination, 1);
	}

	BOOST_CHECK(sprite.getPosition() == destination);

}


// Test that a single sprite is rotated correctly.
BOOST_AUTO_TEST_CASE(moveSpriteStepTowardsPointTests_Rotation) {
	sf::Sprite sprite;
	sf::Vector2f destination{ 0, 10 };
	sf::Vector2f currentPos = sprite.getPosition();
	moveSpriteStepTowardsPoint(sprite, destination, 11);

	float angleToDestination = (fmodf(360.0f + atan2f(destination.y - currentPos.y, destination.x - currentPos.x) * 180.0f / (float)M_PI, 360.0f));

	BOOST_CHECK_CLOSE(sprite.getRotation(), angleToDestination, 0.01);
}


// Test that a single sprite does not rotate if it is already at its destination.
BOOST_AUTO_TEST_CASE(moveSpriteStepTowardsPointTests_No_Movement_No_Rotation) {
	sf::Sprite sprite;
	const float SPECIAL_ROTATION = 12.345;
	sprite.setRotation(SPECIAL_ROTATION);
	sf::Vector2f destination = sprite.getPosition();
	moveSpriteStepTowardsPoint(sprite, destination, 11);


	BOOST_CHECK_EQUAL(sprite.getRotation(), SPECIAL_ROTATION);
}

BOOST_AUTO_TEST_SUITE_END() // end moveSpriteStepTowardsPointTests

BOOST_AUTO_TEST_SUITE(bulkMoveSpriteAlongPathTests)


// Test that the sprites reach their destinations
BOOST_FIXTURE_TEST_CASE(bulkMoveSpriteAlongPath_Reach_Destinations, ReusablePathfindingObjects) {

	//ensure that the sprites reach their destination in one move
	const unsigned int MOVEMENT_SPEED = UINT64_MAX;
	std::vector<float> movementSpeeds;
	for (unsigned int  i = 0; i < NUM_SPRITES; ++i) {
		movementSpeeds.push_back(MOVEMENT_SPEED);
	}

	//move until each sprite should have reached its destination
	for (unsigned int i = 0; i < NUM_SPRITES * BASE_PATH_LENGTH; i++) {
		bulkMoveSpriteAlongPath(sprites, paths, 1, movementSpeeds);
	}

	//ensure that each path is at its end;
	for each (auto path in paths) {
		BOOST_CHECK_EQUAL(path->size(), 0);
	}

	//ensure that each sprite has reached its correct position
	for (unsigned int i = 0; i < NUM_SPRITES; i++) {
		if (!paths[i]->empty()) {
			BOOST_CHECK(sprites[i]->getPosition() == backupPaths[i]->back());
		}
	}

	BOOST_CHECK(sprites[0]->getPosition() == (sf::Vector2f{ 0.0f,0.0f }));
}

// Test that the moving sprites move to each consecutive point in the path in-order
BOOST_FIXTURE_TEST_CASE(bulkMoveSpriteAlongPath_Follow_Full_Path, ReusablePathfindingObjects) {
	//ensure that the sprites reach their destination in one move
	const unsigned int MOVEMENT_SPEED = UINT64_MAX;
	std::vector<float> movementSpeeds;
	for (unsigned int i = 0; i < NUM_SPRITES; ++i) {
		movementSpeeds.push_back(MOVEMENT_SPEED);
	}

	//move until each sprite should have reached its destination
	for (unsigned int i = 0; i < NUM_SPRITES * BASE_PATH_LENGTH; i++) {
		bulkMoveSpriteAlongPath(sprites, paths, 1, movementSpeeds);
		for (unsigned int j = 0; j < sprites.size(); j++) {
			if (!paths[j]->empty()) {
				auto sprPos = sprites[j]->getPosition();
				auto pthPos = backupPaths[j]->front();

				//ensure that the sprite stops along every point of the path
				BOOST_CHECK(sprites[j]->getPosition() == backupPaths[j]->front());
				backupPaths[j]->pop_front();
			}
		}
	}
}

// Ensure that when taking small steps the appropriate number of steps is required to reach a destination
BOOST_FIXTURE_TEST_CASE(bulkMoveSpriteAlongPath_Reach_Destinations_SmallSteps, ReusablePathfindingObjects) {
	
	//each sprite can move 1/2 of the way to its destination each step
	std::vector<float> movementSpeeds;
	for (unsigned int i = 0; i < NUM_SPRITES; ++i) {
		movementSpeeds.push_back(i / 2.0f);
	}

	bulkMoveSpriteAlongPath(sprites, paths, 1, movementSpeeds);


	//ensure that each sprite has not reached its final position
	for (unsigned int i = 0; i < NUM_SPRITES; i++) {
		if (!paths[i]->empty()) {
			BOOST_CHECK(sprites[i]->getPosition() != backupPaths[i]->front());
		}
	}

	bulkMoveSpriteAlongPath(sprites, paths, 1, movementSpeeds);

	//ensure that each sprite has reached its correct position
	for (unsigned int i = 0; i < NUM_SPRITES; i++) {
		if (!paths[i]->empty()) {
			BOOST_CHECK(sprites[i]->getPosition() == backupPaths[i]->front());
		}
	}

}

BOOST_AUTO_TEST_SUITE_END() // end bulkMoveSpriteAlongPathTests

BOOST_AUTO_TEST_SUITE(moveSpriteAlongPathTests)

// ensure that a single sprite following a path can reach its destination
BOOST_FIXTURE_TEST_CASE(moveSpriteAlongPath_Reach_Destination, ReusablePathfindingObjects) {
	// move sprite to the end of the path 
	const unsigned int NUM_STEPS = paths[2]->size();
	for (unsigned int i = 0; i < NUM_STEPS; i++) {
		moveSpriteAlongPath(*sprites[2], paths[2], 1, INTMAX_MAX);
	}

	// ensure that the sprite is at the final position in the path
	BOOST_CHECK(sprites[2]->getPosition() == backupPaths[2]->back());
}

// Test that the moving sprite moves to each consecutive point in the path in-order
BOOST_FIXTURE_TEST_CASE(moveSpriteAlongPath_Follow_Full_Path, ReusablePathfindingObjects) {
	// move sprite to the end of the path 
	const unsigned int NUM_STEPS = paths[2]->size();
	for (unsigned int i = 0; i < NUM_STEPS; i++) {
		moveSpriteAlongPath(*sprites[2], paths[2], 1, INTMAX_MAX);

		// Test that the moving sprite moves to each consecutive point in the path in-order
		BOOST_CHECK(sprites[2]->getPosition() == backupPaths[2]->front());
		backupPaths[2]->pop_front();
	}
}

// Test that destinations can be reached even if it takes more than one move to get there
BOOST_FIXTURE_TEST_CASE(moveSpriteAlongPath_Reach_Destination_SmallSteps, ReusablePathfindingObjects) {
	// move sprite to the end of the path 

	// ensure that it takes two moves to reach the first point
	moveSpriteAlongPath(*sprites[2], paths[2], 1, 1.0f);
	BOOST_CHECK(sprites[2]->getPosition() != backupPaths[2]->front());
	moveSpriteAlongPath(*sprites[2], paths[2], 1, 1.0f);
	BOOST_CHECK(sprites[2]->getPosition() == backupPaths[2]->front());
}

BOOST_AUTO_TEST_SUITE_END() //moveSpriteAlongPathTests

// keep at end of file
BOOST_AUTO_TEST_SUITE_END() // end NavigationToolsTests