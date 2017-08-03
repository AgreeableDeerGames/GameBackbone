#pragma once

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

	//---------------------------------------------------------------------------------------------------------------------


	//NavigationGrid memory

	/// <summary>
	/// Initializes all navigation grid values to the passed value.
	/// </summary>
	/// <param name="navGrid">The navigation grid to fill with values</param>
	/// <param name="gridData">The NavigationGridData to copy into each index of the Navigation Grid.</param>
	template <class NavigationDataType>
	libGameBackbone extern void initAllNavigationGridValues(NavigationGrid & navGrid, NavigationDataType & gridData) {
		for (unsigned int ii = 0; ii < navGrid.getArraySizeX(); ++ii) {
			for (unsigned int jj = 0; jj < navGrid.getArraySizeY(); ++jj)
			{
				NavigationGridData* navData = static_cast<NavigationGridData*>(new NavigationDataType(gridData));
				navGrid[ii][jj] = navData;
			}
		}
	}

	libGameBackbone extern void freeAllNavigationGridData(NavigationGrid & navGrid);

	//---------------------------------------------------------------------------------------------------------------------

	//sprite movement to point
	libGameBackbone extern void moveSpriteStepTowardsPoint(sf::Sprite& sprite,
														   const sf::Vector2f& destination,
														   const float maxStepLength,
														   const bool orientSpriteToDestination = true);


	libGameBackbone extern void bulkMoveSpriteStepTowardsPoint(const std::vector<sf::Sprite*>& sprites, 
																const std::vector<sf::Vector2f>& destinations,
																const std::vector<float>& maxStepLength,
																const bool orientSpritesToDestination = true);

	//---------------------------------------------------------------------------------------------------------------------


	//sprite movement along path
	libGameBackbone extern void moveSpriteAlongPath(sf::Sprite& sprite, 
													std::shared_ptr<std::list<sf::Vector2f>> path,
													sf::Uint64 msPassed,
													float distPerMs,
													const bool orientSpriteToDestination = true);


	libGameBackbone extern void bulkMoveSpriteAlongPath(const std::vector<sf::Sprite*>& sprites,
														 const std::vector<std::shared_ptr<std::list<sf::Vector2f>>>& paths, 
														 const sf::Uint64 msPassed,
														 const std::vector<float>& distPerMs,
													     const bool orientSpritesToDestination = true);

	//---------------------------------------------------------------------------------------------------------------------


}