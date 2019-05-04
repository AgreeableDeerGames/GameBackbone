#pragma once

#include <GameBackbone/Core/GameRegion.h>

#include <SFML/Graphics.hpp>

namespace EXE {

	class DemoRegion : public GB::GameRegion {
	public:
		// Constructors
		DemoRegion(sf::RenderWindow & window);
		virtual ~DemoRegion() = default;

		DemoRegion() = delete;
		DemoRegion(const DemoRegion& other) = delete;
		DemoRegion(DemoRegion&& other) = delete;
		DemoRegion& operator= (const DemoRegion& other) = delete;
		DemoRegion& operator= (DemoRegion&& other) = delete;

		// Handle sf::Events
		virtual void handleMouseMove(sf::Vector2f mousePosition);
		virtual void handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button);
		virtual void handleWheelScroll(float scrollDelta);
		virtual void handleKeyPress(sf::Event::KeyEvent key);
		virtual void handleKeyRelease(sf::Event::KeyEvent key);

	protected:
		// Initialization and Cleanup
		void initGui();
		void resetRegion();

		// Handle TGUI Callbacks
		virtual void returnToMenuCB();

		// GUI Members
		tgui::Button::Ptr returnToMenuButton;
		tgui::Button::Ptr resetButton;
	};

}
