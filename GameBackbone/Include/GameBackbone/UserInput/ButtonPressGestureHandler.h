#pragma once

#include <GameBackbone/Core/Updatable.h>
#include <GameBackbone/UserInput/InputHandler.h>
#include <GameBackbone/UserInput/GestureBind.h>

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

	template <class GestureType, std::enable_if_t<is_gesture_bind_v<GestureType>, bool> = true>
	class ButtonPressGestureHandler : public InputHandler
	{
	private: 
		using GestureContainer = std::vector<GestureType>;

	public:

		using iterator = typename GestureContainer::iterator;
		using const_iterator = typename GestureContainer::const_iterator;
		using size_type = typename GestureContainer::size_type;

		ButtonPressGestureHandler() = default;
		ButtonPressGestureHandler(const ButtonPressGestureHandler&) = default;
		ButtonPressGestureHandler(ButtonPressGestureHandler&&) = default;
		ButtonPressGestureHandler& operator=(const ButtonPressGestureHandler&) = default;
		ButtonPressGestureHandler& operator=(ButtonPressGestureHandler&&) = default;
		virtual ~ButtonPressGestureHandler() = default;

		bool handleEvent(sf::Int64 elapsedTime, const sf::Event& event) override
		{
			bool eventConsumed = applyEventToOpenSet(elapsedTime, event);

			// If the event was not consumed by any active gesture see if it matches
			// with any of the gestures in their original state
			if (!eventConsumed)
			{
				// Reset open set to contain everything again
				resetGestures();
				elapsedTime = 0;

				// If the event still doesn't match anything then the event was not consumed by this handler 
				eventConsumed = applyEventToOpenSet(elapsedTime, event);
			}
			return eventConsumed;
		}

		GestureType& addGesture(GestureType bind)
		{
			m_openSetGestures.push_back(bind);
			return m_wholeSet.emplace_back(std::move(bind));
		}

		void removeGesture(size_type position)
		{
			if ( position >= m_wholeSet.size() )
			{
				throw std::out_of_range("Out of bounds position in ButtonPressGestureHandler::removeGesture");
			}

			m_wholeSet.erase(m_wholeSet.begin() + position);
			resetGestures();
		}

		GestureType& getGesture(size_type position)
		{
			return m_wholeSet.at(position);
		}

		const GestureType& getGesture(size_type position) const
		{
			return m_wholeSet.at(position);
		}

		size_type getGestureCount() const
		{
			return m_wholeSet.size();
		}

		iterator begin() 
		{
			return m_wholeSet.begin();
		}

		const_iterator begin() const
		{
			return m_wholeSet.begin();
		}

		const_iterator cbegin() const
		{
			return m_wholeSet.cbegin();
		}

		iterator end()
		{
			return m_wholeSet.end();
		}

		const_iterator end() const
		{
			return m_wholeSet.end();
		}

		const_iterator cend() const
		{
			return m_wholeSet.cend();
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
				if (result.inputConsumed)
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
			for (const GestureType& bind : m_wholeSet)
			{
				m_openSetGestures.push_back(bind);
			}
		}

		GestureContainer m_openSetGestures;
		GestureContainer m_wholeSet;
	};

	using KeyboardGestureHandler = ButtonPressGestureHandler<KeyDownGestureBind>;

	using JoystickButtonGestureHandler = ButtonPressGestureHandler<JoystickButtonDownGestureBind>;

	using MouseButtonGestureHandler = ButtonPressGestureHandler<MouseButtonDownGestureBind>;

	using AnyButtonGestureHandler = ButtonPressGestureHandler<ButtonDownGestureBind>;
}
