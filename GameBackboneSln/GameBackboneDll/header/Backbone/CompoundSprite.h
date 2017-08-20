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
		explicit CompoundSprite(const std::vector<sf::Sprite*>& components);
		CompoundSprite(const std::vector<sf::Sprite*>& components, const sf::Vector2f& position);
		CompoundSprite(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites);
		CompoundSprite(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites, const sf::Vector2f& position);
		explicit CompoundSprite(const sf::Vector2f initialPosition);
		CompoundSprite(const CompoundSprite& other) = default;
		CompoundSprite(CompoundSprite&& other) = default;
		CompoundSprite& operator= (const CompoundSprite& other) = default;
		CompoundSprite& operator= (CompoundSprite&& other) = default;
		virtual ~CompoundSprite();

		//getters
		std::vector<sf::Sprite*>* getSprites();
		std::vector<AnimatedSprite*>* getAnimatedSprites();
		sf::Vector2f getPosition() const;
		
		//setters
		void setPosition(sf::Vector2f val);
		void setPosition(float x, float y);

		//add / remove
		void addComponent(sf::Sprite* component);
		void addComponent(AnimatedSprite* component);
		void removeSprite(sf::Sprite* component);
		void clearComponents();

		//operations
		void scale(float factorX, float factorY);
		void scale(sf::Vector2f newScale);
		virtual void setScale(float factorX, float factorY);
		virtual void setScale(sf::Vector2f newScale);

		void rotate(float degreeOffset);
		void setRotation(float newRotation);

		void rotateSprites(std::set<size_t> indicesToRotate, float degreeOffset);
		void setRotationOfSprites(std::set<size_t> indicesToRotate, float newRotation);

		void move(float offsetX, float offsetY);
		void move(sf::Vector2f offset);

		virtual void update(sf::Time currentTime);

	protected:
		void removeAnimatedSprite(AnimatedSprite* component);
		std::vector<sf::Sprite*> components;
		std::vector<AnimatedSprite*> animatedSprites;
		sf::Vector2f position;

	};

}
