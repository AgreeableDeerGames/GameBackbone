#pragma once
#include "stdafx.h"
#include <tuple>
/// <summary> A request to calculate a path from the start coordinate to the end coordinate. </summary>
struct libGameBackbone PathRequest {
	std::pair<int, int> start;
	std::pair<int, int> end;
	double minimumFreeSpace;
	int aStarHeuristicNumber;
};