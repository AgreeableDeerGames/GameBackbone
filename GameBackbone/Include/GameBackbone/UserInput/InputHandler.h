#pragma once

#include <GameBackbone/Core/Updatable.h>

#include <SFML/Window/Event.hpp>

#include <vector>
#include <tuple>
#include <functional>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <string>



namespace GB {

	
	enum class EndType
	{
		Continuous,
		Reset,
		Stop,
		BlockLastEvent
	};

	// TODO: The event compare function should be an extension point. Should it be a template? A std::function?

	struct GestureBind
	{

		std::vector<sf::Event> gesture;
		std::function<void()> action;
		std::string name;
		sf::Int64 maxTimeBetweenInputs;

		GB::EndType endType;
	};

	class GestureBindBuilder
	{
	public:
		void addKeyPress(sf::Keyboard::Key key, bool ctrlHeld, bool shiftHeld) {}
		void addTimedKeyPress(sf::Keyboard::Key key, bool ctrlHeld, bool shiftHeld, sf::Int64 duration) {}
		void setAction(std::function<void()> action) {}
		GestureBind bind() { return {}; }
	};

	class InputHandler
	{
	public:


		static constexpr sf::Int64 defaultMaxTimeBetweenInputs = 1000;


		void addGesture(GestureBind bind)
		{
			m_wholeSet.push_back(bind);
			m_openSetGestures.emplace_back(bind, 0);
		}

		// TODO: This should be on the fire system extension point
		std::vector<GestureBind> m_bindsToFire;

		// Extension Point.
		void processActions()
		{
			for (const GestureBind& bind : m_bindsToFire)
			{
				std::invoke(bind.action);
			}
		}

		void consumeEvent(sf::Int64 elapsedTime, const sf::Event& event)
		{
			// Compare ActiveGesture
			if (!applyEventToOpenSet(elapsedTime, event))
			{
				// Reset open set to contain everything again
				resetGestures();
				// Compare ActiveGestures a second time.
				applyEventToOpenSet(elapsedTime, event);
			}

			// Update the process event system, and "fire" events that are ready
			processActions();
		}

	private:

		bool applyEventToOpenSet(sf::Int64 elapsedTime, const sf::Event& event)
		{
			bool eventApplied = false;
			for (std::size_t ii = 0; ii < m_openSetGestures.size(); ++ii)
			{
				// TODO: ensure that minimum time has passed
				if (compareEvents(m_openSetGestures[ii].first.gesture.at(m_openSetGestures[ii].second), event) /* && !hasTimedOut*/)
				{
					//TODO: add action with logged time to the process event system
					eventApplied = true;

					m_openSetGestures[ii].second += 1;

					if (m_openSetGestures[ii].second == m_openSetGestures[ii].first.gesture.size())
					{

						// TODO: fire action extension point handles this
						m_bindsToFire.push_back(m_openSetGestures[ii].first);

						// Tell the Stateful Gesture Bind to do something given its end type
						switch (m_openSetGestures[ii].first.endType)
						{
						case EndType::Continuous:
						{
							m_openSetGestures[ii].second -= 1;
							break;
						}
						case EndType::Reset:
						{
							m_openSetGestures[ii].second = 0;
							break;
						}
						case EndType::Stop:
						{
							m_openSetGestures.erase(m_openSetGestures.begin() + ii);
							break;
						}
						case EndType::BlockLastEvent:
						{
							// TODO: How? Why? Make Michael do it.
							break;
						}
						}
					}
				}
				else
				{
					// TODO: Take gesture out of open set
					m_openSetGestures.erase(m_openSetGestures.begin() + ii);
					--ii;
				}
			}

			return eventApplied;
		}


		// TODO: Extension point
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

		void resetGestures()
		{
			// Clear the open set completely
			m_openSetGestures.clear();

			// Add all gestures from the whole set to the active gestures open set.
			for (const GestureBind& bind : m_wholeSet)
			{
				m_openSetGestures.emplace_back(bind, 0);
			}
		}

		std::vector<std::pair<GestureBind, int>> m_openSetGestures;
		std::vector<GestureBind> m_wholeSet;

	};
}

/*
	Gesture - series of inputs
	Bind - Gesture, function
	ActiveGesture - Bind, state



	User:


*/



//class BoundGesture final : public Updatable
//{
//public:
//	BoundGesture(std::vector<sf::Event> gesture, std::function<void()> action, sf::Int64 maxTimeBetweenEvents) :
//		m_gesture(std::move(gesture)),
//		m_boundFunction(std::move(action)),
//		m_currentPosition(0),
//		m_timeSinceLastEvent(0),
//		m_maxTimeBetweenEvents(maxTimeBetweenEvents),
//		m_available(true)
//	{
//	}
//
//	void consumeEvent(const sf::Event& event)
//	{
//		if (this->isAvailable())
//		{
//			if (compareEvents(event, this->getNextEvent()))
//			{
//				++this->m_currentPosition;
//				this->m_timeSinceLastEvent = 0;
//				if (this->isDone())
//				{
//					// Fire event and disable gesture until timer finishes
//					this->fireEvent();
//				}
//			}
//			else
//			{
//				this->reset();
//			}
//		}
//	}
//
//	void update(sf::Int64 elapsedTime) final
//	{
//		if (!this->m_available || this->m_currentPosition != 0)
//		{
//			this->m_timeSinceLastEvent += elapsedTime;
//		}
//	}
//
//	const sf::Event& getNextEvent() const
//	{
//		assert(m_currentPosition < m_gesture.size());
//		return m_gesture[m_currentPosition];
//	}
//
//	void reset()
//	{
//		m_currentPosition = 0;
//		m_available = true;
//		m_timeSinceLastEvent = 0;
//	}
//
//	bool isAvailable() const
//	{
//		return m_available;
//	}
//
//	bool isDone() const
//	{
//		return m_currentPosition == m_gesture.size();
//	}
//
//	void fireEvent()
//	{
//		std::invoke(this->m_boundFunction);
//		this->m_available = false;
//	}
//
//private:
//
//	bool compareEvents(const sf::Event& lhs, const sf::Event& rhs)
//	{
//		if (lhs.type != rhs.type)
//		{
//			return false;
//		}
//		switch (lhs.type)
//		{
//		case sf::Event::KeyReleased:
//		case sf::Event::KeyPressed:
//			if (lhs.key.code == rhs.key.code)
//			{
//				return true;
//			}
//		default:
//			return false;
//		}
//	};
//
//	std::vector<sf::Event> m_gesture;
//	std::function<void()> m_boundFunction;
//	std::size_t m_currentPosition;
//	sf::Int64 m_timeSinceLastEvent;
//	sf::Int64 m_maxTimeBetweenEvents;
//	bool m_available;
//};