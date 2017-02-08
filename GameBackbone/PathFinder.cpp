#include "PathFinder.h"


///<summary>Creates a PathFinder with a null navigation grid</summary>
Pathfinder::Pathfinder() : Pathfinder(nullptr){}

///<summary>creates a PathFinder with an assigned navigation grid</summary>
///<param name = "navigationGrid"> Three dimensional grid to be used when path-finding</param>
Pathfinder::Pathfinder(NavigationGrid * navigationGrid) {
	this->navigationGrid = navigationGrid;
}

