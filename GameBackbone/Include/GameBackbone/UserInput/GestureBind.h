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

		enum class EndType
		{
			Continuous,
			Reset,
			Block,
			BlockLastEvent
		};

		// TODO: Think about making this a POD struct
		enum class HandleEventResult
		{
			Reset,
			Advanced,
			Completed
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
			m_position(0)
		{
		}

		// TODO: this should probably be a different name so as to not be confused with InputHandler
		// process event, update bind, 
		HandleEventResult handleEvent(sf::Int64 elapsedTime, const sf::Event& event)
		{
			if (compareEvents(getNextEvent(), event) && elapsedTime < m_maxTimeBetweenInputs)
			{
				++m_position;
				if (m_position == m_gesture.size())
				{
					fireAction();
					return getEndType() == EndType::Block ? HandleEventResult::Completed : HandleEventResult::Advanced;
				}
				return HandleEventResult::Advanced;
			}

			m_position = 0;
			return HandleEventResult::Reset;
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

	private:

		bool compareEvents(const sf::Event& lhs, const sf::Event& rhs)
		{
			// TODO: extension point
			return m_eventComparitor(lhs, rhs);
		}

		void fireAction()
		{
			switch (getEndType())
			{
			case BasicGestureBind::EndType::Continuous:
			{
				--m_position;
				break;
			}
			case BasicGestureBind::EndType::Reset:
			{
				m_position = 0;
				break;
			}
			case BasicGestureBind::EndType::BlockLastEvent:
			{
				// TODO: How? Why? Make Michael do it.
				break;
			}
			}
			std::invoke(m_action);
		}

		const sf::Event& getNextEvent() const
		{
			assert(m_position > m_gesture.size());
			return m_gesture[m_position];
		}

		std::vector<sf::Event> m_gesture;
		std::function<void()> m_action;
		std::string m_name;
		sf::Int64 m_maxTimeBetweenInputs;
		EndType m_endType;
		std::size_t m_position;
		EventCompare m_eventComparitor;
	};
}