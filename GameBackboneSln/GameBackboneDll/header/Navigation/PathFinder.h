#pragma once

#include <Util\DllUtil.h>
#include <Util/Array2D.h>
#include <Navigation\NavigationGridData.h>
#include <Navigation\PathRequest.h>
#include <Navigation\NavigationTools.h>

#include <vector>
#include <set>
#include <list>
#include <map>
#include <tuple>

namespace GB {

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
		IntPair chooseNextGridSquare(const PathRequest& pathRequest, const std::set<IntPair> * const availableGridSquares);
		std::vector<IntPair> getNeighbors(const IntPair& gridCoordinate);
		std::list<IntPair> reconstructPath(const IntPair& endPoint, std::map<IntPair, IntPair> const * const cameFrom);

		//data
		NavigationGrid* navigationGrid;

		//deleted copy and assignment
		Pathfinder(const Pathfinder&) = delete;
		Pathfinder(Pathfinder&&) = delete;
		Pathfinder& operator=(const Pathfinder&) = delete;
		Pathfinder& operator=(Pathfinder&&) = delete;
	};

}
