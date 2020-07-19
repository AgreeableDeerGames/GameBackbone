#include "stdafx.h"

#include <GameBackbone/UserInput/GestureBind.h>
#include <GameBackbone/UserInput/EventComparitor.h>

using namespace GB;

BOOST_AUTO_TEST_SUITE(GestureBindTests)

	// Assert For type traits
	struct AlwaysTrueEventComparitor
	{
		bool operator()(const sf::Event&, const sf::Event&) { return true; }
	};
	static_assert(is_event_comparitor_v<AlwaysTrueEventComparitor>, "GestureBindTests SimpleEventComparitor does not meet EventComparitor requirements");
	static_assert(is_gesture_bind_v<BasicGestureBind<AlwaysTrueEventComparitor>>, "BasicGestureBind does not meet GestureBind requirements");
	static_assert(!is_gesture_bind_v<int>, "int is not a GestureBind");
	struct GestureBindWithWrongSignature
	{
		int processEvent(sf::Int64, const sf::Event&) { return true; }
	};
	static_assert(!is_gesture_bind_v<GestureBindWithWrongSignature>, "GestureBind type trait failed to check for return value");

	// Gesture Bind type for easy testing
	using TestGestureBind = BasicGestureBind<AlwaysTrueEventComparitor>;

	BOOST_AUTO_TEST_CASE(TestConstructor)
	{
		sf::Event upPressed = {};
		sf::Event downPressed = {};
		upPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Up, false, false, false, false };
		upPressed.type = sf::Event::KeyPressed;

		downPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Down, false, false, false, false };
		downPressed.type = sf::Event::KeyPressed;

		bool actionFired = false;

		std::vector<sf::Event> gesture{ upPressed, downPressed };
		TestGestureBind::EndType gestureBindEndType = TestGestureBind::EndType::Block;
		TestGestureBind bind(gesture, [&actionFired]() { actionFired = true; }, gestureBindEndType);

		// Check that the gesture was correctly stored
		bool identicalGestures = true;
		for (std::size_t i = 0; i < gesture.size() && i < bind.getGesture().size(); ++i)
		{
			if (gesture[i].key.code != bind.getGesture().at(i).key.code)
			{
				identicalGestures = false;
				break;
			}
		}
		BOOST_TEST(identicalGestures);

		// Check that name was correctly set
		BOOST_CHECK(bind.getEndType() == gestureBindEndType);

		// Check that the bound function is the expected one by running it
		std::invoke(bind.getAction());
		BOOST_CHECK(actionFired);
	}

	BOOST_AUTO_TEST_CASE(TestKeyboardGestureBind) 
	{
		KeyboardGestureBind bind({}, []() {});
	}

	BOOST_AUTO_TEST_CASE(TestJoystickGestureBind)
	{
		JoystickButtonGestureBind bind({}, []() {});
	}

	BOOST_AUTO_TEST_CASE(TestMouseButtonGestureBind)
	{
		MouseButtonGestureBind bind({}, []() {});
	}

	BOOST_AUTO_TEST_CASE(TestButtonGestureBind)
	{
		ButtonGestureBind bind({}, []() {});
	}

	BOOST_AUTO_TEST_CASE(TestEmptyGestureBindIgnoresInput)
	{
		TestGestureBind bind({}, [] {});
		auto[actionFired, readyForInput, inputConsumed] = bind.processEvent(0, {});
		BOOST_CHECK(!actionFired);
		BOOST_CHECK(!readyForInput);
		BOOST_CHECK(!inputConsumed);
	}

	BOOST_AUTO_TEST_CASE(TestEmptyGestureIsNotReadyForInput)
	{
		TestGestureBind bind({}, [] {});
		BOOST_CHECK(!bind.readyForInput());
	}

BOOST_AUTO_TEST_SUITE_END() // GestureBindTests