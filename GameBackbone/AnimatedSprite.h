#pragma once

#include "../../SFML/SFML-2.4.1/include/SFML/Graphics/Sprite.hpp"
#include "updatable.h"

#include <vector>


class AnimatedSprite :
	public sf::Sprite, public Updatable {
public:
	//ctr and dtr
	AnimatedSprite();
	AnimatedSprite(const sf::Texture &texture);
	AnimatedSprite(const sf::Texture &texture, unsigned int rows, unsigned int cols, unsigned int totalFrames);
	virtual ~AnimatedSprite();

	//getters and setters
		//setters
	void setRows(unsigned int rows);
	void setCols(unsigned int cols);
	void setTotalFrames(unsigned int totalFrames);
	void setAnimating(bool animating);
	void setCurrentFrame(unsigned int frame);
		//getters
	unsigned int getRows();
	unsigned int getCols();
	unsigned int getTotalFrames();
	unsigned int getCurrentFrame();
	unsigned int getCurrentAnimationId();
	bool isAnimating();
	
	//operations
	void addAnimation(std::vector<unsigned int> animation);
	void clearAnimations();
	void changeAnimationFrames(unsigned int animationId, std::vector<unsigned int> animation);
	void runAnimation(unsigned int animationId);
	virtual void update();


protected:
	unsigned int rows;
	unsigned int cols;
	unsigned int totalFrames;
	std::vector<std::vector<unsigned int>> animations;
	bool animating;
	unsigned int currentFrame;
	unsigned int currentAnimationId;
	std::vector<unsigned int>* currentAnimation;

private:
	void init(unsigned int rows, unsigned int cols, unsigned int totalFrames);

};

