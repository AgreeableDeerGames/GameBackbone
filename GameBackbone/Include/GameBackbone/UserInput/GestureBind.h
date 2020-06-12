#pragma once

namespace GB
{
	enum class EndType
	{
		Continuous,
		Reset,
		Stop,
		BlockLastEvent
	};

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
}