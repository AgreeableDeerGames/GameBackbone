#pragma once

#include <GameBackbone/Util/DllUtil.h>
#include <GameBackbone/Util/Array2D.h>
#include <GameBackbone/Navigation/NavigationGridData.h>
#include <GameBackbone/Navigation/PathRequest.h>
#include <GameBackbone/Navigation/NavigationTools.h>

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
		void pathFind(const std::vector<PathRequest>& pathRequests, std::vector<std::deque<sf::Vector2i>>* const returnedPaths) const;

	private:

		//helper functions
		sf::Vector2i chooseNextGridSquare(const PathRequest& pathRequest, const std::set<sf::Vector2i, Vec2Compare<int>>& availableGridSquares, std::map<sf::Vector2i, int, Vec2Compare<int>>& score) const;
		std::vector<sf::Vector2i> getNeighbors(const sf::Vector2i& gridCoordinate) const;
		std::deque<sf::Vector2i> reconstructPath(const sf::Vector2i& endPoint, const std::map<sf::Vector2i, sf::Vector2i, Vec2Compare<int>>& cameFrom) const;

		//data
		NavigationGrid* navigationGrid;
	};

}
