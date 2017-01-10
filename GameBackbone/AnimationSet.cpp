#include "AnimationSet.h"



AnimationSet::AnimationSet(unsigned int rows, unsigned int cols) {
}

AnimationSet::AnimationSet(std::vector<std::vector<unsigned int>> frameAnimations, unsigned int textureWidth, unsigned int textureHeight, unsigned int rows, unsigned int cols) {
	this->rows = rows;
	this->cols = cols;
	framesToRects(frameAnimations, textureWidth, textureHeight);
}

AnimationSet::~AnimationSet() {
}

/**
<summary>Converts a full set of animations in the frame number format to the textureRect format</summary>
*/
void AnimationSet::framesToRects(std::vector<std::vector<unsigned int>> frameAnimations, unsigned int textureWidth, unsigned int textureHeight) {

	//find the dimensions of the rectangles
	unsigned int rectWidth = textureWidth / cols;
	unsigned int rectHeight = textureHeight / rows;

	//find the rectangle for each frame number in each animation
	for each (std::vector<unsigned int> frameAnimation in frameAnimations) {
		std::vector<sf::IntRect> rectAnimation;
		for each (unsigned int frameNumber in frameAnimation) {
			unsigned int newRectY = (frameNumber / cols) * rectHeight;
			unsigned int newRectX = (frameNumber % cols) * rectWidth;
			sf::IntRect frameRect(newRectX, newRectY, rectWidth, rectHeight);
			rectAnimation.push_back(frameRect);
		}
		animations.push_back(rectAnimation);
	}
}

///<summary>clears all animations</summary>
void AnimationSet::clearAnimations() {
	animations.clear();
}

///<summary> returns a const pointer to the vector of animations</summary>
std::vector<std::vector<sf::IntRect>>* AnimationSet::getAnimations() {
	return &animations;
}

