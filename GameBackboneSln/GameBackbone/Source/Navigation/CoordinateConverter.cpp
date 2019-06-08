#include <GameBackbone/Navigation/CoordinateConverter.h>

#include <SFML/Graphics.hpp>

using namespace GB;

/// <summary>
/// Initializes a new instance of the <see cref="CoordinateConverter"/> class.
/// Default values of 50 and (0, 0) for gridSquareWidth and originOffset respectively.
/// </summary>
CoordinateConverter::CoordinateConverter() {
	gridSquareWidth = 50.f;
	originOffset.x = 0;
	originOffset.y = 0;
}

/// <summary>
/// Initializes a new instance of the <see cref="CoordinateConverter"/> class.
/// </summary>
/// <param name="WidthOfGridSquares">The width of grid squares.</param>
/// <param name="OffsetOfOrigin">The offset of origin.</param>
CoordinateConverter::CoordinateConverter(float widthOfGridSquares, sf::Vector2f offsetOfOrigin) : originOffset(offsetOfOrigin) {
	gridSquareWidth = widthOfGridSquares;
}

/// <summary>
/// Converts the coordinate to an sf window coordinate.
/// This function returns the center of the Grid Square
/// </summary>
/// <param name="NavGridCoord">The navigation grid coordinate.</param>
/// <returns></returns>
sf::Vector2f CoordinateConverter::convertCoordToWindow(const sf::Vector2i& navGridCoord) const {
	sf::Vector2f windowCoordTopLeft = { navGridCoord.x*gridSquareWidth, navGridCoord.y*gridSquareWidth };

	sf::Vector2f windowCoordCenter = { windowCoordTopLeft.x + (gridSquareWidth /2), windowCoordTopLeft.y + (gridSquareWidth / 2)};

	sf::Vector2f offsetWindowCoord = { windowCoordCenter.x + originOffset.x, windowCoordCenter.y + originOffset.y};
	return offsetWindowCoord;
}

/// <summary>
/// Converts the coordinate to a navigation grid coordinate.
/// The value of right/bottom edge is not contained by the grid square square
/// ei: [0, gridSquareWidth)
/// ei: gridSquareWidth = 50; WindowCoord(49.999, 50) -> NavGridCoord(0, 1)
/// </summary>
/// <param name="WindowCoord">The sf window coordinate.</param>
/// <returns></returns>
sf::Vector2i CoordinateConverter::convertCoordToNavGrid(const sf::Vector2f& windowCoord) const {
	sf::Vector2f windowCoordCenter = { windowCoord.x - originOffset.x, windowCoord.y - originOffset.y};

	sf::Vector2i navGridCoord = {(int)(windowCoordCenter.x/ gridSquareWidth), (int)(windowCoordCenter.y/ gridSquareWidth)};
	return navGridCoord;
}

/// <summary>
/// Converts a path represented in navigation grid coordinates to an equivalent
/// path in window coordinates.
/// </summary>
/// <param name="navGridPath">The nav grid path.</param>
/// <returns></returns>
WindowCoordinatePath CoordinateConverter::convertPathToWindow(const NavGridCoordinatePath & navGridPath) const {

	// convert each coordinate and store it
	WindowCoordinatePath convertedPath;
	for (sf::Vector2i coordinate : navGridPath) {
		convertedPath.push_back(convertCoordToWindow(coordinate));
	}
	return convertedPath;
}

/// <summary>
/// Converts a path represented in window coordinates to an equivalent
/// path in navigation grid coordinates.
/// </summary>
/// <param name="windowPath">The window path.</param>
/// <returns></returns>
NavGridCoordinatePath CoordinateConverter::convertPathToNavGrid(const WindowCoordinatePath & windowPath) const
{
	// convert each coordinate and store it
	NavGridCoordinatePath convertedPath;
	for (sf::Vector2f coordinate : windowPath) {
		convertedPath.push_back(convertCoordToNavGrid(coordinate));
	}
	return convertedPath;
}

/// <summary>
/// Sets the width of the grid square.
/// </summary>
/// <param name="newWidth">The new width.</param>
void CoordinateConverter::setGridSquareWidth(float newWidth) {
	gridSquareWidth = newWidth;
}

/// <summary>
/// Sets the origin offset.
/// </summary>
/// <param name="newOffset">The new offset.</param>
void CoordinateConverter::setOriginOffset(const sf::Vector2f& newOffset) {
	originOffset = newOffset;
}