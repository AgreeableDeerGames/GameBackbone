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

	/**
	 * consider having all gesture state managed by Gesture Bind
	 * provide ways to tell if an event was handled or not and if the gesture
	 * is complete. This way ButtonPressGestureHandler can do its thing
	 */

	template <typename EventCompare, std::enable_if_t<is_event_comparitor_v<EventCompare>, bool> = true>
	class BasicGestureBind
	{
	public:

		static constexpr sf::Int64 defaultMaxTimeBetweenInputs = 1000;

		enum class EndType
		{
			Continuous,
			Reset,
			Block,
			BlockLastEvent
		};

		struct ProcessEventResult
		{
			bool actionFired;
			bool readyForInput;
		};

		BasicGestureBind(
			std::vector<sf::Event> gesture,
			std::function<void()> action,
			std::string name,
			sf::Int64 maxTimeBetweenInputs,
			EndType endType
		) :

			m_gesture(std::move(gesture)),
			m_action(std::move(action)),
			m_name(std::move(name)),
			m_maxTimeBetweenInputs(maxTimeBetweenInputs),
			m_endType(endType),
			m_position(0),
			m_eventComparitor(),
			m_readyForInput(true)
		{
		}

		ProcessEventResult processEvent(sf::Int64 elapsedTime, const sf::Event& event)
		{

			// Exit early if not ready for input
			if (!readyForInput())
			{
				return { false, false };
			}

			// Process the input
			bool actionFired = false;
			if (compareEvents(getNextEvent(), event) && elapsedTime < m_maxTimeBetweenInputs)
			{
				++m_position;
				if (m_position == m_gesture.size())
				{
					fireAction();
					actionFired = true;
				}
			}
			// The input did not match. Disable this GestureBind.
			else
			{
				m_position = 0;
				m_readyForInput = false;
			}

			// Return state to caller
			return { actionFired, readyForInput() };
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

		const std::string& getName() const
		{
			return m_name;
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

		void setName(std::string name)
		{
			m_name = std::move(name);
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
			return m_readyForInput;
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
			// TODO: we can hit this assertion if the gesture has a size of 0
			assert(m_position < m_gesture.size());
			return m_gesture[m_position];
		}

		std::vector<sf::Event> m_gesture;
		std::function<void()> m_action;
		std::string m_name;
		sf::Int64 m_maxTimeBetweenInputs;
		EndType m_endType;
		std::size_t m_position;
		bool m_readyForInput;
		EventCompare m_eventComparitor;
	};
}