#pragma once

#include <Backbone\GameRegion.h>

#include <string>

namespace GB {
	
	/// <summary>
	/// Base class meant to be inherited. Allows standard operation order for main game loop for clients of GB.
	/// Also provides simple and concise way to run the main game loop.
	/// Clients should always override the empty handleCoreEvent.
	///
	/// The execution order of the helper functions is 1) preHandleEvent 2) handleGuiEvent 3) handleCoreEvent, 4) postHandleEvent,
	/// 5) preDraw, 6) coreDraw, 7) postDraw, 8) preUpdate, 9) coreUpdate, 10) postUpdate
	///
	/// </summary>
	class libGameBackbone CoreEventController {
	public:
		//ctr / dtr
		CoreEventController();
		CoreEventController(const std::string& windowName);
		CoreEventController(int windowWidth, int windowHeight, const std::string& windowName);
		CoreEventController(int windowWidth, int windowHeight);
		CoreEventController(const CoreEventController& other) = delete;
		CoreEventController(CoreEventController&& other) = default;
		CoreEventController& operator=(const CoreEventController& other) = delete;
		CoreEventController& operator=(CoreEventController&& other) = default;
		virtual ~CoreEventController();

		//operations
		void runLoop();

protected:
		//events
		virtual void handleEvent(sf::Event& event);
		virtual bool handleGuiEvent(sf::Event& event);
		virtual bool handleCoreEvent(sf::Event& event);
		virtual void preHandleEvent(sf::Event& event);
		virtual void postHandleEvent(sf::Event& event);

		//draw
		virtual void draw();
		virtual void preDraw();
		virtual void coreDraw();
		virtual void postDraw();

		//update
		virtual void update();
		virtual void preUpdate();
		virtual void coreUpdate();
		virtual void postUpdate();

		sf::Clock updateClock;
		sf::RenderWindow* window;
		GameRegion* activeRegion;

	};

}

