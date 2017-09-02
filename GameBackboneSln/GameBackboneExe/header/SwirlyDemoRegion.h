#pragma once

#include <Backbone/GameRegion.h>
#include <Navigation/PathFinder.h>
#include <Util/Array2D.h>
#include <Util/Point.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics.hpp>

namespace GB {
	/// <summary>
	/// GameRegion with logic for demonstrating basic rotation demonstrations.
	/// </summary>
	/// <seealso cref="GameRegion" />
	class libGameBackbone SwirlyDemoRegion : public GameRegion {
	public:

		// ctr / dtr
		SwirlyDemoRegion();
		SwirlyDemoRegion(const SwirlyDemoRegion& other) = delete;
		SwirlyDemoRegion(SwirlyDemoRegion&& other) = delete;
		SwirlyDemoRegion& operator= (const SwirlyDemoRegion& other) = delete;
		SwirlyDemoRegion& operator= (SwirlyDemoRegion&& other) = delete;
		SwirlyDemoRegion(sf::RenderWindow & window);
		virtual ~SwirlyDemoRegion();

		//behavior
		virtual void behave(sf::Time currentTime) override;

		virtual void handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button);
		virtual void handleMouseMove(sf::Vector2f mousePosition);
		virtual void handleWheelScroll(int scrollDelta);



	protected:

		//ctr
		void init();

		//helper functions
		void initGUI();

		//update logic storage
		sf::Time lastUpdateTime;

		// sprite textures
		sf::Texture* navigatorTexture;

		//compound sprite stuff
		CompoundSprite* compSprite;
		sf::Sprite* compComponent1;
		sf::Sprite* compComponent2;
		sf::Sprite* compComponent3;
	};

}
