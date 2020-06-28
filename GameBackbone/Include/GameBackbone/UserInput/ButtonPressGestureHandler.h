#pragma once

#include <GameBackbone/Core/Updatable.h>
#include <GameBackbone/UserInput/InputHandler.h>
#include <GameBackbone/UserInput/GestureBind.h>
#include <GameBackbone/UserInput/EventComparitor.h>

#include <SFML/Window/Event.hpp>

#include <algorithm>
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>


namespace GB
{

	template <typename EventCompare, std::enable_if_t<is_event_comparitor_v<EventCompare>, bool> = true>
	class ButtonPressGestureHandler : public InputHandler
	{
	public:

		using GestureBind = BasicGestureBind<EventCompare>;

		ButtonPressGestureHandler() = default;
		ButtonPressGestureHandler(const ButtonPressGestureHandler&) = default;
		ButtonPressGestureHandler(ButtonPressGestureHandler&&) = default;
		ButtonPressGestureHandler& operator=(const ButtonPressGestureHandler&) = default;
		ButtonPressGestureHandler& operator=(ButtonPressGestureHandler&&) = default;
		virtual ~ButtonPressGestureHandler() = default;

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

		bool applyEventToOpenSet(sf::Int64 elapsedTime, const sf::Event& event)
		{
			bool eventApplied = false;
			for (std::size_t ii = 0; ii < m_openSetGestures.size(); ++ii)
			{
				// Forward event to the gesture bind
				auto result = m_openSetGestures[ii].processEvent(elapsedTime, event);

				// The bind cannot take any more input. Remove it from the open set.
				if (!result.readyForInput)
				{
					m_openSetGestures.erase(m_openSetGestures.begin() + ii);
					--ii;
				}

				// The event was part of the gesture
				if (result.readyForInput || result.actionFired)
				{
					eventApplied = true;
				}
			}

			return eventApplied;
		}

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

		std::vector<GestureBind> m_openSetGestures;
		std::vector<GestureBind> m_wholeSet;
	};
}


/*
	Gesture - series of inputs
	Bind - Gesture, function (callable, usage, id/name/tooltip/icon), stateful inputs
	ActiveGesture - Bind, state

	User:
*/
