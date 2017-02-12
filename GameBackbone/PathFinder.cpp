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

	typedef std::pair<sf::Vector3i, int> hexValuePair;

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

		//cost to move to a point from the start
		std::map<sf::Vector3i, int>* score = new std::map<sf::Vector3i, int>();
		score->insert(hexValuePair(startPoint, 0));

		// For each node, which node it can most efficiently be reached from.
		// If a node can be reached from many nodes, cameFrom will eventually contain the
		// most efficient previous step.
		std::map<sf::Vector3i, sf::Vector3i>* cameFrom = new std::map<sf::Vector3i, sf::Vector3i>();

		//search for path
		while (!openSet->empty()) {
			//check current hex
			sf::Vector3i current = chooseNextHex(pathRequest, openSet);
			if (current == endPoint) {
				//TODO: (pathFind) reconstruct path, free memory, and return
			}
			openSet->erase(openSet->find(current));//TODO: (pathFind) Find a better way to remove an item from the open set.
			closedSet->insert(current);

			//find neighbors
			std::vector<sf::Vector3i> neighbors = getNeighbors(current);

			for each (sf::Vector3i neighbor in neighbors) {
				if (closedSet->find(neighbor) != closedSet->end()) {
					continue;// no need to evaluate already evaluated nodes
				}
				//TODO: (pathFind) calculate the tentative score
				int tentativeScore = 0;

				//discover new node
				if (openSet->find(neighbor) == openSet->end()) {
					openSet->insert(neighbor);
				} else if (tentativeScore >= score->at(neighbor)) {
					continue; // found a worse path
				}

				//update or insert values for node
				cameFrom->insert_or_assign(neighbor, current);
				score->insert_or_assign(neighbor, tentativeScore);
			}

		}
		
		//free memory
		delete closedSet;
		delete openSet;
		delete cameFrom;
		delete score;
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

/// <summary>
/// Gets the neighbors of a hex.
/// </summary>
/// <param name="hexCoordinate">The coordinate of the hex node to get neighbors for</param>
/// <returns>Vector containing all valid neighbors of the hex node at the passed coordinate</returns>
std::vector<sf::Vector3i> Pathfinder::getNeighbors(const sf::Vector3i & hexCoordinate) {

	//find the bounds of the active navigation grid
	int maxX = navigationGrid->getArraySizeX();
	int maxY = navigationGrid->getArraySizeY();
	int maxZ = navigationGrid->getArraySizeZ();
	std::vector<sf::Vector3i> neighbors;

	bool xUp = (hexCoordinate.x + 1 < maxX);
	bool xDown = (hexCoordinate.x - 1 >= 0);
	bool yUp = (hexCoordinate.y + 1 < maxY);
	bool yDown = (hexCoordinate.y - 1 >= 0);
	bool zUP = (hexCoordinate.z + 1 < maxZ);
	bool zDown = (hexCoordinate.z - 1 >= 0);

	if (xUp) {//x
		neighbors.push_back(sf::Vector3i(hexCoordinate.x + 1, hexCoordinate.y, hexCoordinate.z));
		if (yUp) { //x + y
			neighbors.push_back(sf::Vector3i(hexCoordinate.x + 1, hexCoordinate.y + 1, hexCoordinate.z));
			if (zUP) { //x + y + z
				neighbors.push_back(sf::Vector3i(hexCoordinate.x + 1, hexCoordinate.y + 1, hexCoordinate.z + 1));
			}
			if (zDown) {// x + y + z
				neighbors.push_back(sf::Vector3i(hexCoordinate.x + 1, hexCoordinate.y + 1, hexCoordinate.z - 1));
			}
		}
		if (yDown) {// x + y
			neighbors.push_back(sf::Vector3i(hexCoordinate.x + 1, hexCoordinate.y - 1, hexCoordinate.z));
			if (zUP) {//X + y + z
				neighbors.push_back(sf::Vector3i(hexCoordinate.x + 1, hexCoordinate.y - 1, hexCoordinate.z + 1));
			}
			if (zDown) {// X + y + z
				neighbors.push_back(sf::Vector3i(hexCoordinate.x + 1, hexCoordinate.y - 1, hexCoordinate.z - 1));
			}
		}
	}
	if (xDown) {// x
		neighbors.push_back(sf::Vector3i(hexCoordinate.x - 1, hexCoordinate.y, hexCoordinate.z));
		if (yUp) {// x + y
			neighbors.push_back(sf::Vector3i(hexCoordinate.x - 1, hexCoordinate.y + 1, hexCoordinate.z));
			if (zUP) { // x + y + z
				neighbors.push_back(sf::Vector3i(hexCoordinate.x - 1, hexCoordinate.y + 1, hexCoordinate.z + 1));
			}
			if (zDown) {//X + y + z
				neighbors.push_back(sf::Vector3i(hexCoordinate.x - 1, hexCoordinate.y + 1, hexCoordinate.z - 1));
			}
		}
		if (yDown) {//x + y
			neighbors.push_back(sf::Vector3i(hexCoordinate.x - 1, hexCoordinate.y - 1, hexCoordinate.z));
			if (zUP) {// x + y + z
				neighbors.push_back(sf::Vector3i(hexCoordinate.x - 1, hexCoordinate.y - 1, hexCoordinate.z + 1));
			}
			if (zDown) {//X + y + z
				neighbors.push_back(sf::Vector3i(hexCoordinate.x - 1, hexCoordinate.y - 1, hexCoordinate.z - 1));
			}
		}
	}

	if (yUp) { //y
		neighbors.push_back(sf::Vector3i(hexCoordinate.x, hexCoordinate.y + 1, hexCoordinate.z));
		if (zUP) {// y + z
			neighbors.push_back(sf::Vector3i(hexCoordinate.x, hexCoordinate.y + 1, hexCoordinate.z + 1));
		}
		if (zDown) {// y + z
			neighbors.push_back(sf::Vector3i(hexCoordinate.x, hexCoordinate.y + 1, hexCoordinate.z - 1));
		}
	}
	if (yDown) {// y
		neighbors.push_back(sf::Vector3i(hexCoordinate.x, hexCoordinate.y - 1, hexCoordinate.z));
		if (zUP) {// y + z
			neighbors.push_back(sf::Vector3i(hexCoordinate.x, hexCoordinate.y - 1, hexCoordinate.z + 1));
		}
		if (zDown) {// y + z
			neighbors.push_back(sf::Vector3i(hexCoordinate.x, hexCoordinate.y - 1, hexCoordinate.z - 1));
		}
	}
	
	if (zUP) { // z
		neighbors.push_back(sf::Vector3i(hexCoordinate.x, hexCoordinate.y, hexCoordinate.z + 1));
	}
	if (zDown) { //z
		neighbors.push_back(sf::Vector3i(hexCoordinate.x, hexCoordinate.y, hexCoordinate.z - 1));
	}

	return neighbors;

}


