#pragma once
#include "stdafx.h"
#include "AnimatedSprite.h"
#include "AnimationSet.h"
#include "GameRegion.h"
#include "Updatable.h"
#include "CompoundSprite.h"
#include "NavigationDemoRegion.h"

#include <TGUI/TGUI.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <vector>
#include <string>

namespace GB {

	libGameBackbone class CoreEventController {
	public:
		//ctrs / dtr
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
		virtual void handleNonGuiEvent(sf::Event& event);
		virtual void preHandleEvent();
		virtual void postHandleEvent();

		//draw
		virtual void draw();
		virtual void preDraw();
		virtual void postDraw();

		//update
		virtual void update();
		virtual void preUpdate();
		virtual void postUpdate();


		sf::Clock updateClock;
		sf::RenderWindow* window;

	};

}

