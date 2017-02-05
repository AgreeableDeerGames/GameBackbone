#pragma once

#include <vector>



typedef std::vector<std::vector<std::vector<int>>> WeightedHexGrid;

class NavigationGrid {
public:

	//ctr / dtr
	NavigationGrid();
	NavigationGrid(unsigned int cubeGridDimention);
	NavigationGrid(unsigned int xDim, unsigned int yDim, unsigned int zDim);
	virtual ~NavigationGrid();

	//getters / setters

		//setters
	void setWeight(unsigned int x, unsigned int y, unsigned int z, int value);
	void setGridSize(unsigned int x, unsigned int y, unsigned int z);

		//getters
	int getWeight(unsigned int x, unsigned int y, unsigned int z);


private:
	WeightedHexGrid internalHexGrid;

};

