#pragma once

#include <GameBackbone/Core/GameRegion.h>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <string>
#include <iostream>

namespace GB {
	
	/// @brief Abstract class that provides a standard operation order for main game loop for clients of GB.
	///		Also provides simple and concise way to run the main game loop.
	///
	///		The execution order of the helper functions is 1) handleEvent, 2) update, 3) draw, 4) swapRegion
	class libGameBackbone CoreEventController {
	public:

		/// @brief Initializes a new instance of the CoreEventController class. Window width, height, and name are default.
		CoreEventController();

		/// @brief Initializes a new instance of the CoreEventController class. Window width and height are default.
		/// @param windowName Name of the window
		explicit CoreEventController(const std::string& windowName);

		/// @brief Initializes a new instance of the CoreEventController class. Window name is default.
		/// @param windowWidth Width of the window.
		/// @param windowHeight Height of the window.
		CoreEventController(int windowWidth, int windowHeight);

		/// @brief Initializes a new instance of the CoreEventController class.
		/// @param windowWidth Width of the window.
		/// @param windowHeight Height of the window.
		/// @param windowName Name of the window.
		CoreEventController(int windowWidth, int windowHeight, const std::string& windowName);

		/// @brief Destroys this CoreEventController
		virtual ~CoreEventController();

		/// @brief Move construct A CoreEventController
		/// @param other The CoreEventController to move
		CoreEventController(CoreEventController&& other) noexcept = default;

		/// @brief Move assign a CoreEventController
		/// @param other The CoreEventController to move
		/// @return This
		CoreEventController& operator=(CoreEventController&& other) noexcept = default;

		CoreEventController(const CoreEventController& other) = delete;
		CoreEventController& operator=(const CoreEventController& other) = delete;

		/// @brief Begin the main loop of the CoreEventController. This call is blocking.
		///		This loop will exit after the window managed by this instance is closed.
		void runLoop();

		/// @brief Returns the currently active game region, on which all of the operation are being performed.
		/// @return The currently active game region.
		BasicGameRegion* getActiveRegion();

		/// @brief Returns the window owned by this CoreEventController.
		sf::RenderWindow& getWindow();

	protected:

		/// @brief Set the active region on the CoreEventController.
		/// @param activeRegion The new active region. This should never be set to nullptr.
		void setActiveRegion(BasicGameRegion* activeRegion);
		
		/// @brief Handles all window and user input events.
		/// @param elapsedTime The time since events were last handled
		virtual void handleEvents(sf::Int64 elapsedTime);

		/// @brief Primary update logic. Runs behavior logic for active GameRegion. Updates every Updatable object in the active GameRegion.
		/// @param elapsedTime The time since the last update of the active GameRegion
		virtual void update(sf::Int64 elapsedTime);

		/// @brief Clears the screen. Draws the active region.
		virtual void draw();

		/// @brief Changes to the next active region if prompted by the current active region.
		virtual void swapRegion();
		
	private:

		/// @brief Draws the active region.
		void repaint();

		BasicGameRegion* m_activeRegion;
		sf::RenderWindow m_window;
		sf::Clock m_updateClock;
		sf::Int64 m_timeSinceLastHandledEvent;
	};
}

