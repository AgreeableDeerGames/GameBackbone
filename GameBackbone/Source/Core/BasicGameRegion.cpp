#include <GameBackbone/Core/BasicGameRegion.h>

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <exception>
#include <utility>

using namespace GB;

BasicGameRegion::BasicGameRegion() : m_nextRegion(*this) {}

BasicGameRegion& BasicGameRegion::getNextRegion()
{
	return m_nextRegion;
}

const BasicGameRegion& BasicGameRegion::getNextRegion() const
{
	return m_nextRegion;
}

void BasicGameRegion::setNextRegion(BasicGameRegion& nextRegion)
{
	m_nextRegion = nextRegion;
}
