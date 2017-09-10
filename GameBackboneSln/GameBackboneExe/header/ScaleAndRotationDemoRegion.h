#pragma once

#include <DemoRegion.h>

#include <Backbone/CompoundSprite.h>

#include <SFML/Graphics.hpp>

namespace EXE{

	/// <summary>
	/// Options for how to build the compound sprite
	/// </summary>
	enum ROTATION_INIT_TYPE {
		RELATIVE_POSITION_CONSTRUCTOR,
		RELATIVE_OFFSET,
		RELATIVE_POSITION
	};

	/// <summary>
	/// GameRegion with logic for demonstrating basic rotation demonstrations.
	/// </summary>
	/// <seealso cref="GameRegion" />
	class ScaleAndRotationDemoRegion : public DemoRegion {
	public:

		// ctr / dtr
		ScaleAndRotationDemoRegion();
		ScaleAndRotationDemoRegion(const ScaleAndRotationDemoRegion& other) = delete;
		ScaleAndRotationDemoRegion(ScaleAndRotationDemoRegion&& other) = delete;
		ScaleAndRotationDemoRegion& operator= (const ScaleAndRotationDemoRegion& other) = delete;
		ScaleAndRotationDemoRegion& operator= (ScaleAndRotationDemoRegion&& other) = delete;
		ScaleAndRotationDemoRegion(sf::RenderWindow & window);
		virtual ~ScaleAndRotationDemoRegion();

		// behavior
		virtual void behave(sf::Time currentTime) override;

		virtual void handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button) override;
		virtual void handleMouseMove(sf::Vector2f mousePosition) override;
		virtual void handleWheelScroll(float scrollDelta) override;



	protected:

		// ctr / dtr
		void init();
		virtual void reset() override;

		// helper functions
		void initGUI();

		// update logic storage
		sf::Time lastUpdateTime;

		// sprite textures
		sf::Texture* navigatorTexture;

		// compound sprite stuff
		GB::CompoundSprite* compSprite;
		sf::Sprite* compComponent1;
		sf::Sprite* compComponent2;
		sf::Sprite* compComponent3;

		// compound sprite selection
		ROTATION_INIT_TYPE selectedInitMethod;
		void initMethod1CB();
		void initMethod2CB();
		void initMethod3CB();

	private:
		// dtr
		void destroy();
	};

}
