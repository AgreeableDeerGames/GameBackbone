#include "NavigationGrid.h"

#include <set>
#include <map>
#include <queue>
#include <vector>

//ctr / dtr

///<summary>Creates a 100 * 100 * 100 grid. All weights are initialized to 0.</summary>
NavigationGrid::NavigationGrid() : NavigationGrid(100) {}

///<summary> creates a cube grid with the passed width. All weights are initialized to 0.</summary>
///<param name = "cubeGridDimension"> size of the width of the grid cube</param>
NavigationGrid::NavigationGrid(unsigned int cubeGridDimension) : NavigationGrid(cubeGridDimension, cubeGridDimension, cubeGridDimension){}

///<summary> creates a 3D grid with passed x , y and z dimensions.All weights are initialized to 0. </summary>
///<param name = "xDim">size of the grid in the x dimension</param>
///<param name = "yDim">size of the grid in the y dimension</param>
///<param name = "zDim">size of the grid in the z dimension</param>
NavigationGrid::NavigationGrid(unsigned int xDim, unsigned int yDim, unsigned int zDim) {
	internalArray.resize(xDim * yDim * zDim);

	internalArray = { 0 }; //initialize all weights to 0
	this->xDim = xDim;
	this->yDim = yDim;
	this->zDim = zDim;
}


NavigationGrid::~NavigationGrid() {
}


//getters / setters

	//setters

///<summary> sets the weight of the selected grid index to the passed value</summary>
///<param name = "x">x coordinate of the grid index to change</param>
///<param name = "y">y coordinate of the grid index to change</param>
///<param name = "z">z coordinate of the grid index to change</param>
///<param name = "value"> new value for the passed grid index</param>
void NavigationGrid::setWeight(unsigned int x, unsigned int y, unsigned int z, int value) {
	internalArray[Flatten3dCoordinate(x, y, z)] = value;
}

///<summary>sets the game world x position of the grids 0,0,0 index</summary>
///<param name = "x">x position of the grids 0,0,0 index</param>
void NavigationGrid::setOriginX(double x) {
	gridOriginPosition.x = x;
}

///<summary>sets the game world y position of the grids 0,0,0 index</summary>
///<param name = "y">y position of the grids 0,0,0 index</param>
void NavigationGrid::setOriginY(double y) {
	gridOriginPosition.y = y;
}

///<summary> sets the gameWorldDiameter of the individual hexes in the grid</summary>
///<param name = "newDiameter"> The new diameter of the individual hexes in the grid </param>
void NavigationGrid::setHexDiameter(float newDiameter) {
	hexDiameter = newDiameter;
}

	//getters

///<summary> returns the weight of the specified grid index </summary>
///<param name = "x">x position of the grid index to change</param>
///<param name = "y">y position of the grid index to change</param>
///<param name = "z">z position of the grid index to change</param>
int NavigationGrid::getWeight(unsigned int x, unsigned int y, unsigned int z) {
	return internalArray[Flatten3dCoordinate(x, y, z)];
}

///<summary> returns the x dimension of the grid</summary>
int NavigationGrid::getGridXSize() {
	return xDim;
}

///<summary> returns the y dimension of the grid</summary>
int NavigationGrid::getGridYSize() {
	return yDim;
}

///<summary> returns the z dimension of the grid</summary>
int NavigationGrid::getGridZSize() {
	return zDim;
}

///<summary> returns the x position of the 0,0,0 index of the grid within the game world</summary>
double NavigationGrid::getOriginX() {
	return gridOriginPosition.x;
}

///<summary> returns the y position of the 0,0,0 index of the grid within the game world</summary>
double NavigationGrid::getOriginY() {
	return gridOriginPosition.y;
}

///<summary> returns the diameter of the individual hexes within the grid</summary>
float NavigationGrid::getHexDiameter() {
	return hexDiameter;
}

//TODO: Add NavigationGrid::FindPath doc XML
std::vector<sf::Vector3i> NavigationGrid::FindPath(const sf::Vector3i& start, const sf::Vector3i& end) {

	const unsigned int oneDimentionalStart = Flatten3dCoordinate(start.x, start.y, start.z);
	const unsigned int oneDimentionalEnd = Flatten3dCoordinate(end.x, end.y, end.z);

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
		if (current == oneDimentionalEnd) 
		{
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


//Internal Helper Functions

///<summary> returns the 1d array position of the input 3d coordinates </summary>
///<param name = "x"> x position of the 3d coordinate</param>
///<param name = "y"> y position of the 3d coordinate</param>
///<param name = "z"> z position of the 3d coordinate</param>
int NavigationGrid::Flatten3dCoordinate(unsigned int x, unsigned int y, unsigned int z) {
	return z*xDim*yDim + y*xDim + x;
}



	