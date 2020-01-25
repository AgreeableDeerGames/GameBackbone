#pragma once

#include <GameBackbone/Core/GameRegion.h>

#include <string>
#include <iostream>

namespace GB {

	/// <summary>
	/// Base class meant to be inherited. Allows standard operation order for main game loop for clients of GB.
	/// Also provides simple and concise way to run the main game loop.
	///
	/// The execution order of the helper functions is 1) handleEvent, 2) draw, 3) update, 4) swapRegion
	///
	/// </summary>
	class libGameBackbone CoreEventController {
	public:
		// ctr / dtr
		CoreEventController();
		explicit CoreEventController(const std::string& windowName);
		CoreEventController(int windowWidth, int windowHeight);
		CoreEventController(int windowWidth, int windowHeight, const std::string& windowName);
		~CoreEventController();

		CoreEventController(const CoreEventController& other) = delete;
		CoreEventController& operator=(const CoreEventController& other) = delete;
		CoreEventController(CoreEventController&& other) noexcept = default;
		CoreEventController& operator=(CoreEventController&& other) noexcept = default;

		// operations
		void runLoop();

		BasicGameRegion* getActiveRegion();
		sf::RenderWindow& getWindow();

	protected:
		void setActiveRegion(BasicGameRegion* activeRegion);

		// Loop operations
		virtual void handleEvent(sf::Event& event);
		virtual bool handleGuiEvent(sf::Event& event);
		virtual bool handleCoreEvent(sf::Event& /*event*/);
		virtual void draw();
		virtual void update();
		virtual void swapRegion();
		
	private:
		BasicGameRegion* m_activeRegion;
		sf::RenderWindow m_window;
		sf::Clock m_updateClock;
	};

}

