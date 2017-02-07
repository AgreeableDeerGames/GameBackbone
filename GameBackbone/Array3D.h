#pragma once

#include<SFML\System\Vector3.hpp>

#include<vector>

template <class templateClass>
class Array3D {
public:

	//ctr / Dtr

	///<summary> creates a 3D array with dimensions of 100 * 100 * 100<summary>
	Array3D() : Array3D(100) {}


	///<summary> creates a cube 3D array with the passed width.</summary>
	///<param name = "dimensions"> size of the width of the array cube</param>
	Array3D(unsigned int dimensions) : Array3D(dimensions, dimensions, dimensions) {}

	///<summary> creates a 3D array with passed x , y and z dimensions.</summary>
	///<param name = "xDim">size of the array in the x dimension</param>
	///<param name = "yDim">size of the array in the y dimension</param>
	///<param name = "zDim">size of the array in the z dimension</param>
	Array3D(unsigned int xLenght, unsigned int yLength, unsigned int zLength) {
		internalArray.resize(xLenght * yLength * zLength);
		this->xLength = xLenght;
		this->yLength = yLength;
		this->zLength = zLength;
	}


	~Array3D();

	

	//getters / setters

		//setters

///<summary> sets the value of the selected array index to the passed value</summary>
///<param name = "x">x coordinate of the array index to change</param>
///<param name = "y">y coordinate of the array index to change</param>
///<param name = "z">z coordinate of the array index to change</param>
///<param name = "value"> new value for the passed array index</param>
	void setValueAt(unsigned int x, unsigned int y, unsigned int z, templateClass value) {
		internalArray[Flatten3dCoordinate(x, y, z)] = value;
	}
		//getters


///<summary> returns the weight of the specified array index </summary>
///<param name = "x">x position of the array index to change</param>
///<param name = "y">y position of the array index to change</param>
///<param name = "z">z position of the array index to change</param>
	templateClass getValueAt(unsigned int x, unsigned int y, unsigned int z) {
		return 	internalArray[Flatten3dCoordinate(x, y, z)];
	}

	///<summary> returns the x dimension of the array</summary>
	unsigned int getArraySizeX() {
		return xLength;
	}

	///<summary> returns the y dimension of the array</summary>
	unsigned int getArraySizeY() {
		return yLength;
	}

	///<summary> returns the z dimension of the grid</summary>
	unsigned int getArraySizeZ() {
		return zLength;
	}

	//operations

	///<summary>Initializes all values of the array to the passed value. Existing values are overwritten. </summary>
	///<param name = "value"> new value for every element in the array </param>
	void initAllValues(templateClass value) {
		for (size_t i = 0; i < internalArray.size(); i++) {
			internalArray[i] = value;
		}
	}




private:

	//Internal Helper Functions

	///<summary> returns the 1d array position of the input 3d coordinates </summary>
	///<param name = "x"> x position of the 3d coordinate</param>
	///<param name = "y"> y position of the 3d coordinate</param>
	///<param name = "z"> z position of the 3d coordinate</param>
	unsigned int Flatten3dCoordinate(unsigned int x, unsigned int y, unsigned int z) {
		return z*xLength*yLength + y*zLength + x;

	}
	
	//properties
	unsigned int xLength;
	unsigned int yLength;
	unsigned int zLength;


	//storage
	std::vector<templateClass> internalArray;

};

