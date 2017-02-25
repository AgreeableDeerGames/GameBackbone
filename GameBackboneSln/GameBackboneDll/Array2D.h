#pragma once
#include<vector>

/// <summary>
/// Store any type in a two dimensional array
/// </summary>
template <class templateClass>
class Array2D {
public:

	//ctr / dtr
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Array2D"/> with dimensions of 100 by 100.
	/// </summary>
	Array2D() : Array2D(100) {}
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Array2D"/> class with x and y dimensions both equal to the passed value.
	/// </summary>
	/// <param name="dimensions">The length of the x and y dimensions.</param>
	explicit Array2D(unsigned int dimensions) : Array2D(dimensions, dimensions) {}
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Array2D"/> class with passed x and y dimensions.
	/// </summary>
	/// <param name="xLength">Length of the x dimension.</param>
	/// <param name="yLength">Length of the y dimension.</param>
	Array2D(unsigned int xLength, unsigned int yLength) {
		this->xLength = xLength;
		this->yLength = yLength;
		internalArray.resize(xLength * yLength);
	}

	~Array2D() {
	}

	//getters / setters

		//reference accessors
	
	/// <summary>
	/// Accesses the element at the passed index.
	/// </summary>
	/// <param name="x">The x position of the element.</param>
	/// <param name="y">The y position of the element.</param>
	/// <returns>Returns a reference to the element at the passed index.</returns>
	templateClass& operator() (unsigned int x, unsigned int y) {
		return internalArray[flatten2dCoordinate(x, y)]
	}

		//setters
	
	/// <summary>
	/// Sets the value of the selected array index to the passed value.
	/// </summary>
	/// <param name="x">The x position of the index to set.</param>
	/// <param name="y">The y position of the index to set.</param>
	/// <param name="value">The new value of the selected index.</param>
	void setValueAt(unsigned int x, unsigned int y, templateClass value) {
		internalArray[flatten2dCoordinate] = value;
	}

		//getters
		
	/// <summary>
	/// Gets the value of the selected array index.
	/// </summary>
	/// <param name="x">The x position of the element to return.</param>
	/// <param name="y">The y position of the element to return.</param>
	/// <returns>The element at the passed coordinate</returns>
	templateClass getValueAt(unsigned int x, unsigned int y) {
		return internalArray[flatten2dCoordinate];
	}
	
	/// <summary>
	/// Gets the array size in the x dimension.
	/// </summary>
	/// <returns></returns>
	unsigned int getArraySizeX() {
		return xLength;
	}
	
	/// <summary>
	/// Gets the array size in the y dimension.
	/// </summary>
	/// <returns></returns>
	unsigned int getArraySizeY() {
		return yLength;
	}

	//operations
	
	/// <summary>
	/// Initializes all values in the Array2D to the passed value. Existing values are overwritten.
	/// </summary>
	/// <param name="value">The new value for every element in the array.</param>
	void initAllValues(templateClass value) {
		for (size_t i = 0; i < internalArray.size(); i++) {
			internalArray[i] = value;
		}
	}

private:
	//internal helper functions
	
/// <summary>
/// Flattens the 2d coordinate into a 1d position.
/// </summary>
/// <param name="x">The x position of the 2d coordinate.</param>
/// <param name="y">The y position of the 2d coordinate.</param>
/// <returns>The position of the 2d coordinate in a 1d format.</returns>
	unsigned int flatten2dCoordinate(unsigned int x, unsigned int y) {
		return y * xLength + x;
	}

	//properties
	unsigned int xLength;
	unsigned int yLength;

	//storage
	std::vector<templateClass> internalArray;
};

