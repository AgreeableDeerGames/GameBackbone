#include "stdafx.h"
#include <iostream>

#define _USE_MATH_DEFINES

#include "NavigationDemoRegion.h"

#include <SFML/Graphics.hpp>

#include <string>
#include <math.h>


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

	initMaze();

	//fill visual grid
	for (unsigned int i = 0; i < navGrid->getArraySizeX(); i++) {
		for (unsigned int j = 0; j < navGrid->getArraySizeY(); j++) {
			//create sprite in correct position
			sf::Sprite* gridSquare = new sf::Sprite(*gridTexture);
			gridSquare->setScale(VISUAL_GRID_SCALE, VISUAL_GRID_SCALE);
			gridSquare->move(i * gridSquare->getLocalBounds().width, j * gridSquare->getLocalBounds().height);

			//shade blocked grids
			bool blocked = (*navGrid)[i][j].weight == BLOCKED_GRID_WEIGHT;
			if (blocked) {
				gridSquare->setColor(sf::Color::Red);
			}

			//add grids to storage
			(*visualNavigationGrid)[i][j] = gridSquare;

			//ensure grids are drawn
			setDrawable(true, gridSquare);
		}
	}



	//init navigators

		//create navigators and add to respective arrays
	sf::Sprite* navigator1 = new sf::Sprite(*navigatorTexture);
	sf::Sprite* navigator2 = new sf::Sprite(*navigatorTexture);
	navigators.push_back(navigator1);
	navigators.push_back(navigator2);
	navigator2->setColor(sf::Color::Green);
	navigator1->setColor(sf::Color::Blue);
	setDrawable(true, navigator1);
	setDrawable(true, navigator2);


	//set rotation point of navigators
	for each (sf::Sprite* navigator in navigators) {
		const sf::IntRect * const  textureRect = &navigator->getTextureRect();
		sf::Vector2f newOrigin(textureRect->width / 2, textureRect->height / 2);
		navigator->setOrigin(newOrigin);
	}

		//position navigators
	IntPair navigator1StartingGrid(0, 0);
	IntPair navigator2StartingGrid(3, 0);

	const sf::Vector2f navigator1StartingPos = gridCoordToWorldCoord(navigator1StartingGrid);
	const sf::Vector2f navigator2StartingPos = gridCoordToWorldCoord(navigator2StartingGrid);
	navigator1->setPosition(navigator1StartingPos);
	navigator2->setPosition(navigator2StartingPos);



	//Path-find from starting positions to end positions
	//create request
	PathRequest pathRequest{ navigator1StartingGrid, IntPair(2,2), 3, 0 };
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

	/*std::cout << "N1 start: (0,0)\tN1 current: " << worldCoordToGridCoord(navigators[0]->getPosition()).first << "," << worldCoordToGridCoord(navigators[0]->getPosition()).second << std::endl;
	std::cout << "N1 world pos: " << navigators[0]->getPosition().x << "," << navigators[0]->getPosition().y << std::endl;

	std::cout << "N2 start: (3,0)\tN2 current: " << worldCoordToGridCoord(navigators[1]->getPosition()).first << "," << worldCoordToGridCoord(navigators[1]->getPosition()).second << std::endl;
	std::cout << "N2 world pos: " << navigators[1]->getPosition().x << "," << navigators[1]->getPosition().y << std::endl;
	*/


	//sf::Sprite* spriteToMove = navigators[0];

	//moveSpriteTowardsPoint(spriteToMove, sf::Vector2f(spriteToMove->getPosition().x + 1, spriteToMove->getPosition().y + 1), 0.01);
	
	//std::cout << "x: " << spriteToMove->getPosition().x << "\tY: " << spriteToMove->getPosition().y << std::endl;
	/*for (size_t i = 0; i < navigators.size(); i++) {
		int msPassed = currentTime.asMilliseconds() - lastUpdateTime.asMicroseconds();
		moveSpriteAlongPath(navigators[i], &(pathsReturn[i]), msPassed, 0.01f);
	}*/

	lastUpdateTime = currentTime;
}

/// <summary>
/// Initializes the maze that the navigators will use.
/// </summary>
void NavigationDemoRegion::initMaze() {
	/*

	representation of the maze
	Key:
	0: clear
	1: blocked

	0	0	1	0	0	0
	0	0	1	0	0	0
	0	1	1	0	0	0
	0	0	1	1	1	0
	0	0	1	0	0	0
	0	0	1	0	0	0
	0	0	0	0	0	0

	*/

	//block grids for maze
	(*navGrid)[2][0] = NavigationGridData{ BLOCKED_GRID_WEIGHT, 0 };
	(*navGrid)[2][1] = NavigationGridData{ BLOCKED_GRID_WEIGHT, 0 };
	(*navGrid)[2][2] = NavigationGridData{ BLOCKED_GRID_WEIGHT, 0 };
	(*navGrid)[2][3] = NavigationGridData{ BLOCKED_GRID_WEIGHT, 0 };
	(*navGrid)[2][4] = NavigationGridData{ BLOCKED_GRID_WEIGHT, 0 };
	(*navGrid)[2][5] = NavigationGridData{ BLOCKED_GRID_WEIGHT, 0 };
	(*navGrid)[1][2] = NavigationGridData{ BLOCKED_GRID_WEIGHT, 0 };
	(*navGrid)[1][2] = NavigationGridData{ BLOCKED_GRID_WEIGHT, 0 };
	(*navGrid)[3][3] = NavigationGridData{ BLOCKED_GRID_WEIGHT, 0 };
	(*navGrid)[4][3] = NavigationGridData{ BLOCKED_GRID_WEIGHT, 0 };
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
	sf::Vector2f offsetOrigin(0 + (gridSquareWidth / 2), 0 + (gridSquareHeight / 2));// bad hack

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
	int gridSquareWidth = gridTexture->getSize().x;
	int gridSquareHeight = gridTexture->getSize().y;
	sf::Vector2f offsetOrigin(0 + (gridSquareWidth / 2), 0 + (gridSquareHeight / 2));// bad hack

	// use size of grid squares and grid origin position to calculate grid coordinate
	return IntPair((int)(worldCoordinate.x - offsetOrigin.x / gridSquareWidth),
				   (int)(worldCoordinate.y - offsetOrigin.y / gridSquareHeight));
}

/// <summary>
/// Moves the sprite towards point.
/// </summary>
/// <param name="sprite">The sprite.</param>
/// <param name="destination">The destination.</param>
/// <param name="distance">The distance.</param>
void NavigationDemoRegion::moveSpriteTowardsPoint(sf::Sprite * sprite, sf::Vector2f destination, float distance) {

	//angle between the sprite and the destination
	const float angleToDestination = atan2(destination.y - sprite->getPosition().y, destination.x - sprite->getPosition().x);
	const float angleToDestinationDeg = angleToDestination * (180.0f / M_PI) + 90;// This is offset by 90 degrees. This is because this value is only used to rotate the sprite. 
																				  //The sprite is currently rotated at -90 from the games coordinate system
	
	//angle sprite to point at destination 
	sprite->setRotation(angleToDestinationDeg);

	//move sprite by distance towards its destination
	const sf::Vector2f spriteMovement(cosf(angleToDestination) * distance, sinf(angleToDestination) * distance);
	sprite->move(spriteMovement);
}

/// <summary>
/// Moves a single sprite along a navigation path.
/// </summary>
/// <param name="sprite">The sprite.</param>
/// <param name="path">The path.</param>
/// <param name="msPassed">The time passed in ms since the last movement.</param>
/// <param name="speed">The speed of the sprite in pixels per ms.</param>
void NavigationDemoRegion::moveSpriteAlongPath(sf::Sprite * sprite, std::list<IntPair>* path, unsigned int msPassed, float speed) {
	//determine if sprite has reached first point in path
	if (path->size() >= 1) {
		//move sprite a step towards the next point in the path
		float actualMovement = speed / msPassed;
		sf::Vector2f targetPosition = gridCoordToWorldCoord(path->front());
		moveSpriteTowardsPoint(sprite, targetPosition, actualMovement);

		if (worldCoordToGridCoord(sprite->getPosition()) == path->front()) { // this is a bad way, but quick to code and run
			path->pop_front();
		}
	}
}



