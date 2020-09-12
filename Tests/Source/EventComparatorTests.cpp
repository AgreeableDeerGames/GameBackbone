#include "stdafx.h"

#include <GameBackbone/UserInput/EventComparator.h>

#include <functional>
#include <type_traits>
#include <vector>

using namespace GB;

BOOST_AUTO_TEST_SUITE(EventComparatorTests)


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

	template <
		class EventComparatorType,
		std::enable_if_t<is_event_comparator_v<EventComparatorType>, bool> = true
	>
	void checkEventCompare(EventComparatorType&& compare, const sf::Event& targetEvent, const std::vector<sf::Event>& passEvents, const std::vector<sf::Event>& failEvents)
	{
		for (const auto& event : passEvents)
		{
			BOOST_TEST(std::invoke(compare, targetEvent, event));
		}
		for (const auto& event : failEvents)
		{
			BOOST_TEST(!std::invoke(compare, targetEvent, event));
		}
	}

	BOOST_FIXTURE_TEST_CASE(KeyEventComparatorCorrectlyComparesEvents, SFEventFixture)
	{
		checkEventCompare(KeyEventComparator{}, upPressed, { upPressed }, { downPressed, upReleased, mouseButton1Pressed, mouseButton1Released, joystickButton1Pressed, joystickButton1Released });
		checkEventCompare(KeyEventComparator{}, upReleased, { upReleased }, { upPressed, downPressed, mouseButton1Pressed, mouseButton1Released, joystickButton1Pressed, joystickButton1Released } );
	}

BOOST_AUTO_TEST_SUITE_END() // EventComparatorTests
