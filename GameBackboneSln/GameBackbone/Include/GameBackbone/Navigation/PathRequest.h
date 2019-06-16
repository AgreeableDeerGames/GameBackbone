#pragma once
#include<GameBackbone/Util/DllUtil.h>

#include <SFML/System/Vector2.hpp>

namespace GB {
	/// <summary> A request to calculate a path from the start coordinate to the end coordinate. </summary>
	struct libGameBackbone PathRequest {
		sf::Vector2i start;
		sf::Vector2i end;
	};

}
