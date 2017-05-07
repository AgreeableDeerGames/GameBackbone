#pragma once
#include "stdafx.h"
#include "DllUtil.h"

#include <vector>
#include <SFML/Graphics/Rect.hpp>

namespace GB {

	///<summary>A groups of Animation frames used by animated sprites to determine animation loops</summary>
	class libGameBackbone AnimationSet {
	public:
		AnimationSet(unsigned int rows, unsigned int cols);
		AnimationSet(const std::vector<std::vector<unsigned int>>& frameAnimations, unsigned int textureWidth, unsigned int textureHeight, unsigned int rows, unsigned int cols);
		virtual ~AnimationSet();

		void framesToRects(const std::vector<std::vector<unsigned int>>& frameAnimations, unsigned int textureWidth, unsigned int textureHeight);

		void clearAnimations();

		std::vector<std::vector<sf::IntRect>>* getAnimations();

	protected:
		unsigned int rows;
		unsigned int cols;
		std::vector<std::vector<sf::IntRect>>* animations;

	};

}
