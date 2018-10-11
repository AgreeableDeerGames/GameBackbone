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
	using AnimationVectorPtr = std::shared_ptr<AnimationVector>;

	using AnimationFrameIndex = std::vector<unsigned int>;
	using AnimationFrameIndexVector = std::vector<AnimationFrameIndex>;
	using AnimationFrameIndexVectorPtr = std::shared_ptr<const AnimationFrameIndexVector>;


    class libGameBackbone AnimationSet {
    public:

        // ctrs / dtr
        AnimationSet(AnimationFrameIndexVectorPtr animationFrames,
                     sf::Vector2u textureSize,
                     sf::Vector2u animationFrameDimensions);
        AnimationSet(AnimationFrameIndexVectorPtr animationFrames,
                     const sf::Texture& texture,
                     sf::Vector2u animationFrameDimensions);
        AnimationSet() = delete;
        AnimationSet(const AnimationSet& other) = default;
        AnimationSet(AnimationSet&& other) noexcept = default;
        AnimationSet& operator=(const AnimationSet& other) = default;
        AnimationSet& operator=(AnimationSet&& other) noexcept = default;
        virtual ~AnimationSet() = default;

        // operations
        AnimationVectorPtr getAnimations() const;
        void clearAnimations();

    protected:
        // internal operations
        void calculateAnimations(AnimationFrameIndexVectorPtr animationFrameIndices,
                                 sf::Vector2u textureSize,
                                 sf::Vector2u animationFrameDimensions);

        // internal storage
        AnimationVectorPtr animations;
    };


	///<summary>A groups of Animation frames used by animated sprites to determine animation loops</summary>
	class libGameBackbone DynamicAnimationSet : public AnimationSet {
	public:

		// ctrs / dtr
		explicit DynamicAnimationSet(sf::Vector2u animationFrameDimensions);

        DynamicAnimationSet(AnimationFrameIndexVectorPtr animationFrameIndices,
				     sf::Vector2u textureSize,
				     sf::Vector2u animationFrameDimensions);

        DynamicAnimationSet(AnimationFrameIndexVectorPtr animationFrameIndices,
					 const sf::Texture& texture,
					 sf::Vector2u animationFrameDimensions);

        DynamicAnimationSet();
        DynamicAnimationSet(const DynamicAnimationSet& other) = default;
        DynamicAnimationSet(DynamicAnimationSet&& other) noexcept = default;
        DynamicAnimationSet& operator= (const DynamicAnimationSet& other) = default;
        DynamicAnimationSet& operator= (DynamicAnimationSet&& other) noexcept = default;
		~DynamicAnimationSet() override = default;



		// setters
		void setAnimationFrameDimensions(sf::Vector2u dimensions);
		void setTextureSize(sf::Vector2u size);
		void setAnimationFrameIndices(AnimationFrameIndexVectorPtr animationFrames);

		// getters
		sf::Vector2u getAnimationFrameDimensions() const;
		sf::Vector2u getTextureSize() const;
		AnimationFrameIndexVectorPtr getAnimationFrameIndices() const;

	private:

		// internal storage
		sf::Vector2u textureSize;
		sf::Vector2u animationFrameDimensions;
		AnimationFrameIndexVectorPtr animationFrameIndices;
	};
}
