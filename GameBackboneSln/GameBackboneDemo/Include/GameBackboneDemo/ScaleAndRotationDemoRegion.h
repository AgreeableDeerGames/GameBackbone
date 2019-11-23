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
		RELATIVE_POSITION,
		TEXTURE_BASED_OFFSET,
	};

	/// <summary>
	/// GameRegion with logic for demonstrating basic rotation demonstrations.
	/// </summary>
	/// <seealso cref="GameRegion" />
	class ScaleAndRotationDemoRegion : public DemoRegion {
	public:
		// Constructors
		ScaleAndRotationDemoRegion(sf::RenderWindow & window);
		ScaleAndRotationDemoRegion() = delete;
		virtual ~ScaleAndRotationDemoRegion() = default;
		ScaleAndRotationDemoRegion(const ScaleAndRotationDemoRegion& other) = delete;
		ScaleAndRotationDemoRegion(ScaleAndRotationDemoRegion&& other) = delete;
		ScaleAndRotationDemoRegion& operator= (const ScaleAndRotationDemoRegion& other) = delete;
		ScaleAndRotationDemoRegion& operator= (ScaleAndRotationDemoRegion&& other) = delete;

		// Handle sf::Events
		virtual void handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button) override;
		virtual void handleMouseMove(sf::Vector2f mousePosition) override;
		virtual void handleWheelScroll(float scrollDelta) override;
		virtual void handleKeyPress(sf::Event::KeyEvent key) override;
		
	protected:
		// Initialization and Cleanup
		void init();
		void initGUI();
		virtual void reset() override;

		// Sprite textures
		std::unique_ptr<sf::Texture> arrowTexture;
		std::unique_ptr<sf::Texture> rotationArrowCenterTexture;
		std::unique_ptr<sf::Texture> rotationArrowLowTexture;
		std::unique_ptr<sf::Texture> rotationArrowLeftTexture;

		// Compound sprite stuff
		std::unique_ptr<GB::CompoundSprite> displaySprite;

		// Compound sprite selection
		ROTATION_INIT_TYPE selectedInitMethod = ROTATION_INIT_TYPE::RELATIVE_POSITION_CONSTRUCTOR;
		void selectRelativePositionConstructorCB();
		void selectRelativePositionAssignmentCB();
		void selectTextureOffsetCB();
	};

}
