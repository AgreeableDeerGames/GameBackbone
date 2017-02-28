#include "stdafx.h"
#include "NavigationDemoRegion.h"

#include <SFML/Graphics.hpp>

#include <string>


NavigationDemoRegion::NavigationDemoRegion() {
	//init storage
	navGrid = new NavigationGrid(NAV_GRID_DIM);
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
	sf::Sprite* navigator1 = new sf::Sprite(*navigatorTexture);
	sf::Sprite* navigator2 = new sf::Sprite(*navigatorTexture);
	navigators.push_back(navigator1);
	navigators.push_back(navigator2);
	navigator2->setColor(sf::Color::Green);
	navigator1->setColor(sf::Color::Blue);
	setDrawable(true, navigator1);
	setDrawable(true, navigator2);

	navigator1->setPosition((*visualNavigationGrid)[0][0]->getPosition());
	navigator2->setPosition((*visualNavigationGrid)[3][0]->getPosition());


	//Path-find from starting positions to end positions

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
void NavigationDemoRegion::behave() {
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



