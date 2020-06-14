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
	template <typename T>
	using is_event_comparitor = std::conjunction<
		std::is_invocable<T, const sf::Event&, const sf::Event&>, 
		std::is_same<typename std::invoke_result<T, const sf::Event&, const sf::Event&>::type, bool>
	>;

	template <typename T>
	static inline constexpr bool is_event_comparitor_v = is_event_comparitor<T>::value;
	
	template <typename EventCompare, std::enable_if_t<is_event_comparitor_v<EventCompare>, bool> = true>
	class ButtonPressGestureHandler : public InputHandler
	{
	public:

		static constexpr sf::Int64 defaultMaxTimeBetweenInputs = 1000;

		void addGesture(GestureBind bind)
		{
			m_wholeSet.push_back(bind);
			m_openSetGestures.emplace_back(bind, 0);
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

		bool applyEventToOpenSet(sf::Int64 elapsedTime, const sf::Event& event)
		{
			bool eventApplied = false;
			for (std::size_t ii = 0; ii < m_openSetGestures.size(); ++ii)
			{
				// TODO: ensure that minimum time has passed
				if (compareEvents(m_openSetGestures[ii].first.gesture.at(m_openSetGestures[ii].second), event) /* && !hasTimedOut*/)
				{
					//TODO: add action with logged time to the process event system
					eventApplied = true;

					m_openSetGestures[ii].second += 1;

					if (m_openSetGestures[ii].second == m_openSetGestures[ii].first.gesture.size())
					{
						// Invoke bound action
						std::invoke(m_openSetGestures[ii].first.action);

						// Tell the stateful gesture bind to do something given its end type
						switch (m_openSetGestures[ii].first.endType)
						{
						case EndType::Continuous:
						{
							m_openSetGestures[ii].second -= 1;
							break;
						}
						case EndType::Reset:
						{
							m_openSetGestures[ii].second = 0;
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
				m_openSetGestures.emplace_back(bind, 0);
			}
		}

		std::vector<std::pair<GestureBind, int>> m_openSetGestures;
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
