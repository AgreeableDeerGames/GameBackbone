#pragma once

#include <Util\DllUtil.h>
#include <Util\Point.h>

#include <SFML\Graphics.hpp>

namespace GB {
	
	/// <summary>
	/// Converts coordinates between sf window and navigation grid.
	/// </summary>
	class libGameBackbone CoordinateConverter {
	public:
		// ctr / dtr
		CoordinateConverter();
		CoordinateConverter(const CoordinateConverter& other) = default;
		CoordinateConverter(CoordinateConverter&& other) = default;
		CoordinateConverter& operator= (const CoordinateConverter& other) = default;
		CoordinateConverter& operator= (CoordinateConverter&& other) = default;
		CoordinateConverter(float WidthOfGridSquares, Point2D<float> OffsetOfOrigin);
		virtual ~CoordinateConverter() = default;

		sf::Vector2<float> ConvertCoordToWindow(const Point2D<int>& NavGridCoord);
		Point2D<int> ConvertCoordToNavGrid(const sf::Vector2<float>& WindowCoord);

		void setGridSquareWidth(float newWidth);
		void setOriginOffset(const Point2D<float>& newOffset);

	private:
		float gridSquareWidth;
		Point2D<float> originOffset;

	};
}