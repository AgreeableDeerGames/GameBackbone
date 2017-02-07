#include "PathFinder.h"

//ctr / dtr

///<Summary>Create a pathfinder with a minimum free space of 1 and no path blockers.</summary>
Pathfinder::Pathfinder() : Pathfinder(sf::Vector2f(1,1)) {}

///<Summary> Create a pathfinder with a given minimum free space, and no path blockers.</summary>
///<Param name = "minFreeSpace">The minimum amount of free space around a node for it to be traversable.</param>
Pathfinder::Pathfinder(sf::Vector2f minFreeSpace) {
	pathBlockers = nullptr;
	this->minFreeSpace = minFreeSpace;

	Array3D<int> tempArray();//todo: Remove this after Array3D is debugged
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

