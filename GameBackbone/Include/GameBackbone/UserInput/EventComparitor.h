#pragma once

#include <SFML/Window/Event.hpp>

namespace GB
{
	template <typename T>
	using is_event_comparitor = std::conjunction<
		std::is_invocable<T, const sf::Event&, const sf::Event&>,
		std::is_same<typename std::invoke_result<T, const sf::Event&, const sf::Event&>::type, bool>
	>;

	template <typename T>
	static inline constexpr bool is_event_comparitor_v = is_event_comparitor<T>::value;

	class KeyEventComparitor
	{
	public:
		bool operator()(const sf::Event& userEvent, const sf::Event& gestureEvent) const
		{
			// Short circuit if the type doesn't match or if the types are not handlable.
			if (userEvent.type != gestureEvent.type || userEvent.type != sf::Event::KeyPressed || userEvent.type != sf::Event::KeyReleased)
			{
				return false;
			}

			if (userEvent.key.code == gestureEvent.key.code && userEvent.key.code != sf::Keyboard::Unknown)
			{
				return true;
			}

			return false;
		}
	};

	class JoystickButtonEventComparitor
	{
	public:
		bool operator()(const sf::Event& userEvent, const sf::Event& gestureEvent) const
		{
			// Short circuit if the type doesn't match or if the types are not handlable.
			if (userEvent.type != gestureEvent.type || userEvent.type != sf::Event::JoystickButtonPressed || userEvent.type != sf::Event::JoystickButtonReleased)
			{
				return false;
			}

			if (userEvent.joystickButton.button == gestureEvent.joystickButton.button)
			{
				return true;
			}

			return false;
		}
	};

	class MouseButtonEventComparitor
	{
	public:
		bool operator()(const sf::Event& userEvent, const sf::Event& gestureEvent) const
		{
			// Short circuit if the type doesn't match or if the types are not handlable.
			if (userEvent.type != gestureEvent.type || userEvent.type != sf::Event::MouseButtonPressed || userEvent.type != sf::Event::MouseButtonReleased)
			{
				return false;
			}

			if (userEvent.mouseButton.button == gestureEvent.mouseButton.button)
			{
				return true;
			}

			return false;
		}
	};

	class ButtonEventComparitor
	{
	public:
		bool operator()(const sf::Event& userEvent, const sf::Event& gestureEvent) const
		{
			// Short circuit if the type doesn't match or if the types are not handlable.
			if (userEvent.type != gestureEvent.type)
			{
				return false;
			}
			
			// Forward gestures to each comparitor.
			return KeyEventComparitor{}(userEvent, gestureEvent)
				|| JoystickButtonEventComparitor{}(userEvent, gestureEvent)
				|| MouseButtonEventComparitor{}(userEvent, gestureEvent);
		}
	};
}
