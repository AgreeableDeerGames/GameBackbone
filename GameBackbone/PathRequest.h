#pragma once
#include <SFML/System/Vector3.hpp>

struct PathRequest {
	sf::Vector3i start;
	sf::Vector3i end;
	double minimumFreeSpace;
	int aStarHeuristicNumber;
};