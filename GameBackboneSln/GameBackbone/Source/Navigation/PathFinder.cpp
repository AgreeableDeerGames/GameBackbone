#include <GameBackbone/Navigation/PathFinder.h>
#include <GameBackbone/Util/UtilMath.h>

#include <deque>
#include <limits.h>
#include <map>
#include <queue>
#include <set>

using namespace GB;

//ctr / dtr

/// <summary> Creates a PathFinder with a null navigation grid. </summary>
Pathfinder::Pathfinder() : Pathfinder(nullptr) {}

/// <summary> Creates a PathFinder with an assigned navigation grid. </summary>
/// <param name = "navigationGrid"> Three dimensional grid to be used when path-finding. </param>
Pathfinder::Pathfinder(NavigationGrid* navigationGrid) {
	this->navigationGrid = navigationGrid;
}

//getters / setters

//setters

/// <summary>
/// Sets the navigation grid.
/// </summary>
/// <param name="navigationGrid">The navigation grid.</param>
void Pathfinder::setNavigationGrid(NavigationGrid* navigationGrid) {
	this->navigationGrid = navigationGrid;
}

//setters

/// <summary>
/// Gets the navigation grid.
/// </summary>
/// <returns>NavigationGrid pointer</returns>
NavigationGrid* Pathfinder::getNavigationGrid() {
	return navigationGrid;
}

/// <summary>
/// Creates an unblocked path of adjacent grid squares to for each path request.
/// </summary>
/// <param name="pathRequests">vector containing the requirements for each path.</param>
/// <param name="returnedPaths">vector containing the found path for each PathRequest. The path is found at the same index as its corresponding request.</param>

void Pathfinder::pathFind(const std::vector<PathRequest>& pathRequests, std::vector<std::deque<sf::Vector2i>>* const returnedPaths) const {

	typedef std::pair<sf::Vector2i, int> GridValuePair;

	//ensure that returned paths is big enough to store all results
	returnedPaths->resize(pathRequests.size());

	//find result for each path request
	for (unsigned int i = 0; i < pathRequests.size(); i++) {

		PathRequest pathRequest = pathRequests[i];

		//grid address of start and end points
		sf::Vector2i startPoint = pathRequest.start;
		sf::Vector2i endPoint = pathRequest.end;

		// the set of nodes already evaluated
		std::set<sf::Vector2i, IsVector2Less<int>> closedSet;

		//the set of currently discovered nodes that are already evaluated.
		std::set<sf::Vector2i, IsVector2Less<int>> openSet;
		openSet.insert(startPoint);

		//cost to move to a point from the start
		std::map<sf::Vector2i, int, IsVector2Less<int>> score;
		score.insert(GridValuePair(startPoint, 0));

		// For each node, which node it can most efficiently be reached from.
		// If a node can be reached from many nodes, cameFrom will eventually contain the
		// most efficient previous step.
		std::map<sf::Vector2i, sf::Vector2i, IsVector2Less<int>> cameFrom;

		//search for path
		(*returnedPaths)[i] = std::deque<sf::Vector2i>(); //initialize path as empty
		while (!openSet.empty()) {
			//check current grid square
			sf::Vector2i current = chooseNextGridSquare(pathRequest, openSet, score);
			if (current == endPoint) {
				//reconstruct path, and add to output vector

				std::deque<sf::Vector2i> inOrderPath = reconstructPath(endPoint, cameFrom);
				(*returnedPaths)[i] = inOrderPath;
				break;
			}
			openSet.erase(openSet.find(current));
			closedSet.insert(current);

			//find neighbors
			std::vector<sf::Vector2i> neighbors = getNeighbors(current);

			for (sf::Vector2i neighbor : neighbors) {
				if (closedSet.find(neighbor) != closedSet.end()) {
					continue;// no need to evaluate already evaluated nodes
				}
				//cost of reaching neighbor using current path
				int transitionCost = (navigationGrid->at(current.x, current.y)->weight + navigationGrid->at(neighbor.x, neighbor.y)->weight) / 2;
				int tentativeScore = score.at(current) + transitionCost;

				//discover new node
				if (openSet.find(neighbor) == openSet.end()) {
					//add blocked to closed set and unblocked to open set
					if (navigationGrid->at(neighbor.x, neighbor.y)->weight >= BLOCKED_GRID_WEIGHT) {
						closedSet.insert(neighbor);
						continue;
					}
					else {
						openSet.insert(neighbor);
					}
				}
				else if (tentativeScore >= score.at(neighbor)) {
					continue; // found a worse path
				}

				//update or insert values for node
				cameFrom.insert_or_assign(neighbor, current);
				score.insert_or_assign(neighbor, tentativeScore);
			}
		}
	}
}


// private helper functions

/// <summary>
/// Chooses the next grid square for pathFind based on the pathRequest and the available grid squares.
/// </summary>
/// <param name="pathRequest">The path request.</param>
/// <param name="gridSquares">The available gridSquares.</param>
/// <returns>coordinates of the best available grid square for the passed pathRequest.</returns>
sf::Vector2i Pathfinder::chooseNextGridSquare(const PathRequest& pathRequest, const std::set<sf::Vector2i, IsVector2Less<int>>& availableGridSquares, std::map<sf::Vector2i, int, IsVector2Less<int>>& score) const {

	unsigned int shortestDistance = UINT_MAX;
	sf::Vector2i bestGridSquare = {-1, -1};

	for (const sf::Vector2i& gridSquare : availableGridSquares) {
		unsigned int gridSquareDistance = GB::calcSquaredDistance2D<int>(gridSquare, pathRequest.end);
		gridSquareDistance *= score.at(gridSquare);
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
std::vector<sf::Vector2i> Pathfinder::getNeighbors(const sf::Vector2i & gridSquareCoordinate) const {

	//find the bounds of the active navigation grid
	int maxX = navigationGrid->getArraySizeX();
	int maxY = navigationGrid->getArraySizeY();
	std::vector<sf::Vector2i> neighbors;

	bool xUp = (gridSquareCoordinate.x + 1 < maxX);
	bool xDown = (gridSquareCoordinate.x - 1 >= 0);
	bool yUp = (gridSquareCoordinate.y + 1 < maxY);
	bool yDown = (gridSquareCoordinate.y - 1 >= 0);

	if (xUp) {
		neighbors.push_back(sf::Vector2i{gridSquareCoordinate.x + 1, gridSquareCoordinate.y});
	}
	if (xDown) {
		neighbors.push_back(sf::Vector2i{gridSquareCoordinate.x - 1, gridSquareCoordinate.y});
	}
	if (yUp) {
		neighbors.push_back(sf::Vector2i{gridSquareCoordinate.x, gridSquareCoordinate.y + 1});
	}
	if (yDown) {
		neighbors.push_back(sf::Vector2i{gridSquareCoordinate.x, gridSquareCoordinate.y - 1});
	}


	return neighbors;

}

/// <summary>
/// Reconstructs the path of grid squares to the endpoint.
/// </summary>
/// <param name="endPoint">The end point.</param>
/// <param name="cameFrom">A map containing each grid square's predecessor from.</param>
/// <returns>A vector of grid square indexes representing an in-order path to the passed endPoint.</returns>

std::deque<sf::Vector2i> Pathfinder::reconstructPath(const sf::Vector2i& endPoint, const std::map<sf::Vector2i, sf::Vector2i, IsVector2Less<int>>& cameFrom) const {
	
	std::deque<sf::Vector2i> inOrderPath;

	//add grid squares until the beginning (grid square that did not come from anywhere) is found
	// do not add first grid square. the path-finding object is already there.
	auto foundSquare = cameFrom.find(endPoint);
	while (foundSquare != cameFrom.end()) {
		inOrderPath.push_front(foundSquare->first);
		foundSquare = cameFrom.find(foundSquare->second);
	}
	return inOrderPath;
}


