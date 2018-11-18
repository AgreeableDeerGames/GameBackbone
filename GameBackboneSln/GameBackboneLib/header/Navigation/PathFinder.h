#pragma once

#include <Util/DllUtil.h>
#include <Util/Array2D.h>
#include <Navigation/NavigationGridData.h>
#include <Navigation/PathRequest.h>
#include <Navigation/NavigationTools.h>
#include <Util/Point.h>

#include <deque>
#include <map>
#include <set>
#include <vector>

namespace GB {

	/// <summary> used to calculate groups of paths in one navigation grid. </summary>
	class libGameBackbone Pathfinder {
	public:
		//ctr / dtr
		Pathfinder();
		explicit Pathfinder(NavigationGrid* navigationGrid);
		~Pathfinder() = default;

		//deleted copy and assignment
		Pathfinder(const Pathfinder&) = delete;
		Pathfinder(Pathfinder&&) = delete;
		Pathfinder& operator=(const Pathfinder&) = delete;
		Pathfinder& operator=(Pathfinder&&) = delete;

		//getters / setters

			//setters
		void setNavigationGrid(NavigationGrid* navigationGrid);

		//getters
		NavigationGrid* getNavigationGrid();

		//operations
		void pathFind(const std::vector<PathRequest>& pathRequests, std::vector<std::deque<Point2D<int>>>* const returnedPaths) const;

	private:

		//helper functions
		Point2D<int> chooseNextGridSquare(const PathRequest& pathRequest, const std::set<Point2D<int>>* const availableGridSquares) const;
		std::vector<Point2D<int>> getNeighbors(const Point2D<int>& gridCoordinate) const;
		std::deque<Point2D<int>> reconstructPath(const Point2D<int>& endPoint, std::map<Point2D<int>, Point2D<int>> const * const cameFrom) const;

		//data
		NavigationGrid* navigationGrid;
	};

}
