#include "NavigationGrid.h"

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


//Internal Helper Functions

///<summary> returns the 1d array position of the input 3d coordinates </summary>
///<param name = "x"> x position of the 3d coordinate</param>
///<param name = "y"> y position of the 3d coordinate</param>
///<param name = "z"> z position of the 3d coordinate</param>
int NavigationGrid::Flatten3dCoordinate(unsigned int x, unsigned int y, unsigned int z) {
	return z*xDim*yDim + y*xDim + x;
}



	