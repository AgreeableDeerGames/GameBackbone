#pragma once
#include <Backbone\CompoundSprite.h>

#include <vector>

namespace GB {

	/// <summary> Controls several sprites and animated sprites as one logical unit. </summary>
	class libGameBackbone RelativeRotationSprite : public CompoundSprite {
	public:

		//ctr / dtr
		//shallow copy and move are fine for this class
		RelativeRotationSprite();
		explicit RelativeRotationSprite(const std::vector<sf::Sprite*>& components);
		RelativeRotationSprite(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites);
		RelativeRotationSprite(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites, const sf::Vector2f& initialPosition);
		explicit RelativeRotationSprite(const sf::Vector2f& initialPosition);
		RelativeRotationSprite(const RelativeRotationSprite& other) = default;
		RelativeRotationSprite(RelativeRotationSprite&& other) = default;
		RelativeRotationSprite& operator= (const RelativeRotationSprite& other) = default;
		RelativeRotationSprite& operator= (RelativeRotationSprite&& other) = default;
		virtual ~RelativeRotationSprite();

		//add / remove
		virtual void addComponent(sf::Sprite* component) override;
		virtual void addComponent(sf::Sprite* component, sf::Vector2f relativeOffset);
		virtual void addComponent(AnimatedSprite* component) override;
		virtual void addComponent(AnimatedSprite* component, sf::Vector2f relativeOffset);

		//operations
		virtual void scale(float factorX, float factorY) override;
		virtual void scale(sf::Vector2f newScale) override;

		virtual void move(float offsetX, float offsetY);
		virtual void move(sf::Vector2f offset);
		virtual void setPosition(sf::Vector2f val);
		virtual void setPosition(float x, float y);

	protected:

	private:
		virtual void setScale(float factorX, float factorY) final;
		virtual void setScale(sf::Vector2f newScale) final;
	};

}
