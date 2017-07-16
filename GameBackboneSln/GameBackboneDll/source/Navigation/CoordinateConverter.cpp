#include <Navigation\CoordinateConverter.h>
#include <Util\Point.h>

#include <SFML\Graphics.hpp>

using namespace GB;

/// <summary>
/// Initializes a new instance of the <see cref="CoordinateConverter"/> class.
/// Default values of 50 and (0, 0) for gridSquareWidth and originOffset respectively.
/// </summary>
CoordinateConverter::CoordinateConverter() {
	gridSquareWidth = 50.f;
	originOffset.x = originOffset.y = 0;
}

/// <summary>
/// Initializes a new instance of the <see cref="CoordinateConverter"/> class.
/// </summary>
/// <param name="WidthOfGridSquares">The width of grid squares.</param>
/// <param name="OffsetOfOrigin">The offset of origin.</param>
CoordinateConverter::CoordinateConverter(float WidthOfGridSquares, Point2D<float> OffsetOfOrigin) {
	gridSquareWidth = WidthOfGridSquares;
	originOffset = OffsetOfOrigin;
}

/// <summary>
/// Converts the coordinate to an sf window coordinate.
/// This function returns the center of the sf Grid Square
/// </summary>
/// <param name="NavGridCoord">The navigation grid coordinate.</param>
/// <returns></returns>
sf::Vector2<float> CoordinateConverter::ConvertCoordToWindow(const Point2D<int>& NavGridCoord) {
	sf::Vector2<float> WindowCoordTopLeft = {NavGridCoord.x*gridSquareWidth, NavGridCoord.y*gridSquareWidth };

	sf::Vector2<float> WindowCoordCenter = {WindowCoordTopLeft.x + (gridSquareWidth /2), WindowCoordTopLeft.y + (gridSquareWidth / 2)};

	sf::Vector2<float> OffsetWindowCoord = {WindowCoordCenter.x + originOffset.x, WindowCoordCenter.y + originOffset.y};
	return OffsetWindowCoord;
}

/// <summary>
/// Converts the coordinate to a navigation grid coordinate.
/// The value of right/bottom edge is not contained by the grid square square 
/// ei: [0, gridSquareWidth)
/// ei: gridSquareWidth = 50; WindowCoord(49.999, 50) -> NavGridCoord(0, 1)
/// </summary>
/// <param name="WindowCoord">The sf window coordinate.</param>
/// <returns></returns>
Point2D<int> CoordinateConverter::ConvertCoordToNavGrid(const sf::Vector2<float>& WindowCoord) {
	sf::Vector2<float> WindowCoordCenter = {WindowCoord.x - originOffset.x, WindowCoord.y - originOffset.y};

	Point2D<int> NavGridCoord = {(int)(WindowCoordCenter.x/ gridSquareWidth), (int)(WindowCoordCenter.y/ gridSquareWidth)};
	return NavGridCoord;
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
void CoordinateConverter::setOriginOffset(const Point2D<float>& newOffset) {
	originOffset = newOffset;
}