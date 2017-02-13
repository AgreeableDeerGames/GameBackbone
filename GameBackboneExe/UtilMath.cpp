#include"UtilMath.h"

#include<SFML/System/Vector3.hpp>

#include<math.h>

/// <summary>
/// Determines the distance between two points in an three dimensional space.
/// </summary>
/// <param name="point1">The first point</param>
/// <param name="point2">The second point</param>
/// <returns>the distance between the two points</returns>
unsigned int Dist3d(const sf::Vector3i & point1, const sf::Vector3i & point2) {
	return sqrt(SquaredDist3d(point1, point2));
}

/// <summary>
/// Determines the square of the distance between two three dimensional points.
/// </summary>
/// <param name="point1">The first point.</param>
/// <param name="point2">The second point.</param>
/// <returns>The square of the distance between two three dimensional points.</returns>
unsigned int SquaredDist3d(const sf::Vector3i & point1, const sf::Vector3i & point2) {
	return pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2) + pow(point1.z - point2.z, 2);
}