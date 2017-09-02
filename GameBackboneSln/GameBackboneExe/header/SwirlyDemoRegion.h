#pragma once

#include <DemoRegion.h>

#include <Backbone/CompoundSprite.h>

#include <SFML/Graphics.hpp>

namespace EXE{
	/// <summary>
	/// GameRegion with logic for demonstrating basic rotation demonstrations.
	/// </summary>
	/// <seealso cref="GameRegion" />
	class SwirlyDemoRegion : public DemoRegion {
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

		virtual void handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button) override;
		virtual void handleMouseMove(sf::Vector2f mousePosition) override;
		virtual void handleWheelScroll(float scrollDelta) override;



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
		GB::CompoundSprite* compSprite;
		sf::Sprite* compComponent1;
		sf::Sprite* compComponent2;
		sf::Sprite* compComponent3;
	};

}
