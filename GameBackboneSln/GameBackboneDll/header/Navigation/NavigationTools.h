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

	//NavigationGrid memory
	libGameBackbone extern void initAllNavigationGridValues(NavigationGrid & navGrid, NavigationGridData & gridData);
	libGameBackbone extern void freeAllNavigationGridData(NavigationGrid & navGrid);

	//sprite movement to point
	libGameBackbone extern void moveSpriteStepTowardsPoint(sf::Sprite& sprite, const sf::Vector2f& destination, const float maxStepLength, const bool orientSpriteToDestination = true);
	libGameBackbone extern void batchMoveSpriteStepTowardsPoint(const std::vector<sf::Sprite*>& sprites, 
																const std::vector<sf::Vector2f>& destinations,
																const std::vector<float>& maxStepLength,
																const bool orientSpritesToDestination = true);

	//sprite movement along path
	libGameBackbone extern void moveSpriteAlongPath(sf::Sprite& sprite, std::list<Point2D<int>>* path, sf::Int64 msPassed, float distPerMs);
	libGameBackbone extern void batchMoveSpriteAlongPath(const std::vector<sf::Sprite*>& sprites,
														 const std::vector<std::list<Point2D<int>>*>& paths, 
														 const sf::Int64 msPassed,
														 const std::vector<float>& distPerMs,
													     const bool orientSpriteToDestination = true);
}