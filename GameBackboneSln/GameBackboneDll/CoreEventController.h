#pragma once
#include "stdafx.h"
#include "GameRegion.h"

#include <string>

namespace GB {

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
		virtual bool handleNonGuiEvent(sf::Event& event);
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

