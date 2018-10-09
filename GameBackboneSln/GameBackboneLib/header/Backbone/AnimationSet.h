#pragma once

#include <Util/DllUtil.h>

#include <memory>
#include <vector>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace GB {

	using Animation = std::vector<sf::IntRect>;
	using AnimationVector = std::vector<Animation>;
	using AnimationVectorPtr = std::shared_ptr<const AnimationVector>;

	using AnimationFrameIndex = std::vector<unsigned int>;
	using AnimationFrameIndexVector = std::vector<AnimationFrameIndex>;
	using AnimationFrameIndexVectorPtr = std::shared_ptr<const AnimationFrameIndexVector>;


	///<summary>A groups of Animation frames used by animated sprites to determine animation loops</summary>
	class libGameBackbone GenericAnimationSet {
	public:
		virtual ~GenericAnimationSet() = default;
		virtual AnimationVectorPtr getAnimations() = 0;
	};

	///<summary>A groups of Animation frames used by animated sprites to determine animation loops</summary>
	class libGameBackbone AnimationSet : public GenericAnimationSet {
	public:

		// ctrs / dtr
		explicit AnimationSet(sf::Vector2u animationFrameDimensions);

		AnimationSet(AnimationFrameIndexVectorPtr animationFrameIndices,
				     sf::Vector2u textureSize,
				     sf::Vector2u animationFrameDimensions);

		AnimationSet(AnimationFrameIndexVectorPtr animationFrameIndices,
					 const sf::Texture& texture,
					 sf::Vector2u animationFrameDimensions);

		AnimationSet() = default;
		AnimationSet(const AnimationSet& other) = default;
		AnimationSet(AnimationSet&& other) = default;
		AnimationSet& operator= (const AnimationSet& other) = default;
		AnimationSet& operator= (AnimationSet&& other) noexcept = default;
		~AnimationSet() override = default;

		// reset
		void clearAnimations();

		// setters
		void setAnimationFrameDimensions(sf::Vector2u dimensions);
		void setTextureSize(sf::Vector2u size);
		void setAnimationFrameIndices(AnimationFrameIndexVectorPtr animationFrames);

		// getters
		AnimationVectorPtr getAnimations() override;
		sf::Vector2u getTextureSize();
		sf::Vector2u getAnimationFrameDimensions();
		AnimationFrameIndexVectorPtr getAnimationFrameIndices();

	private:
		// internal operations
		void calculateAnimations();

		// internal storage
		sf::Vector2u textureSize;
		sf::Vector2u animationFrameDimensions;
		AnimationFrameIndexVectorPtr animationFrameIndices;
		AnimationVectorPtr animations;
	};

	// todo: AnimationSet should probably inherit from LightAnimationSet
	class libGameBackbone LightAnimationSet : public GenericAnimationSet{
	public:
		LightAnimationSet(sf::Vector2u animationFrameDimensions);
		LightAnimationSet(AnimationFrameIndexVectorPtr animationFrames,
		sf::Vector2u textureSize,
				sf::Vector2u animationFrameDimensions);
		AnimationVectorPtr getAnimations() override;

	private:
		AnimationVectorPtr animations;
	};

}
