#pragma once

#include <vector>




class NavigationGrid {
public:

	//ctr / dtr
	NavigationGrid();
	NavigationGrid(unsigned int cubeGridDimension);
	NavigationGrid(unsigned int xDim, unsigned int yDim, unsigned int zDim);
	virtual ~NavigationGrid();

	//getters / setters

		//setters
	void setWeight(unsigned int x, unsigned int y, unsigned int z, int value);

		//getters
	int getWeight(unsigned int x, unsigned int y, unsigned int z);
	int getGridXSize();
	int getGridYSize();
	int getGridZSize();


private:
	std::vector<int> internalArray;

	unsigned int xDim;
	unsigned int yDim;
	unsigned int zDim;

	int Flatten3dCoordinate(unsigned int x, unsigned int y, unsigned int z);


};

