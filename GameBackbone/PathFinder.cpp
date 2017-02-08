#include "PathFinder.h"

//ctr / dtr

///<summary>Creates a PathFinder with a null navigation grid</summary>
Pathfinder::Pathfinder() : Pathfinder(nullptr){}

///<summary>creates a PathFinder with an assigned navigation grid</summary>
///<param name = "navigationGrid"> Three dimensional grid to be used when path-finding</param>
Pathfinder::Pathfinder(NavigationGrid * navigationGrid) {
	this->navigationGrid = navigationGrid;
}


//getters / setters

	//setters

/// <summary>
/// Sets the navigation grid.
/// </summary>
/// <param name="navigationGrid">The navigation grid.</param>
void Pathfinder::setNavigationGrid(NavigationGrid * navigationGrid) {
	this->navigationGrid = navigationGrid;
}

	//setters

/// <summary>
/// Gets the navigation grid.
/// </summary>
/// <returns>NavigationGrid pointer</returns>
NavigationGrid * Pathfinder::getNavigationGrid() {
	return navigationGrid;
}


