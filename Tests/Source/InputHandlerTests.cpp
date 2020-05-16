#include "stdafx.h"

#include <GameBackbone/Core/GameRegion.h>
#include <GameBackbone/UserInput/InputHandler.h>
#include <GameBackbone/UserInput/Gesture.h>

#include <memory>
#include <vector>

using namespace GB;

BOOST_AUTO_TEST_SUITE(InputHandlerTests)
	BOOST_AUTO_TEST_CASE(InputHandlerTest)
	{
		// Crate gesture
		Gesture gesture;
		sf::Event e;
		e.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Up, false, false, false, false };
		e.type = sf::Event::KeyPressed;
		gesture.addEvent(GB::milliseconds_d{ 0 }, GB::milliseconds_d{ 10 }, e);
		gesture.addEvent(GB::milliseconds_d{ 0 }, GB::milliseconds_d{ 10 }, e);
		
		// Create handler
		bool gestureComplete = false;
		InputHandler handler;
		handler.addGesture(gesture, [&gestureComplete]() { gestureComplete = true; });

		// Send events to gesture
		handler.consumeEvent(e);
		BOOST_TEST(!gestureComplete);
		handler.consumeEvent(e);
		BOOST_TEST(gestureComplete);
	}

BOOST_AUTO_TEST_SUITE_END() // InputHandlerTests