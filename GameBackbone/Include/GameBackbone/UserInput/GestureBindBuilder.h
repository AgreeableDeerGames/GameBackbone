#pragma once

#include <GameBackbone/UserInput/GestureBind.h>

#include <SFML/Window/Event.hpp>

#include <optional>

namespace GB
{

	class GestureBindBuilder
	{
	public:
		void addKeyPress(sf::Keyboard::Key key, bool ctrlHeld, bool shiftHeld) {}
		void addTimedKeyPress(sf::Keyboard::Key key, bool ctrlHeld, bool shiftHeld, sf::Int64 duration) {}
		void setAction(std::function<void()> action) {}
		void setEndType() {}
		GestureBind bind() { return *m_activeBind; }

	private:
		std::optional<GestureBind> m_activeBind;
	};

}
