#pragma once
#include "DllUtil.h"

#define BLOCKED_GRID_WEIGHT 10000

/// <summary> Information stored in each navigation grid square. </summary>
struct libGameBackbone NavigationGridData {
	int weight;
	unsigned int blockerDist;
};


/*
libGameBackbone bool operator<(const NavigationGridData& lhs, const NavigationGridData& rhs) {
	return lhs.weight < rhs.weight;
}
libGameBackbone bool operator>(const NavigationGridData& lhs, const NavigationGridData& rhs) {
	return lhs.weight > rhs.weight;
}
*/