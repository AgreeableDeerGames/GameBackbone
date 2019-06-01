#pragma once

#include <SFML/System/Vector2.hpp>

namespace GB {

	/// <summary>
	/// Used to compare which of two sf::Vector2 is less
	/// Designed to facilitate map and set use of sf::Vector2
	/// </summary>
	template <typename T>
	class IsVector2Less {
	public:
		bool operator()(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs) const {
			return lhs.x < rhs.x || (!(rhs.x < lhs.x) && lhs.y < rhs.y);
		}
	};
}
