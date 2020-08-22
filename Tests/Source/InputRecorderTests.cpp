#include "stdafx.h"

#include <GameBackbone/UserInput/EventComparitor.h>
#include <GameBackbone/UserInput/InputRecorder.h>
#include <GameBackbone/UserInput/GestureBind.h>


#include <SFML/Window/Event.hpp>

using namespace GB;

BOOST_AUTO_TEST_SUITE(InputRecorderTests)

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
			
			leftMousePressed.mouseButton = sf::Event::MouseButtonEvent{ sf::Mouse::Button::Left, 0, 0};
			leftMousePressed.type = sf::Event::MouseButtonPressed;
		}
	
		using TestRecorder = InputRecorder<KeyEventComparitor, KeyDownEventFilter>;
		using TestGestureBind = TestRecorder::ReturnBind;

		// Compare two binds. For now, only check that the Sequence on them is equal.
		bool CompareBinds(TestGestureBind lhs, TestGestureBind rhs)
		{
			// Get all underlying sf::Events from the GestureBinds
			const std::vector<sf::Event>& lhVec = lhs.getGesture();
			const std::vector<sf::Event>& rhVec = rhs.getGesture();

			// Return false if the lengths are different
			if (lhVec.size() != rhVec.size())
			{
				return false;
			}

			// Loop through all Gestures from each GestureMatchSginaler
			for (int ii = 0; ii < lhVec.size(); ii++)
			{
				// If any Comparison returns false, return false. 
				if (!std::invoke(KeyEventComparitor{}, lhVec[ii], rhVec[ii]))
				{
					return false;
				}
			}

			return true;
		}

		// Event for gesture
		sf::Event upPressed = {};
		sf::Event downPressed = {};
		sf::Event upReleased = {};
		sf::Event downReleased = {};
		sf::Event leftMousePressed = {};

		TestRecorder inputRecorder;
	};

	BOOST_AUTO_TEST_SUITE(ValidCases)

		BOOST_FIXTURE_TEST_CASE(TwoDifferentEvents, InputHandlerConsumeEventFixture)
		{
			TestGestureBind bindToCompare({ upPressed, downPressed }, [](){});

			inputRecorder.handleEvent(0, upPressed);
			inputRecorder.handleEvent(0, downPressed);
			TestGestureBind testBind = inputRecorder.getCompletedBind([](){});

			BOOST_TEST(CompareBinds(bindToCompare, testBind));
		}

		BOOST_FIXTURE_TEST_CASE(TwoSameEvents, InputHandlerConsumeEventFixture)
		{
			TestGestureBind bindToCompare({ upPressed, upPressed }, []() {});

			inputRecorder.handleEvent(0, upPressed);
			inputRecorder.handleEvent(0, upPressed);
			TestGestureBind testBind = inputRecorder.getCompletedBind([]() {});

			BOOST_TEST(CompareBinds(bindToCompare, testBind));
		}

		BOOST_FIXTURE_TEST_CASE(FilteredEvent, InputHandlerConsumeEventFixture)
		{
			TestGestureBind bindToCompare({ upPressed, upPressed }, []() {});

			inputRecorder.handleEvent(0, upPressed);
			inputRecorder.handleEvent(0, leftMousePressed);
			inputRecorder.handleEvent(0, upPressed);
			TestGestureBind testBind = inputRecorder.getCompletedBind([]() {});

			BOOST_TEST(CompareBinds(bindToCompare, testBind));
		}
		
		BOOST_FIXTURE_TEST_CASE(FilteredUpEvent, InputHandlerConsumeEventFixture)
		{
			TestGestureBind bindToCompare({ upPressed, upPressed }, []() {});

			inputRecorder.handleEvent(0, upPressed);
			inputRecorder.handleEvent(0, upReleased);
			inputRecorder.handleEvent(0, upPressed);
			inputRecorder.handleEvent(0, upReleased);
			TestGestureBind testBind = inputRecorder.getCompletedBind([]() {});

			BOOST_TEST(CompareBinds(bindToCompare, testBind));
		}

	BOOST_AUTO_TEST_SUITE_END() // ValidCases
	
BOOST_AUTO_TEST_SUITE_END() // InputRecorderTests
