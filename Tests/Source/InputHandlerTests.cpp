#include "stdafx.h"

#include <GameBackbone/Core/GameRegion.h>
#include <GameBackbone/UserInput/InputHandler.h>
#include <GameBackbone/UserInput/InputRouter.h>
#include <GameBackbone/UserInput/ButtonPressGestureHandler.h>
#include <GameBackbone/UserInput/EventComparitor.h>

using namespace GB;


BOOST_AUTO_TEST_SUITE(InputHandlerTests)

	class TestInputHandler : public InputHandler
	{
	public:
		bool handleEvent(sf::Int64 /*elapsedTime*/, const sf::Event& /*event*/) override
		{
			std::cout << "button hold" << std::endl;
			return true;
		}
	};

	BOOST_AUTO_TEST_CASE(TestCompile)
	{
		InputRouter router{ ButtonPressGestureHandler<KeyEventComparitor>{}, TestInputHandler{} };
		router.handleEvent(1, sf::Event{});

		BasicGestureBind<KeyEventComparitor> bind({}, []() {}, "", 1, BasicGestureBind<KeyEventComparitor>::EndType::Reset);
		bind.processEvent(1, sf::Event{});
	}

	static_assert(is_event_comparitor<KeyEventComparitor>::value, "wat");
	static_assert(is_event_comparitor_v<KeyEventComparitor>, "wat");

BOOST_AUTO_TEST_SUITE_END() // InputHandlerTests



//
//#include <memory>
//#include <vector>
//
//using namespace GB;
//
//BOOST_AUTO_TEST_SUITE(InputHandlerTests)
//
//	struct InputHandlerConsumeEventFixture
//	{
//		InputHandlerConsumeEventFixture()
//		{
//			upPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Up, false, false, false, false };
//			upPressed.type = sf::Event::KeyPressed;
//
//			downPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Down, false, false, false, false };
//			downPressed.type = sf::Event::KeyPressed;
//
//			upReleased.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Up, false, false, false, false };
//			upReleased.type = sf::Event::KeyReleased;
//
//			downReleased.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Down, false, false, false, false };
//			downReleased.type = sf::Event::KeyReleased;
//		}
//
//		// Event for gesture
//		sf::Event upPressed = {};
//		sf::Event downPressed = {};
//		sf::Event upReleased = {};
//		sf::Event downReleased = {};
//
//		// Create handler
//		int gesture1Count = 0;
//		int gesture2Count = 0;
//		InputHandler handler;
//	};
//
//	BOOST_FIXTURE_TEST_CASE(CompletingGestureFiresAction, InputHandlerConsumeEventFixture)
//	{
//		bool actionFired = false;
//		handler.addGesture({ upPressed }, [&actionFired]() { actionFired = true; });
//		handler.consumeEvent(upPressed);
//		BOOST_TEST(actionFired == true);
//	}
//
//	BOOST_FIXTURE_TEST_CASE(UnboundEventDoesNotFireAction, InputHandlerConsumeEventFixture)
//	{
//		bool actionFired = false;
//		handler.addGesture({ upPressed }, [&actionFired]() { actionFired = true; });
//		handler.consumeEvent(downPressed);
//		BOOST_TEST(actionFired == false);
//	}
//
//	BOOST_FIXTURE_TEST_CASE(CompletingGestureFiresActionForMultiInputGesture, InputHandlerConsumeEventFixture)
//	{
//		bool actionFired = false;
//		handler.addGesture({ upPressed, upPressed, downPressed, downPressed }, [&actionFired]() { actionFired = true; });
//		handler.consumeEvent(upPressed);
//		BOOST_TEST(actionFired == false);
//		handler.consumeEvent(upPressed);
//		BOOST_TEST(actionFired == false);
//		handler.consumeEvent(downPressed);
//		BOOST_TEST(actionFired == false);
//		handler.consumeEvent(downPressed);
//
//		BOOST_TEST(actionFired == true);
//	}
//
//	BOOST_FIXTURE_TEST_CASE(CompletingGestureFiresCorrectActionWithMultipleGesturesBound, InputHandlerConsumeEventFixture)
//	{
//		bool correctActionFired = false;
//		bool wrongActionFired = false;
//		handler.addGesture({ upPressed }, [&correctActionFired]() { correctActionFired = true; });
//		handler.addGesture({ downPressed }, [&wrongActionFired]() { wrongActionFired = true; });
//		handler.consumeEvent(upPressed);
//		BOOST_TEST(correctActionFired == true);
//		BOOST_TEST(wrongActionFired == false);
//	}
//
//	BOOST_FIXTURE_TEST_CASE(GivenTwoGesturesWithOneASubsetOfTheOtherEachWillFireOnce, InputHandlerConsumeEventFixture)
//	{
//		bool action1Fired = false;
//		bool action2Fired = false;
//		handler.addGesture({ upPressed, upPressed }, [&action1Fired]() { action1Fired = true; });
//		handler.addGesture({ upPressed, upPressed, upPressed }, [&action2Fired]() { action2Fired = true; });
//
//		handler.consumeEvent(upPressed);
//		handler.consumeEvent(upPressed);
//
//		// Only subset should have fired here
//		BOOST_TEST(action1Fired == true);
//		BOOST_TEST(action2Fired == false);
//
//		handler.consumeEvent(upPressed);
//
//		// Now superset should have fired
//		BOOST_TEST(action1Fired == true);
//		BOOST_TEST(action2Fired == true);
//	}
//
//	BOOST_FIXTURE_TEST_CASE(GivenThreeGesturesEachASubsetOfTheNextEachWillFireOnce, InputHandlerConsumeEventFixture)
//	{
//		bool action1Fired = false;
//		bool action2Fired = false;
//		bool action3Fired = false;
//
//		handler.addGesture({ upPressed }, [&action1Fired]() { action1Fired = true; });
//		handler.addGesture({ upPressed, upPressed }, [&action2Fired]() { action2Fired = true; });
//		handler.addGesture({ upPressed, upPressed, upPressed }, [&action3Fired]() { action3Fired = true; });
//		handler.consumeEvent(upPressed);
//		handler.consumeEvent(upPressed);
//		handler.consumeEvent(upPressed);
//		BOOST_TEST(action1Fired == true);
//		BOOST_TEST(action2Fired == true);
//		BOOST_TEST(action2Fired == true);
//	}
//
//	BOOST_FIXTURE_TEST_CASE(GestureCannotCompleteAgainUntilTheMinimumTimeHasPassed, InputHandlerConsumeEventFixture)
//	{
//		int actionFiredCount = 0;
//		handler.addGesture({ upPressed }, [&actionFiredCount]() { ++actionFiredCount; });
//		handler.consumeEvent(upPressed);
//		handler.consumeEvent(upPressed);
//		BOOST_TEST(actionFiredCount == 1);
//
//		for (std::size_t i = 0; i < InputHandler::defaultMinTimeBetweenTrigger - sf::Int64{ 1 }; ++i)
//		{
//			handler.update(sf::Int64{ 1 });
//			handler.consumeEvent(upPressed);
//			BOOST_TEST(actionFiredCount == 1);
//		}
//
//		handler.update(sf::Int64{ 1 });
//		handler.consumeEvent(upPressed);
//		BOOST_TEST(actionFiredCount == 2);
//	}
//
//	BOOST_FIXTURE_TEST_CASE(GestureCannotCompleteAgainUntilACustomMinimumTimeHasPassed, InputHandlerConsumeEventFixture)
//	{
//		int actionFiredCount = 0;
//		sf::Int64 minTimeBetweenTrigger = 1122;
//		handler.addGesture({ upPressed }, [&actionFiredCount]() { ++actionFiredCount; }, 200000, minTimeBetweenTrigger);
//		handler.consumeEvent(upPressed);
//		handler.consumeEvent(upPressed);
//		BOOST_TEST(actionFiredCount == 1);
//
//		for (std::size_t i = 0; i < static_cast<std::size_t>(minTimeBetweenTrigger -  1); ++i)
//		{
//			handler.update(sf::Int64{ 1 });
//			handler.consumeEvent(upPressed);
//			BOOST_TEST(actionFiredCount == 1);
//		}
//
//		handler.update(sf::Int64{ 1 });
//		handler.consumeEvent(upPressed);
//		BOOST_TEST(actionFiredCount == 2);
//	}
//
//	BOOST_FIXTURE_TEST_CASE(DisabledGestureIsNotEnabledByOtherSuccessfulGesture, InputHandlerConsumeEventFixture)
//	{
//		int actionFiredCount = 0;
//		handler.addGesture({ upPressed }, [&actionFiredCount]() { ++actionFiredCount; });
//		handler.addGesture({ upPressed, downPressed }, [](){});
//		handler.consumeEvent(upPressed);
//		handler.consumeEvent(downPressed);
//		handler.consumeEvent(upPressed);
//		BOOST_TEST(actionFiredCount == 1);
//	}
//
//	BOOST_FIXTURE_TEST_CASE(InvalidInputFollowedByValidGestureFiresAction, InputHandlerConsumeEventFixture)
//	{
//		bool actionFired = false;
//		handler.addGesture({ upPressed }, []() {});
//		handler.addGesture({ downPressed, upPressed }, [&actionFired]() { actionFired = true; });
//		handler.consumeEvent(upPressed);
//		handler.consumeEvent(downPressed);
//		handler.consumeEvent(upPressed);
//		BOOST_TEST(actionFired == true);
//	}
//
//	BOOST_FIXTURE_TEST_CASE(WhenMaxTimeBetweenInputsElapsesGestureResets, InputHandlerConsumeEventFixture)
//	{
//		bool actionFired = false;
//		handler.addGesture({ upPressed, upPressed }, [&actionFired]() { actionFired = true; });
//		handler.consumeEvent(upPressed); // Starts gesture
//		handler.update(InputHandler::defaultMaxTimeBetweenInputs + 1); // Resets gesture
//		handler.consumeEvent(upPressed); // Starts gesture again
//		BOOST_TEST(actionFired == false);
//		handler.consumeEvent(upPressed); // finish gesture again
//		BOOST_TEST(actionFired == true);
//	}
//
//	BOOST_FIXTURE_TEST_CASE(WhenCustomMaxTimeBetweenInputsElapsesGestureResets, InputHandlerConsumeEventFixture)
//	{
//		sf::Int64 maxTimeBetweenInputs = 1234;
//		bool actionFired = false;
//		handler.addGesture({ upPressed, upPressed }, [&actionFired]() { actionFired = true; }, maxTimeBetweenInputs, 0);
//		handler.consumeEvent(upPressed); // Starts gesture
//		handler.update(maxTimeBetweenInputs + 1); // Resets gesture
//		handler.consumeEvent(upPressed); // Starts gesture again
//		BOOST_TEST(actionFired == false);
//		handler.consumeEvent(upPressed); // finish gesture again
//		BOOST_TEST(actionFired == true);
//	}
//
//	BOOST_AUTO_TEST_CASE(test)
//	{
//		// Event for gesture
//		sf::Event e;
//		e.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Up, false, false, false, false };
//		e.type = sf::Event::KeyPressed;
//		
//		// Create handler
//		int gesture1Count = 0;
//		int gesture2Count = 0;
//		InputHandler handler;
//		// handler.addGesture(gesture, [&gestureComplete]() { gestureComplete = true; });
//		handler.addGesture({e}, [&gesture1Count]() { ++gesture1Count; });
//		handler.addGesture({ e, e }, [&gesture2Count]() { ++gesture2Count; });
//
//		// Send events to gesture
//		handler.consumeEvent(e);
//		BOOST_TEST(gesture1Count == 1);
//		BOOST_TEST(gesture2Count == 0);
//
//		handler.update(5);
//		handler.consumeEvent(e);
//		BOOST_TEST(gesture1Count == 1);
//		BOOST_TEST(gesture2Count == 1);
//
//		handler.update(5000);
//		handler.consumeEvent(e);
//		BOOST_TEST(gesture1Count == 2);
//		BOOST_TEST(gesture2Count == 1);
//
//		handler.update(5000);
//		handler.consumeEvent(e);
//		BOOST_TEST(gesture1Count == 3);
//		BOOST_TEST(gesture2Count == 1);
//	}
//
//
//BOOST_AUTO_TEST_SUITE_END() // InputHandlerTests