#pragma once

#include <GameBackbone/Core/GameRegion.h>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <string>
#include <iostream>

namespace GB {

	/// <summary>
	/// Base class meant to be inherited. Allows standard operation order for main game loop for clients of GB.
	/// Also provides simple and concise way to run the main game loop.
	///
	/// The execution order of the helper functions is 1) handleEvent, 2) update, 3) draw, 4) swapRegion
	///
	/// </summary>
	class libGameBackbone CoreEventController {
	public:
		// ctr / dtr
		CoreEventController();
		explicit CoreEventController(const std::string& windowName);
		CoreEventController(int windowWidth, int windowHeight);
		CoreEventController(int windowWidth, int windowHeight, const std::string& windowName);
		virtual ~CoreEventController();

		CoreEventController(const CoreEventController& other) = delete;
		CoreEventController& operator=(const CoreEventController& other) = delete;
		CoreEventController(CoreEventController&& other) noexcept = default;
		CoreEventController& operator=(CoreEventController&& other) noexcept = default;

		void runLoop();

		BasicGameRegion* getActiveRegion();
		sf::RenderWindow& getWindow();

	protected:
		void setActiveRegion(BasicGameRegion* activeRegion);

		// Loop operations
		/// <summary>
		/// Handles all window and user input events.
		/// </summary>
		/// <param name="event">The event.</param>
		virtual void handleEvents(sf::Int64 elapsedTime);
		virtual void update(sf::Int64 elapsedTime);
		virtual void draw();
		virtual void swapRegion();
		
	private:
		void repaint();

		BasicGameRegion* m_activeRegion;
		sf::RenderWindow m_window;
		sf::Clock m_updateClock;
	};

}

