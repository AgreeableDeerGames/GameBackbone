#include "PathFinder.h"
#include "Array3D.h"


#include <queue>
#include <set>

//ctr / dtr

///<Summary>Create a pathfinder with a minimum free space of 1 and no path blockers.</summary>
Pathfinder::Pathfinder() : Pathfinder(sf::Vector2f(1,1)) {}

///<Summary> Create a pathfinder with a given minimum free space, and no path blockers.</summary>
///<Param name = "minFreeSpace">The minimum amount of free space around a node for it to be traversable.</param>
Pathfinder::Pathfinder(sf::Vector2f minFreeSpace) {
	pathBlockers = nullptr;
	this->minFreeSpace = minFreeSpace;
}

Pathfinder::~Pathfinder() {
}

//operations

//TODO: doc string
std::list<Point2D>* Pathfinder::pathfind(double startX, double startY, double endX, double endY) {
	//determine the position of the start and end coordinates in the SFML coordinate system
	sf::Vector2f sfStart(startX - anchor->getGx(), startY - anchor->getGy());
	sf::Vector2f sfEnd(endX - anchor->getGx(), endY - anchor->getGy());


	return nullptr;//TODO: fill stub
}

//TODO: doc string
std::list<Point2D>* Pathfinder::pathfind(double startX, double startY, double endX, double endY, sf::Vector2f minFreeSpace) {
	this->minFreeSpace = minFreeSpace;
	return pathfind(startX, startY, endX, endY);
}

void Pathfinder::addPathBlocker(sf::Sprite * blocker) {//TODO: fill stub
}

void Pathfinder::removePathBlocker(sf::Sprite * blocker) {//TODO: fill stub
}

//TODO: PathFinder::NavigationGridPathFind add docstring and finish function
std::vector<sf::Vector3i> Pathfinder::NavigationGridPathFind(sf::Vector3i start, sf::Vector3i stop) {
	const unsigned int oneDimentionalStart = 0;//Flatten3dCoordinate(start.x, start.y, start.z);
	const unsigned int oneDimentionalEnd = 0;//Flatten3dCoordinate(end.x, end.y, end.z);

	// the set of nodes already evaluated
	std::set<unsigned int>* closedSet = new std::set<unsigned int>();

	//the set of currently discovered nodes that are already evaluated.
	//std::set<unsigned int>* openSet = new std::set<unsigned int>();
	typedef std::priority_queue<unsigned int, std::vector<int>, std::less<int> > PriorityIntQueue;//TODO: NavigationGrid::FindPath : This priority queue is wrong. It only prioritizes grid positions with a lower index. Perhaps use a custom struct?
	PriorityIntQueue* openSet = new PriorityIntQueue();

	//Start node is always explored
	openSet->push(oneDimentionalStart);

	// For each node, which node it can most efficiently be reached from.
	// If a node can be reached from many nodes, cameFrom will eventually contain the
	// most efficient previous step.
	std::map<unsigned int, unsigned int>* cameFrom = new std::map<unsigned int, unsigned int>();

	while (!openSet->empty()) {
		unsigned int current = openSet->top();
		if (current == oneDimentionalEnd) {
			//TODO: NavigationGrid::FindPath: reconstruct path, free memory, and return
		}
		openSet->pop();
		closedSet->insert(current);

	}


	//free all memory
	delete closedSet;
	delete openSet;
	delete cameFrom;

	return std::vector<sf::Vector3i>();//TODO: fill NavigationGrid::FindPath stub
}
