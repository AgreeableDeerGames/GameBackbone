#include "PathFinder.h"

#include <set>
#include <queue>
#include <map>

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

/// <summary>
/// Creates an unblocked path of adjacent hexes to for each path request.
/// </summary>
/// <param name="pathRequests">vector containing the requirements for each path.</param>
/// <returns>Pointer to a vector containing the found path for each PathRequest. The path is found at the same index as its corresponding request. 
/// Impossible path requests will result in an empty path.</returns>
std::vector<std::vector<sf::Vector3i>>* Pathfinder::pathFind(const std::vector<PathRequest>& pathRequests) {

	//TODO: (pathFind) find a way to move memory allocations out of the loop. They are bad for performance.

	for each (PathRequest pathRequest in pathRequests) {

		//grid address of start and end points
		sf::Vector3i startPoint = pathRequest.start;
		sf::Vector3i endPoint = pathRequest.end;

		// the set of nodes already evaluated
		std::set<sf::Vector3i>* closedSet = new std::set<sf::Vector3i>();

		//the set of currently discovered nodes that are already evaluated.
		std::set<sf::Vector3i>* openSet = new std::set<sf::Vector3i>();
		openSet->insert(startPoint);


		// For each node, which node it can most efficiently be reached from.
		// If a node can be reached from many nodes, cameFrom will eventually contain the
		// most efficient previous step.
		std::map<sf::Vector3i, sf::Vector3i>* cameFrom = new std::map<sf::Vector3i, sf::Vector3i>();

		
		while (!openSet->empty()) {
			sf::Vector3i current = chooseNextHex(pathRequest, openSet);
			if (current == endPoint) {
				//TODO: (pathFind) reconstruct path, free memory, and return
			}
			openSet->erase(openSet->find(current));//TODO: (pathFind) Find a better way to remove an item from the open set.
			closedSet->insert(current);
		}
		
		//free memory
		delete closedSet;
		delete openSet;
	}

	

	return nullptr;//TODO: (pathFind) fill stub
}


// private helper functions 

/// <summary>
/// Chooses the next Hex-grid for pathFind based on the pathRequest and the available hexes.
/// </summary>
/// <param name="pathRequest">The path request.</param>
/// <param name="availableHexes">The available hexes.</param>
/// <returns>coordinates of the best available hex grid for the passed pathRequest.</returns>
sf::Vector3i Pathfinder::chooseNextHex(const PathRequest & pathRequest, const std::set<sf::Vector3i>* const availableHexes) {
	return sf::Vector3i();//TODO: (chooseNextHex) fill stub
}


