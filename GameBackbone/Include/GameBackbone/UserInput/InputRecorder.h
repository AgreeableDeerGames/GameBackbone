#pragma once


#include <GameBackbone/Util/DllUtil.h>
#include <GameBackbone/UserInput/EventFilter.h>
#include <GameBackbone/UserInput/InputHandler.h>
#include <GameBackbone/UserInput/GestureMatchSignaler.h>

#include <SFML/Window/Event.hpp>

namespace GB
{
	/// @brief Records all events passed to handleEvent and then can construct a GestureMatchSignaler that matches with these events.
	/// @tparam EventComparator Passed into each GestureMatchSignaler upon construction.
	/// @tparam EventFilter Used to filter out events that this recorder should ignore and passed into each GestureMatchSignaler upon construction.
	template <
		typename EventComparator,
		typename EventFilter,
		std::enable_if_t<is_event_comparator_v<EventComparator>, bool> = true,
		std::enable_if_t<is_event_filter_v<EventFilter>, bool> = true
	>
	class InputRecorder final : public InputHandler
	{
	public:
		// Return type of getCompletedBind
		using ReturnGestureMatchSignaler = GestureMatchSignaler<EventComparator, EventFilter>;
		// Compare and Filter Type
		using EventComparatorType = EventComparator;
		using EventFilterType = EventFilter;

		/// @brief Construct an instance of InputRecorder.
		/// @param eventComparator Passed into each GestureMatchSignaler upon construction.
		/// @param eventFilter Used to filter out events that this recorder should ignore and passed into each GestureMatchSignaler upon construction.
		InputRecorder(EventComparatorType eventComparator, EventFilterType eventFilter) :
			m_eventComparator(std::move(eventComparator)),
			m_eventFilter(std::move(eventFilter)),
			m_bindKeys()
		{
		}

		/// @brief Construct an instance of InputRecorder. Default constructs the EventComparatorType and EventFilterType.
		template <
			typename = std::enable_if_t< std::is_default_constructible_v<EventComparatorType> >,
			typename = std::enable_if_t< std::is_default_constructible_v<EventFilterType> >
		>
		InputRecorder() : InputRecorder(EventComparatorType{}, EventFilterType{})
		{
		}

		/// @brief Records all events passed that then can construct a GestureMatchSignaler that matches with these events.
		/// @param elapsedTime Unused.
		/// @param event The event to record.
		/// @return Returns true if the event was recorded.
		bool handleEvent(sf::Int64 /*elapsedTime*/, const sf::Event& event) final
		{
			if (std::invoke(m_eventFilter, event))
			{
				// Push the event into the vector
				m_bindKeys.push_back(event);
				return true;
			}

			return false;
		}

		/// @brief Construct a ReturnGestureMatchSignaler to match the recorded Events.
		/// @param action The action that will be attached to the GB::GestureBindSignaler.
		/// @param matchBehavior The behavior of the resulting GB::GestureMatchSignaler after a successful match.
		/// @param maxTimeBetweenInputs The Maximum time in between inputs on the GB::GestureBindSignaler.
		/// @param shouldClear If true, clears the recorded events after construction of the GB::GestureBindSignaler. 
		/// @return The constructed ReturnGestureMatchSignaler.
		[[nodiscard]]
		ReturnGestureMatchSignaler getCompletedBind(
			std::function<void()> action, 
			typename ReturnGestureMatchSignaler::MatchBehavior matchBehavior = ReturnGestureMatchSignaler::MatchBehavior::Block,
			sf::Int64 maxTimeBetweenInputs = 1000000,
			bool shouldClear = true)
		{
			// Construct an ReturnGestureMatchSignaler with the current recorded events and the given action, matchBehavior, and maxTimeBetweenInputs.
			// m_eventComparator and m_eventFilter are copied and passed into the ReturnGestureMatchSignaler
			ReturnGestureMatchSignaler returnsignaler{
				m_bindKeys,
				action,
				matchBehavior,
				maxTimeBetweenInputs,
				m_eventComparator,
				m_eventFilter
			};

			if (shouldClear)
			{
				// Clear the internal state
				clear();
			}

			return returnsignaler;
		}

		/// @brief Clear all recorded events. 
		void clear()
		{
			m_bindKeys.clear();
		}

		/// @return Returns a reference to the instance of the EventComparator on the InputRecorder
		[[nodiscard]]
		const EventComparatorType& getEventComparator() const
		{
			return m_eventComparator;
		}

		/// @return Returns a reference to the instance of the EventComparator on the InputRecorder
		[[nodiscard]]
		EventComparatorType& getEventComparator()
		{
			return m_eventComparator;
		}

		
		/// @return Returns a reference to the instance of the EventFilter on the InputRecorder
		[[nodiscard]]
		const EventFilterType& getEventFilter() const
		{
			return m_eventFilter;
		}

		/// @return Returns a reference to the instance of the EventFilter on the InputRecorder
		[[nodiscard]]
		EventFilterType& getEventFilter()
		{
			return m_eventFilter;
		}

	private:
		EventComparatorType m_eventComparator;
		EventFilterType m_eventFilter;

		std::vector<sf::Event> m_bindKeys;
	};
}