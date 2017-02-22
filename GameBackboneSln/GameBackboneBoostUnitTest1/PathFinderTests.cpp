#include "stdafx.h"

#include <PathFinder.h>

BOOST_AUTO_TEST_CASE(Pathfinder_default_ctr_test) {

	Pathfinder* pathfinder = new Pathfinder();

	NavigationGrid* navGrid = pathfinder->getNavigationGrid();
	BOOST_CHECK(nullptr == navGrid);

	delete pathfinder;
}

BOOST_AUTO_TEST_CASE(Pathfinder_navigationGrid_ctr_test) {
	NavigationGrid navGrid(10);
	Pathfinder* pathfinder = new Pathfinder(&navGrid);

	//ensure the grid is not copied;
	BOOST_CHECK_EQUAL(&navGrid, pathfinder->getNavigationGrid());

	delete pathfinder;
}


BOOST_AUTO_TEST_CASE(Pathfinder_setNavigationGrid) {
	NavigationGrid navGrid(10);
	Pathfinder* pathfinder = new Pathfinder();

	//ensure the grid is not copied;
	pathfinder->setNavigationGrid(&navGrid);
	BOOST_CHECK_EQUAL(&navGrid, pathfinder->getNavigationGrid());

	delete pathfinder;
}

BOOST_AUTO_TEST_CASE(Pathfinder_pathFind_one_simple_path_no_sol) {
	const int CUBE_DIM = 3;
	NavigationGrid navGrid(CUBE_DIM);
	Pathfinder* pathfinder = new Pathfinder(&navGrid);

	//block all hexes
	navGrid.initAllValues(NavigationHexData{ BLOCKED_HEX_WEIGHT, 0 });

	//Set value at the midPoint
	sf::Vector3i startPoint(1, 1, 1);
	navGrid.setValueAt(startPoint.x, startPoint.y, startPoint.z, NavigationHexData{0, 0});

	//create request
	PathRequest pathRequest{ startPoint, sf::Vector3i(2,2,2), 1, 0 };
	std::vector<PathRequest> pathRequests;
	pathRequests.push_back(pathRequest);


	//create return value
	std::vector<std::list<sf::Vector3i>> pathsReturn;
	pathsReturn.resize(pathRequests.size());
	//find the path
	pathfinder->pathFind(pathRequests, &pathsReturn);

	//ensure the returned path is empty
	BOOST_CHECK(pathsReturn[0].size() == 0);

	delete pathfinder;
}


BOOST_AUTO_TEST_CASE(Pathfinder_pathFind_one_simple_path_no_blocker) {
	const int CUBE_DIM = 3;
	NavigationGrid navGrid(CUBE_DIM);
	Pathfinder* pathfinder = new Pathfinder(&navGrid);

	//ensure all hexes are clear
	navGrid.initAllValues(NavigationHexData{ 0,0 });

	//create request
	sf::Vector3i startPoint(1, 1, 1);
	PathRequest pathRequest{ startPoint, sf::Vector3i(2,2,2), 1, 0 };
	std::vector<PathRequest> pathRequests;
	pathRequests.push_back(pathRequest);


	//create return value
	std::vector<std::list<sf::Vector3i>> pathsReturn;
	pathsReturn.resize(pathRequests.size());
	//find the path
	pathfinder->pathFind(pathRequests, &pathsReturn);

	//ensure the returned path is empty
	BOOST_CHECK(pathsReturn[0].size() > 0);

	delete pathfinder;
}