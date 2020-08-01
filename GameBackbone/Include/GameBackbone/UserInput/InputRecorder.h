#pragma once


#include <GameBackbone/Util/DllUtil.h>
#include <GameBackbone/UserInput/EventFilter.h>
#include <GameBackbone/UserInput/InputHandler.h>
#include <GameBackbone/UserInput/GestureBind.h>

#include <SFML/Window/Event.hpp>

namespace GB
{
	template <typename EventCompare, typename EventFilter>
	class InputRecorder : public InputHandler
	{
	public:
		using ReturnBind = BasicGestureBind<EventCompare, EventFilter>;

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


		ReturnBind GetCompletedBind(
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
			m_bindKeys.clear();

			return returnBind;
		}

		EventCompare m_eventComparitor;
		EventFilter m_eventFilter;

		std::vector<sf::Event> m_bindKeys;
	};
}