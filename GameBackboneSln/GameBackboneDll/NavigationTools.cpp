#include "stdafx.h"
#include "NavigationTools.h"

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
