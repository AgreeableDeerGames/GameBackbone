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

	class SimpleEventComparitor
	{
	public:
		bool operator()(const sf::Event& lhs, const sf::Event& rhs)
		{
			if (lhs.type != rhs.type)
			{
				return false;
			}
			switch (lhs.type)
			{
			case sf::Event::KeyReleased:
			case sf::Event::KeyPressed:
				if (lhs.key.code == rhs.key.code)
				{
					return true;
				}
			default:
				return false;
			}
		}
	};
}
