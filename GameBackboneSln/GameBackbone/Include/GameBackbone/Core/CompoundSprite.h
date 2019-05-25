#pragma once

#include <GameBackbone/Core/AnimatedSprite.h>
#include <GameBackbone/Core/Updatable.h>
#include <GameBackbone/Util/DllUtil.h>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <cstddef>
#include <set>
#include <vector>

namespace GB {

	/// <summary> Controls several sprites and animated sprites as one logical unit. </summary>
	class libGameBackbone CompoundSprite : public Updatable, public sf::Drawable {
	public:
		//ctr / dtr
		CompoundSprite();
		explicit CompoundSprite(std::vector<sf::Sprite> components);
		CompoundSprite(std::vector<sf::Sprite> components, sf::Vector2f position);
		CompoundSprite(std::vector<sf::Sprite> drawableComponents, std::vector<AnimatedSprite> animatedComponents);
		CompoundSprite(std::vector<sf::Sprite> drawableComponents, std::vector<AnimatedSprite> animatedComponents, sf::Vector2f position);
		explicit CompoundSprite(sf::Vector2f initialPosition);
		CompoundSprite(const CompoundSprite&) = default;
		CompoundSprite& operator=(const CompoundSprite&) = default;
		CompoundSprite(CompoundSprite&&) noexcept = default;
		CompoundSprite& operator=(CompoundSprite&&) noexcept = default;
		virtual ~CompoundSprite() = default;

		//getters
		sf::Vector2f getPosition() const;
		virtual sf::Sprite& getSpriteComponent(std::size_t componentIndex);
		virtual AnimatedSprite& getAnimatedComponent(std::size_t componentIndex);
		virtual std::size_t getSpriteComponentCount() const;
		virtual std::size_t getAnimatedComponentCount() const;
		virtual bool isEmpty() const;

		//setters
		virtual void setPosition(sf::Vector2f val);
		virtual void setPosition(float x, float y);

		//add / remove
		virtual std::size_t addComponent(sf::Sprite component);
		virtual std::size_t addComponent(AnimatedSprite component);
		virtual void removeSpriteComponent(std::size_t componentIndex);
		virtual void removeAnimatedComponent(std::size_t componentIndex);
		virtual void clearComponents();

		//operations
		virtual void scale(float factorX, float factorY);
		virtual void scale(sf::Vector2f newScale);
		virtual void setScale(float factorX, float factorY);
		virtual void setScale(sf::Vector2f newScale);

		virtual void rotate(float degreeOffset);
		virtual void setRotation(float newRotation);

		virtual void move(float offsetX, float offsetY);
		virtual void move(sf::Vector2f offset);

		virtual void update(sf::Int64 elapsedTime) override;

	protected:
		
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		std::vector<sf::Sprite> components;
		std::vector<AnimatedSprite> animatedComponents;
		sf::Vector2f position;

	};
}
