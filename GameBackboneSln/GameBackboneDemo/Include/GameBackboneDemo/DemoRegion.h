#pragma once

#include <GameBackbone/Core/GameRegion.h>

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

namespace EXE {

	class DemoRegion : public GB::GameRegion {
	public:

		/// <summary>A shared_ptr to DemoRegion</summary>
		using Ptr = std::shared_ptr<DemoRegion>;

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

		// Relations
		void addChild(DemoRegion::Ptr child);

	protected:
		// Initialization and Cleanup
		void initGui();
		virtual void reset();

		// Handle TGUI Callbacks
		virtual void returnToMenuCB();

		// region relations
		DemoRegion* parent;
		std::vector<DemoRegion::Ptr> children;

		// GUI Members
		tgui::Button::Ptr returnToMenuButton;
		tgui::Button::Ptr resetButton;
	};

}
