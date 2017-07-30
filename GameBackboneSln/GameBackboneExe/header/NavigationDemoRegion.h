#pragma once

#include <Backbone\GameRegion.h>
#include <Navigation\CoordinateConverter.h>
#include <Navigation\PathFinder.h>
#include <Util\Array2D.h>
#include <Util\Point.h>

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics.hpp>

namespace GB {

	enum SELECTED_NAVIGATOR_BUTTON_TYPE
	{
		NAVIGATOR_1,
		NAVIGATOR_2,
		ALL_NAVIGATORS
	};

	struct NavigationDemoData : public NavigationGridData
	{
		sf::Sprite* demoSprite;

		NavigationDemoData(){demoSprite = nullptr;}
		virtual ~NavigationDemoData(){delete demoSprite;}
	};

	/// <summary>
	/// GameRegion with logic for demonstrating basic path-finding demonstrations.
	/// </summary>
	/// <seealso cref="GameRegion" />
	class libGameBackbone NavigationDemoRegion : public GameRegion {
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

		virtual void handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button);


	protected:

		//ctr
		void init();

		//helper functions
		void initGUI();
		void initMaze(std::vector<Point2D<int>> nonBlockablePositions);

		//update logic storage
		sf::Time lastUpdateTime;

		// sprite textures
		sf::Texture* navigatorTexture;
		sf::Texture* gridTexture;

		//	store visual representation of maze solvers
		std::vector<sf::Sprite*> navigators;

		//path-finding
		Pathfinder regionPathfinder;
		NavigationGrid* navGrid;
		const unsigned int NAV_GRID_DIM = 20;
		const float VISUAL_GRID_SCALE = 1.0f;
		std::vector<std::shared_ptr<std::list<sf::Vector2f>>> paths;
		CoordinateConverter coordinateConverter;
		

		//GUI handle functions
		SELECTED_NAVIGATOR_BUTTON_TYPE selectedNavigatorOption;
		void Navigator1CB();
		void Navigator2CB();
		void AllNavigatorsCB();

	};

}
