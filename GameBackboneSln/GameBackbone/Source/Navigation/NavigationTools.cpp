#include <GameBackbone/Navigation/NavigationTools.h>
#include <GameBackbone/Util/UtilMath.h>

#include <SFML/Graphics/Sprite.hpp>

#include <math.h>
#include <memory>

using namespace GB;




/// <summary>
/// Frees all memory stored in the NavigationGrid
/// </summary>
/// <param name="navGrid">The NavigationGrid.</param>
void GB::freeAllNavigationGridData(NavigationGrid& navGrid) {
	for (unsigned int ii = 0; ii < navGrid.getArraySizeX(); ++ii) {
		for (unsigned int jj = 0; jj < navGrid.getArraySizeY(); ++jj)
		{
			delete navGrid[ii][jj];
		}
	}
}

