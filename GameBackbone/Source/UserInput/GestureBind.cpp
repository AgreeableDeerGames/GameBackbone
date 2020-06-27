
#include <GameBackbone/UserInput/GestureBind.h>
#include <GameBackbone/UserInput/EventComparitor.h>

#include <SFML/System/Time.hpp>

#include <string>
#include <cassert>

using namespace GB;

//GestureBind::GestureBind(
//	std::vector<sf::Event> gesture,
//	std::function<void()> action,
//	std::string name,
//	sf::Int64 maxTimeBetweenInputs,
//	EndType endType) :
//
//	m_gesture(std::move(gesture)),
//	m_action(std::move(action)),
//	m_name(std::move(name)),
//	m_maxTimeBetweenInputs(maxTimeBetweenInputs),
//	m_endType(endType),
//	m_position(0)
//{
//}
//
//GestureBind::HandleEvenResult GestureBind::handleEvent(sf::Int64 elapsedTime, const sf::Event& event)
//{
//	if (compareEvents(getNextEvent(), event) && elapsedTime < m_maxTimeBetweenInputs )
//	{
//		++m_position;
//		if ( m_position == m_gesture.size())
//		{
//			fireAction();
//			return getEndType() == EndType::Block ? HandleEvenResult::Completed : HandleEvenResult::Advanced;
//		}
//		return HandleEvenResult::Advanced;
//	}
//
//	m_position = 0;
//	return HandleEvenResult::Reset;
//}

//const std::vector<sf::Event>& GestureBind::getGesture() const
//{
//	return m_gesture;
//}
//
//std::function<void()>& GestureBind::getAction()
//{
//	return m_action;
//}
//
//const std::function<void()>& GestureBind::getAction() const
//{
//	return m_action;
//}
//
//const std::string& GestureBind::getName() const
//{
//	return m_name;
//}
//
//sf::Int64 GestureBind::getMaxTimeBetweenInputs() const
//{
//	return m_maxTimeBetweenInputs;
//}
//
//GestureBind::EndType GestureBind::getEndType() const
//{
//	return m_endType;
//}
//
//void GestureBind::setGesture(std::vector<sf::Event> gesture)
//{
//	m_gesture = std::move(gesture);
//}
//
//void GestureBind::setAction(std::function<void()> action)
//{
//	m_action = std::move(action);
//}
//
//void GestureBind::setName(std::string name)
//{
//	m_name = std::move(name);
//}
//
//void GestureBind::setMaxTimeBetweenInputs(sf::Int64 maxTimeBetweenInputs)
//{
//	m_maxTimeBetweenInputs = maxTimeBetweenInputs;
//}
//
//void GestureBind::setEndType(EndType endType)
//{
//	m_endType = endType;
//}
//
//bool GestureBind::compareEvents(const sf::Event& lhs, const sf::Event& rhs)
//{
//	// TODO: extension point
//	GB::SimpleEventComparitor cmp;
//	return cmp(lhs, rhs);
//}
//
//void GestureBind::fireAction()
//{
//	switch (getEndType())
//	{
//		case GestureBind::EndType::Continuous:
//		{
//			--m_position;
//			break;
//		}
//		case GestureBind::EndType::Reset:
//		{
//			m_position = 0;
//			break;
//		}
//		case GestureBind::EndType::BlockLastEvent:
//		{
//			// TODO: How? Why? Make Michael do it.
//			break;
//		}
//	}
//	std::invoke(m_action);
//}
//
//const sf::Event& GestureBind::getNextEvent() const
//{
//	assert(m_position > m_gesture.size());
//	return m_gesture[m_position];
//}
