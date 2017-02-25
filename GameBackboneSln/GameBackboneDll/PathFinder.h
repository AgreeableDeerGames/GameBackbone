#pragma once
#include "stdafx.h"
#include "DllUtil.h"
#include "Array2D.h"
#include "NavigationGridData.h"
#include "PathRequest.h"

#include<vector>
#include<set>
#include<list>
#include<map>
#include<tuple>

typedef Array2D<NavigationGridData> NavigationGrid;
typedef std::pair<int, int> IntPair;

/// <summary> used to calculate groups of paths in one navigation grid. </summary>
class libGameBackbone Pathfinder {
public:
	//ctr / dtr
	Pathfinder();
	explicit Pathfinder(NavigationGrid* navigationGrid);
	
	~Pathfinder();

	//getters / setters
	
		//setters
	void setNavigationGrid(NavigationGrid* navigationGrid);

		//getters
	NavigationGrid* getNavigationGrid();

	//operations
	void pathFind(const std::vector<PathRequest>& pathRequests, std::vector<std::list<IntPair>> * const returnedPaths);

private:

	//helper functions
	IntPair chooseNextHex(const PathRequest& pathRequest, const std::set<IntPair> * const availableHexes);
	std::vector<IntPair> getNeighbors(const IntPair& hexCoordinate);
	std::list<IntPair> reconstructPath(const IntPair& endPoint, std::map<IntPair, IntPair> const * const cameFrom);

	//data
	NavigationGrid* navigationGrid;

	//deleted copy and assignment
	Pathfinder(const Pathfinder&) = delete;
	Pathfinder(Pathfinder&&) = delete;
	Pathfinder& operator=(const Pathfinder&) = delete;
	Pathfinder& operator=(Pathfinder&&) = delete;
};



//define required functions to use sf::Vector3i in sets
/*namespace sf {
	
	/// <summary>
	/// Strict weak ordering less than comparator for sf::Vector3i
	/// </summary>
	/// <param name="lhs">The left hand side sf::Vector3i.</param>
	/// <param name="rhs">The right hand side sf::Vector3i.</param>
	/// <returns>True if lhs is less than rhs, false otherwise</returns>
	bool operator<(const sf::Vector3i& lhs, const sf::Vector3i& rhs) {
		if (lhs.x < rhs.x) return true;
		if (lhs.x > rhs.x) return false;
		if (lhs.y < rhs.y) return true;
		if (lhs.y > rhs.y) return false;
		if (lhs.z < rhs.z) return true;
		if (lhs.z > rhs.z) return false;
		return false;
	}
	
	/// <summary>
	/// Strict weak ordering greater than comparator for sf::Vector3i
	/// </summary>
	/// <param name="lhs">The left hand side sf::Vector3i.</param>
	/// <param name="rhs">The right hand side sf::Vector3i.</param>
	/// <returns>True if lhs is greater than rhs, false otherwise</returns>
	bool operator>(const sf::Vector3i& lhs, const sf::Vector3i& rhs) {
		return !(lhs < rhs);
	}

}*/