#pragma once
#include "stdafx.h"
#include "DllUtil.h"
#include<SFML/System/Vector3.hpp>

#include<math.h>

namespace GB {

	//vector operations

	libGameBackbone unsigned int Dist3d(const sf::Vector3i & point1, const sf::Vector3i & point2);

	libGameBackbone unsigned int SquaredDist3d(const sf::Vector3i & point1, const sf::Vector3i & point2);

	libGameBackbone unsigned int SquaredDist2d(const std::pair<int, int> & point1, const std::pair<int, int> & point2);

	libGameBackbone unsigned int Dist2d(const std::pair<int, int> & point1, const std::pair<int, int> & point2);

}
