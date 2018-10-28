#include "stdafx.h"
#include <Backbone/BackboneBaseExceptions.h>
#include <Navigation/NavigationTools.h>
#include <Util/DebugIncludes.h>

#include <SFML/Graphics.hpp>

#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>
#include <vector>
#include <cfloat>


using namespace GB;

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
			WindowCoordinatePathPtr path = std::make_shared<WindowCoordinatePath>();
			WindowCoordinatePathPtr backupPath = std::make_shared<WindowCoordinatePath>();
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
	std::vector<WindowCoordinatePathPtr> paths;
	std::vector<WindowCoordinatePathPtr> backupPaths;

	const unsigned int NUM_SPRITES = 3;
	const unsigned int BASE_PATH_LENGTH = 3;
};

/// <summary>
/// Struct to store objects that can be reused for all or nearly all compound sprite tests
/// This struct is meant to be used with fixtures at the unit test level.
/// </summary>
struct ReusableCompoundObjects {


	ReusableCompoundObjects() {
		// add sprites
		for (unsigned int ii = 0; ii < NUM_SPRITES; ++ii) {

			// build compound sprites
			CompoundSprite* compoundSprite = new CompoundSprite();
			for (unsigned int jj = 0; jj < NUM_COMPONENTS; ++jj) {
				sf::Sprite* component = new sf::Sprite();
				components.push_back(component);
				compoundSprite->addComponent(component);
			}
			compoundSprites.push_back(compoundSprite);


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


	~ReusableCompoundObjects() {
		for (sf::Sprite* component : components) {
			delete component;
		}
		for (CompoundSprite* compoundSprite : compoundSprites) {
			delete compoundSprite;
		}
	}

	const unsigned int NUM_SPRITES = 100;
	const unsigned int NUM_COMPONENTS = 2;
	std::vector<CompoundSprite*> compoundSprites;
	std::vector<sf::Sprite*> components;
	std::vector<sf::Vector2f> destinations;
	std::vector<std::list<sf::Vector2f>*> paths;
};

/// <summary>
/// Test fixture for moving CompoundSprite along paths
/// </summary>
struct ReusableCompoundPathfindingObjects {
	ReusableCompoundPathfindingObjects() {

		// create sprites
		for (unsigned int i = 0; i < NUM_SPRITES; i++) {
			sf::Sprite* sprite1 = new sf::Sprite();
			sf::Sprite* sprite2 = new sf::Sprite();
			sprites.push_back(sprite1);
			sprites.push_back(sprite2);

			CompoundSprite* compoundSprite = new CompoundSprite({ sprite1, sprite2 });
			compoundSprites.push_back(compoundSprite);
		}

		//fill the path for each sprite
		for (unsigned int ii = 0; ii < NUM_SPRITES; ii++) {

			//each sprite gets a longer path
			WindowCoordinatePathPtr path = std::make_shared<WindowCoordinatePath>();
			WindowCoordinatePathPtr backupPath = std::make_shared<WindowCoordinatePath>();
			for (unsigned int jj = 0; jj < ii * BASE_PATH_LENGTH; jj++) {
				path->push_back({ (float)ii, (float)jj });
				backupPath->push_back({ (float)ii, (float)jj });
			}
			paths.push_back(path);
			backupPaths.push_back(backupPath);
		}
	}
	~ReusableCompoundPathfindingObjects() {
		for (sf::Sprite* sprite : sprites) {
			delete sprite;
		}
		for (CompoundSprite* compoundSprite: compoundSprites) {
			delete compoundSprite;
		}


	}

	// sprites
	std::vector<CompoundSprite*> compoundSprites;
	std::vector<sf::Sprite*> sprites;
	const unsigned int NUM_SPRITES = 3;

	// paths
	std::vector<WindowCoordinatePathPtr> paths;
	std::vector<WindowCoordinatePathPtr> backupPaths;
	const unsigned int BASE_PATH_LENGTH = 3;
};


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

// Test that a single sprite is not rotated when the option is off.
BOOST_AUTO_TEST_CASE(moveSpriteStepTowardsPointTests_No_Rotation) {
	sf::Sprite sprite;
	sf::Vector2f destination{ 0, 10 };
	sf::Vector2f currentPos = sprite.getPosition();

	const float origionalRotation = sprite.getRotation();

	moveSpriteStepTowardsPoint(sprite, destination, 11, false);


	BOOST_CHECK_EQUAL(sprite.getRotation(), origionalRotation);
}


// Test that a single sprite does not rotate if it is already at its destination.
BOOST_AUTO_TEST_CASE(moveSpriteStepTowardsPointTests_No_Movement_No_Rotation) {
	sf::Sprite sprite;
	const float SPECIAL_ROTATION = 12.345f;
	sprite.setRotation(SPECIAL_ROTATION);
	sf::Vector2f destination = sprite.getPosition();
	moveSpriteStepTowardsPoint(sprite, destination, 11);


	BOOST_CHECK_EQUAL(sprite.getRotation(), SPECIAL_ROTATION);
}

BOOST_AUTO_TEST_SUITE_END() // end moveSpriteStepTowardsPointTests

BOOST_AUTO_TEST_SUITE(moveSpriteAlongPathTests)

// ensure that a single sprite following a path can reach its destination
BOOST_FIXTURE_TEST_CASE(moveSpriteAlongPath_Reach_Destination, ReusablePathfindingObjects) {
	// move sprite to the end of the path
	const size_t NUM_STEPS = paths[2]->size();
	for (size_t i = 0; i < NUM_STEPS; i++) {
		moveSpriteAlongPath(*sprites[2], paths[2], 1, FLT_MAX);
	}

	// ensure that the sprite is at the final position in the path
	BOOST_CHECK(sprites[2]->getPosition() == backupPaths[2]->back());
}

// Test that the moving sprite moves to each consecutive point in the path in-order
BOOST_FIXTURE_TEST_CASE(moveSpriteAlongPath_Follow_Full_Path, ReusablePathfindingObjects) {
	// move sprite to the end of the path
	const size_t NUM_STEPS = paths[2]->size();
	for (size_t i = 0; i < NUM_STEPS; i++) {
		moveSpriteAlongPath(*sprites[2], paths[2], 1, FLT_MAX);

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

// Ensure that sprites rotate to the destination that they are moving to when following a path
BOOST_FIXTURE_TEST_CASE(moveSpriteAlongPath_Rotation, ReusableCompoundPathfindingObjects) {

	// move the sprite
	moveSpriteAlongPath(*sprites[2], paths[2], 1, 1.0f);
	float angleToDestination = (fmodf(360.0f + atan2f(paths[2]->front().y - sprites[2]->getPosition().y, paths[2]->front().x - sprites[2]->getPosition().x) * 180.0f / (float)M_PI, 360.0f));

	// ensure that the sprite rotated
	BOOST_CHECK_EQUAL(sprites[2]->getRotation(), angleToDestination);

}

// Ensure that sprites don't rotate to the destination that they are moving to when following a path if the option is off
BOOST_FIXTURE_TEST_CASE(moveSpriteAlongPath_No_Rotation, ReusableCompoundPathfindingObjects) {

	const float origionalAngle = sprites[2]->getRotation();

	// move the sprite
	moveSpriteAlongPath(*sprites[2], paths[2], 1, 1.0f, false);

	// ensure that the sprite didn't rotate
	BOOST_CHECK_EQUAL(sprites[2]->getRotation(), origionalAngle);

}

BOOST_AUTO_TEST_SUITE_END() // end moveSpriteAlongPathTests


BOOST_AUTO_TEST_SUITE(moveCompoundSpriteAlongPathTests)

// ensure that a single CompoundSprite following a path can reach its destination
BOOST_FIXTURE_TEST_CASE(moveCompoundSpriteAlongPath_Reach_Destination, ReusableCompoundPathfindingObjects) {
	// move sprite to the end of the path
	const size_t NUM_STEPS = paths[2]->size();
	for (size_t i = 0; i < NUM_STEPS; i++) {
		moveCompoundSpriteAlongPath(*compoundSprites[2], paths[2], 1, FLT_MAX, {});
	}

	// ensure that the sprite is at the final position in the path
	BOOST_CHECK(compoundSprites[2]->getPosition() == backupPaths[2]->back());
}

// Test that the moving CompoundSprite moves to each consecutive point in the path in-order
BOOST_FIXTURE_TEST_CASE(moveCompoundSpriteAlongPath_Follow_Full_Path, ReusableCompoundPathfindingObjects) {
	// move sprite to the end of the path
	const size_t NUM_STEPS = paths[2]->size();
	for (size_t i = 0; i < NUM_STEPS; i++) {
		moveCompoundSpriteAlongPath(*compoundSprites[2], paths[2], 1, FLT_MAX, {});

		// Test that the moving sprite moves to each consecutive point in the path in-order
		BOOST_CHECK(compoundSprites[2]->getPosition() == backupPaths[2]->front());
		backupPaths[2]->pop_front();
	}
}

// Test that destinations can be reached even if it takes more than one move to get there
BOOST_FIXTURE_TEST_CASE(moveCompoundSpriteAlongPath_Reach_Destination_SmallSteps, ReusableCompoundPathfindingObjects) {
	// move sprite to the end of the path

	// ensure that it takes two moves to reach the first point
	moveCompoundSpriteAlongPath(*compoundSprites[2], paths[2], 1, 1.0f, {});
	BOOST_CHECK(compoundSprites[2]->getPosition() != backupPaths[2]->front());
	moveCompoundSpriteAlongPath(*compoundSprites[2], paths[2], 1, 1.0f, {});
	BOOST_CHECK(compoundSprites[2]->getPosition() == backupPaths[2]->front());
}

BOOST_AUTO_TEST_SUITE_END() // end moveCompoundSpriteAlongPathTests


BOOST_AUTO_TEST_SUITE(moveCompoundSpriteStepTowardsPointTests)

// Test that a single CompoundSprite can reach its destination when given a movement length greater than the distance to its destination.
BOOST_AUTO_TEST_CASE(moveCompoundSpriteStepTowardsPointTests_Large_Step) {
	CompoundSprite sprite;
	sf::Vector2f destination{ 0, 10 };
	moveCompoundSpriteStepTowardsPoint(sprite, destination, 11, {});

	// ensure that the sprite has reached its destination
	BOOST_CHECK(sprite.getPosition() == destination);
}

// Test that a single compoundSprite can reach its destination
BOOST_AUTO_TEST_CASE(moveCompoundSpriteStepTowardsPoint_Small_Step) {
	CompoundSprite sprite;
	const float DIST_FROM_SPRITE = 10;
	sf::Vector2f destination{ 0, DIST_FROM_SPRITE };

	//move 1 more time than should be required to account for floating point error
	for (unsigned int i = 0; i < DIST_FROM_SPRITE + 1; i++) {
		moveCompoundSpriteStepTowardsPoint(sprite, destination, 1, {});
	}

	// ensure that the sprite has reached its destination
	BOOST_CHECK(sprite.getPosition() == destination);

}


// Test that a single CompoundSprite is rotated correctly.
BOOST_AUTO_TEST_CASE(moveCompoundSpriteStepTowardsPointTests_Rotation) {
	sf::Sprite testSprite;
	CompoundSprite sprite({&testSprite});
	sf::Vector2f destination{ 0, 10 };
	sf::Vector2f currentPos = sprite.getPosition();
	moveCompoundSpriteStepTowardsPoint(sprite, destination, 11, {0});

	float angleToDestination = (fmodf(360.0f + atan2f(destination.y - currentPos.y, destination.x - currentPos.x) * 180.0f / (float)M_PI, 360.0f));

	// ensure that the sprite is rotated correctly
	BOOST_CHECK_CLOSE(sprite.getComponents().at(0)->getRotation(), angleToDestination, 0.01);
}

// Test that a single CompoundSprite is not rotated when the option is off.
BOOST_AUTO_TEST_CASE(moveCompoundSpriteStepTowardsPointTests_No_Rotation) {
	sf::Sprite testSprite;
	CompoundSprite sprite({ &testSprite });
	sf::Vector2f destination{ 0, 10 };
	sf::Vector2f currentPos = sprite.getPosition();
	const float origionalRotation = sprite.getComponents().at(0)->getRotation();
	moveCompoundSpriteStepTowardsPoint(sprite, destination, 11, {});

	// ensure that the component has its original rotation.
	BOOST_CHECK_EQUAL(sprite.getComponents().at(0)->getRotation(), origionalRotation);
}


// Test that a single CompoundSprite does not rotate if it is already at its destination.
BOOST_AUTO_TEST_CASE(moveCompoundSpriteStepTowardsPointTests_No_Movement_No_Rotation) {
	sf::Sprite testSprite;
	CompoundSprite sprite({ &testSprite });
	const float SPECIAL_ROTATION = 12.345f;
	testSprite.setRotation(SPECIAL_ROTATION);
	sf::Vector2f destination = sprite.getPosition();
	moveCompoundSpriteStepTowardsPoint(sprite, destination, 11, {0});

	// ensure that the component was not rotated
	BOOST_CHECK_EQUAL(testSprite.getRotation(), SPECIAL_ROTATION);
}


BOOST_AUTO_TEST_SUITE_END() // end moveCompoundSpriteStepTowardsPointTests

BOOST_AUTO_TEST_SUITE(initAllNavigationGridValuesTests)

struct TestNavigationData : public NavigationGridData
{
	sf::Sprite testDataSprite0;
	sf::Sprite testDataSprite1;
	sf::Sprite testDataSprite2;
	sf::Sprite testDataSprite3;
};

// Test that NavigationGridData can be extended and that pointers
// to the child classes can be used in a Navigation grid without corrupting the heap.
BOOST_AUTO_TEST_CASE(initAllNavigationGridValues_Test_Inheritance) {
	NavigationGrid navGrid;

	initAllNavigationGridValues(navGrid, TestNavigationData());

	for (unsigned int i = 0; i < navGrid.getArraySizeX(); i++) {
		for (unsigned int j = 0; j < navGrid.getArraySizeY(); j++) {
			//these values aren't anything specific. Just changing data in a way that would corrupt the heap if
			//the navigation grid is not populated with TestNavigationData
			static_cast<TestNavigationData*> (navGrid.at(i, j))->testDataSprite3.setScale(1, 2);
			static_cast<TestNavigationData*> (navGrid.at(i, j))->testDataSprite3.setRotation(100);
			static_cast<TestNavigationData*> (navGrid.at(i, j))->testDataSprite3.setColor(sf::Color::Green);
		}
	}

	freeAllNavigationGridData(navGrid);
	// No assert here. Just ensure that nothing weird happens with the memory.
}


BOOST_AUTO_TEST_SUITE_END() // end initAllNavigationGridValuesTests

// keep at end of file
BOOST_AUTO_TEST_SUITE_END() // end NavigationToolsTests