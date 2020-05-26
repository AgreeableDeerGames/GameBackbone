#include "stdafx.h"

#include <GameBackbone/Core/GameRegion.h>
#include <GameBackbone/UserInput/InputHandler.h>

#include <memory>
#include <vector>

using namespace GB;

BOOST_AUTO_TEST_SUITE(InputHandlerTests)
	BOOST_AUTO_TEST_CASE(InputHandlerTest)
	{
		// Event for gesture
		sf::Event e;
		e.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Up, false, false, false, false };
		e.type = sf::Event::KeyPressed;
		
		// Create handler
		int gesture1Count = 0;
		int gesture2Count = 0;
		InputHandler handler;
		// handler.addGesture(gesture, [&gestureComplete]() { gestureComplete = true; });
		handler.addGesture({e}, [&gesture1Count]() { ++gesture1Count; });
		handler.addGesture({ e, e }, [&gesture2Count]() { ++gesture2Count; });

		// Send events to gesture
		handler.consumeEvent(e);
		BOOST_TEST(gesture1Count == 1);
		BOOST_TEST(gesture2Count == 0);

		handler.update(5);
		handler.consumeEvent(e);
		BOOST_TEST(gesture1Count == 1);
		BOOST_TEST(gesture2Count == 1);

		handler.update(5000);
		handler.consumeEvent(e);
		BOOST_TEST(gesture1Count == 2);
		BOOST_TEST(gesture2Count == 1);

		handler.update(5000);
		handler.consumeEvent(e);
		BOOST_TEST(gesture1Count == 3);
		BOOST_TEST(gesture2Count == 1);
	}


BOOST_AUTO_TEST_SUITE_END() // InputHandlerTests