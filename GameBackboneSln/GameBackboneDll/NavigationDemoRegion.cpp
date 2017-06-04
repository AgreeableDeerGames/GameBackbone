#include "stdafx.h"
#include <iostream>

#define _USE_MATH_DEFINES

#include "NavigationDemoRegion.h"
#include "NavigationTools.h"

#include <SFML/Graphics.hpp>

#include <string>
#include <math.h>

using namespace GB;

/// <summary>
/// Initializes a new instance of the <see cref="NavigationDemoRegion"/> class.
/// </summary>
NavigationDemoRegion::NavigationDemoRegion() {
	//init storage
	navGrid = new NavigationGrid(NAV_GRID_DIM);
	regionPathfinder.setNavigationGrid(navGrid);
	visualNavigationGrid = new Array2D<sf::Sprite*>(NAV_GRID_DIM);

	//init textures
	std::string arrowPath("..\\..\\Textures\\SmallArrow.png");
	navigatorTexture = new sf::Texture();
	navigatorTexture->loadFromFile(arrowPath);
	std::string navigationGridPath("..\\..\\Textures\\NavigationGrid.png");
	gridTexture = new sf::Texture();
	gridTexture->loadFromFile(navigationGridPath);

	//internal function logic
	std::vector<IntPair> nonBlockableGridSquares;


	//init navigators

		//create navigators and add to respective arrays
	sf::Sprite* navigator1 = new sf::Sprite(*navigatorTexture);
	sf::Sprite* navigator2 = new sf::Sprite(*navigatorTexture);
	navigators.push_back(navigator1);
	navigators.push_back(navigator2);
	navigator2->setColor(sf::Color::Green);
	navigator1->setColor(sf::Color::Blue);

	//set rotation point of navigators
	for each (sf::Sprite* navigator in navigators) {
		const sf::IntRect * const  textureRect = &navigator->getTextureRect();
		sf::Vector2f newOrigin(textureRect->width / 2.0f, textureRect->height / 2.0f);
		navigator->setOrigin(newOrigin);
	}
	
		//position navigators
	IntPair navigator1StartingGrid(0, 0);
	IntPair navigator2StartingGrid(15, 15);
	nonBlockableGridSquares.push_back(navigator1StartingGrid);
	nonBlockableGridSquares.push_back(navigator2StartingGrid);
	const sf::Vector2f navigator1StartingPos = gridCoordToWorldCoord(navigator1StartingGrid);
	const sf::Vector2f navigator2StartingPos = gridCoordToWorldCoord(navigator2StartingGrid);
	navigator1->setPosition(navigator1StartingPos);
	navigator2->setPosition(navigator2StartingPos);

	//create maze
	initMaze(nonBlockableGridSquares);

	//draw navigators on top of maze
	setDrawable(true, navigator1);
	setDrawable(true, navigator2);


	//Path-find from starting positions to end positions
	//create request
	PathRequest pathRequest{ navigator1StartingGrid, IntPair(15,15), 3, 0 };
	std::vector<PathRequest> pathRequests;
	pathRequests.push_back(pathRequest);

	//second request
	PathRequest pathRequest2{ navigator2StartingGrid, IntPair(0,0), 1, 0 };
	pathRequests.push_back(pathRequest2);

	//find the path
	pathsReturn.resize(pathRequests.size());
	regionPathfinder.pathFind(pathRequests, &pathsReturn);

}

/// <summary>
/// Finalizes an instance of the <see cref="NavigationDemoRegion"/> class.
/// </summary>
NavigationDemoRegion::~NavigationDemoRegion() {

	//delete navigation data
	freeAllNavigationGridData(*navGrid);
	delete navGrid;
	navGrid = nullptr;

	//delete visual navigation grid data
	for (unsigned int i = 0; i < visualNavigationGrid->getArraySizeX(); i++) {
		for (unsigned int j = 0; j < visualNavigationGrid->getArraySizeY(); j++) {
			delete (*visualNavigationGrid)[i][j];
			(*visualNavigationGrid)[i][j] = nullptr;
		}
	}
	delete visualNavigationGrid;

	//delete navigators
	for each (auto navigator in navigators) {
		delete navigator;
		navigator = nullptr;
	}

	//delete textures
	delete navigatorTexture;
	navigatorTexture = nullptr;
	delete gridTexture;
	gridTexture = nullptr;
}

/// <summary>
/// Executes a single cycle of the main logic loop for this region.
/// </summary>
void NavigationDemoRegion::behave(sf::Time currentTime) {

	for (size_t i = 0; i < navigators.size(); i++) {
		sf::Int64 msPassed = currentTime.asMilliseconds() - lastUpdateTime.asMicroseconds();
		moveSpriteAlongPath(navigators[i], &(pathsReturn[i]), msPassed, 1);
	}

	lastUpdateTime = currentTime;
}

/// <summary>
/// Handles mouse click logic.
/// </summary>
/// <param name="newPosition">The position of the click.</param>
/// <param name="button">The mouse button clicked button.</param>
void NavigationDemoRegion::handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button) {
	if (button == sf::Mouse::Left) {
		std::vector<PathRequest> pathRequests(navigators.size());

		//create each path request
		for (size_t i = 0; i < navigators.size(); i++) {
			sf::Sprite* currentNavigator = navigators[i];
			IntPair startingPos = worldCoordToGridCoord(currentNavigator->getPosition());
			IntPair endingPos = worldCoordToGridCoord(newPosition);
			pathRequests[i] = PathRequest{ startingPos, endingPos, 1, 0 };
		}

		//path-find
		pathsReturn.resize(pathRequests.size());
		regionPathfinder.pathFind(pathRequests, &pathsReturn);
	}
}

/// <summary>
/// Initializes the maze that the navigators will use.
/// </summary>
void NavigationDemoRegion::initMaze(std::vector<IntPair> nonBlockablePositions) {

	initAllNavigationGridValues(*navGrid, NavigationGridData{ 1, 0 });

	//block grids for maze
	srand((unsigned int)time(NULL));
	for (unsigned int i = 0; i < navGrid->getArraySizeX(); i++) {
		for (unsigned int j = 0; j < navGrid->getArraySizeY(); j++) {
			if (! (rand() % 5)) {//1 in 5 are blocked
				bool blockable = true;
				//determine if the square is non-blockable
				for each (IntPair nonBlockable in nonBlockablePositions) {
					if (nonBlockable.first == i && nonBlockable.second == j) {
						blockable = false;
					}
				}
				//only block blockable grids	
				if (blockable) {
					(*navGrid)[i][j]->weight = BLOCKED_GRID_WEIGHT;
				}
			}
		}
	}

	//fill visual grid
	for (unsigned int i = 0; i < navGrid->getArraySizeX(); i++) {
		for (unsigned int j = 0; j < navGrid->getArraySizeY(); j++) {
			//create sprite in correct position
			sf::Sprite* gridSquare = new sf::Sprite(*gridTexture);
			const float gridOriginOffsetX = gridSquare->getLocalBounds().width / 2;
			const float gridOriginOffsetY = gridSquare->getLocalBounds().height / 2;
			gridSquare->setOrigin(gridOriginOffsetX, gridOriginOffsetY); //set origin to center of grid
			gridSquare->setScale(VISUAL_GRID_SCALE, VISUAL_GRID_SCALE);
			gridSquare->move(i * gridSquare->getLocalBounds().width + gridOriginOffsetX, j * gridSquare->getLocalBounds().height + gridOriginOffsetY);

			//shade blocked grids
			bool blocked = (*navGrid)[i][j]->weight == BLOCKED_GRID_WEIGHT;
			if (blocked) {
				gridSquare->setColor(sf::Color::Red);
			}

			//add grids to storage
			(*visualNavigationGrid)[i][j] = gridSquare;

			//ensure grids are drawn
			setDrawable(true, gridSquare);
		}
	}
}

/// <summary>
/// Calculates the game world position of a grid coordinate.
/// </summary>
/// <param name="gridCoordinate">The grid coordinate.</param>
/// <returns>The 2D position of the grid coordinate's top left corner in the game world's coordinate system.</returns>
sf::Vector2f NavigationDemoRegion::gridCoordToWorldCoord(const IntPair & gridCoordinate) {
	//for the demo we can assume that the grid starts at the origin
	sf::Vector2f gridOrigin(0, 0);

	int gridSquareWidth = gridTexture->getSize().x;
	int gridSquareHeight = gridTexture->getSize().y;
	sf::Vector2f offsetOrigin(0 + (gridSquareWidth / 2.0f), 0 + (gridSquareHeight / 2.0f));// bad hack

	// use size of grid squares and grid origin position to calculate world coordinate
	return sf::Vector2f(gridCoordinate.first * gridSquareWidth + offsetOrigin.x, 
						gridCoordinate.second * gridSquareHeight + offsetOrigin.y);
}


/// <summary>
/// Determine what grid square a game world coordinate lies in. 
/// </summary>
/// <param name="worldCoordinate">The world coordinate.</param>
/// <returns>The coordinate of the grid that the game world coordinate lies in.</returns>
IntPair NavigationDemoRegion::worldCoordToGridCoord(const sf::Vector2f & worldCoordinate) {
	//for the demo we can assume that the grid starts at the origin
	sf::Vector2f gridOrigin(0, 0);

	//offset origin to produce coordinate in center of grid square
	unsigned int gridSquareWidth = gridTexture->getSize().x;
	unsigned int gridSquareHeight = gridTexture->getSize().y;
	sf::Vector2f offsetOrigin(0.0f + ((float)gridSquareWidth / 2.0f), 0.0f + ((float)gridSquareHeight / 2.0f));// bad hack

	// use size of grid squares and grid origin position to calculate grid coordinate
	return IntPair((int)((worldCoordinate.x - offsetOrigin.x) / gridSquareWidth),
				   (int)((worldCoordinate.y - offsetOrigin.y) / gridSquareHeight));
}

/// <summary>
/// Moves the sprite towards point.
/// </summary>
/// <param name="sprite">The sprite.</param>
/// <param name="destination">The destination.</param>
/// <param name="distance">The distance.</param>
void NavigationDemoRegion::moveSpriteTowardsPoint(sf::Sprite * sprite, sf::Vector2f destination, float distance) {
	
	distance = 0.1f; //TODO: figure out why this isn't ever big enough

	//angle between the sprite and the destination
	const float angleToDestination = atan2(destination.y - sprite->getPosition().y, destination.x - sprite->getPosition().x);
	const float angleToDestinationDeg = angleToDestination * (180.0f / (float)M_PI) + 90.0f;// This is offset by 90 degrees. This is because this value is only used to rotate the sprite. 
																				  //The sprite is currently rotated at -90 from the games coordinate system
	
	//angle sprite to point at destination 
	sprite->setRotation(angleToDestinationDeg);

	//move sprite by distance towards its destination
	const sf::Vector2f spriteMovement(cosf(angleToDestination) * distance, sinf(angleToDestination) * distance);
	sprite->move(spriteMovement);
	volatile auto sx = sprite->getPosition().x;
	volatile auto sy = sprite->getPosition().y;
}

/// <summary>
/// Moves a single sprite along a navigation path.
/// </summary>
/// <param name="sprite">The sprite.</param>
/// <param name="path">The path.</param>
/// <param name="msPassed">The time passed in ms since the last movement.</param>
/// <param name="speed">The speed of the sprite in pixels per ms.</param>
void NavigationDemoRegion::moveSpriteAlongPath(sf::Sprite * sprite, std::list<IntPair>* path, sf::Int64 msPassed, float speed) {
	//determine if sprite has reached first point in path
	if (path->size() >= 1) {

		//move sprite a step towards the next point in the path
		float actualMovement = speed / msPassed;
		auto nextGrid = path->front();
		sf::Vector2f targetPosition = ((*visualNavigationGrid)[nextGrid.first][nextGrid.second])->getPosition();
		moveSpriteTowardsPoint(sprite, targetPosition, actualMovement);
		
		//check if the sprite is close enough to its destination
		auto spriteCurrentPosition = sprite->getPosition();
		auto destination = targetPosition;
		const float acceptableDistance = 0.2f;
		if(abs(destination.x - spriteCurrentPosition.x) < acceptableDistance && abs(destination.y - spriteCurrentPosition.y) < acceptableDistance) {// this is a bad way, but quick to code and run
			path->pop_front();
		}
	}
}



