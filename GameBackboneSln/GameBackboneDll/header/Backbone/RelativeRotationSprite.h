#pragma once
#include <Backbone\CompoundSprite.h>

#include <vector>

namespace GB {

	/// <summary> Special type of CompoundSprite which controls rotation of each component Sprite for the user. 
	/// It does so using either passed in or assumed relative position offsets for each Sprite compared to the CompoundSprite's position.</summary>
	class libGameBackbone RelativeRotationSprite : public CompoundSprite {
	public:

		//ctr / dtr
		//shallow copy and move are fine for this class
		RelativeRotationSprite();
		explicit RelativeRotationSprite(const std::vector<sf::Sprite*>& components);
		explicit RelativeRotationSprite(const sf::Vector2f& initialPosition);
		RelativeRotationSprite(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites);
		RelativeRotationSprite(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites, const sf::Vector2f& initialPosition);
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

	protected:

	private:
		virtual void setScale(float factorX, float factorY) final;
		virtual void setScale(sf::Vector2f newScale) final;
	};

}
