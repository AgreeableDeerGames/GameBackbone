#pragma once

#include <SFML/System/Vector2.hpp>

namespace GB {

	template <typename T>
	class Vec2Compare {
	public:
		bool operator()(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs) const {
			return lhs.x < rhs.x || (!(rhs.x < lhs.x) && lhs.y < rhs.y);
		}
	};

}