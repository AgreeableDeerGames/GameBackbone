#pragma once

#include <GameBackbone/Util/DllUtil.h>

#include <SFML/Window/Event.hpp>

#include <vector>
#include <tuple>
#include <chrono>
#include <cassert>

namespace GB {

	using milliseconds_d = std::chrono::duration<double, std::milli>;

	class Gesture
	{
	public:
		void addEvent(milliseconds_d minTimeBefore, milliseconds_d maxTimeBefore, sf::Event event)
		{
			m_componentEvents.push_back(std::make_tuple(minTimeBefore, maxTimeBefore, event));
		}

		// return true if the added event completes the gesture
		bool applyEvent(const sf::Event& event)
		{

			auto compareEvents = [](const sf::Event& lhs, const sf::Event& rhs) -> bool
			{
				if (lhs.type != rhs.type)
				{
					return false;
				}
				switch (lhs.type)
				{
				case sf::Event::KeyPressed:
					if (lhs.key.code == rhs.key.code)
					{
						return true;
					}
				default:
					return false;
				}
			};

			// Does the event match
			assert(m_currentEvent < m_componentEvents.size());
			if (compareEvents(event, std::get<2>(m_componentEvents[m_currentEvent])))
			{
				++m_currentEvent;
				// We have hit the last
				if (m_currentEvent == m_componentEvents.size())
				{
					m_currentEvent = 0;
					return true;
				}
				return false;
			}
			m_currentEvent = 0;
			return false;
		}

	private:
		std::vector<std::tuple<milliseconds_d, milliseconds_d, sf::Event>> m_componentEvents;
		std::size_t m_currentEvent = 0;
		
	};

}

// If looking for WS and user presses WWS
// Allow for both reset and continue gesture after completion