#pragma once

#include <GameBackbone/Core/ActivationProvider.h>
#include <GameBackbone/Core/GameRegion.h>

#include <string>
#include <iostream>

namespace GB {

	static const int DEFAULT_WINDOW_HEIGHT = 700;
	static const int DEFAULT_WINDOW_WIDTH = 700;
	static const std::string DEFAULT_WINDOW_NAME = "GameBackbone";

	/// <summary>
	/// Base class meant to be inherited. Allows standard operation order for main game loop for clients of GB.
	/// Also provides simple and concise way to run the main game loop.
	/// Clients should always override the empty handleCoreEvent.
	///
	/// The execution order of the helper functions is 1) preHandleEvent 2) handleGuiEvent 3) handleCoreEvent, 4) postHandleEvent,
	/// 5) preDraw, 6) coreDraw, 7) postDraw, 8) preUpdate, 9) coreUpdate, 10) postUpdate
	///
	/// </summary>
	class CoreEventController {
	public:
		//ctr / dtr

		/// <summary>
		/// Initializes a new instance of the <see cref="CoreEventController"/> class. Window width, height, and name are default.
		/// </summary>
		CoreEventController() : CoreEventController(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_NAME) {}

		/// <summary>
		/// Initializes a new instance of the <see cref="CoreEventController"/> class. Window width and height are default.
		/// </summary>
		/// <param name="windowName">Name of the window.</param>
		explicit CoreEventController(const std::string& windowName) : CoreEventController(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, windowName) {}

		/// <summary>
		/// Initializes a new instance of the <see cref="CoreEventController"/> class. Window name is default.
		/// </summary>
		/// <param name="windowWidth">Width of the window.</param>
		/// <param name="windowHeight">Height of the window.</param>
		CoreEventController(int windowWidth, int windowHeight) : CoreEventController(windowWidth, windowHeight, DEFAULT_WINDOW_NAME){}

		/// <summary>
		/// Initializes a new instance of the <see cref="CoreEventController"/> class.
		/// </summary>
		/// <param name="windowWidth">Width of the window.</param>
		/// <param name="windowHeight">Height of the window.</param>
		/// <param name="windowName">Name of the window.</param>
		CoreEventController(int windowWidth, int windowHeight, const std::string & windowName) {
			m_window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), windowName);
			m_activeRegion = nullptr;
		}

		/// <summary>
		/// Finalizes an instance of the <see cref="CoreEventController"/> class.
		/// </summary>
		~CoreEventController() {
			delete m_window;
		}

		CoreEventController(const CoreEventController& other) = delete;
		CoreEventController& operator=(const CoreEventController& other) = delete;
		CoreEventController(CoreEventController&& other) noexcept = default;
		CoreEventController& operator=(CoreEventController&& other) noexcept = default;

		//operations
		void runLoop() {
			sf::Event event;

			// Ensure the window is fully opened before we do any work on it.
			while (m_window->isOpen() == false) {
				continue;
			}

			while (m_window->isOpen()) {
				while (m_window->pollEvent(event)) {
					handleEvent(event);
				}

				draw();
				update();
				swapRegion();
			}
		}
		
		BasicGameRegion* getActiveRegion()
		{
			return m_activeRegion;
		}

protected:
		//events

		/// <summary>
		/// Handles all window and user input events.
		/// </summary>
		/// <param name="event">The event.</param>
		virtual void handleEvent(sf::Event& event) {
			preHandleEvent(event);
			if (!handleGuiEvent(event)) {
				handleCoreEvent(event);
			}
			postHandleEvent(event);
		}

		/// <summary>
		/// Handles the GUI event.
		/// </summary>
		/// <param name="event">The event.</param>
		/// <returns>Returns true if the event was consumed by the GUI. Returns false otherwise.</returns>
		virtual bool handleGuiEvent(sf::Event& event) {
			return getActiveRegion()->getGUI().handleEvent(event);
		}

		/// <summary>
		/// Handles the non GUI event.
		/// </summary>
		/// <param name="event">The event.</param>
		/// <returns>Returns true if the event was consumed. Returns false otherwise.</returns>
		virtual bool handleCoreEvent(sf::Event& /*event*/) {
			return false;
		}

		/// <summary>
		/// Called before handleGuiEvent and handleCoreEvent. Place logic to be executed before the main event logic here.
		/// </summary>
		/// <param name="event">The event.</param>
		virtual void preHandleEvent(sf::Event& /*event*/) {}

		/// <summary>
		/// Called after handleGuiEvent and handleCoreEvent. Place logic to be executed after the main event logic here.
		/// </summary>
		/// <param name="event">The event.</param>
		virtual void postHandleEvent(sf::Event& /*event*/) {}

		//draw

		/// <summary>
		/// Calls all draw helper functions then displays the window.
		/// </summary>
		virtual void draw() {
			m_window->clear();
			preDraw();
			coreDraw();
			postDraw();

			m_window->display();
		}

		/// <summary>
		/// Called before coreDraw. PLace logic to be executed before the main draw logic here.
		/// </summary>
		virtual void preDraw() {}

		/// <summary>
		/// Primary drawing logic. Draws every drawable object in the game region and the active regions gui.
		/// </summary>
		virtual void coreDraw() {
			// Draw m_activeRegion so it can draw its drawables.
			m_window->draw(*getActiveRegion());

			getActiveRegion()->getGUI().draw();
		}

		/// <summary>
		/// called after core draw. Place logic to be executed after the main draw logic here.
		/// </summary>
		virtual void postDraw() {}

		//update

		/// <summary>
		/// Calls all update helper functions (preUpdate, coreUpdate, postUpdate).
		/// </summary>
		virtual void update() {
			preUpdate();
			coreUpdate();
			postUpdate();
		}

		/// <summary>
		/// called before coreUpdate. Place logic meant to execute before the main update logic here.
		/// </summary>
		virtual void preUpdate() {}

		/// <summary>
		/// Primary update logic. Runs behavior logic for active GameRegion. Updates every Updatable object in the active GameRegion.
		/// </summary>
		virtual void coreUpdate() {
			sf::Time elapsedTime = m_updateClock.restart();
			getActiveRegion()->update(elapsedTime.asMicroseconds());
		}

		/// <summary>
		/// Executes after coreUpdate. Place logic meant to update after the main update logic here.
		/// </summary>
		virtual void postUpdate() {}

		/// <summary>
		/// Changes to the next active region if prompted by the current active region.
		/// </summary>
		virtual void swapRegion()
		{
			BasicGameRegion& newRegion = getActiveRegion()->getNextRegion();
			if (m_activeRegion != &newRegion)
			{
				m_activeRegion->setNextRegion(*m_activeRegion);
				m_activeRegion = &newRegion;
			}
		}
		
		BasicGameRegion* m_activeRegion;
		sf::Clock m_updateClock;
		sf::RenderWindow* m_window;
	};

}

