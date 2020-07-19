#pragma once

#include <GameBackbone/Util/DllUtil.h>
#include <GameBackbone/UserInput/EventComparitor.h>
#include <GameBackbone/UserInput/InputHandler.h>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <cassert>
#include <functional>
#include <string>
#include <vector>



namespace GB
{

	struct GestureBindProcessEventResult
	{
		bool actionFired;
		bool readyForInput;
		bool inputConsumed;
	};

	namespace detail 
	{
		template <class GestureBind>
		using GestureBindProcessEvent = decltype(
			std::declval<GestureBindProcessEventResult>() = std::declval<GestureBind>().processEvent(std::declval<sf::Int64>(), std::declval<const sf::Event&>())
		);

		template <class GestureBind, class = void>
		struct supports_gesture_bind_process_event : std::false_type {};

		template <class GestureBind>
		struct supports_gesture_bind_process_event <GestureBind, std::void_t<GestureBindProcessEvent<GestureBind>>> :
			std::true_type {};
	}

	template <class GestureBind>
	using is_gesture_bind =
		std::conjunction<
			std::is_copy_constructible<GestureBind>,
			detail::supports_gesture_bind_process_event<GestureBind>
		>;

	template <class GestureBind>
	inline constexpr bool is_gesture_bind_v = is_gesture_bind<GestureBind>::value;

	template <typename EventCompare, std::enable_if_t<is_event_comparitor_v<EventCompare>, bool> = true>
	class BasicGestureBind
	{
	public:

		static constexpr sf::Int64 defaultMaxTimeBetweenInputs = 1000;

		using ProcessEventResult = GestureBindProcessEventResult;

		enum class EndType
		{
			Continuous,
			Reset,
			Block,
			BlockLastEvent
		};

		BasicGestureBind(
			std::vector<sf::Event> gesture,
			std::function<void()> action,
			EndType endType,
			sf::Int64 maxTimeBetweenInputs
		) :

			m_gesture(std::move(gesture)),
			m_action(std::move(action)),
			m_endType(endType),
			m_maxTimeBetweenInputs(maxTimeBetweenInputs),
			m_position(0),
			m_eventComparitor(),
			m_readyForInput(true)
		{
		}

		BasicGestureBind(
			std::vector<sf::Event> gesture,
			std::function<void()> action,
			EndType endType) :
			BasicGestureBind(
				std::move(gesture),
				std::move(action),
				endType,
				defaultMaxTimeBetweenInputs)
		{
		}

		BasicGestureBind(
			std::vector<sf::Event> gesture,
			std::function<void()> action) :
			BasicGestureBind(
				std::move(gesture),
				std::move(action),
				EndType::Block,
				defaultMaxTimeBetweenInputs)
		{
		}

		ProcessEventResult processEvent(sf::Int64 elapsedTime, const sf::Event& event)
		{

			// Exit early if not ready for input
			if (!readyForInput())
			{
				return { false, false, false };
			}

			// Process the input
			bool actionFired = false;
			bool inputConsumed = false;
			if (compareEvents(getNextEvent(), event) && elapsedTime < m_maxTimeBetweenInputs)
			{
				++m_position;
				if (m_position == m_gesture.size())
				{
					fireAction();
					actionFired = true;
				}
				inputConsumed = true;
			}
			// The input did not match. Disable this GestureBind.
			else
			{
				m_position = 0;
				m_readyForInput = false;
			}

			// Return state to caller
			return { actionFired, readyForInput(), inputConsumed };
		}

		const std::vector<sf::Event>& getGesture() const
		{
			return m_gesture;
		}

		const std::function<void()>& getAction() const
		{
			return m_action;
		}

		std::function<void()>& getAction()
		{
			return m_action;
		}

		sf::Int64 getMaxTimeBetweenInputs() const
		{
			return m_maxTimeBetweenInputs;
		}

		EndType getEndType() const
		{
			return m_endType;
		}

		void setGesture(std::vector<sf::Event> gesture)
		{
			m_gesture = std::move(gesture);
		}

		void setAction(std::function<void()> action)
		{
			m_action = std::move(action);
		}

		void setMaxTimeBetweenInputs(sf::Int64 maxTimeBetweenInputs)
		{
			m_maxTimeBetweenInputs = maxTimeBetweenInputs;
		}

		void setEndType(EndType endType)
		{
			m_endType = endType;
		}

		void reset()
		{
			m_position = 0;
			m_readyForInput = true;
		}

		bool readyForInput() const
		{
			return m_readyForInput && !m_gesture.empty();
		}

	private:

		bool compareEvents(const sf::Event& lhs, const sf::Event& rhs)
		{
			return std::invoke(m_eventComparitor, lhs, rhs);
		}

		void fireAction()
		{
			switch (getEndType())
			{
			case EndType::Continuous:
			{
				--m_position;
				break;
			}
			case EndType::Reset:
			{
				reset();
				break;
			}
			case EndType::BlockLastEvent:
			{
				// TODO: How? Why? Make Michael do it.
				break;
			}
			case EndType::Block:
			{
				m_position = 0;
				m_readyForInput = false;
				break;
			}
			}
			std::invoke(m_action);
		}

		const sf::Event& getNextEvent() const
		{
			assert(m_position < m_gesture.size());
			return m_gesture[m_position];
		}

		std::vector<sf::Event> m_gesture;
		std::function<void()> m_action;
		EndType m_endType;
		sf::Int64 m_maxTimeBetweenInputs;
		std::size_t m_position;
		bool m_readyForInput;
		EventCompare m_eventComparitor;
	};

	using KeyboardGestureBind = BasicGestureBind<KeyEventComparitor>;

	using JoystickButtonGestureBind = BasicGestureBind<JoystickButtonEventComparitor>;

	using MouseButtonGestureBind = BasicGestureBind<MouseButtonEventComparitor>;

	using ButtonGestureBind = BasicGestureBind<ButtonEventComparitor>;
}