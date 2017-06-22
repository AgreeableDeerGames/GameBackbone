#pragma once
#include "stdafx.h"
#include "Point.h"

namespace GB {
	/// <summary> A request to calculate a path from the start coordinate to the end coordinate. </summary>
	struct libGameBackbone PathRequest {
		Point2D<int> start;
		Point2D<int> end;
		double minimumFreeSpace;
		int aStarHeuristicNumber;
	};

}
