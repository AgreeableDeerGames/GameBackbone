#include "stdafx.h"
#include "PathFinder.h"
#include "UtilMath.h"

#include <set>
#include <queue>
#include <map>
#include <limits.h>
#include <list>

//ctr / dtr

/// <summary> Creates a PathFinder with a null navigation grid. </summary>
Pathfinder::Pathfinder() : Pathfinder(nullptr){}

/// <summary> Creates a PathFinder with an assigned navigation grid. </summary>
/// <param name = "navigationGrid"> Three dimensional grid to be used when path-finding. </param>
Pathfinder::Pathfinder(NavigationGrid * navigationGrid) {
	this->navigationGrid = navigationGrid;
}

/// <summary>
/// Finalizes an instance of the <see cref="Pathfinder"/> class.
/// </summary>
Pathfinder::~Pathfinder() {
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
/// <param name="returnedPaths">vector containing the found path for each PathRequest. The path is found at the same index as its corresponding request.</param>
void Pathfinder::pathFind(const std::vector<PathRequest>& pathRequests, std::vector<std::list<IntPair>> * const returnedPaths) {

	typedef std::pair<IntPair, int> GridValuePair;

	for (unsigned int i = 0; i < pathRequests.size(); i++) {

		PathRequest pathRequest = pathRequests[i];

		//grid address of start and end points
		IntPair startPoint = pathRequest.start;
		IntPair endPoint = pathRequest.end;

		// the set of nodes already evaluated
		std::set<IntPair>* closedSet = new std::set<IntPair>();

		//the set of currently discovered nodes that are already evaluated.
		std::set<IntPair>* openSet = new std::set<IntPair>();
		openSet->insert(startPoint);

		//cost to move to a point from the start
		std::map<IntPair, int>* score = new std::map<IntPair, int>();
		score->insert(GridValuePair(startPoint, 0));

		// For each node, which node it can most efficiently be reached from.
		// If a node can be reached from many nodes, cameFrom will eventually contain the
		// most efficient previous step.
		std::map<IntPair, IntPair>* cameFrom = new std::map<IntPair, IntPair>();

		//search for path
		while (!openSet->empty()) {
			//check current hex
			IntPair current = chooseNextHex(pathRequest, openSet);
			if (current == endPoint) {
				//reconstruct path, and add to output vector

				std::list<IntPair> inOrderPath = reconstructPath(endPoint, cameFrom);
				(*returnedPaths)[i] = inOrderPath;

				//free memory
				delete closedSet;
				delete openSet;
				delete cameFrom;
				delete score;
				return;
			}
			openSet->erase(openSet->find(current));
			closedSet->insert(current);

			//find neighbors
			std::vector<IntPair> neighbors = getNeighbors(current);

			for each (IntPair neighbor in neighbors) {
				if (closedSet->find(neighbor) != closedSet->end()) {
					continue;// no need to evaluate already evaluated nodes
				}
				//cost of reaching neighbor using current path
				int transitionCost = (navigationGrid->getValueAt(current.first, current.second).weight + navigationGrid->getValueAt(neighbor.first, neighbor.second).weight) / 2;
				int tentativeScore = score->at(current) + transitionCost;

				//discover new node
				if (openSet->find(neighbor) == openSet->end()) {
					//add blocked to closed set and unblocked to open set
					if (navigationGrid->getValueAt(neighbor.first, neighbor.second).weight >= BLOCKED_HEX_WEIGHT) {
						closedSet->insert(neighbor);
						continue;
					} else {
						openSet->insert(neighbor);
					}
				} else if (tentativeScore >= score->at(neighbor)) {
					continue; // found a worse path
				}

				//update or insert values for node
				cameFrom->insert_or_assign(neighbor, current);
				score->insert_or_assign(neighbor, tentativeScore);
			}
		}
		
		// no path found. Place empty path for this request.
		(*returnedPaths)[i] = std::list<IntPair>();

		//free memory
		delete closedSet;
		delete openSet;
		delete cameFrom;
		delete score;
	}
}


// private helper functions 

/// <summary>
/// Chooses the next Hex-grid for pathFind based on the pathRequest and the available hexes.
/// </summary>
/// <param name="pathRequest">The path request.</param>
/// <param name="availableHexes">The available hexes.</param>
/// <returns>coordinates of the best available hex grid for the passed pathRequest.</returns>
IntPair Pathfinder::chooseNextHex(const PathRequest & pathRequest, const std::set<IntPair>* const availableHexes) {

	unsigned int shortestDistance = UINT_MAX;
	IntPair const * bestHex = nullptr;

	for each (const IntPair hex in *availableHexes) {
		unsigned int hexDistance = SquaredDist2d(hex, pathRequest.end);
		if ( hexDistance < shortestDistance) {
			shortestDistance = hexDistance;
			bestHex = &hex;
		}
	}

	return *bestHex;
}

/// <summary>
/// Gets the neighbors of a hex.
/// </summary>
/// <param name="hexCoordinate">The coordinate of the hex node to get neighbors for</param>
/// <returns>Vector containing all valid neighbors of the hex node at the passed coordinate</returns>
std::vector<IntPair> Pathfinder::getNeighbors(const IntPair & hexCoordinate) {

	//find the bounds of the active navigation grid
	int maxX = navigationGrid->getArraySizeX();
	int maxY = navigationGrid->getArraySizeY();
	std::vector<IntPair> neighbors;

	bool xUp = (hexCoordinate.first + 1 < maxX);
	bool xDown = (hexCoordinate.first - 1 >= 0);
	bool yUp = (hexCoordinate.second + 1 < maxY);
	bool yDown = (hexCoordinate.second - 1 >= 0);

	if (xUp) {
		neighbors.push_back(IntPair(hexCoordinate.first + 1, hexCoordinate.second));
	}
	if (xDown) {
		neighbors.push_back(IntPair(hexCoordinate.first - 1, hexCoordinate.second));
	}
	if (yUp) {
		neighbors.push_back(IntPair(hexCoordinate.first, hexCoordinate.second + 1));
	}
	if (yDown) {
		neighbors.push_back(IntPair(hexCoordinate.first, hexCoordinate.second - 1));
	}
	

	return neighbors;

}

/// <summary>
/// Reconstructs the path of hexes to the endpoint.
/// </summary>
/// <param name="endPoint">The end point.</param>
/// <param name="cameFrom">A map containing each hex's predecessor from.</param>
/// <returns>A vector of hex indexes representing an in-order path to the passed endPoint.</returns>
std::list<IntPair> Pathfinder::reconstructPath(const IntPair & endPoint, std::map<IntPair, IntPair> const * const cameFrom) {

	std::list<IntPair> inOrderPath;

	IntPair const * lastHex = &endPoint;

	//add hexes until the beginning (hex that did not come from anywhere) is found
	// do not add first hex. the path-finding object is already there.
	auto foundHex = cameFrom->find(*lastHex);
	while (foundHex != cameFrom->end()) {
		inOrderPath.push_front(foundHex->first);
		lastHex = &foundHex->second;
		foundHex = cameFrom->find(*lastHex);
	}
	return inOrderPath;
}


