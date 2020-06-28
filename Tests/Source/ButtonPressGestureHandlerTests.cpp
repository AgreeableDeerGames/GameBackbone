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

			aPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::A, false, false, false, false };
			aPressed.type = sf::Event::KeyPressed;

			bPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::B, false, false, false, false };
			bPressed.type = sf::Event::KeyPressed;

			cPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::C, false, false, false, false };
			cPressed.type = sf::Event::KeyPressed;

			dPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::D, false, false, false, false };
			dPressed.type = sf::Event::KeyPressed;

			ePressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::E, false, false, false, false };
			ePressed.type = sf::Event::KeyPressed;

			wPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::W, false, false, false, false };
			wPressed.type = sf::Event::KeyPressed;
		}
	
		// Event for gesture
		sf::Event upPressed = {};
		sf::Event downPressed = {};
		sf::Event upReleased = {};
		sf::Event downReleased = {};

		sf::Event aPressed = {};
		sf::Event bPressed = {};
		sf::Event cPressed = {};
		sf::Event dPressed = {};
		sf::Event ePressed = {};
		sf::Event wPressed = {};
	
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
			decltype(handler)::GestureBind::EndType::Block);

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
			decltype(handler)::GestureBind::EndType::Block);

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
			decltype(handler)::GestureBind::EndType::Block);

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
			decltype(handler)::GestureBind::EndType::Block);

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
			decltype(handler)::GestureBind::EndType::Block);

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
			decltype(handler)::GestureBind::EndType::Block);

		decltype(handler)::GestureBind bind2(
			{ downPressed },
			[&wrongActionFired]() { wrongActionFired = true; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Block);

		handler.addGesture(bind);
		handler.addGesture(bind2);
		handler.handleEvent(0, upPressed);
		BOOST_TEST(correctActionFired == true);
		BOOST_TEST(wrongActionFired == false);
	}

	BOOST_FIXTURE_TEST_CASE(GestureDoesNotCompleteWhenTimeExpires, InputHandlerConsumeEventFixture)
	{
		bool actionFired = false;

		decltype(handler)::GestureBind bind(
			{ upPressed, upPressed },
			[&actionFired]() { actionFired = true; },
			"",
			10,
			decltype(handler)::GestureBind::EndType::Block);


		handler.addGesture(bind);
		handler.handleEvent(0, upPressed);
		handler.handleEvent(20, upPressed);
		BOOST_TEST(actionFired == false);
	}

	BOOST_FIXTURE_TEST_CASE(GestureCanRestartAfterTimeExpires, InputHandlerConsumeEventFixture)
	{
		bool actionFired = false;

		decltype(handler)::GestureBind bind(
			{ upPressed, upPressed },
			[&actionFired]() { actionFired = true; },
			"",
			10,
			decltype(handler)::GestureBind::EndType::Block);


		handler.addGesture(bind);
		handler.handleEvent(0, upPressed);

		// This fails the first attempt at the gesture, but starts the second one
		handler.handleEvent(20, upPressed);
		BOOST_TEST(actionFired == false);

		// This finishes the second attempt at the gesture
		handler.handleEvent(0, upPressed);
		BOOST_TEST(actionFired == true);
	}

	/*
	 *	# Case 1
	 * 
	 *	|     gesture       | bound action |
	 *	|       :----:      | :----:       |
	 *	|  a -> b -> c ->d  | Action 1     |
	 *	|         e         | Action 2     |
	 *
	 *  User inputs:
     *  `a -> b -> c -> e`
	 *  
	 *  Result:
     *  Action 2 is fired
	 */
	BOOST_FIXTURE_TEST_CASE(Case1, InputHandlerConsumeEventFixture)
	{
		bool correctActionFired = false;
		bool wrongActionFired = false;

		decltype(handler)::GestureBind bind(
			{ aPressed, bPressed, cPressed, dPressed },
			[&wrongActionFired]() { wrongActionFired = true; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Block);

		decltype(handler)::GestureBind bind2(
			{ ePressed },
			[&correctActionFired]() { correctActionFired = true; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Block);

		handler.addGesture(bind);
		handler.addGesture(bind2);
		handler.handleEvent(0, aPressed);
		handler.handleEvent(0, bPressed);
		handler.handleEvent(0, cPressed);
		handler.handleEvent(0, ePressed);
		BOOST_TEST(correctActionFired == true);
		BOOST_TEST(wrongActionFired == false);
	}

	/*
	 *  # Case 2
	 * 
	 *  |  gesture | bound action |
	 *	|  :----:  |    :----:    |
	 *	|  a -> b  |    Action 1  |
	 *	|     c    |    Action 2  |
	 *
	 * 	User inputs:
	 *	`a -> b -> c -> a -> b`
	 * 
	 *  Result:
	 *  Action 1 Fires
     *  Action 2 Fires
     *  Action 1 Fires
	 */
	BOOST_FIXTURE_TEST_CASE(Case2, InputHandlerConsumeEventFixture)
	{
		int action1Fired = 0;
		int action2Fired = 0;

		decltype(handler)::GestureBind bind(
			{ aPressed, bPressed },
			[&action1Fired]() { ++action1Fired; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Block);

		decltype(handler)::GestureBind bind2(
			{ cPressed },
			[&action2Fired]() { ++action2Fired; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Block);

		handler.addGesture(bind);
		handler.addGesture(bind2);

		// Action 1 should fire
		handler.handleEvent(0, aPressed);
		handler.handleEvent(0, bPressed);
		BOOST_TEST(action1Fired == 1);

		// Action 2 should fire
		handler.handleEvent(0, cPressed);
		BOOST_TEST(action2Fired == 1);

		// Action 1 should fire again
		handler.handleEvent(0, aPressed);
		handler.handleEvent(0, bPressed);

		// Make sure final counts are correct
		BOOST_TEST(action1Fired == 2);
		BOOST_TEST(action2Fired == 1);
	}

	/*
	 *  # Case 3
	 *
	 *  |   gesture    |   bound action   |   End Type  |
	 *  |    :----:    |      :----:      |    :---:    |
	 *  |      w       |     Action 1     |    Block    |
	 *  |    w -> w    |     Action 2     |    Block    |
	 *  | w -> w -> w  |     Action 3     |    Block    |
	 *
	 *
	 *  User Inputs
	 *  `w -> w -> w`
	 *
	 *  Result:
	 *  Action 1 fires
	 *  Action 2 fires
	 *  Action 3 fires
	 */
	BOOST_FIXTURE_TEST_CASE(Case3, InputHandlerConsumeEventFixture)
	{
		int action1Fired = 0;
		int action2Fired = 0;
		int action3Fired = 0;

		decltype(handler)::GestureBind bind(
			{ wPressed },
			[&action1Fired]() { ++action1Fired; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Block);

		decltype(handler)::GestureBind bind2(
			{ wPressed, wPressed },
			[&action2Fired]() { ++action2Fired; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Block);

		decltype(handler)::GestureBind bind3(
			{ wPressed, wPressed, wPressed },
			[&action3Fired]() { ++action3Fired; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Block);


		handler.addGesture(bind);
		handler.addGesture(bind2);
		handler.addGesture(bind3);

		handler.handleEvent(0, wPressed);
		BOOST_CHECK(action1Fired == 1);
		BOOST_CHECK(action2Fired == 0);
		BOOST_CHECK(action3Fired == 0);
		handler.handleEvent(0, wPressed);
		BOOST_CHECK(action1Fired == 1);
		BOOST_CHECK(action2Fired == 1);
		BOOST_CHECK(action3Fired == 0);
		handler.handleEvent(0, wPressed);
		BOOST_CHECK(action1Fired == 1);
		BOOST_CHECK(action2Fired == 1);
		BOOST_CHECK(action3Fired == 1);
	}


	/*
	 *  # Case 3.1
	 *  
	 *  |    gesture   | bound action |  End Type  |
	 *  |    :----:    |    :----:    |    :---:   |
	 *  |      w       |   Action 1   | Continuous |
	 *  |    w -> w    |   Action 2   | Continuous |
	 *  | w -> w -> w  |   Action 3   | Continuous |
	 *  
	 *  User Inputs
	 *  `w -> w -> w`
	 *  
	 *  Result:
	 *  Action 1 fires
	 *  Action 1 fires
	 *  Action 2 fires
	 *  Action 1 fires
	 *  Action 2 fires
	 *  Action 3 fires
	 */
	BOOST_FIXTURE_TEST_CASE(Case3_1, InputHandlerConsumeEventFixture)
	{
		int action1Fired = 0;
		int action2Fired = 0;
		int action3Fired = 0;

		decltype(handler)::GestureBind bind(
			{ wPressed },
			[&action1Fired]() { ++action1Fired; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Continuous);

		decltype(handler)::GestureBind bind2(
			{ wPressed, wPressed },
			[&action2Fired]() { ++action2Fired; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Continuous);

		decltype(handler)::GestureBind bind3(
			{ wPressed, wPressed, wPressed },
			[&action3Fired]() { ++action3Fired; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Continuous);


		handler.addGesture(bind);
		handler.addGesture(bind2);
		handler.addGesture(bind3);

		handler.handleEvent(0, wPressed);
		BOOST_CHECK(action1Fired == 1);
		BOOST_CHECK(action2Fired == 0);
		BOOST_CHECK(action3Fired == 0);
		handler.handleEvent(0, wPressed);
		BOOST_CHECK(action1Fired == 2);
		BOOST_CHECK(action2Fired == 1);
		BOOST_CHECK(action3Fired == 0);
		handler.handleEvent(0, wPressed);
		BOOST_CHECK(action1Fired == 3);
		BOOST_CHECK(action2Fired == 2);
		BOOST_CHECK(action3Fired == 1);
	}



	/*
	 *  # Case 3.2
	 *  
	 *  |   gesture    | bound action  | End Type |
	 *  |    :----:    |    :----:     |   :---:  |
	 *  |      w       |    Action 1   |   Stop   |
	 *  |    w -> w    |    Action 2   |   Reset  |
	 *  | w -> w -> w  |    Action 3   |   Reset  |
	 *  
	 *  User Inputs
	 *  `w -> w -> w -> w -> w`
	 *  	
	 *  Result:
     *  Action 1 fires
     *  Action 2 fires
     *  Action 3 fires
     *  Action 2 fires
	 */
	BOOST_FIXTURE_TEST_CASE(Case3_2, InputHandlerConsumeEventFixture)
	{
		int action1Fired = 0;
		int action2Fired = 0;
		int action3Fired = 0;

		decltype(handler)::GestureBind bind(
			{ wPressed },
			[&action1Fired]() { ++action1Fired; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Block);

		decltype(handler)::GestureBind bind2(
			{ wPressed, wPressed },
			[&action2Fired]() { ++action2Fired; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Reset);

		decltype(handler)::GestureBind bind3(
			{ wPressed, wPressed, wPressed },
			[&action3Fired]() { ++action3Fired; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Reset);


		handler.addGesture(bind);
		handler.addGesture(bind2);
		handler.addGesture(bind3);

		handler.handleEvent(0, wPressed);
		BOOST_CHECK(action1Fired == 1);
		BOOST_CHECK(action2Fired == 0);
		BOOST_CHECK(action3Fired == 0);

		handler.handleEvent(0, wPressed);
		BOOST_CHECK(action1Fired == 1);
		BOOST_CHECK(action2Fired == 1);
		BOOST_CHECK(action3Fired == 0);

		handler.handleEvent(0, wPressed);
		BOOST_CHECK(action1Fired == 1);
		BOOST_CHECK(action2Fired == 1);
		BOOST_CHECK(action3Fired == 1);

		handler.handleEvent(0, wPressed);
		BOOST_CHECK(action1Fired == 1);
		BOOST_CHECK(action2Fired == 2);
		BOOST_CHECK(action3Fired == 1);

		handler.handleEvent(0, wPressed);
		BOOST_CHECK(action1Fired == 1);
		BOOST_CHECK(action2Fired == 2);
		BOOST_CHECK(action3Fired == 1);

	}


	/*
     *  # Case 4
     *  |      gesture      | bound action |
     *  |       :----:      |     :----:   |
     *  |  a -> b -> c ->d  |   Action 1   |
     *  |         d         |   Action 2   |
     *  
     *  User inputs:
     *  `a -> b -> c -> d`
     *  
     *  Result:
     *  Action 1 fires
     *  Action 2 does NOT fire
	 */
	BOOST_FIXTURE_TEST_CASE(Case4, InputHandlerConsumeEventFixture)
	{
		int action1Fired = 0;
		int action2Fired = 0;

		decltype(handler)::GestureBind bind(
			{ aPressed, bPressed, cPressed, dPressed },
			[&action1Fired]() { ++action1Fired; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Block);

		decltype(handler)::GestureBind bind2(
			{ dPressed },
			[&action2Fired]() { ++action2Fired; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Block);

		handler.addGesture(bind);
		handler.addGesture(bind2);

		handler.handleEvent(0, aPressed);
		BOOST_CHECK(action1Fired == 0);
		BOOST_CHECK(action2Fired == 0);

		handler.handleEvent(0, bPressed);
		BOOST_CHECK(action1Fired == 0);
		BOOST_CHECK(action2Fired == 0);

		handler.handleEvent(0, cPressed);
		BOOST_CHECK(action1Fired == 0);
		BOOST_CHECK(action2Fired == 0);

		handler.handleEvent(0, dPressed);
		BOOST_CHECK(action1Fired == 1);
		BOOST_CHECK(action2Fired == 0);
	}

	/*
     *  # Case 5
     *  |    gesture    | bound action |
     *  |     :----:    |    :----:    |
     *  |  a -> b -> c  |   Action 1   |
     *  
     *  User inputs:
     *  `a -> b -> a -> b -> c`
     *  
     *  Result:
     *  Action 1 fires 1 time
	 */
	BOOST_FIXTURE_TEST_CASE(Case5, InputHandlerConsumeEventFixture)
	{
		int action1Fired = 0;

		decltype(handler)::GestureBind bind(
			{ aPressed, bPressed, cPressed },
			[&action1Fired]() { ++action1Fired; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Block);

		handler.addGesture(bind);

		handler.handleEvent(0, aPressed);
		BOOST_CHECK(action1Fired == 0);

		handler.handleEvent(0, bPressed);
		BOOST_CHECK(action1Fired == 0);

		handler.handleEvent(0, aPressed);
		BOOST_CHECK(action1Fired == 0);

		handler.handleEvent(0, bPressed);
		BOOST_CHECK(action1Fired == 0);

		handler.handleEvent(0, cPressed);
		BOOST_CHECK(action1Fired == 1);
	}

	/*
     *  # Case 5.1
     *  |     gesture    | bound action |
     *  |     :----:     |    :----:    |
     *  |  a -> b -> c   |   Action 1   |
     *  |       a        |   Action 2   |
     *  
     *  User inputs:
     *  `a -> a -> b -> c`
     *  
     *  Result:
     *  Action 2 fires n times, Action 1 fires 1 time
	 */
	BOOST_FIXTURE_TEST_CASE(Case5_1, InputHandlerConsumeEventFixture)
	{
		int action1Fired = 0;
		int action2Fired = 0;

		decltype(handler)::GestureBind bind(
			{ aPressed, bPressed, cPressed },
			[&action1Fired]() { ++action1Fired; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Block);

		decltype(handler)::GestureBind bind2(
			{ aPressed },
			[&action2Fired]() { ++action2Fired; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Block);

		handler.addGesture(bind);
		handler.addGesture(bind2);

		handler.handleEvent(0, aPressed);
		BOOST_CHECK(action1Fired == 0);
		BOOST_CHECK(action2Fired == 1);

		handler.handleEvent(0, aPressed);
		BOOST_CHECK(action1Fired == 0);
		BOOST_CHECK(action2Fired == 2);

		handler.handleEvent(0, bPressed);
		BOOST_CHECK(action1Fired == 0);
		BOOST_CHECK(action2Fired == 2);

		handler.handleEvent(0, cPressed);
		BOOST_CHECK(action1Fired == 1);
		BOOST_CHECK(action2Fired == 2);
	}

	/*
     *  
     *  # Case 5.2
     *  |     gesture    | bound action |
     *  |     :----:     |    :----:    |
     *  |  a -> b -> c   |   Action 1   |
     *  |     a  -> b    |   Action 2   |
     *  
     *  User inputs:
     *  `a -> a -> b -> c`
     *  
     *  Result:
     *  Action 2 fires 1 time, Action 1 fires 1 time
	 */
	BOOST_FIXTURE_TEST_CASE(Case5_2, InputHandlerConsumeEventFixture)
	{
		int action1Fired = 0;
		int action2Fired = 0;

		decltype(handler)::GestureBind bind(
			{ aPressed, bPressed, cPressed },
			[&action1Fired]() { ++action1Fired; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Block);

		decltype(handler)::GestureBind bind2(
			{ aPressed, bPressed },
			[&action2Fired]() { ++action2Fired; },
			"",
			1,
			decltype(handler)::GestureBind::EndType::Block);

		handler.addGesture(bind);
		handler.addGesture(bind2);

		handler.handleEvent(0, aPressed);
		BOOST_CHECK(action1Fired == 0);
		BOOST_CHECK(action2Fired == 0);

		handler.handleEvent(0, aPressed);
		BOOST_CHECK(action1Fired == 0);
		BOOST_CHECK(action2Fired == 0);

		handler.handleEvent(0, bPressed);
		BOOST_CHECK(action1Fired == 0);
		BOOST_CHECK(action2Fired == 1);

		handler.handleEvent(0, cPressed);
		BOOST_CHECK(action1Fired == 1);
		BOOST_CHECK(action2Fired == 1);
	}

BOOST_AUTO_TEST_SUITE_END() // ButtonPressGestureHandlerTests
