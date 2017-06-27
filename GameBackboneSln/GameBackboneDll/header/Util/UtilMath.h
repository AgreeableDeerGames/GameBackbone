#pragma once

#include <Util\DllUtil.h>
#include <Util\Point.h>

#include <SFML\System\Vector3.hpp>

#include <math.h>

namespace GB {

	//vector operations

	/// <summary>
	/// Determines the distance between two points in an three dimensional space.
	/// </summary>
	/// <param name="point1">The first point</param>
	/// <param name="point2">The second point</param>
	/// <returns>The distance between the two points</returns>
	template<class T>
	libGameBackbone T CalcDistance(const Point3D<T> & point1, const Point3D<T> & point2) {
		return (T)sqrt(CalcSquaredDistance(point1, point2));
	}

	/// <summary>
	/// Determines the square of the distance between two three dimensional points.
	/// </summary>
	/// <param name="point1">The first point.</param>
	/// <param name="point2">The second point.</param>
	/// <returns>The square of the distance between two three dimensional points.</returns>
	template<class T>
	libGameBackbone T CalcSquaredDistance(const Point3D<T> & point1, const Point3D<T> & point2) {
		return (T)(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2) + pow(point1.z - point2.z, 2));
	}

	/// <summary>
	/// Determines the distance between two points in an two dimensional space.
	/// </summary>
	/// <param name="point1">The first point</param>
	/// <param name="point2">The second point</param>
	/// <returns>the distance between the two points</returns>
	template<class T>
	libGameBackbone T CalcDistance(const Point2D<T> & point1, const Point2D<T> & point2) {
		return (T)sqrt(CalcSquaredDistance(point1, point2));
	}

	/// <summary>
	/// Determines the square of the distance between two 2 dimensional points.
	/// </summary>
	/// <param name="point1">The first point.</param>
	/// <param name="point2">The second point.</param>
	/// <returns>The square of the distance between two three dimensional points.</returns>
	template<class T>
	libGameBackbone T CalcSquaredDistance(const Point2D<T> & point1, const Point2D<T> & point2) {
		return (T)(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
	}

}
