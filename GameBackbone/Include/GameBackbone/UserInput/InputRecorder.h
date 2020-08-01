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
		using BasicGestureBind<EventCompare, EventFilter>;

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


		 GetCompletedBind(std::string name, std::function<void()> action)
		{
			sf::Int64 maxTimeBetweenInputs = 1000000;
			NumberGestureBind::EndType endType = NumberGestureBind::EndType::Block;

			NumberGestureBind returnBind{
				m_bindKeys,
				action,
				name,
				maxTimeBetweenInputs,
				endType
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