#include "stdafx.h"

#include <GameBackbone/UserInput/ButtonPressGestureHandler.h>
#include <GameBackbone/UserInput/EventComparitor.h>

using namespace GB;


BOOST_AUTO_TEST_SUITE(ButtonPressGestureHandlerTests)

	struct InputHandlerConsumeEventFixture
	{
		InputHandlerConsumeEventFixture()
		{
			upPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Up, false, false, false, false };
			upPressed.type = sf::Event::KeyPressed;
	
			downPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Down, false, false, false, false };
			downPressed.type = sf::Event::KeyPressed;
	
			upReleased.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Up, false, false, false, false };
			upReleased.type = sf::Event::KeyReleased;
	
			downReleased.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Down, false, false, false, false };
			downReleased.type = sf::Event::KeyReleased;
		}
	
		// Event for gesture
		sf::Event upPressed = {};
		sf::Event downPressed = {};
		sf::Event upReleased = {};
		sf::Event downReleased = {};
	
		// Create handler
		int gesture1Count = 0;
		int gesture2Count = 0;
		ButtonPressGestureHandler<ButtonEventComparitor> handler;
	};

	BOOST_FIXTURE_TEST_CASE(HandleEventFalseWhenNoGesturesAreBound, InputHandlerConsumeEventFixture)
	{
		BOOST_TEST(!handler.handleEvent(0, upPressed));
	}

	BOOST_FIXTURE_TEST_CASE(HandleEventReturnsTrueWhenEventMatchesGesture, InputHandlerConsumeEventFixture)
	{
		decltype(handler)::GestureBind bind(
			{ upPressed, upPressed },
			[]() {},
			"",
			1,
			decltype(handler)::GestureBind::EndType::Continuous);

		handler.addGesture(bind);
		BOOST_TEST(handler.handleEvent(0, upPressed));
	}

	BOOST_FIXTURE_TEST_CASE(HandleEventReturnsFalseWhenEventDoesNotMatchGesture, InputHandlerConsumeEventFixture)
	{
		decltype(handler)::GestureBind bind(
			{ upPressed, upPressed },
			[]() {},
			"",
			1,
			decltype(handler)::GestureBind::EndType::Continuous);

		handler.addGesture(bind);
		BOOST_TEST(!handler.handleEvent(0, downPressed));
	}

	BOOST_FIXTURE_TEST_CASE(CompletingGestureFiresAction, InputHandlerConsumeEventFixture)
	{
		bool actionFired = false;
		decltype(handler)::GestureBind bind(
			{ upPressed },
			[&actionFired]() { actionFired = true; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Continuous);

		handler.addGesture(bind);
		handler.handleEvent(0, upPressed);
		BOOST_TEST(actionFired == true);
	}

	BOOST_FIXTURE_TEST_CASE(UnboundEventDoesNotFireAction, InputHandlerConsumeEventFixture)
	{
		bool actionFired = false;
		decltype(handler)::GestureBind bind(
			{ upPressed },
			[&actionFired]() { actionFired = true; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Continuous);

		handler.handleEvent(0, downPressed);
		BOOST_TEST(actionFired == false);
	}

	BOOST_FIXTURE_TEST_CASE(CompletingGestureFiresActionForMultiInputGesture, InputHandlerConsumeEventFixture)
	{
		bool actionFired = false;
		decltype(handler)::GestureBind bind(
			{ upPressed, upPressed, downPressed, downPressed },
			[&actionFired]() { actionFired = true; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Continuous);

		handler.addGesture(bind);
		handler.handleEvent(0, upPressed);
		BOOST_TEST(actionFired == false);
		handler.handleEvent(0, upPressed);
		BOOST_TEST(actionFired == false);
		handler.handleEvent(0, downPressed);
		BOOST_TEST(actionFired == false);
		handler.handleEvent(0, downPressed);

		BOOST_TEST(actionFired == true);
	}

	BOOST_FIXTURE_TEST_CASE(CompletingGestureFiresCorrectActionWithMultipleGesturesBound, InputHandlerConsumeEventFixture)
	{
		bool correctActionFired = false;
		bool wrongActionFired = false;

		decltype(handler)::GestureBind bind(
			{ upPressed },
			[&correctActionFired]() { correctActionFired = true; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Continuous);

		decltype(handler)::GestureBind bind2(
			{ downPressed },
			[&wrongActionFired]() { wrongActionFired = true; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Continuous);

		handler.addGesture(bind);
		handler.addGesture(bind2);
		handler.handleEvent(0, upPressed);
		BOOST_TEST(correctActionFired == true);
		BOOST_TEST(wrongActionFired == false);
	}

	// TODO: test cases 1 - 5 from issue

BOOST_AUTO_TEST_SUITE_END() // ButtonPressGestureHandlerTests
