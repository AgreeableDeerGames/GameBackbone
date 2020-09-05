#pragma once

#include <SFML/Window/Event.hpp>

namespace GB
{
	/// @brief A type_trait expressing the concept of an EventFilter. An EventFilter checks to see if an sf::Event meets some criteria.
	/// @note An EventFilter is used by various InputHandler implementations to filter out unwanted sf::Events.
	/// @tparam T The type to check.
	template <typename T>
	using is_event_filter = std::conjunction<
		std::is_invocable<T, const sf::Event&>,
		std::is_same<typename std::invoke_result<T, const sf::Event&>::type, bool>
	>;

	/// @brief Value is true if T is the type EventFilter.
	/// @tparam T The type to check.
	template <typename T>
	static inline constexpr bool is_event_filter_v = is_event_filter<T>::value;

	/// @brief Fulfills the requirements of the concept EventFilter. Filters for any sf::Event that is a key down event.
	/// @details Filters for any sf::Event that has a type of sf::Event::KeyPressed.
	class KeyDownEventFilter
	{
	public:
		bool operator()(const sf::Event& userEvent)
		{
			return userEvent.type == sf::Event::KeyPressed;
		}
	};

	/// @brief Fulfills the requirements of the concept EventFilter. Filters for any sf::Event that is not a key up event.
	/// @details Filters for any sf::Event that has a type of sf::Event::KeyReleased.
	class KeyUpEventFilter
	{
	public:
		bool operator()(const sf::Event& userEvent)
		{
			return userEvent.type == sf::Event::KeyReleased;
		}
	};
	
	/// @brief Fulfills the requirements of the concept EventFilter. Filters for any sf::Event that is not a key event.
	/// @details Filters for any sf::Event which would be filtered for by KeyDownEventFilter or KeyUpEventFilter.
	class AnyKeyEventFilter
	{
	public:
		bool operator()(const sf::Event& userEvent)
		{
			return KeyDownEventFilter{}(userEvent) || KeyUpEventFilter{}(userEvent);
		}
	};
	
	/// @brief Fulfills the requirements of the concept EventFilter. Filters for any sf::Event that is a mouse button down event.
	/// @details Filters for any sf::Event that has a type of sf::Event::MouseButtonPressed.
	class MouseButtonDownEventFilter
	{
	public:
		bool operator()(const sf::Event& userEvent)
		{
			return userEvent.type == sf::Event::MouseButtonPressed;
		}
	};
	
	/// @brief Fulfills the requirements of the concept EventFilter. Filters for any sf::Event that is a mouse button up event.
	/// @details Filters for any sf::Event that has a type of sf::Event::MouseButtonReleased.
	class MouseButtonUpEventFilter
	{
	public:
		bool operator()(const sf::Event& userEvent)
		{
			return userEvent.type == sf::Event::MouseButtonReleased;
		}
	};
	
	/// @brief Fulfills the requirements of the concept EventFilter. Filters for any sf::Event that is a mouse button event.
	/// @details Filters for any sf::Event which would be filtered for by MouseButtonDownEventFilter or MouseButtonUpEventFilter.
	class AnyMouseButtonEventFilter
	{
	public:
		bool operator()(const sf::Event& userEvent)
		{
			return MouseButtonDownEventFilter{}(userEvent) || MouseButtonUpEventFilter{}(userEvent);
		}
	};
	
	/// @brief Fulfills the requirements of the concept EventFilter. Filters for any sf::Event that is a joystick button down event.
	/// @details Filters for any sf::Event that has a type of sf::Event::JoystickButtonPressed.
	class JoystickButtonDownEventFilter
	{
	public:
		bool operator()(const sf::Event& userEvent)
		{
			return userEvent.type == sf::Event::JoystickButtonPressed;
		}
	};
	
	/// @brief Fulfills the requirements of the concept EventFilter. Filters for any sf::Event that is a joystick button up event.
	/// @details Filters for any sf::Event that has a type of sf::Event::JoystickButtonReleased.
	class JoystickButtonUpEventFilter
	{
	public:
		bool operator()(const sf::Event& userEvent)
		{
			return userEvent.type == sf::Event::JoystickButtonReleased;
		}
	};
	
	/// @brief Fulfills the requirements of the concept EventFilter. Filters for any sf::Event that is a joystick button event.
	/// @details Filters for any sf::Event which would be filtered for by JoystickButtonDownEventFilter or JoystickButtonUpEventFilter.
	class AnyJoystickButtonEventFilter
	{
	public:
		bool operator()(const sf::Event& userEvent)
		{
			return JoystickButtonDownEventFilter{}(userEvent) || JoystickButtonUpEventFilter{}(userEvent);
		}
	};
	
	/// @brief Fulfills the requirements of the concept EventFilter. Filters for any sf::Event that is a button down event.
	/// @details Filters for any sf::Event which would be filtered for by KeyDownEventFilter, MouseButtonDownEventFilter, or JoystickButtonDownEventFilter.
	class AnyButtonDownEventFilter
	{
	public:
		bool operator()(const sf::Event& userEvent)
		{
			return KeyDownEventFilter{}(userEvent) || MouseButtonDownEventFilter{}(userEvent) || JoystickButtonDownEventFilter{}(userEvent);
		}
	};
	
	/// @brief Fulfills the requirements of the concept EventFilter. Filters for any sf::Event that is a button up event.
	/// @details Filters for any sf::Event which would be filtered for by KeyUpEventFilter, MouseButtonUpEventFilter, or JoystickButtonUpEventFilter.
	class AnyButtonUpEventFilter
	{
	public:
		bool operator()(const sf::Event& userEvent)
		{
			return KeyUpEventFilter{}(userEvent) || MouseButtonUpEventFilter{}(userEvent) || JoystickButtonUpEventFilter{}(userEvent);
		}
	};
	
	/// @brief Fulfills the requirements of the concept EventFilter. Filters for any sf::Event.
	/// @details Always returns true.
	class AnyEventFilter
	{
	public:
		bool operator()(const sf::Event& /*userEvent*/)
		{
			return true;
		}
	};
}