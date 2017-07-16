#include <Navigation\CoordinateConverter.h>
#include <Util\Point.h>

#include <SFML\Graphics.hpp>

using namespace GB;

CoordinateConverter::CoordinateConverter() {
	GridSquareWidth = 50.f;
	OriginOffset.x = OriginOffset.y = 0;
}

CoordinateConverter::CoordinateConverter(float WidthOfGridSquares, Point2D<float> OffsetOfOrigin) {
	GridSquareWidth = WidthOfGridSquares;
	OriginOffset = OffsetOfOrigin;
}


sf::Vector2<float> CoordinateConverter::ConvertCoordToWindow(Point2D<int> NavGridCoord) {
	sf::Vector2<float> WindowCoordTopLeft = {NavGridCoord.x*GridSquareWidth, NavGridCoord.y*GridSquareWidth};

	sf::Vector2<float> WindowCoordCenter = {WindowCoordTopLeft.x + (GridSquareWidth/2), WindowCoordTopLeft.y + (GridSquareWidth / 2)};

	sf::Vector2<float> OffsetWindowCoord = { WindowCoordCenter.x + OriginOffset.x, WindowCoordCenter.y + OriginOffset.y};
	return OffsetWindowCoord;
}

Point2D<int> CoordinateConverter::ConvertCoordToNavGrid(sf::Vector2<float> WindowCoord) {
	sf::Vector2<float> WindowCoordCenter = {WindowCoord.x - OriginOffset.x, WindowCoord.y - OriginOffset.y};

	Point2D<int> NavGridCoord = { WindowCoordCenter.x/GridSquareWidth, WindowCoordCenter.y/GridSquareWidth};
	return NavGridCoord;
}