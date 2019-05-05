#pragma once

#include <GameBackboneDemo/DemoRegion.h>

#include <GameBackbone/Navigation/CoordinateConverter.h>
#include <GameBackbone/Navigation/PathFinder.h>
#include <GameBackbone/Util/Point.h>

#include <SFML/Graphics.hpp>

#include <memory>

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
		// Constructors
		NavigationDemoRegion(sf::RenderWindow & window);
		virtual ~NavigationDemoRegion();

		NavigationDemoRegion() = delete;
		NavigationDemoRegion(const NavigationDemoRegion& other) = delete;
		NavigationDemoRegion(NavigationDemoRegion&& other) = delete;
		NavigationDemoRegion& operator= (const NavigationDemoRegion& other) = delete;
		NavigationDemoRegion& operator= (NavigationDemoRegion&& other) = delete;

		// Behavior
		void behave(sf::Time currentTime) override;

		// Handle sf::Events
		void handleMouseClick(sf::Vector2f clickPosition, sf::Mouse::Button button) override;


	protected:
		// Initialization and Cleanup
		void init();
		void initGUI();
		void initMaze();
		void destroy();
		void reset() override;

		// Update logic storage
		sf::Time lastUpdateTime;

		// Sprite textures
		std::unique_ptr<sf::Texture> navigatorTexture;
		std::unique_ptr<sf::Texture> gridTexture;

		// Store visual representation of maze solvers
		std::vector<std::unique_ptr<sf::Sprite>> navigators;

		// Pathfinding
		GB::Pathfinder regionPathfinder;
		std::unique_ptr<GB::NavigationGrid> navGrid;
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
