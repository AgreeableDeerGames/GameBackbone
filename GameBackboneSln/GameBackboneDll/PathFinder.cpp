#include "stdafx.h"
#include "PathFinder.h"
#include "UtilMath.h"

#include <set>
#include <queue>
#include <map>
#include <limits.h>
#include <list>

using namespace GB;

//ctr / dtr

/// <summary> Creates a PathFinder with a null navigation grid. </summary>
Pathfinder::Pathfinder() : Pathfinder(nullptr) {}

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
/// Creates an unblocked path of adjacent grid squares to for each path request.
/// </summary>
/// <param name="pathRequests">vector containing the requirements for each path.</param>
/// <param name="returnedPaths">vector containing the found path for each PathRequest. The path is found at the same index as its corresponding request.</param>
void Pathfinder::pathFind(const std::vector<PathRequest>& pathRequests, std::vector<std::list<IntPair>> * const returnedPaths) {

	typedef std::pair<IntPair, int> GridValuePair;

	//ensure that returned paths is big enough to store all results
	returnedPaths->resize(pathRequests.size());

	//find result for each path request
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
		(*returnedPaths)[i] = std::list<IntPair>(); //initialize path as empty
		while (!openSet->empty()) {
			//check current grid square
			IntPair current = chooseNextGridSquare(pathRequest, openSet);
			if (current == endPoint) {
				//reconstruct path, and add to output vector

				std::list<IntPair> inOrderPath = reconstructPath(endPoint, cameFrom);
				(*returnedPaths)[i] = inOrderPath;
				break;
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
				int transitionCost = (navigationGrid->at(current.first, current.second)->weight + navigationGrid->at(neighbor.first, neighbor.second)->weight) / 2;
				int tentativeScore = score->at(current) + transitionCost;

				//discover new node
				if (openSet->find(neighbor) == openSet->end()) {
					//add blocked to closed set and unblocked to open set
					if (navigationGrid->at(neighbor.first, neighbor.second)->weight >= BLOCKED_GRID_WEIGHT) {
						closedSet->insert(neighbor);
						continue;
					}
					else {
						openSet->insert(neighbor);
					}
				}
				else if (tentativeScore >= score->at(neighbor)) {
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
}


// private helper functions 

/// <summary>
/// Chooses the next grid square for pathFind based on the pathRequest and the available grid squares.
/// </summary>
/// <param name="pathRequest">The path request.</param>
/// <param name="gridSquares">The available gridSquares.</param>
/// <returns>coordinates of the best available grid square for the passed pathRequest.</returns>
IntPair Pathfinder::chooseNextGridSquare(const PathRequest & pathRequest, const std::set<IntPair>* const availableGridSquares) {

	unsigned int shortestDistance = UINT_MAX;
	IntPair bestGridSquare;

	for each (const IntPair gridSquare in *availableGridSquares) {
		unsigned int gridSquareDistance = GB::CalcSquaredDistance(gridSquare, pathRequest.end);
		if (gridSquareDistance < shortestDistance) {
			shortestDistance = gridSquareDistance;
			bestGridSquare = gridSquare;
		}
	}

	return bestGridSquare;
}

/// <summary>
/// Gets the neighbors of a gridSquare.
/// </summary>
/// <param name="gridSquareCoordinate">The coordinate of the grid square to get neighbors for.</param>
/// <returns>Vector containing all valid neighbors of the grid square at the passed coordinate.</returns>
std::vector<IntPair> Pathfinder::getNeighbors(const IntPair & gridSquareCoordinate) {

	//find the bounds of the active navigation grid
	int maxX = navigationGrid->getArraySizeX();
	int maxY = navigationGrid->getArraySizeY();
	std::vector<IntPair> neighbors;

	bool xUp = (gridSquareCoordinate.first + 1 < maxX);
	bool xDown = (gridSquareCoordinate.first - 1 >= 0);
	bool yUp = (gridSquareCoordinate.second + 1 < maxY);
	bool yDown = (gridSquareCoordinate.second - 1 >= 0);

	if (xUp) {
		neighbors.push_back(IntPair(gridSquareCoordinate.first + 1, gridSquareCoordinate.second));
	}
	if (xDown) {
		neighbors.push_back(IntPair(gridSquareCoordinate.first - 1, gridSquareCoordinate.second));
	}
	if (yUp) {
		neighbors.push_back(IntPair(gridSquareCoordinate.first, gridSquareCoordinate.second + 1));
	}
	if (yDown) {
		neighbors.push_back(IntPair(gridSquareCoordinate.first, gridSquareCoordinate.second - 1));
	}


	return neighbors;

}

/// <summary>
/// Reconstructs the path of grid squares to the endpoint.
/// </summary>
/// <param name="endPoint">The end point.</param>
/// <param name="cameFrom">A map containing each grid square's predecessor from.</param>
/// <returns>A vector of grid square indexes representing an in-order path to the passed endPoint.</returns>
std::list<IntPair> Pathfinder::reconstructPath(const IntPair & endPoint, std::map<IntPair, IntPair> const * const cameFrom) {

	std::list<IntPair> inOrderPath;

	//add grid squares until the beginning (grid square that did not come from anywhere) is found
	// do not add first grid square. the path-finding object is already there.
	auto foundSquare = cameFrom->find(endPoint);
	while (foundSquare != cameFrom->end()) {
		inOrderPath.push_front(foundSquare->first);
		foundSquare = cameFrom->find(foundSquare->second);
	}
	return inOrderPath;
}


