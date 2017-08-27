#pragma once

#include <Util/DllUtil.h>

#define BLOCKED_GRID_WEIGHT 10000

namespace GB {

	/// <summary> Information stored in each navigation grid square. </summary>
	struct libGameBackbone NavigationGridData {
		int weight;
		unsigned int blockerDist;

		NavigationGridData() = default;
		NavigationGridData(int gridWeight, unsigned int gridBlockerDist) : weight(gridWeight), blockerDist(gridBlockerDist) {}
		virtual ~NavigationGridData() {}
	};

}
