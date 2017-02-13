#pragma once
#include <SFML/System/Vector3.hpp>

/// <summary> A request to calculate a path from the start coordinate to the end coordinate. </summary>
struct libGameBackbone PathRequest {
	sf::Vector3i start;
	sf::Vector3i end;
	double minimumFreeSpace;
	int aStarHeuristicNumber;
};