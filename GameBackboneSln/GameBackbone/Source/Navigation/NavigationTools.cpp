#include <GameBackbone/Navigation/NavigationTools.h>

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

