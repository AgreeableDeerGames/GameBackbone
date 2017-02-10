#pragma once
struct NavigationHexData {
	int weight;
	unsigned int blockerDist;
};

bool operator<(const NavigationHexData& lhs, const NavigationHexData& rhs) {
	return lhs.weight < rhs.weight;
}
bool operator>(const NavigationHexData& lhs, const NavigationHexData& rhs) {
	return lhs.weight > rhs.weight;
}
