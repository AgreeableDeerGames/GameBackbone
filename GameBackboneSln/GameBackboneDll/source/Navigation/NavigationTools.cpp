#include <Backbone\BackboneBaseExceptions.h>
#include <Navigation\NavigationTools.h>
#include <Util\UtilMath.h>

#include <SFML\Graphics\Sprite.hpp>

#include <math.h>

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
	std::vector<sf::Sprite*> sprites = {&sprite};
	std::vector<sf::Vector2f> destinations = {destination};
	std::vector<float> maxStepLengths = {maxStepLength};

	bulkMoveSpriteStepTowardsPoint(sprites, destinations, maxStepLengths, orientSpriteToDestination);
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
		float angleToDest = atan2f(destination.y - currentPosition.y, destination.x - currentPosition.x);


		// Move directly to the destination if it's within reach
		if (CalcDistance2D_2<float, sf::Vector2f>(currentPosition, destination) <= maxStepLength) {
			sprite->setPosition(destination);
		} else { //Move the sprite as close as possible to the destination
			float xProgress = cosf(angleToDest) * maxStepLength;
			float yProgress = sinf(angleToDest) * maxStepLength;
			sprite->move(xProgress, yProgress);
		}

		//rotate the sprite if rotation is on
		if (orientSpritesToDestination) {
			sprite->setRotation(angleToDest * 180.0f / M_PI);
		}
	}
}

void GB::moveSpriteAlongPath(sf::Sprite & sprite, std::list<sf::Vector2f>* path, sf::Int64 msPassed, float distPerMs, const bool orientSpriteToDestination)
{
	std::vector<sf::Sprite*> sprites = {&sprite};
	std::vector<std::list<sf::Vector2f>*> paths = {path};
	std::vector<float> distPerMsVec = {distPerMs};

	bulkMoveSpriteAlongPath(sprites, paths, msPassed, distPerMsVec, orientSpriteToDestination);
}

void GB::bulkMoveSpriteAlongPath(const std::vector<sf::Sprite*>& sprites, const std::vector<std::list<sf::Vector2f>*>& paths, const sf::Int64 msPassed, const std::vector<float>& distPerMs, const bool orientSpritesToDestination)
{
	// insure that the input sizes match
	if (sprites.size() != paths.size() || sprites.size() != distPerMs.size()) {
		throw Error::NavigationTools_MismatchedNavigationSizes();
	}


	// determine speed and destination
	std::vector<float> maxStepLengths;
	maxStepLengths.reserve(sprites.size());
	std::vector<sf::Vector2f> destinations;
	destinations.reserve(sprites.size());
	for (unsigned int ii = 0; ii < paths.size(); ++ii) {
		if (!paths[ii]->empty()) {
			destinations.push_back(paths[ii]->front());
		} else {
			destinations.push_back(sprites[ii]->getPosition());
			paths[ii]->push_back(sprites[ii]->getPosition());
		}
		maxStepLengths.push_back(msPassed*distPerMs[ii]);
	}

	// move the sprites
	bulkMoveSpriteStepTowardsPoint(sprites, destinations, maxStepLengths, orientSpritesToDestination);

	// if the sprite has reached destination, move on to next point in path
	for (unsigned int ii = 0; ii < sprites.size(); ii++) {
		sf::Sprite* sprite = sprites[ii];
		if (sprite->getPosition() == destinations[ii]){
			paths[ii]->pop_front();
		}
	}
}
