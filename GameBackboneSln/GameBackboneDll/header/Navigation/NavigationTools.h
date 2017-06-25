#pragma once
#include <Util\stdafx.h>

#include <Util\DllUtil.h>
#include <Util\Array2D.h>
#include <Navigation\NavigationGridData.h>



namespace GB {
	libGameBackbone typedef Array2D<NavigationGridData*> NavigationGrid;
	libGameBackbone typedef std::pair<int, int> IntPair;


	libGameBackbone extern void initAllNavigationGridValues(NavigationGrid & navGrid, NavigationGridData & gridData);
	libGameBackbone extern void freeAllNavigationGridData(NavigationGrid & navGrid);
}