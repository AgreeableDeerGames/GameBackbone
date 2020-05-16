#pragma once

#include <GameBackbone/UserInput/Gesture.h>

#include <vector>
#include <tuple>
#include <functional>


namespace GB {
	class InputHandler
	{

	public:
		void addGesture(Gesture gesture, std::function<void()> func)
		{
			m_gestureBinds.push_back(std::pair<Gesture, std::function<void()>>{std::move(gesture), std::move(func)});
		}

		void consumeEvent(const sf::Event& event)
		{
			for (auto& bind : m_gestureBinds)
			{
				// Invoke the function associated with the gesture if the event completed the gesture
				if (bind.first.applyEvent(event))
				{
					std::invoke(bind.second);
				}
			}
		}

	private:
		std::vector<std::pair<Gesture, std::function<void()>>> m_gestureBinds;

	};
}
