#pragma once

#include <SFML/Window/Event.hpp>

namespace GB
{

	template <typename T>
	using is_event_filter = std::conjunction<
		std::is_invocable<T, const sf::Event&>,
		std::is_same<typename std::invoke_result<T, const sf::Event&>::type, bool>
	>;

	template <typename T>
	static inline constexpr bool is_event_filter_v = is_event_filter<T>::value;

	class KeyDownEventFilter
	{
	public:
		bool operator()(const sf::Event& userEvent)
		{
			return userEvent.type == sf::Event::KeyPressed;
		}
	};

	class KeyUpEventFilter
	{
	public:
		bool operator()(const sf::Event& userEvent)
		{
			return userEvent.type == sf::Event::KeyReleased;
		}
	};

	class AnyKeyEventFilter
	{
	public:
		bool operator()(const sf::Event& userEvent)
		{
			return KeyDownEventFilter{}(userEvent) || KeyUpEventFilter{}(userEvent);
		}
	};

	class MouseButtonDownEventFilter
	{
	public:
		bool operator()(const sf::Event& userEvent)
		{
			return userEvent.type == sf::Event::MouseButtonPressed;
		}
	};

	class MouseButtonUpEventFilter
	{
	public:
		bool operator()(const sf::Event& userEvent)
		{
			return userEvent.type == sf::Event::MouseButtonReleased;
		}
	};

	class AnyMouseButtonEventFilter
	{
	public:
		bool operator()(const sf::Event& userEvent)
		{
			return MouseButtonDownEventFilter{}(userEvent) || MouseButtonUpEventFilter{}(userEvent);
		}
	};

	class JoystickButtonDownEventFilter
	{
	public:
		bool operator()(const sf::Event& userEvent)
		{
			return userEvent.type == sf::Event::JoystickButtonPressed;
		}
	};

	class JoystickButtonUpEventFilter
	{
	public:
		bool operator()(const sf::Event& userEvent)
		{
			return userEvent.type == sf::Event::JoystickButtonReleased;
		}
	};

	class AnyJoystickButtonEventFilter
	{
	public:
		bool operator()(const sf::Event& userEvent)
		{
			return JoystickButtonDownEventFilter{}(userEvent) || JoystickButtonUpEventFilter{}(userEvent);
		}
	};

	class AnyButtonDownEventFilter
	{
	public:
		bool operator()(const sf::Event& userEvent)
		{
			return KeyDownEventFilter{}(userEvent) || MouseButtonDownEventFilter{}(userEvent) || JoystickButtonDownEventFilter{}(userEvent);
		}
	};

	class AnyButtonUpEventFilter
	{
	public:
		bool operator()(const sf::Event& userEvent)
		{
			return KeyUpEventFilter{}(userEvent) || MouseButtonUpEventFilter{}(userEvent) || JoystickButtonUpEventFilter{}(userEvent);
		}
	};

	class AnyEventFilter
	{
	public:
		bool operator()(const sf::Event& /*userEvent*/)
		{
			return true;
		}
	};
}