#pragma once
#include <Util\stdafx.h>

#include <Backbone\AnimatedSprite.h>
#include <Backbone\Updatable.h>
#include <Util\DllUtil.h>

#include <SFML/Graphics/Sprite.hpp>

#include <vector>

namespace GB {

	/// <summary> Controls several sprites and animated sprites as one logical unit. </summary>
	class libGameBackbone CompoundSprite : public virtual Updatable {
	public:

		//ctr / dtr
		//shallow copy and move are fine for this class
		CompoundSprite() = default;
		CompoundSprite(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites);
		CompoundSprite(const CompoundSprite& other) = default;
		CompoundSprite(CompoundSprite&& other) = default;
		CompoundSprite& operator= (const CompoundSprite& other) = default;
		CompoundSprite& operator= (CompoundSprite&& other) = default;
		virtual ~CompoundSprite();

		//getters
		std::vector<sf::Sprite*>* getSfSprites();
		std::vector<AnimatedSprite*>* getAnimatedSprites();

		//add / remove
		void addSprite(sf::Sprite* component);
		void addAnimatedSprite(AnimatedSprite* component);
		void removeSprite(sf::Sprite* component);
		void removeAnimatedSprite(AnimatedSprite* component);
		void clearComponents();

		//operations
		void scale(float factorX, float factorY);
		void move(float offsetX, float offsetY);
		virtual void update(sf::Time currentTime);

	protected:
		std::vector<sf::Sprite*> sprites;
		std::vector<AnimatedSprite*> animatedSprites;
	};

}
