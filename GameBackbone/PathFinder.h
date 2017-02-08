#pragma once
#include "Array3D.h"
#include "NavigationHexData.h"
#include "PathRequest.h"

#include<SFML/System/Vector3.hpp>

#include<vector>

typedef Array3D<NavigationHexData> NavigationGrid;

class Pathfinder {
public:
	//ctr / dtr
	Pathfinder();
	explicit Pathfinder(NavigationGrid* navigationGrid);
	
	~Pathfinder();

	//getters / setters
	
		//setters
	void setNavigationGrid(NavigationGrid* navigationGrid);

		//getters
	NavigationGrid* getNavigationGrid();

	//operations
	std::vector<std::vector<sf::Vector3i>> pathFind(std::vector<PathRequest> pathRequests);

private:

	//data
	NavigationGrid* navigationGrid;

	//deleted copy and assignment
	Pathfinder(const Pathfinder&) = delete;
	Pathfinder(Pathfinder&&) = delete;
	Pathfinder& operator=(const Pathfinder&) = delete;
	Pathfinder& operator=(Pathfinder&&) = delete;
};

