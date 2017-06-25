#pragma once
#include "stdafx.h"
#include "DllUtil.h"
#include "Array2D.h"
#include "NavigationGridData.h"



namespace GB {
	libGameBackbone typedef Array2D<NavigationGridData*> NavigationGrid;


	libGameBackbone extern void initAllNavigationGridValues(NavigationGrid & navGrid, NavigationGridData & gridData);
	libGameBackbone extern void freeAllNavigationGridData(NavigationGrid & navGrid);
}