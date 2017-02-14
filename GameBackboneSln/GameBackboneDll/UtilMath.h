#pragma once
#include "stdafx.h"
#include "DllUtil.h"
#include<SFML/System/Vector3.hpp>

#include<math.h>

//vector operations

libGameBackbone unsigned int Dist3d(const sf::Vector3i & point1, const sf::Vector3i & point2);

libGameBackbone unsigned int SquaredDist3d(const sf::Vector3i & point1, const sf::Vector3i & point2);