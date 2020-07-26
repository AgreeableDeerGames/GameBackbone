#include "stdafx.h"

#include <GameBackbone/UserInput/EventFilter.h>


using namespace GB;

BOOST_AUTO_TEST_SUITE(EventFilterTests)

	struct SFEventFixture
	{
		SFEventFixture()
		{
			// Keys
			upPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Up, false, false, false, false };
			upPressed.type = sf::Event::KeyPressed;

			downPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Down, false, false, false, false };
			downPressed.type = sf::Event::KeyPressed;

			upReleased.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Up, false, false, false, false };
			upReleased.type = sf::Event::KeyReleased;

			downReleased.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Down, false, false, false, false };
			downReleased.type = sf::Event::KeyReleased;

			// Mouse
			mouseButton1Pressed.mouseButton = sf::Event::MouseButtonEvent();
			mouseButton1Pressed.mouseButton.button = sf::Mouse::Button::Left;
			mouseButton1Pressed.type = sf::Event::MouseButtonPressed;

			mouseButton1Released.mouseButton = sf::Event::MouseButtonEvent();
			mouseButton1Released.mouseButton.button = sf::Mouse::Button::Left;
			mouseButton1Released.type = sf::Event::MouseButtonReleased;

			// Joystick
			joystickButton1Pressed.joystickButton = sf::Event::JoystickButtonEvent();
			joystickButton1Pressed.joystickButton.button = sf::Joystick::R;
			joystickButton1Pressed.type = sf::Event::JoystickButtonPressed;

			joystickButton1Released.joystickButton = sf::Event::JoystickButtonEvent();
			joystickButton1Released.joystickButton.button = sf::Joystick::R;
			joystickButton1Released.type = sf::Event::JoystickButtonReleased;

		}


		// Keys
		sf::Event upPressed = {};
		sf::Event downPressed = {};
		sf::Event upReleased = {};
		sf::Event downReleased = {};

		// Mouse
		sf::Event mouseButton1Pressed = {};
		sf::Event mouseButton1Released = {};

		// Joystick
		sf::Event joystickButton1Pressed = {};
		sf::Event joystickButton1Released = {};

	};

	template <class EventFilterType>
	void checkEventFilter(EventFilterType&& filter, const std::vector<sf::Event>& passEvents, const std::vector<sf::Event>& failEvents)
	{
		for (const auto& event : passEvents)
		{
			BOOST_TEST(std::invoke(filter, event));
		}
		for (const auto& event : failEvents)
		{
			BOOST_TEST(!std::invoke(filter, event));
		}
	}

	BOOST_FIXTURE_TEST_CASE(KeyDownEventFilterAcceptsCorrectEvents, SFEventFixture)
	{
		checkEventFilter(KeyDownEventFilter{}, {upPressed, downPressed}, {upReleased, downReleased, mouseButton1Pressed, mouseButton1Released, joystickButton1Pressed, joystickButton1Released});
	}

	BOOST_FIXTURE_TEST_CASE(KeyUpEventFilterAcceptsCorrectEvents, SFEventFixture)
	{
		checkEventFilter(KeyUpEventFilter{}, { upReleased, downReleased }, { upPressed, downPressed, mouseButton1Pressed, mouseButton1Released, joystickButton1Pressed, joystickButton1Released });
	}

	BOOST_FIXTURE_TEST_CASE(AnyKeyEventFilterAcceptsCorrectEvents, SFEventFixture)
	{
		checkEventFilter(AnyKeyEventFilter{}, { upReleased, downReleased, upPressed, downPressed }, { mouseButton1Pressed, mouseButton1Released, joystickButton1Pressed, joystickButton1Released });
	}

	BOOST_FIXTURE_TEST_CASE(MouseButtonDownEventFilterAcceptsCorrectEvents, SFEventFixture)
	{
		checkEventFilter(MouseButtonDownEventFilter{}, { mouseButton1Pressed }, { upReleased, downReleased, upPressed, downPressed, mouseButton1Released, joystickButton1Pressed, joystickButton1Released });
	}

	BOOST_FIXTURE_TEST_CASE(MouseButtonUpEventFilterAcceptsCorrectEvents, SFEventFixture)
	{
		checkEventFilter(MouseButtonUpEventFilter{}, { mouseButton1Released }, { upReleased, downReleased, upPressed, downPressed, mouseButton1Pressed, joystickButton1Pressed, joystickButton1Released });
	}

	BOOST_FIXTURE_TEST_CASE(AnyMouseButtoEventFilterAcceptsCorrectEvents, SFEventFixture)
	{
		checkEventFilter(AnyMouseButtonEventFilter{}, { mouseButton1Released, mouseButton1Pressed }, { upReleased, downReleased, upPressed, downPressed, joystickButton1Pressed, joystickButton1Released });
	}

	BOOST_FIXTURE_TEST_CASE(JoystickButtonDownEventFilterAcceptsCorrectEvents, SFEventFixture)
	{
		checkEventFilter(JoystickButtonDownEventFilter{}, { joystickButton1Pressed }, { upReleased, downReleased, upPressed, downPressed, mouseButton1Released, mouseButton1Pressed, joystickButton1Released });
	}

	BOOST_FIXTURE_TEST_CASE(JoystickButtonUpEventFilterAcceptsCorrectEvents, SFEventFixture)
	{
		checkEventFilter(JoystickButtonUpEventFilter{}, { joystickButton1Released }, { upReleased, downReleased, upPressed, downPressed, mouseButton1Released, mouseButton1Pressed, joystickButton1Pressed });
	}

	BOOST_FIXTURE_TEST_CASE(AnyJoystickButtonEventFilterAcceptsCorrectEvents, SFEventFixture)
	{
		checkEventFilter(AnyJoystickButtonEventFilter{}, { joystickButton1Released, joystickButton1Pressed }, { upReleased, downReleased, upPressed, downPressed, mouseButton1Released, mouseButton1Pressed });
	}

	BOOST_FIXTURE_TEST_CASE(AnyButtonDownEventFilterAcceptsCorrectEvents, SFEventFixture)
	{
		checkEventFilter(AnyButtonDownEventFilter{}, { upPressed, downPressed, mouseButton1Pressed, joystickButton1Pressed }, { upReleased, downReleased, mouseButton1Released, joystickButton1Released });
	}

	BOOST_FIXTURE_TEST_CASE(AnyButtonUpEventFilterAcceptsCorrectEvents, SFEventFixture)
	{
		checkEventFilter(AnyButtonUpEventFilter{}, { upReleased, downReleased, mouseButton1Released, joystickButton1Released }, { upPressed, downPressed, mouseButton1Pressed, joystickButton1Pressed } );
	}

	BOOST_FIXTURE_TEST_CASE(AnyEventFilterAcceptsAllEvents, SFEventFixture)
	{
		checkEventFilter(AnyEventFilter{}, { upReleased, downReleased, mouseButton1Released, joystickButton1Released, upPressed, downPressed, mouseButton1Pressed, joystickButton1Pressed }, {} );
	}

BOOST_AUTO_TEST_SUITE_END() // EventFilterTests
