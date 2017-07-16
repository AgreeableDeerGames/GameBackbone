#include <Navigation\CoordinateConverter.h>
#include <Util\Point.h>

#include <SFML\Graphics.hpp>

using namespace GB;

CoordinateConverter::CoordinateConverter() {
	gridSquareWidth = 50.f;
	originOffset.x = originOffset.y = 0;
}

CoordinateConverter::CoordinateConverter(float WidthOfGridSquares, Point2D<float> OffsetOfOrigin) {
	gridSquareWidth = WidthOfGridSquares;
	originOffset = OffsetOfOrigin;
}


sf::Vector2<float> CoordinateConverter::ConvertCoordToWindow(const Point2D<int>& NavGridCoord) {
	sf::Vector2<float> WindowCoordTopLeft = {NavGridCoord.x*gridSquareWidth, NavGridCoord.y*gridSquareWidth };

	sf::Vector2<float> WindowCoordCenter = {WindowCoordTopLeft.x + (gridSquareWidth /2), WindowCoordTopLeft.y + (gridSquareWidth / 2)};

	sf::Vector2<float> OffsetWindowCoord = {WindowCoordCenter.x + originOffset.x, WindowCoordCenter.y + originOffset.y};
	return OffsetWindowCoord;
}

Point2D<int> CoordinateConverter::ConvertCoordToNavGrid(const sf::Vector2<float>& WindowCoord) {
	sf::Vector2<float> WindowCoordCenter = {WindowCoord.x - originOffset.x, WindowCoord.y - originOffset.y};

	Point2D<int> NavGridCoord = {(int)(WindowCoordCenter.x/ gridSquareWidth), (int)(WindowCoordCenter.y/ gridSquareWidth)};
	return NavGridCoord;
}


void CoordinateConverter::setGridSquareWidth(float newWidth) {
	gridSquareWidth = newWidth;
}

void CoordinateConverter::setOriginOffset(const Point2D<float>& newOffset) {
	originOffset = newOffset;
}