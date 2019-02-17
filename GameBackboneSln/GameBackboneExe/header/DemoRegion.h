#pragma once

#include <GameBackbone/Core/GameRegion.h>

#include <SFML/Graphics.hpp>

namespace EXE {

	class DemoRegion : public GB::GameRegion {
	public:
		// ctr / dtr
		DemoRegion();
		DemoRegion(const DemoRegion& other) = delete;
		DemoRegion(DemoRegion&& other) = delete;
		DemoRegion& operator= (const DemoRegion& other) = delete;
		DemoRegion& operator= (DemoRegion&& other) = delete;
		DemoRegion(sf::RenderWindow & window);
		virtual ~DemoRegion() = default;


		// public handles and callbacks
		virtual void handleMouseMove(sf::Vector2f mousePosition);
		virtual void handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button);
		virtual void handleWheelScroll(float scrollDelta);
		virtual void handleKeyPress(sf::Event::KeyEvent key);
		virtual void handleKeyRelease(sf::Event::KeyEvent key);


	protected:
		// initialization
		void initGui();

		void resetRegion();

		// protected handles and callbacks
		virtual void returnToMenuCB();

		// gui
		tgui::Button::Ptr returnToMenuButton;
		tgui::Button::Ptr resetButton;
	};

}
