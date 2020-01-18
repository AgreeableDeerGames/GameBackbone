#pragma once

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
	/// The execution order of the helper functions is 1) preHandleEvent 2) handleEvent 3) postHandleEvent,
	/// 4) preDraw, 5) coreDraw, 6) postDraw, 7) preUpdate, 8) coreUpdate, 9) postUpdate
	///
	/// </summary>
	template <class Child>
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
					childCastThis()->baseHandleEvent(event);
				}

				childCastThis()->draw();

				childCastThis()->update();
			}
		}

		/// <summary>
		/// Changes the active region to the passed game region.
		/// </summary>
		/// <param name="activeRegion">The new active GameRegion.</param>
		void setActiveRegion(GameRegion* activeRegion) {
			m_activeRegion = activeRegion;
		}

protected:
		//events

		/// <summary>
		/// Handles all window and user input events.
		/// </summary>
		/// <param name="event">The event.</param>
		void baseHandleEvent(sf::Event& event) {
			childCastThis()->preHandleEvent(event);
			childCastThis()->handleEvent(event);
			childCastThis()->postHandleEvent(event);
		}

		/// <summary>
		/// Called before baseHandleEvent Place logic to be executed before the main event logic here.
		/// </summary>
		/// <param name="event">The event.</param>
		void preHandleEvent(sf::Event& /*event*/) {}

		/// <summary>
		/// Called after handleEvent. Place logic to be executed after the main event logic here.
		/// </summary>
		/// <param name="event">The event.</param>
		void postHandleEvent(sf::Event& /*event*/) {}

		//draw

		/// <summary>
		/// Calls all draw helper functions then displays the window.
		/// </summary>
		void draw() { 	
			m_window->clear();
			childCastThis()->preDraw();
			childCastThis()->coreDraw();
			childCastThis()->postDraw();

			m_window->display();
		}

		/// <summary>
		/// Called before coreDraw. PLace logic to be executed before the main draw logic here.
		/// </summary>
		void preDraw() {}

		/// <summary>
		/// Primary drawing logic. Draws every drawable object in the game region.
		/// </summary>
		void coreDraw() {
			// Draw m_activeRegion so it can draw its drawables.
			m_window->draw(*m_activeRegion);
		}

		/// <summary>
		/// called after core draw. Place logic to be executed after the main draw logic here.
		/// </summary>
		void postDraw() {}

		//update

		/// <summary>
		/// Calls all update helper functions (preUpdate, coreUpdate, postUpdate).
		/// </summary>
		void update() {
			childCastThis()->preUpdate();
			childCastThis()->coreUpdate();
			childCastThis()->postUpdate();
		}

		/// <summary>
		/// called before coreUpdate. Place logic meant to execute before the main update logic here.
		/// </summary>
		void preUpdate() {}

		/// <summary>
		/// Primary update logic. Runs behavior logic for active GameRegion. Updates every Updatable object in the active GameRegion.
		/// </summary>
		void coreUpdate() {
			sf::Time elapsedTime = m_updateClock.restart();
			m_activeRegion->update(elapsedTime.asMicroseconds());
		}

		/// <summary>
		/// Executes after coreUpdate. Place logic meant to update after the main update logic here.
		/// </summary>
		void postUpdate() {}

		sf::Clock m_updateClock;
		sf::RenderWindow* m_window;
		GameRegion* m_activeRegion;

	private:
		Child* childCastThis() {
			return static_cast<Child*>(this);
		}

	};

}

