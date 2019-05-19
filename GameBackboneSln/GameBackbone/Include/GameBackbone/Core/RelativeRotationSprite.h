#pragma once

#include <GameBackbone/Core/CompoundSprite.h>

#include <GameBackbone/Core/AnimatedSprite.h>

#include <SFML/Graphics/Sprite.hpp>

#include <cstddef>
#include <vector>

namespace GB {

	/// <summary> Special type of CompoundSprite which controls rotation of each component Sprite for the user.
	/// It does so using either passed in or assumed relative position offsets for each Sprite compared to the CompoundSprite's position.</summary>
	class libGameBackbone RelativeRotationSprite : public CompoundSprite {
	public:

		//ctr / dtr
		using CompoundSprite::CompoundSprite; // inherit constructors

		RelativeRotationSprite(
			std::vector<sf::Sprite> components,
			const std::vector<sf::Vector2f>& relativeOffsets
		);

		RelativeRotationSprite(
			std::vector<sf::Sprite> components,
			const std::vector<sf::Vector2f>& relativeOffsets,
			sf::Vector2f initialPosition
		);

		RelativeRotationSprite(
			std::vector<sf::Sprite> components,
			std::vector<AnimatedSprite> animatedSprites,
			const std::vector<sf::Vector2f>& relativeOffsets
		);

		RelativeRotationSprite(
			std::vector<sf::Sprite> components,
			std::vector<AnimatedSprite> animatedSprites,
			const std::vector<sf::Vector2f>& relativeOffsets,
			sf::Vector2f initialPosition
		);

		virtual ~RelativeRotationSprite() = default;

		//add / remove
		virtual std::size_t addComponent(sf::Sprite component) override;
		virtual std::size_t addComponent(sf::Sprite component, sf::Vector2f relativeOffset);
		virtual std::size_t addComponent(AnimatedSprite component) override;
		virtual std::size_t addComponent(AnimatedSprite component, sf::Vector2f relativeOffset);

		//operations
		virtual void scale(float factorX, float factorY) override;
		virtual void scale(sf::Vector2f newScale) override;

	protected:

		void initializeComponentVector(
			std::vector<sf::Sprite> components,
			const std::vector<sf::Vector2f>& relativeOffsets
		);

		void initializeComponentVector(
			std::vector<sf::Sprite> components,
			std::vector<AnimatedSprite> animatedComponents,
			const std::vector<sf::Vector2f>& relativeOffsets
		);

	private:
		virtual void setScale(float factorX, float factorY) final;
		virtual void setScale(sf::Vector2f newScale) final;
	};

}
