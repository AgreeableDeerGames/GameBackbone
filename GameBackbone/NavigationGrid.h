#pragma once
#include"Point2D.h"

#include<SFML\System\Vector3.hpp>

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
	
	void setOriginX(double x);
	void setOriginY(double y);

	void setHexDiameter(float newDiameter);

		//getters
	int getWeight(unsigned int x, unsigned int y, unsigned int z);
	int getGridXSize();
	int getGridYSize();
	int getGridZSize();

	double getOriginX();
	double getOriginY();

	float getHexDiameter();

	//operations
	std::vector<Point2D> FindPath(Point2D start, Point2D end);
	std::vector<sf::Vector3i> FindPath(const sf::Vector3i& start, const sf::Vector3i& end);

private:
	//Internal Array properties
	std::vector<int> internalArray;
	unsigned int xDim;
	unsigned int yDim;
	unsigned int zDim;

	//Game World tie in properties
	Point2D gridOriginPosition;
	float hexDiameter;


	//Internal helper functions
	int Flatten3dCoordinate(unsigned int x, unsigned int y, unsigned int z);
	sf::Vector3i WorldPointToGridIdx(Point2D worldPoint);
	


};

