#pragma once

#include <Util\Array2D.h>
#include <SFML\System\Vector3.hpp>

#include <vector>

namespace GB {

	///<summary>Store any type in a three dimensional array</summary>
	template <class templateClass>
	class Array3D {
	public:

		//ctr / Dtr
		//default copy and move are fine for this class

		///<summary> creates a 3D array with dimensions of 100 * 100 * 100<summary>
		Array3D() : Array3D(100) {}


		///<summary> creates a cube 3D array with the passed width.</summary>
		///<param name = "dimensions"> size of the width of the array cube</param>
		explicit Array3D(unsigned int dimensions) : Array3D(dimensions, dimensions, dimensions) {}

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

		Array3D(const Array3D<templateClass>& other) = default;
		Array3D(Array3D<templateClass>&& other) = default; 
		Array3D& operator= (const Array3D<templateClass>& other) = default;
		Array3D& operator= (Array3D<templateClass>&& other) = default;

		~Array3D() {

		}



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
///<param name = "x">x position of the element to return</param>
///<param name = "y">y position of the element to return</param>
///<param name = "z">z position of the element to return</param>
/// <returns>The element stored at the passed coordinates</returns>
		templateClass getValueAt(unsigned int x, unsigned int y, unsigned int z) {
			return 	internalArray[Flatten3dCoordinate(x, y, z)];
		}

		/// <summary>
		/// returns the weight of the specified array index.
		/// </summary>
		/// <param name="coordinate">The 3d position of the element to return.</param>
		/// <returns>The element stored at the passed coordinates</returns>
		templateClass getValueAt(sf::Vector3i coordinate) {
			return internalArray[Flatten3dCoordinate(coordinate.x, coordinate.y, coordinate.z)];
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

}
