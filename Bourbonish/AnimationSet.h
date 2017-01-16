#pragma once
#include <vector>
#include <SFML/Graphics/Rect.hpp>

class AnimationSet {
public:
	AnimationSet(unsigned int rows, unsigned int cols);
	AnimationSet(std::vector<std::vector<unsigned int>> frameAnimations, unsigned int textureWidth, unsigned int textureHeight, unsigned int rows, unsigned int cols);
	virtual ~AnimationSet();

	void framesToRects(std::vector<std::vector<unsigned int>> frameAnimations, unsigned int textureWidth, unsigned int textureHeight);

	void clearAnimations();

	std::vector<std::vector<sf::IntRect>>* getAnimations();

protected:
	unsigned int rows;
	unsigned int cols;
	std::vector<std::vector<sf::IntRect>> animations;

};

