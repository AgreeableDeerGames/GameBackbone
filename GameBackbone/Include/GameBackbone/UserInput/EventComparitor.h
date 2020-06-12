#pragma once

#include <SFML/Window/Event.hpp>

namespace GB
{
	class EventComparitor
	{
	public:
		virtual bool compare(const sf::Event& lhs, const sf::Event& rhs) = 0;
	};
}
