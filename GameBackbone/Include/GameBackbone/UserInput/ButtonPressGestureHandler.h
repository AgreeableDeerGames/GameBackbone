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

		static constexpr sf::Int64 defaultMaxTimeBetweenInputs = 1000;

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

				// TODO: the use of GestureBind::HandleEvenResult really indicates that
				// We only care if the gesture is ready for new input or not. We dont really care about the current
				// three states
				typename GestureBind::HandleEventResult result = m_openSetGestures[ii].handleEvent(elapsedTime, event);
				if (result != GestureBind::HandleEventResult::Advanced)
				{
					m_openSetGestures.erase(m_openSetGestures.begin() + ii);
					--ii;
				}
				if (result != GestureBind::HandleEventResult::Reset)
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
