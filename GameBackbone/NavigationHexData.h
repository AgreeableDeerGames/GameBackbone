#pragma once
struct NavigationHexData {
	int weight;
	unsigned int blockerDist;

	bool operator<(const NavigationHexData& other) {
		return weight < other.weight;
	}
	bool operator>(const NavigationHexData& other) {
		return weight > other.weight;
	}
};