#pragma once

#include <Backbone\CompoundSprite.h>
#include <Navigation\NavigationGridData.h>
#include <Util\Array2D.h>
#include <Util\DllUtil.h>
#include <Util\Point.h>

#include <SFML\Graphics.hpp>

#include <list>
#include <vector>
#include <memory>


namespace GB {
	libGameBackbone typedef Array2D<NavigationGridData*> NavigationGrid;
	libGameBackbone typedef std::list<sf::Vector2f> WindowCoordinatePath;
	libGameBackbone typedef std::shared_ptr<WindowCoordinatePath> WindowCoordinatePathPtr;

	//---------------------------------------------------------------------------------------------------------------------
	// NavigationGrid memory


	libGameBackbone extern void initAllNavigationGridValues(NavigationGrid & navGrid, NavigationGridData & gridData);
	libGameBackbone extern void freeAllNavigationGridData(NavigationGrid & navGrid);

	//---------------------------------------------------------------------------------------------------------------------
	// sprite movement to point


	libGameBackbone extern void moveSpriteStepTowardsPoint(sf::Sprite& sprite,
														   const sf::Vector2f& destination,
														   const float maxStepLength,
														   const bool orientSpriteToDestination = true);


	libGameBackbone extern void bulkMoveSpriteStepTowardsPoint(const std::vector<sf::Sprite*>& sprites, 
																const std::vector<sf::Vector2f>& destinations,
																const std::vector<float>& maxStepLength,
																const bool orientSpritesToDestination = true);

	libGameBackbone extern void moveCompoundSpriteStepTowardsPoint(CompoundSprite& sprite,
																   const sf::Vector2f& destination,
																   const float maxStepLength,
																   const bool orientSpriteToDestination = true);


	libGameBackbone extern void bulkMoveCompoundSpriteStepTowardsPoint(const std::vector<CompoundSprite*>& sprites,
																	   const std::vector<sf::Vector2f>& destinations,
																	   const std::vector<float>& maxStepLength,
																	   const bool orientSpritesToDestination = true);

	//---------------------------------------------------------------------------------------------------------------------
	// sprite movement along path


	libGameBackbone extern void moveSpriteAlongPath(sf::Sprite& sprite, 
													WindowCoordinatePathPtr path,
													sf::Uint64 msPassed,
													float distPerMs,
													const bool orientSpriteToDestination = true);


	libGameBackbone extern void bulkMoveSpriteAlongPath(const std::vector<sf::Sprite*>& sprites,
														 const std::vector<WindowCoordinatePathPtr>& paths,
														 const sf::Uint64 msPassed,
														 const std::vector<float>& distPerMs,
													     const bool orientSpritesToDestination = true);

	//---------------------------------------------------------------------------------------------------------------------


}