#pragma once

#include <GameBackbone/Core/Updatable.h>

#include <SFML/Window/Event.hpp>

#include <vector>
#include <tuple>
#include <functional>
#include <algorithm>
#include <chrono>



namespace GB {

	// TODO: The event compare function should be an extension point. Should it be a template? A std::function?

	class InputHandler : Updatable
	{
	public:

		static constexpr sf::Int64 defaultMaxTimeBetweenInputs = 1000;
		static constexpr sf::Int64 defaultMinTimeBetweenTrigger = 200;

		void addGesture(std::vector<sf::Event> gesture, std::function<void()> func)
		{
			addGesture(std::move(gesture), func, defaultMaxTimeBetweenInputs, defaultMinTimeBetweenTrigger);
		}

		void addGesture(std::vector<sf::Event> gesture, std::function<void()> func, sf::Int64 maxTimeBetweenInputs, sf::Int64 minTimeBetweenTrigger)
		{
			m_gestureBinds.emplace_back(std::move(gesture), std::move(func), maxTimeBetweenInputs, minTimeBetweenTrigger);
		}

		void consumeEvent(const sf::Event& event)
		{
			for (auto& bound : m_gestureBinds)
			{
				bound.consumeEvent(event);
			}
		}

		void update(sf::Int64 elapsedTime) override
		{
			for (auto& bound : m_gestureBinds)
			{
				bound.update(elapsedTime);
			}
		}

	private:

		class BoundGesture final : public Updatable
		{
		public:
			BoundGesture(std::vector<sf::Event> gesture, std::function<void()> action, sf::Int64 maxTimeBetweenEvents, sf::Int64 minTimeBetweenTrigger) :
				m_gesture(std::move(gesture)),
				m_boundFunction(std::move(action)),
				m_currentPosition(0),
				m_timeSinceLastEvent(0),
				m_maxTimeBetweenEvents(maxTimeBetweenEvents),
				m_minTimeBetweenTrigger(minTimeBetweenTrigger),
				m_available(true)
			{
			}

			void consumeEvent(const sf::Event& event)
			{
				if (this->isAvailable())
				{
					if (compareEvents(event, this->getNextEvent()))
					{
						++this->m_currentPosition;
						this->m_timeSinceLastEvent = 0;
						if (this->isDone())
						{
							// Fire event and disable gesture until timer finishes
							this->fireEvent();
						}
					}
					else
					{
						this->reset();
					}
				}
			}

			void update(sf::Int64 elapsedTime) final
			{
				if (!this->m_available || this->m_currentPosition != 0)
				{
					this->m_timeSinceLastEvent += elapsedTime;
				}

				// enough time has passed after last action to be able to fire again or current bind has timed out
				if ((!this->m_available && this->m_timeSinceLastEvent >= this->m_minTimeBetweenTrigger)
					|| (this->m_timeSinceLastEvent >= this->m_maxTimeBetweenEvents))
				{
					this->reset();
				}
			}

			const sf::Event& getNextEvent() const
			{
				assert(m_currentPosition < m_gesture.size());
				return m_gesture[m_currentPosition];
			}

			void reset()
			{
				m_currentPosition = 0;
				m_available = true;
				m_timeSinceLastEvent = 0;
			}

			bool isAvailable() const
			{
				return m_available;
			}

			bool isDone() const
			{
				return m_currentPosition == m_gesture.size();
			}

			void fireEvent()
			{
				std::invoke(this->m_boundFunction);
				this->m_available = false;
			}

		private:

			bool compareEvents(const sf::Event& lhs, const sf::Event& rhs)
			{
				if (lhs.type != rhs.type)
				{
					return false;
				}
				switch (lhs.type)
				{
				case sf::Event::KeyReleased:
				case sf::Event::KeyPressed:
					if (lhs.key.code == rhs.key.code)
					{
						return true;
					}
				default:
					return false;
				}
			};

			std::vector<sf::Event> m_gesture;
			std::function<void()> m_boundFunction;
			std::size_t m_currentPosition;
			sf::Int64 m_timeSinceLastEvent;
			sf::Int64 m_maxTimeBetweenEvents;
			sf::Int64 m_minTimeBetweenTrigger;
			bool m_available;
		};

		std::vector<BoundGesture> m_gestureBinds;
	};
}
