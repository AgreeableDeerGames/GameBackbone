#pragma once

#include <GameBackbone/Util/DllUtil.h>
#include <GameBackbone/UserInput/EventComparator.h>
#include <GameBackbone/UserInput/EventFilter.h>
#include <GameBackbone/UserInput/InputHandler.h>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <cassert>
#include <functional>
#include <string>
#include <type_traits>
#include <vector>


namespace GB
{
	/// @brief Stores the result of GestureMatchSignaler::processEvent.
	///	@details actionFired indicates that the GestureMatchSignaler has fired its action.
	///		isReadyForInput indicates that the GestureMatchSignaler is still active and can successfully handle more input.
	///		inputConsumed indicates that the GestureMatchSignaler processed the last input provided to GestureMatchSignaler::processEvent
	struct GestureMatchSignalerProcessEventResult
	{
		bool actionFired;
		bool isReadyForInput;
		bool inputConsumed;
	};

	namespace Detail 
	{
		template <class GestureMatchSignalerType>
		using GestureMatchSignalerProcessEvent = decltype(
			std::declval<GestureMatchSignalerProcessEventResult>() = std::declval<GestureMatchSignalerType>().processEvent(std::declval<sf::Int64>(), std::declval<const sf::Event&>())
		);

		template <class GestureMatchSignalerType, class = void>
		struct supports_gesture_match_signaler_process_event : std::false_type {};

		template <class GestureMatchSignalerType>
		struct supports_gesture_match_signaler_process_event <GestureMatchSignalerType, std::void_t<GestureMatchSignalerProcessEvent<GestureMatchSignalerType>>> :
			std::true_type {};
	}

	/// @brief Type trait that determines if a type is a GestureMatchSignaler. If the type is a GestureMatchSignaler
	///		then a member constant value is equal to true. If the type is not a GestureMatchSignaler then the member constant value is equal to false.
	/// @tparam GestureMatchSignalerType The type to check
	template <class GestureMatchSignalerType>
	using is_gesture_match_signaler =
		std::conjunction<
			std::is_copy_constructible<GestureMatchSignalerType>,
			Detail::supports_gesture_match_signaler_process_event<GestureMatchSignalerType>
		>;

	/// @brief Type trait that determines if a type is a GestureMatchSignaler. True if the type is a GestureMatchSignaler. False otherwise.
	/// @tparam GestureMatchSignalerType The type to check
	template <class GestureMatchSignalerType>
	inline constexpr bool is_gesture_match_signaler_v = is_gesture_match_signaler<GestureMatchSignalerType>::value;

	/// @brief Signal class that fires an action when it handles a set of inputs that match an expected gesture.
	/// @tparam EventCompare The type of the comparator that will be used to check if two events match.
	/// @tparam EventFilter The type of the filter that determines if an event should be matched against the expected
	///						gesture or skipped entirely.
	template <
		typename EventCompare,
		typename EventFilter,
		std::enable_if_t<is_event_comparator_v<EventCompare>, bool> = true,
		std::enable_if_t<is_event_filter_v<EventFilter>, bool> = true
	>
	class GestureMatchSignaler
	{
	public:

		static constexpr sf::Int64 defaultMaxTimeBetweenInputs = 1000;

		using EventComparatorType = EventCompare;
		using EventFilterType = EventFilter;
		using ProcessEventResult = GestureMatchSignalerProcessEventResult;

		/// @brief Indicates the desired behavior after a match is found.
		enum class MatchBehavior
		{
			/// @brief Signal with every subsequent event that matches the last event in the gesture.
			Penultimate,

			/// @brief Puts the gesture back to position 0 after it completes and allows the gesture to complete again.
			Reset,

			/// @brief Stop handling events after signaling the next match.
			Block
		};

		
		/// @brief Creates a new instance of a GestureMatchSignaler.
		/// @param gesture The Sequence of sf::Event that the GestureMatchSignaler will match.
		/// @param action The action to fire upon the Sequence being matched. The "Slot".
		template <
			typename = std::enable_if_t< std::is_default_constructible_v<EventComparatorType>>,
			typename = std::enable_if_t< std::is_default_constructible_v<EventFilterType>>
		>
		GestureMatchSignaler(
			std::vector<sf::Event> gesture,
			std::function<void()> action) :
			GestureMatchSignaler(
				std::move(gesture),
				std::move(action),
				MatchBehavior::Block,
				defaultMaxTimeBetweenInputs)
		{
		}

		/// @brief Creates a new instance of a GestureMatchSignaler.
		/// @param gesture The Sequence of sf::Event that the GestureMatchSignaler will match.
		/// @param action The action to fire upon the Sequence being matched. The "Slot".
		/// @param matchBehavior The behavior of this GestureMatchSignaler after a successful match.
		template <
			typename = std::enable_if_t< std::is_default_constructible_v<EventComparatorType>>,
			typename = std::enable_if_t< std::is_default_constructible_v<EventFilterType>>
		>
		GestureMatchSignaler(
			std::vector<sf::Event> gesture,
			std::function<void()> action,
			MatchBehavior matchBehavior) :
			GestureMatchSignaler(
				std::move(gesture),
				std::move(action),
				matchBehavior,
				defaultMaxTimeBetweenInputs)
		{
		}

		/// @brief Creates a new instance of a GestureMatchSignaler.
		/// @param gesture The Sequence of sf::Event that the GestureMatchSignaler will match.
		/// @param action The action to fire upon the Sequence being matched. The "Slot".
		/// @param matchBehavior The behavior of this GestureMatchSignaler after a successful match.
		/// @param maxTimeBetweenInputs The amount of time allowed between each sf::Event in the Sequence. 
		///				If an sf::Event is sent after this period of time, the GestureMatchSignaler will not accept the sf::Event.
		template <
			typename = std::enable_if_t< std::is_default_constructible_v<EventComparatorType>>,
			typename = std::enable_if_t< std::is_default_constructible_v<EventFilterType>>
		>
		GestureMatchSignaler(
			std::vector<sf::Event> gesture,
			std::function<void()> action,
			MatchBehavior matchBehavior,
			sf::Int64 maxTimeBetweenInputs
		) :
			GestureMatchSignaler(
				std::move(gesture),
				std::move(action),
				matchBehavior,
				maxTimeBetweenInputs,
				EventCompare{},
				EventFilterType{})
		{
		}

		/// @brief Creates a new instance of a GestureMatchSignaler.
		/// @param gesture The Sequence of sf::Event that the GestureMatchSignaler will match.
		/// @param action The action to fire upon the Sequence being matched. The "Slot".
		/// @param matchBehavior The behavior of this GestureMatchSignaler after a successful match.
		/// @param maxTimeBetweenInputs The amount of time allowed between each sf::Event in the Sequence. 
		///				If an sf::Event is sent after this period of time, the GestureMatchSignaler will not accept the sf::Event.
		/// @param eventComparator A function or function object for comparing an input event to an expected one.
		/// @param eventFilter A function or function object that returns true if the input event should be matched against the expected
		///						one and false if it should be skipped entirely.
		GestureMatchSignaler(
			std::vector<sf::Event> gesture,
			std::function<void()> action,
			MatchBehavior matchBehavior,
			sf::Int64 maxTimeBetweenInputs,
			EventComparatorType eventComparator,
			EventFilterType eventFilter
		) :
			m_gesture(std::move(gesture)),
			m_action(std::move(action)),
			m_matchBehavior(matchBehavior),
			m_maxTimeBetweenInputs(maxTimeBetweenInputs),
			m_position(0),
			m_readyForInput(true),
			m_eventComparator(std::move(eventComparator)),
			m_eventFilter(std::move(eventFilter))
		{
		}

		/// @brief Check if the incoming event matches the next event in the expected gesture.
		/// @param elapsedTime The time since the last event was processed.
		/// @param event The event to be checked.
		/// @return The resulting changes to the GestureMatchSignaler.
		ProcessEventResult processEvent(sf::Int64 elapsedTime, const sf::Event& event)
		{
			// Exit early if not ready for input
			if (!isReadyForInput())
			{
				// Return that the GestureMatchSignaler did not fire an action, is not ready for input, and the input was not consumed.
				return { false, false, false };
			}

			// Filter out events that this GestureMatchSignaler should ignore
			if (!std::invoke(m_eventFilter, event))
			{
				// Return that the GestureMatchSignaler did not fire an action, its ready state, and the input was not consumed.
				return { false, isReadyForInput(), false };
			}

			// Process the input.
			bool actionFired = false;
			bool inputConsumed = false;
			// If the events are the same and the time is within the maximum, increment the position and behave accordingly.
			if (compareEvents(getNextEvent(), event) && elapsedTime < m_maxTimeBetweenInputs)
			{
				++m_position;
				// If the input was the last sf::Event in the Sequence, complete the match.
				if (m_position == m_gesture.size())
				{
					completeMatch();
					actionFired = true;
				}
				inputConsumed = true;
			}
			// The input did not match. Disable this GestureMatchSignaler.
			else
			{
				m_position = 0;
				m_readyForInput = false;
			}

			// Return if the GestureMatchSignaler fired an action, its ready state, and if it consumed the input.
			return { actionFired, isReadyForInput(), inputConsumed };
		}

		/// @brief Returns the sf::Event Sequence that is being matched for.
		const std::vector<sf::Event>& getGesture() const
		{
			return m_gesture;
		}

		/// @brief Returns the action that will be fired upon the Sequence being matched.
		const std::function<void()>& getAction() const
		{
			return m_action;
		}

		/// @brief Returns the maximum time allowed between inputs in the same event sequence. 
		sf::Int64 getMaxTimeBetweenInputs() const
		{
			return m_maxTimeBetweenInputs;
		}

		/// @brief The behavior of this GestureMatchSignaler after a successful match.
		MatchBehavior getMatchBehavior() const
		{
			return m_matchBehavior;
		}

		/// @brief Set the Sequence of sf::Event that the GestureMatchSignaler will match.
		void setGesture(std::vector<sf::Event> gesture)
		{
			m_gesture = std::move(gesture);
		}

		/// @brief Set the action that will be fired upon the Sequence being matched.
		void setAction(std::function<void()> action)
		{
			m_action = std::move(action);
		}

		/// @brief Sets the maximum time allowed between inputs in the same event sequence. 
		void setMaxTimeBetweenInputs(sf::Int64 maxTimeBetweenInputs)
		{
			m_maxTimeBetweenInputs = maxTimeBetweenInputs;
		}

		/// @brief Sets the behavior of this GestureMatchSignaler after a successful match.
		void setMatchBehavior(MatchBehavior matchBehavior)
		{
			m_matchBehavior = matchBehavior;
		}
		
		/// @brief Resets the state of the GestureMatchSignaler.
		void reset()
		{
			m_position = 0;
			m_readyForInput = true;
		}
		
		/// @brief Returns if the GestureMatchSignaler is ready for input.
		bool isReadyForInput() const
		{
			return m_readyForInput && !m_gesture.empty();
		}

	private:

		/// @brief Invoke the EventComparator
		/// @param lhs The left-hand sf::Event.
		/// @param rhs The right-hand sf::Event.
		/// @return The result of the EventComparator.
		bool compareEvents(const sf::Event& lhs, const sf::Event& rhs)
		{
			return std::invoke(m_eventComparator, lhs, rhs);
		}

		/// @brief Signals the slot and sets the state that corresponds to the MatchType
		void completeMatch()
		{
			// Set completed/matched/new state
			switch (getMatchBehavior())
			{
			case MatchBehavior::Penultimate:
			{
				--m_position;
				break;
			}
			case MatchBehavior::Reset:
			{
				reset();
				break;
			}
			case MatchBehavior::Block:
			{
				m_position = 0;
				m_readyForInput = false;
				break;
			}
			}

			// Signal.
			std::invoke(m_action);
		}
		
		/// @brief Get the next expected event
		const sf::Event& getNextEvent() const
		{
			assert(m_position < m_gesture.size());
			return m_gesture[m_position];
		}

		// Matching Criteria
		std::vector<sf::Event> m_gesture;
		std::function<void()> m_action;
		sf::Int64 m_maxTimeBetweenInputs;

		// State control and State
		MatchBehavior m_matchBehavior;
		std::size_t m_position;
		bool m_readyForInput;

		// Customizable behaviors
		EventComparatorType m_eventComparator;
		EventFilterType m_eventFilter;
	};

	/// @brief Signal class that fires an action when it handles a set of key down events. Ignores all events that are not key down events.
	using KeyDownMatchSignaler = GestureMatchSignaler<KeyEventComparator, KeyDownEventFilter>;

	/// @brief Signal class that fires an action when it handles a set of joystick button down events. Ignores all events that are not joystick button down events.
	using JoystickButtonDownMatchSignaler = GestureMatchSignaler<JoystickButtonEventComparator, JoystickButtonDownEventFilter>;

	/// @brief Signal class that fires an action when it handles a set of mouse button down events. Ignores all events that are not mouse button down events.
	using MouseButtonDownMatchSignaler = GestureMatchSignaler<MouseButtonEventComparator, MouseButtonDownEventFilter>;

	/// @brief Signal class that fires an action when it handles a set of mouse button down events. Ignores all events that are not mouse button down events.
	using ButtonDownMatchSignaler = GestureMatchSignaler<ButtonEventComparator, AnyButtonDownEventFilter>;
}