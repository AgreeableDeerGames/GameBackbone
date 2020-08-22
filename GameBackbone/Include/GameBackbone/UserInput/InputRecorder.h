#pragma once


#include <GameBackbone/Util/DllUtil.h>
#include <GameBackbone/UserInput/EventFilter.h>
#include <GameBackbone/UserInput/InputHandler.h>
#include <GameBackbone/UserInput/GestureBind.h>

#include <SFML/Window/Event.hpp>

namespace GB
{
	// SFNIAE
	template <typename EventCompare, typename EventFilter>
	class InputRecorder : public InputHandler
	{
	public:
		using ReturnBind = BasicGestureBind<EventCompare, EventFilter>;
		// Compare and Filter Type
		// using ReturnBind = BasicGestureBind<EventCompare, EventFilter>;
		// using ReturnBind = BasicGestureBind<EventCompare, EventFilter>;

		// Constructors

		bool handleEvent(sf::Int64 elapsedTime, const sf::Event& event) override
		{
			if (std::invoke(m_eventFilter, event))
			{
				// Push the event into the vector
				m_bindKeys.push_back(event);
				return true;
			}

			return false;
		}

		
		ReturnBind getCompletedBind(
			std::function<void()> action, 
			typename ReturnBind::EndType endType = ReturnBind::EndType::Block,
			sf::Int64 maxTimeBetweenInputs = 1000000)
		{
			ReturnBind returnBind{
				m_bindKeys,
				action,
				endType,
				maxTimeBetweenInputs
			};

			// Clear the internal state
			reset();

			return returnBind;
		}

		void reset()
		{
			m_bindKeys.clear();
		}

		void Getter()
		{}

		void Getter()
		{}


	private:
		EventCompare m_eventComparitor;
		EventFilter m_eventFilter;

		std::vector<sf::Event> m_bindKeys;
	};
}