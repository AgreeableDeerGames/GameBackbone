#pragma once
#include "stdafx.h"
#include "DllUtil.h"
#include "Array2D.h"
#include "PathRequest.h"
#include "Point.h"
#include "NavigationGridData.h"
#include "NavigationTools.h"

#include<list>
#include<map>
#include<set>
#include<vector>

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
		void pathFind(const std::vector<PathRequest>& pathRequests, std::vector<std::list<Point2D<int>>> * const returnedPaths);

	private:

		//helper functions
		Point2D<int> chooseNextGridSquare(const PathRequest& pathRequest, const std::set<Point2D<int>> * const availableGridSquares);
		std::vector<Point2D<int>> getNeighbors(const Point2D<int>& gridCoordinate);
		std::list<Point2D<int>> reconstructPath(const Point2D<int>& endPoint, std::map<Point2D<int>, Point2D<int>> const * const cameFrom);

		//data
		NavigationGrid* navigationGrid;

		//deleted copy and assignment
		Pathfinder(const Pathfinder&) = delete;
		Pathfinder(Pathfinder&&) = delete;
		Pathfinder& operator=(const Pathfinder&) = delete;
		Pathfinder& operator=(Pathfinder&&) = delete;
	};

}
