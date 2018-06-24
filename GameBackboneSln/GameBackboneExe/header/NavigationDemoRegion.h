#pragma once

#include <DemoRegion.h>

#include <Navigation/CoordinateConverter.h>
#include <Navigation/PathFinder.h>
#include <Util/Point.h>

#include <SFML/Graphics.hpp>

namespace EXE {

	/// <summary>
	/// Options for selected navigator button
	/// </summary>
	enum SELECTED_NAVIGATOR_BUTTON_TYPE
	{
		NAVIGATOR_1,
		NAVIGATOR_2,
		ALL_NAVIGATORS
	};

	/// <summary>
	/// Data stored in each NavigationGridSquare for this region.
	/// </summary>
	struct NavigationDemoData : public GB::NavigationGridData
	{
		sf::Sprite* demoSprite = nullptr;

		NavigationDemoData() = default;
		virtual ~NavigationDemoData(){delete demoSprite;}
	};

	/// <summary>
	/// GameRegion with logic for demonstrating basic path-finding demonstrations.
	/// </summary>
	/// <seealso cref="GameRegion" />
	class NavigationDemoRegion : public DemoRegion {
	public:

		// ctr / dtr
		NavigationDemoRegion();
		NavigationDemoRegion(const NavigationDemoRegion& other) = delete;
		NavigationDemoRegion(NavigationDemoRegion&& other) = delete;
		NavigationDemoRegion& operator= (const NavigationDemoRegion& other) = delete;
		NavigationDemoRegion& operator= (NavigationDemoRegion&& other) = delete;
		NavigationDemoRegion(sf::RenderWindow & window);
		virtual ~NavigationDemoRegion();

		//behavior

		virtual void behave(sf::Time currentTime) override;

		virtual void handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button) override;
		virtual void handleMouseMove(sf::Vector2f mousePosition) override;


	protected:

		// ctr / dtr
		void init();
		void destroy();
		virtual void reset() override;

		// helper functions
		void initGUI();
		void initMaze(std::vector<GB::Point2D<int>> nonBlockablePositions);

		// update logic storage
		sf::Time lastUpdateTime;

		// sprite textures
		sf::Texture* navigatorTexture;
		sf::Texture* gridTexture;

		// store visual representation of maze solvers
		std::vector<sf::Sprite*> navigators;

		// path-finding
		GB::Pathfinder regionPathfinder;
		GB::NavigationGrid* navGrid;
		const unsigned int NAV_GRID_DIM = 20;
		const float VISUAL_GRID_SCALE = 1.0f;
		std::vector<GB::WindowCoordinatePathPtr> paths;
		GB::CoordinateConverter coordinateConverter;

		// GUI handle functions
		SELECTED_NAVIGATOR_BUTTON_TYPE selectedNavigatorOption;
		void Navigator1CB();
		void Navigator2CB();
		void AllNavigatorsCB();

	};

}
