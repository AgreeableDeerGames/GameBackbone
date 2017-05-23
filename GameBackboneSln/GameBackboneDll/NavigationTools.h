#pragma once
#include "stdafx.h"
#include "DllUtil.h"
#include "Array2D.h"
#include "NavigationGridData.h"

#include<tuple>



namespace GB {
	libGameBackbone typedef GB::Array2D<GB::NavigationGridData*> NavigationGrid;
	libGameBackbone typedef std::pair<int, int> IntPair;


	libGameBackbone extern void initAllNavigationGridValues(NavigationGrid & navGrid, NavigationGridData & gridData);
	libGameBackbone extern void freeAllNavigationGridData(NavigationGrid & navGrid);
}