#pragma once

#include <SFML/Window/Event.hpp>

namespace GB
{
	/*class EventComparitor
	{
	public:
		virtual bool compare(const sf::Event& lhs, const sf::Event& rhs) = 0;
	};

	class SimpleEventComparitor : public EventComparitor
	{
	public:
		bool compare(const sf::Event& lhs, const sf::Event& rhs) override
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
	};*/

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
