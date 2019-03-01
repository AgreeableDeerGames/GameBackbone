#pragma once

#include <vector>

namespace GB {

	/// <summary>
	/// Store any type in a two dimensional array
	/// </summary>
	template <class templateClass>
	class Array2D {
	public:

		//ctr / dtr
		//default copy and move are fine for this class

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

		Array2D(const Array2D<templateClass>& other) = default;
		Array2D(Array2D<templateClass>&& other) noexcept = default;
		Array2D& operator= (const Array2D<templateClass>& other) = default;
		Array2D& operator= (Array2D<templateClass>&& other) noexcept = default;

		~Array2D() = default;

		//getters / setters

			//reference accessors

		/// <summary>
		/// Accesses the element at the passed index.
		/// </summary>
		/// <param name="x">The x position of the element.</param>
		/// <param name="y">The y position of the element.</param>
		/// <returns>Returns a reference to the element at the passed index.</returns>
		templateClass& operator() (unsigned int x, unsigned int y) {
			return internalArray[flatten2dCoordinate(x, y)];
		}

		/// <summary>
		/// Returns the 1d array for the passed row coordinate
		/// </summary>
		/// <param name="x">The position of the row to return.</param>
		/// <returns>Returns the 1d array for the passed row coordinate.</returns>
		templateClass* operator[] (unsigned int x) {
			return &internalArray[flatten2dCoordinate(x, 0)];
		}

		//accessors

        /// <summary>
        /// Accesses the element at the passed index.
        /// </summary>
        /// <param name="x">The x position of the element.</param>
        /// <param name="y">The y position of the element.</param>
        /// <returns>Returns a reference to the element at the passed index.</returns>
		templateClass& at(unsigned int x, unsigned int y) {
			return (*this)(x, y);
		}

		/// <summary>
		/// Returns the 1d array for the passed row coordinate
		/// </summary>
		/// <param name="x">The position of the row to return.</param>
		/// <returns>Returns the 1d array for the passed row coordinate.</returns>
		templateClass* at(unsigned int x) {
			return (*this)[x];
		}


		//getters

        /// <summary>
        /// Gets the array size in the x dimension.
        /// </summary>
        /// <returns></returns>
		unsigned int getArraySizeX() const {
			return xLength;
		}

		/// <summary>
		/// Gets the array size in the y dimension.
		/// </summary>
		/// <returns></returns>
		unsigned int getArraySizeY() const {
			return yLength;
		}

		//operations

		/// <summary>
		/// Initializes all values in the Array2D to the passed value. Existing values are overwritten.
		/// </summary>
		/// <param name="value">The new value for every element in the array.</param>
		void initAllValues(templateClass value) {
			for (std::size_t i = 0; i < internalArray.size(); i++) {
				internalArray[i] = value;
			}
		}

        /// <summary>
        /// Checks if the given element is within the Array2D
        /// </summary>
	    /// <param name="x">The x position of the element.</param>
	    /// <param name="y">The y position of the element.</param>
	    /// <returns>Returns true if in the Array2D, false if not.</returns>
        bool isInArray(unsigned int x, unsigned int y) const {
            if (x < getArraySizeX() && y < getArraySizeY()) {
                return true;
            }
            return false;
        }

	private:
		//internal helper functions

        /// <summary>
        /// Flattens the 2d coordinate into a 1d position.
        /// </summary>
        /// <param name="x">The x position of the 2d coordinate.</param>
        /// <param name="y">The y position of the 2d coordinate.</param>
        /// <returns>The position of the 2d coordinate in a 1d format.</returns>
		unsigned int flatten2dCoordinate(unsigned int x, unsigned int y) const {
			//return y * xLength + x;
			return x * yLength + y;
		}

		//properties
		unsigned int xLength;
		unsigned int yLength;

		//storage
		std::vector<templateClass> internalArray;
	};

}
