#pragma once

#include <GameBackbone/Navigation/NavigationTools.h>
#include <GameBackbone/Util/DllUtil.h>

#include <SFML/Graphics.hpp>

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
		CoordinateConverter(float widthOfGridSquares, sf::Vector2f offsetOfOrigin);
		virtual ~CoordinateConverter() = default;

		sf::Vector2f convertCoordToWindow(const sf::Vector2i& navGridCoord) const;
		sf::Vector2i convertCoordToNavGrid(const sf::Vector2f& windowCoord) const;
		WindowCoordinatePath convertPathToWindow(const NavGridCoordinatePath& navGridPath) const;
		NavGridCoordinatePath convertPathToNavGrid(const WindowCoordinatePath& windowPath) const;


		void setGridSquareWidth(float newWidth);
		void setOriginOffset(const sf::Vector2f& newOffset);

	private:
		float gridSquareWidth;
		sf::Vector2f originOffset;

	};
}