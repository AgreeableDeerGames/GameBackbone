#pragma once

#include <Backbone/GameRegion.h>

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

	protected:


		// initialization
		void initGui();

		// protected handles and callbacks
		virtual void returnToMenuCB();

		// gui
		tgui::Button::Ptr returnToMenuButton;

	};

}
