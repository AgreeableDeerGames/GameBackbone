#pragma once
#include <Util\stdafx.h>

#include <Util\DllUtil.h>
#include <SFML/System/Vector3.hpp>

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
	libGameBackbone T CalcDistance(const sf::Vector3<T> & point1, const sf::Vector3<T> & point2) {
		return (T)sqrt(CalcSquaredDistance(point1, point2));
	}

	/// <summary>
	/// Determines the square of the distance between two three dimensional points.
	/// </summary>
	/// <param name="point1">The first point.</param>
	/// <param name="point2">The second point.</param>
	/// <returns>The square of the distance between two three dimensional points.</returns>
	template<class T>
	libGameBackbone T CalcSquaredDistance(const sf::Vector3<T> & point1, const sf::Vector3<T> & point2) {
		return (T)(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2) + pow(point1.z - point2.z, 2));
	}

	/// <summary>
	/// Determines the distance between two points in an two dimensional space.
	/// </summary>
	/// <param name="point1">The first point</param>
	/// <param name="point2">The second point</param>
	/// <returns>the distance between the two points</returns>
	template<class T>
	libGameBackbone T CalcDistance(const std::pair<T, T> & point1, const std::pair<T, T> & point2) {
		return (T)sqrt(CalcSquaredDistance(point1, point2));
	}

	/// <summary>
	/// Determines the square of the distance between two 2 dimensional points.
	/// </summary>
	/// <param name="point1">The first point.</param>
	/// <param name="point2">The second point.</param>
	/// <returns>The square of the distance between two three dimensional points.</returns>
	template<class T>
	libGameBackbone T CalcSquaredDistance(const std::pair<T, T> & point1, const std::pair<T, T> & point2) {
		return (T)(pow(point1.first - point2.first, 2) + pow(point1.second - point2.second, 2));
	}

}
