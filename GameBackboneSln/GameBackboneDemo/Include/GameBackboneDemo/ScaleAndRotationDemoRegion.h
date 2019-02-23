#pragma once

#include <GameBackboneDemo/DemoRegion.h>

#include <GameBackbone/Core/CompoundSprite.h>

#include <SFML/Graphics.hpp>

#include <memory>

namespace EXE{

	/// <summary>
	/// Options for how to build the compound sprite
	/// </summary>
	enum ROTATION_INIT_TYPE {
		RELATIVE_POSITION_CONSTRUCTOR,
		RELATIVE_OFFSET,
		RELATIVE_POSITION,
		TEXTURE_BASED_OFFSET,
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
		std::unique_ptr<sf::Texture> navigatorTexture;
		std::unique_ptr<sf::Texture> rotationArrowCenterTexture;
		std::unique_ptr<sf::Texture> rotationArrowLowTexture;
		std::unique_ptr<sf::Texture> rotationArrowLeftTexture;

		// compound sprite stuff
		std::unique_ptr<GB::CompoundSprite> compSprite;
		std::unique_ptr<sf::Sprite> compComponent1;
		std::unique_ptr<sf::Sprite> compComponent2;
		std::unique_ptr<sf::Sprite> compComponent3;
		std::vector<sf::Sprite*> textureOffsetSprites;

		// compound sprite selection
		ROTATION_INIT_TYPE selectedInitMethod = ROTATION_INIT_TYPE::RELATIVE_POSITION_CONSTRUCTOR;
		void initMethod1CB();
		void initMethod2CB();
		void initMethod3CB();
		void initMethod4CB();

	private:
		// dtr
		void destroy();
	};

}
