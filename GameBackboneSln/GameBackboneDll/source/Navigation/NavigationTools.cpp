#include <Backbone\BackboneBaseExceptions.h>
#include <Navigation\NavigationTools.h>
#include <Util\UtilMath.h>

#include <SFML\Graphics\Sprite.hpp>

using namespace GB;

/// <summary>
/// Initializes all navigation grid values to the passed value.
/// </summary>
/// <param name="navGrid">The navigation grid to fill with values</param>
/// <param name="gridData">The NavigationGridData to copy into each index of the Navigation Grid.</param>
void GB::initAllNavigationGridValues(NavigationGrid & navGrid, NavigationGridData & gridData) {
	for (unsigned int ii = 0; ii < navGrid.getArraySizeX(); ++ii) {
		for (unsigned int jj = 0; jj < navGrid.getArraySizeY(); ++jj)
		{
			navGrid[ii][jj] = new NavigationGridData(gridData);
		}
	}
}

/// <summary>
/// Frees all memory stored in the NavigationGrid
/// </summary>
/// <param name="navGrid">The NavigationGrid.</param>
void GB::freeAllNavigationGridData(NavigationGrid & navGrid) {
	for (unsigned int ii = 0; ii < navGrid.getArraySizeX(); ++ii) {
		for (unsigned int jj = 0; jj < navGrid.getArraySizeY(); ++jj)
		{
			delete navGrid[ii][jj];
		}
	}
}

void GB::moveSpriteStepTowardsPoint(sf::Sprite & sprite, const sf::Vector2f & destination, const float maxStepLength, const bool orientSpriteToDestination)
{
	return;
}

/// <summary>
/// Moves all passed sprites towards the destination of the same index.
/// Sprites will not overshoot their destination.
/// </summary>
/// <param name="sprites">The sprites.</param>
/// <param name="destinations">The destinations.</param>
/// <param name="maxStepLengths">The maximum distances to move the sprites.</param>
/// <param name="orientSpritesToDestination">Orients sprites towards their destination if true. Does not orient sprites otherwise.</param>
void GB::bulkMoveSpriteStepTowardsPoint(const std::vector<sf::Sprite*>& sprites,
										 const std::vector<sf::Vector2f>& destinations,
										 const std::vector<float>& maxStepLengths,
										 const bool orientSpritesToDestination) {

	//ensure that all arrays are the same size
	if (sprites.size() != destinations.size() || sprites.size() != maxStepLengths.size()) {
		throw Error::NavigationTools_MismatchedNavigationSizes();
	}

	for (unsigned int ii = 0; ii < sprites.size(); ii++) {
		sf::Sprite* sprite = sprites[ii];
		const sf::Vector2f currentPosition = sprite->getPosition();
		sf::Vector2f destination = destinations[ii];
		float maxStepLength = maxStepLengths[ii];
		float angleToDest = atan2f(currentPosition.y - destination.y, currentPosition.x - destination.x);


		// Move directly to the destination if it's within reach
		if (CalcDistance2D_2<float, sf::Vector2f>(currentPosition, destination) >= maxStepLength) {
			sprite->setPosition(destination);
		} else { //Move the sprite as close as possible to the destination
			float xProgress = cosf(angleToDest) * maxStepLength;
			float yProgress = sinf(angleToDest) * maxStepLength;
			sprite->move(xProgress, yProgress);
		}

		//rotate the sprite if rotation is on
		if (orientSpritesToDestination) {
			sprite->setRotation(angleToDest);
		}
	}
}

void GB::moveSpriteAlongPath(sf::Sprite & sprite, std::list<Point2D<int>>* path, sf::Int64 msPassed, float distPerMs)
{
	return;
}

void GB::bulkMoveSpriteAlongPath(const std::vector<sf::Sprite*>& sprites, const std::vector<std::list<Point2D<int>>*>& paths, const sf::Int64 msPassed, const std::vector<float>& distPerMs, const bool orientSpriteToDestination)
{
	return;
}
