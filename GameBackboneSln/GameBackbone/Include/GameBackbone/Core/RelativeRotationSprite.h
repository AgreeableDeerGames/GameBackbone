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
		RelativeRotationSprite() = default;
		explicit RelativeRotationSprite(std::vector<sf::Sprite> components);
		RelativeRotationSprite(std::vector<sf::Sprite> components, sf::Vector2f position);
		RelativeRotationSprite(std::vector<sf::Sprite> components, std::vector<AnimatedSprite> animatedComponents);
		RelativeRotationSprite(std::vector<sf::Sprite> components, std::vector<AnimatedSprite> animatedComponents, sf::Vector2f position);
		explicit RelativeRotationSprite(sf::Vector2f position);
		RelativeRotationSprite(std::vector<sf::Sprite> components, const std::vector<sf::Vector2f>& relativeOffsets);
		RelativeRotationSprite(std::vector<sf::Sprite> components, const std::vector<sf::Vector2f>& relativeOffsets, sf::Vector2f position);
		RelativeRotationSprite(std::vector<sf::Sprite> components, std::vector<AnimatedSprite> animatedComponents, const std::vector<sf::Vector2f>& relativeOffsets);
		RelativeRotationSprite(std::vector<sf::Sprite> components, std::vector<AnimatedSprite> animatedComponents, const std::vector<sf::Vector2f>& relativeOffsets, sf::Vector2f position);

		RelativeRotationSprite(const RelativeRotationSprite&) = default;
		RelativeRotationSprite& operator=(const RelativeRotationSprite&) = default;
		RelativeRotationSprite(RelativeRotationSprite&&) noexcept = default;
		RelativeRotationSprite& operator=(RelativeRotationSprite&&) noexcept = default;
		virtual ~RelativeRotationSprite() = default;

		//add / remove
		virtual std::size_t addComponent(sf::Sprite component) override;
		virtual std::size_t addComponent(sf::Sprite component, sf::Vector2f relativeOffset);
		virtual std::size_t addComponent(AnimatedSprite component) override;
		virtual std::size_t addComponent(AnimatedSprite component, sf::Vector2f relativeOffset);

		//operations
		virtual void scale(float factorX, float factorY) override;
		virtual void scale(sf::Vector2f newScale) override;
		virtual void setScale(float newScaleX, float newScaleY) override;
		virtual void setScale(sf::Vector2f newScale) override;
		virtual sf::Vector2f getScale() const;

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
		sf::Vector2f m_currentScale;
	};

}
