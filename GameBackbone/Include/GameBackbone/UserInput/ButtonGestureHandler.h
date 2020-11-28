#pragma once

#include <GameBackbone/Core/Updatable.h>
#include <GameBackbone/UserInput/InputHandler.h>
#include <GameBackbone/UserInput/GestureMatchSignaler.h>

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
	/// @brief Specialized GB::InputHandler to match incoming sf::Events into a set of GB::GestureMatchSignaler to fire their actions upon a complete match.
	/// @details This class attempts to match incoming Events to the Event Sequences (Gestures) in a set of GB::GestureMatchSignaler.
	///				If an Event sequence matches the GB::GestureMatchSignaler, that GB::GestureMatchSignaler continues to be active.
	///				If the Sequence does not match, then the GB::GestureMatchSignaler is no longer active. 
	///				When there are no GB::GestureMatchSignaler matches the sequence so far, the Sequence is restarted 
	///				at the current Event and is reapplied to all GB::GestureMatchSignaler.
	/// @tparam Signaler The type of GestureMatchSignaler that will be used to match against event sequences.
	template <class Signaler, std::enable_if_t<is_gesture_match_signaler_v<Signaler>, bool> = true>
	class ButtonGestureHandler : public InputHandler
	{

	public:
		/// @brief The type of GestureMatchSignaler that inputs will be matched against.
		using GestureMatchSignalerType = Signaler;
	private:
		template <typename T>
		using GestureContainer = std::vector<T>;
		using GestureValueContainer = GestureContainer<GestureMatchSignalerType>;
		using GesturePointerContainer = GestureContainer<std::add_pointer_t<GestureMatchSignalerType>>;
	public:
		using iterator = typename GestureValueContainer::iterator;
		using const_iterator = typename GestureValueContainer::const_iterator;
		using size_type = typename GestureValueContainer::size_type;

		/// @brief Default construct a ButtonGestureHandler. It contains no instances of GB::GestureMatchSignaler.
		ButtonGestureHandler() = default;

		/// @brief Copy construct a ButtonGestureHandler.
		/// @param other The ButtonGestureHandler to copy.
		ButtonGestureHandler(const ButtonGestureHandler& other) = default;

		/// @brief Move construct a ButtonGestureHandler.
		/// @param other The ButtonGestureHandler to move.
		ButtonGestureHandler(ButtonGestureHandler&& other) = default;

		/// @brief Copy Assignment.
		/// @param other The ButtonGestureHandler to copy.
		/// @return *this
		ButtonGestureHandler& operator=(const ButtonGestureHandler& other) = default;

		/// @brief Move Assignment.
		/// @param other The ButtonGestureHandler to move.
		/// @return *this
		ButtonGestureHandler& operator=(ButtonGestureHandler&& other) = default;

		/// @brief Destroy the ButtonGestureHandler.
		~ButtonGestureHandler() override = default;

		/// @brief Apply the incoming event to each active GB::GestureMatchSignaler stored on this instance.
		/// @details Match the incoming Event against the stored instances of GB::GestureMatchSignaler.
		///			Any GB::GestureMatchSignaler that matches the event will continue to be active.
		///			All other GB::GestureMatchSignaler will no longer be active.
		///			If no GB::GestureMatchSignaler matches then all GB::GestureMatchSignaler are reset and activated and
		///			the event is applied to each one again.
		/// @param elapsedTime The time since the last event.
		/// @param event The incoming event.
		/// @return Value is true if any GB::GestureMatchSignaler matched the incoming event. False otherwise.
		bool handleEvent(sf::Int64 elapsedTime, const sf::Event& event) override
		{
			bool eventConsumed = applyEventToOpenSet(elapsedTime, event);

			// If the event was not consumed by any active gesture see if it matches
			// with any of the gestures in their original state
			if (!eventConsumed)
			{
				// Reset open set to contain everything again
				reset();
				elapsedTime = 0;

				// If the event still doesn't match anything then the event was not consumed by this handler 
				eventConsumed = applyEventToOpenSet(elapsedTime, event);
			}
			return eventConsumed;
		}

		/// @brief Adds a GB::GestureMatchSignaler to match against incoming events. Resets every GB::GestureMatchSignaler that is
		///			currently stored on this ButtonGestureHandler instance.
		/// @param matchSignaler The GB::GestureMatchSignaler to add.
		/// @return A reference to the added GB::GestureMatchSignaler.
		/// @note The reference returned by this function is invalidated by any future calls to
		///			addMatchSignaler or removeMatchSignaler.
		GestureMatchSignalerType& addMatchSignaler(GestureMatchSignalerType matchSignaler)
		{
			auto& emplacedSignaler = m_wholeSet.emplace_back(std::move(matchSignaler));
			reset();
			return emplacedSignaler;
		}

		/// @brief Removes the GB::GestureMatchSignaler at the provided location.
		/// @param position The index of the GB::GestureMatchSignaler to remove.
		/// @throws std::out_of_range exception if the position is invalid.
		void removeMatchSignaler(size_type position)
		{
			if ( position >= m_wholeSet.size() )
			{
				throw std::out_of_range("Out of bounds position in ButtonGestureHandler::removeGesture");
			}

			// Remove from the open set if it exists
			auto removeResult = std::remove(m_openSetGestures.begin(), m_openSetGestures.end(), &m_wholeSet[position]);
			if (removeResult != m_openSetGestures.end())
			{
				m_openSetGestures.erase(removeResult);
			}

			// Remove from the whole set
			m_wholeSet.erase(m_wholeSet.begin() + position);
		}

		/// @brief Gets a reference to the GB::GestureMatchSignaler at the provided location.
		/// @param position the index of the GB::GestureMatchSignaler to return.
		/// @return The GB::GestureMatchSignaler at the provided index.
		/// @throws std::out_of_range exception if the position is invalid.
		GestureMatchSignalerType& getMatchSignaler(size_type position)
		{
			return m_wholeSet.at(position);
		}

		/// @brief Gets a reference to the GB::GestureMatchSignaler at the provided location.
		/// @param position the index of the GB::GestureMatchSignaler to return.
		/// @return The GB::GestureMatchSignaler at the provided index.
		/// @throws std::out_of_range exception if the position is invalid.
		const GestureMatchSignalerType& getMatchSignaler(size_type position) const
		{
			return m_wholeSet.at(position);
		}

		/// @brief Get the number of GB::GestureMatchSignaler stored on this instance.
		size_type getMatchSignalerCount() const
		{
			return m_wholeSet.size();
		}

		/// @brief Makes all instances of GB::GestureMatchSignaler active. Resets the state of all instances of GB::GestureMatchSignaler.
		void reset()
		{
			// Clear the open set completely
			m_openSetGestures.clear();

			// Add all gestures from the whole set to the active gestures open set.
			for (GestureMatchSignalerType& bind : m_wholeSet)
			{
				bind.reset();
				m_openSetGestures.push_back(&bind);
			}
		}

		/// @brief Gets an iterator to the first GB::GestureMatchSignaler stored on this instance.
		/// @note all iterators are invalidated by calls to addMatchSignaler or removeMatchSignaler.
		iterator begin() 
		{
			return m_wholeSet.begin();
		}

		/// @brief Gets an iterator to the first GB::GestureMatchSignaler stored on this instance.
		/// @note all iterators are invalidated by calls to addMatchSignaler or removeMatchSignaler.
		const_iterator begin() const
		{
			return m_wholeSet.begin();
		}

		/// @brief Gets an iterator to the first GB::GestureMatchSignaler stored on this instance.
		/// @note all iterators are invalidated by calls to addMatchSignaler or removeMatchSignaler.
		const_iterator cbegin() const
		{
			return m_wholeSet.cbegin();
		}

		/// @brief End iterator to the instances of GB::GestureMatchSignaler that are stored on this instance.
		/// @note all iterators are invalidated by calls to addMatchSignaler or removeMatchSignaler.
		iterator end()
		{
			return m_wholeSet.end();
		}

		/// @brief End iterator to the instances of GB::GestureMatchSignaler that are stored on this instance.
		/// @note all iterators are invalidated by calls to addMatchSignaler or removeMatchSignaler.
		const_iterator end() const
		{
			return m_wholeSet.end();
		}

		/// @brief End iterator to the instances of GB::GestureMatchSignaler that are stored on this instance.
		/// @note all iterators are invalidated by calls to addMatchSignaler or removeMatchSignaler.
		const_iterator cend() const
		{
			return m_wholeSet.cend();
		}

	private:
	
		/// @brief Apply the incoming event to each active GB::GestureMatchSignaler stored on this instance.
		/// @details Forwards inputs to a set of active GB::GestureMatchSignaler. In ButtonGestureHandler::handleEvent
		///				events are passed to each GB::GestureMatchSignaler in the open set. If any GB::GestureMatchSignaler
		///             does not match the input it will be taken out of the active set until the GB::ButtonGestureHandler is reset.
		///             If nothing in the active set matches the input then GB::ButtonGestureHandler is automatically reset and
		///				the input is reapplied to the active set one extra time. 
		///				The reset and  reapplication of the event is because we want to be able to bail out and then start a new Gesture immediately.
		/// @param elapsedTime The time since the last event.
		/// @param event The incoming event.
		/// @return Value is true if any GB::GestureMatchSignaler matched the incoming event. False otherwise.
		bool applyEventToOpenSet(sf::Int64 elapsedTime, const sf::Event& event)
		{
			bool eventConsumed = false;
			for (std::size_t ii = 0; ii < m_openSetGestures.size(); ++ii)
			{
				// Forward event to the gesture bind
				auto result = m_openSetGestures[ii]->processEvent(elapsedTime, event);

				// The bind cannot take any more input. Remove it from the open set.
				if (!result.isReadyForInput)
				{
					m_openSetGestures.erase(m_openSetGestures.begin() + ii);
					--ii;
				}

				// The event was part of the gesture
				if (result.inputConsumed)
				{
					eventConsumed = true;
				}
			}

			return eventConsumed;
		}

		GesturePointerContainer m_openSetGestures;
		GestureValueContainer m_wholeSet;
	};

	/// @brief GB::ButtonGestureHandler that handles sequences of key down inputs. 
	using KeyboardGestureHandler = ButtonGestureHandler<KeyDownMatchSignaler>;
	
	/// @brief GB::ButtonGestureHandler that handles sequences of joystick button down inputs. 
	using JoystickButtonGestureHandler = ButtonGestureHandler<JoystickButtonDownMatchSignaler>;
	
	/// @brief GB::ButtonGestureHandler that handles sequences of mouse button down inputs. 
	using MouseButtonGestureHandler = ButtonGestureHandler<MouseButtonDownMatchSignaler>;

	/// @brief GB::ButtonGestureHandler that handles sequences of button down inputs. 
	using AnyButtonGestureHandler = ButtonGestureHandler<ButtonDownMatchSignaler>;
}
