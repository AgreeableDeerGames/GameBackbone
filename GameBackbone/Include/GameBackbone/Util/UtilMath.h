#pragma once
#include <GameBackbone/Util/DllUtil.h>

#define _USE_MATH_DEFINES
#include <math.h>

namespace GB {
	/// <summary>
	/// Determines the square of the distance between two points in a two dimensional space.
	/// Passed points must have publicly available x and y members.
	/// </summary>
	/// <param name="point1">The first point.</param>
	/// <param name="point2">The second point.</param>
	/// <returns>The square of the distance between two three dimensional points.</returns>
	template<class T, class C>
	T calcSquaredDistance2D(const C & point1, const C & point2) {
		return (T)(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
	}

	/// <summary>
	/// Determines the distance between two points in a two dimensional space.
	/// Passed points must have publicly available x and y members.
	/// </summary>
	/// <param name="point1">The first point</param>
	/// <param name="point2">The second point</param>
	/// <returns>the distance between the two points</returns>
	template<class T, class C>
	T calcDistance2D(const C & point1, const C & point2) {
		return (T)sqrt(calcSquaredDistance2D<T, C>(point1, point2));
	}
}

