#pragma once

#include <Navigation\NavigationGridData.h>
#include <Util\Array2D.h>
#include <Util\DllUtil.h>
#include <Util\Point.h>

#include <SFML\Graphics.hpp>

#include <list>
#include <vector>


namespace GB {
	libGameBackbone typedef Array2D<NavigationGridData*> NavigationGrid;

	libGameBackbone extern void initAllNavigationGridValues(NavigationGrid & navGrid, NavigationGridData & gridData);
	libGameBackbone extern void freeAllNavigationGridData(NavigationGrid & navGrid);

	libGameBackbone extern void moveSpriteToPoint(sf::Sprite& sprite, const sf::Vector2f& destination, const float pixelsPerMs);
	libGameBackbone extern void moveAllSpritesToPoint(const std::vector<sf::Sprite*>& sprites, const std::vector<const sf::Vector2f>& destinations, const std::vector<const float>& pixelsPerMs);
	libGameBackbone extern void moveSpriteStepTowardsPoint(sf::Sprite& sprite, const sf::Vector2f& destination, const float maxStepLength);

}