#pragma once

#include <Backbone\AnimatedSprite.h>
#include <Backbone\Updatable.h>
#include <Util\DllUtil.h>
#include <Util\Point.h>

#include <SFML\Graphics\Sprite.hpp>

#include <set>
#include <vector>

namespace GB {

	/// <summary> Controls several sprites and animated sprites as one logical unit. </summary>
	class libGameBackbone CompoundSprite : public virtual Updatable {
	public:

		//ctr / dtr
		//shallow copy and move are fine for this class
		CompoundSprite();
		CompoundSprite(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites);
		CompoundSprite(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites, Point2D<float> position);
		CompoundSprite(const Point2D<float> initialPosition);
		CompoundSprite(const CompoundSprite& other) = default;
		CompoundSprite(CompoundSprite&& other) = default;
		CompoundSprite& operator= (const CompoundSprite& other) = default;
		CompoundSprite& operator= (CompoundSprite&& other) = default;
		virtual ~CompoundSprite();

		//getters
		std::vector<sf::Sprite*>* getSfSprites();
		std::vector<AnimatedSprite*>* getAnimatedSprites();
		Point2D<float> getPosition() const;
		
		//setters
		void setPosition(Point2D<float> val);
		void setPosition(float x, float y);

		//add / remove
		virtual void addSprite(sf::Sprite* component);
		virtual void addAnimatedSprite(AnimatedSprite* component);
		void removeSprite(sf::Sprite* component);
		void removeAnimatedSprite(AnimatedSprite* component);
		void clearComponents();

		//operations
		virtual void scale(float factorX, float factorY);
		virtual void scale(Point2D<float> newScale);
		virtual void setScale(float factorX, float factorY);
		virtual void setScale(Point2D<float> newScale);

		virtual void rotate(float degreeOffset);
		virtual void setRotation(float newRotation);

		virtual void rotateAnimatedSprites(std::set<size_t> indiciesToRotate, float degreeOffset);
		virtual void setRotationAnimatedSprites(std::set<size_t> indicesToRotate, float newRotation);

		virtual void rotateSfSprites(std::set<size_t> indicesToRotate, float degreeOffset);
		virtual void setRotationSfSprites(std::set<size_t> indicesToRotate, float newRotation);

		void move(float offsetX, float offsetY);
		void move(Point2D<float> offset);

		virtual void update(sf::Time currentTime);

	protected:
		std::vector<sf::Sprite*> sprites;
		std::vector<AnimatedSprite*> animatedSprites;
		Point2D<float> position;
	};

}
