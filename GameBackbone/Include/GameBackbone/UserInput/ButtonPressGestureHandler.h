#pragma once

#include <GameBackbone/Core/Updatable.h>
#include <GameBackbone/UserInput/InputHandler.h>
#include <GameBackbone/UserInput/GestureBind.h>
#include <GameBackbone/UserInput/EventComparitor.h>

#include <SFML/Window/Event.hpp>

#include <vector>
#include <tuple>
#include <functional>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <string>
#include <iostream>

#include <type_traits>

namespace GB
{

	
	template <typename EventCompare, std::enable_if_t<is_event_comparitor_v<EventCompare>, bool> = true>
	class ButtonPressGestureHandler : public InputHandler
	{
	public:

		static constexpr sf::Int64 defaultMaxTimeBetweenInputs = 1000;

		void addGesture(GestureBind bind)
		{
			m_wholeSet.push_back(bind);
			m_openSetGestures.emplace_back(bind);
		}

		bool handleEvent(sf::Int64 elapsedTime, const sf::Event& event) override
		{
			bool eventConsumed = applyEventToOpenSet(elapsedTime, event);

			// If the event was not consumed by any active gesture see if it matches
			// with any of the gestures in their original state
			if (!eventConsumed)
			{
				// Reset open set to contain everything again
				resetGestures();

				// If the event still doesn't match anything then the event was not consumed by this handler 
				eventConsumed = applyEventToOpenSet(elapsedTime, event);
			}
			return eventConsumed;
		}

	private:

		class StatefulGestureBind : public GestureBind
		{
		public:
			
			StatefulGestureBind(const GestureBind& bind) : GestureBind(bind),
				m_position(0) 
			{
			}

			std::size_t getPosition() const
			{
				return m_position;
			}

			void advance(int distance = 1)
			{
				m_position += distance;
			}

			void reset()
			{
				m_position = 0;
			}

			const sf::Event& getNextEvent() const
			{
				return gesture.at(m_position);
			}

		private:
			int m_position;
		};


		bool applyEventToOpenSet(sf::Int64 elapsedTime, const sf::Event& event)
		{
			bool eventApplied = false;
			for (std::size_t ii = 0; ii < m_openSetGestures.size(); ++ii)
			{
				// TODO: ensure that minimum time has passed
				if (compareEvents(m_openSetGestures[ii].getNextEvent(), event) /* && !hasTimedOut*/)
				{
					//TODO: add action with logged time to the process event system
					eventApplied = true;

					m_openSetGestures[ii].advance();

					if (m_openSetGestures[ii].getPosition() == m_openSetGestures[ii].gesture.size())
					{
						// Invoke bound action
						std::invoke(m_openSetGestures[ii].action);

						// Tell the stateful gesture bind to do something given its end type
						switch (m_openSetGestures[ii].endType)
						{
						case EndType::Continuous:
						{
							m_openSetGestures[ii].advance(-1);
							break;
						}
						case EndType::Reset:
						{
							m_openSetGestures[ii].reset();
							break;
						}
						case EndType::Stop:
						{
							m_openSetGestures.erase(m_openSetGestures.begin() + ii);
							break;
						}
						case EndType::BlockLastEvent:
						{
							// TODO: How? Why? Make Michael do it.
							break;
						}
						}
					}
				}
				else
				{
					// TODO: Take gesture out of open set
					m_openSetGestures.erase(m_openSetGestures.begin() + ii);
					--ii;
				}
			}

			return eventApplied;
		}


		// TODO: Extension point
		bool compareEvents(const sf::Event& lhs, const sf::Event& rhs)
		{
			return std::invoke(m_eventComparitor, lhs, rhs);
		};

		void resetGestures()
		{
			// Clear the open set completely
			m_openSetGestures.clear();

			// Add all gestures from the whole set to the active gestures open set.
			for (const GestureBind& bind : m_wholeSet)
			{
				m_openSetGestures.emplace_back(bind);
			}
		}

		std::vector<StatefulGestureBind> m_openSetGestures;
		std::vector<GestureBind> m_wholeSet;
		EventCompare m_eventComparitor;
	};
}


/*
	Gesture - series of inputs
	Bind - Gesture, function
	ActiveGesture - Bind, state

	User:
*/
