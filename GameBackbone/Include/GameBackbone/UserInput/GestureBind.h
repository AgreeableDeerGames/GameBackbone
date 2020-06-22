#pragma once

#include <GameBackbone/Util/DllUtil.h>
#include <GameBackbone/UserInput/InputHandler.h>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

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

	class libGameBackbone GestureBind //  : public InputHandler
	{
	public:

		enum class EndType
		{
			Continuous,
			Reset,
			Block,
			BlockLastEvent
		};

		enum class HandleEvenResult
		{
			Reset,
			Advanced,
			Completed
		};

		GestureBind(
			std::vector<sf::Event> gesture,
			std::function<void()> action,
			std::string name,
			sf::Int64 maxTimeBetweenInputs,
			EndType endType
		);

		// TODO: this should probably be a different name so as to not be confused with InputHandler
		HandleEvenResult handleEvent(sf::Int64 elapsedTime, const sf::Event& event); // override;
		void reset();

		const std::vector<sf::Event>& getGesture() const;
		const std::function<void()>& getAction() const;
		std::function<void()>& getAction();
		const std::string& getName() const;
		sf::Int64 getMaxTimeBetweenInputs() const;
		EndType getEndType() const;
		bool isDone() const;

		void setGesture(std::vector<sf::Event> gesture);
		void setAction(std::function<void()> action);
		void setName(std::string name);
		void setMaxTimeBetweenInputs(sf::Int64 maxTimeBetweenInputs);
		void setEndType(EndType endType);

	private:

		bool compareEvents(const sf::Event& lhs, const sf::Event& rhs);
		void fireAction();
		const sf::Event& getNextEvent() const;

		std::vector<sf::Event> m_gesture;
		std::function<void()> m_action;
		std::string m_name;
		sf::Int64 m_maxTimeBetweenInputs;
		EndType m_endType;
		std::size_t m_position;
		bool m_isDone;
	};
}