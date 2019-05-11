#pragma once

#include <GameBackbone/Util/DllUtil.h>

namespace GB {

	/// Any value above this weight is considered blocked
	const int BLOCKED_GRID_WEIGHT = 10000;

	/// <summary> Information stored in each navigation grid square. </summary>
	struct libGameBackbone NavigationGridData {
		int weight = 0;
		unsigned int blockerDist = 0;

		NavigationGridData() = default;
		NavigationGridData(int gridWeight, unsigned int gridBlockerDist) : weight(gridWeight), blockerDist(gridBlockerDist) {}
		virtual ~NavigationGridData() {}
	};

}
