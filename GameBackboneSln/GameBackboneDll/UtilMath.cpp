#include "stdafx.h"
#include"UtilMath.h"

#include<SFML/System/Vector3.hpp>

#include<math.h>
#include<tuple>



/// <summary>
/// Determines the square of the distance between two three dimensional points.
/// </summary>
/// <param name="point1">The first point.</param>
/// <param name="point2">The second point.</param>
/// <returns>The square of the distance between two three dimensional points.</returns>
unsigned int SquaredDist3d(const sf::Vector3i & point1, const sf::Vector3i & point2) {
	return (unsigned int)(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2) + pow(point1.z - point2.z, 2));
}

/// <summary>
/// Determines the distance between two points in an three dimensional space.
/// </summary>
/// <param name="point1">The first point</param>
/// <param name="point2">The second point</param>
/// <returns>the distance between the two points</returns>
unsigned int Dist3d(const sf::Vector3i & point1, const sf::Vector3i & point2) {
	return (unsigned int)sqrt(SquaredDist3d(point1, point2));
}

/// <summary>
/// Determines the square of the distance between two 2 dimensional points.
/// </summary>
/// <param name="point1">The first point.</param>
/// <param name="point2">The second point.</param>
/// <returns>The square of the distance between two three dimensional points.</returns>
unsigned int SquaredDist2d(const std::pair<int, int> & point1, const std::pair<int, int> & point2) {
	return (unsigned int) (pow(point1.first - point2.first, 2) + pow(point1.second - point2.second, 2));
}

/// <summary>
/// Determines the distance between two points in an two dimensional space.
/// </summary>
/// <param name="point1">The first point</param>
/// <param name="point2">The second point</param>
/// <returns>the distance between the two points</returns>
unsigned int Dist2d(const std::pair<int, int> & point1, const std::pair<int, int> & point2) {
	return (unsigned int)sqrt(SquaredDist2d(point1, point2));
}


