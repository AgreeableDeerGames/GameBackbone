#pragma once

#include <Util\DllUtil.h>
#include <Util\Point.h>

#include <SFML\Graphics.hpp>

namespace GB {

	/// <summary> used to calculate groups of paths in one navigation grid. </summary>
	class libGameBackbone CoordinateConverter {
	public:
		// ctr / dtr
		CoordinateConverter();
		CoordinateConverter(const CoordinateConverter& other) = delete;
		CoordinateConverter(CoordinateConverter&& other) = delete;
		CoordinateConverter& operator= (const CoordinateConverter& other) = delete;
		CoordinateConverter& operator= (CoordinateConverter&& other) = delete;
		CoordinateConverter(float WidthOfGridSquares, Point2D<float> OffsetOfOrigin);
		virtual ~CoordinateConverter() = default;

		sf::Vector2<float> ConvertCoordToWindow(Point2D<int> NavGridCoord);
		Point2D<int> ConvertCoordToNavGrid(sf::Vector2<float> WindowCoord);

	private:
		float GridSquareWidth;
		Point2D<float> OriginOffset;

	};
}