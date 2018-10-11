#pragma once

#include <Util/DllUtil.h>

#include <memory>
#include <vector>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace GB {

    /// <summary> A series of frames that can be displayed from a single texture.</summary>
	using Animation = std::vector<sf::IntRect>;
	/// <summary> A vector of Animations </summary>
	using AnimationVector = std::vector<Animation>;
    /// <summary> A Pointer to a vector of Animations </summary>
    using AnimationVectorPtr = std::shared_ptr<AnimationVector>;

    /// <summary>
    /// A series of indices representing the frames that compose an animation.
    /// The indices correspond to a row major order grid laid on top of a sprite sheet, then flattened.
    /// The same indices can be used for multiple sprite sheets.
    /// </summary>
    using FrameIndexAnimation = std::vector<unsigned int>;
    /// <summary> A vector of FrameIndexAnimation </summary>
    using FrameIndexAnimationVector = std::vector<FrameIndexAnimation>;
    /// <summary> A Pointer to a vector of FrameIndexAnimation </summary>
    using FrameIndexAnimationVectorPtr = std::shared_ptr<FrameIndexAnimationVector>;


    class libGameBackbone AnimationSet {
    public:

        // ctrs / dtr
        AnimationSet(FrameIndexAnimationVectorPtr frameIndexAnimations,
                     sf::Vector2u textureSize,
                     sf::Vector2u animationFrameDimensions);
        AnimationSet(FrameIndexAnimationVectorPtr frameIndexAnimations,
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
        void calculateAnimations(FrameIndexAnimationVectorPtr frameIndexAnimations,
                                 sf::Vector2u textureSize,
                                 sf::Vector2u animationFrameDimensions);

        // internal storage
        AnimationVectorPtr animations = std::make_shared<AnimationVector>();
    };


	///<summary>A groups of Animation frames used by animated sprites to determine animation loops</summary>
	class libGameBackbone DynamicAnimationSet : public AnimationSet {
	public:

		// ctrs / dtr
		explicit DynamicAnimationSet(sf::Vector2u animationFrameDimensions);

        DynamicAnimationSet(FrameIndexAnimationVectorPtr frameIndexAnimations,
				     sf::Vector2u textureSize,
				     sf::Vector2u animationFrameDimensions);

        DynamicAnimationSet(FrameIndexAnimationVectorPtr frameIndexAnimations,
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
		void setFrameIndexAnimations(FrameIndexAnimationVectorPtr frameIindexAnimations);

		// getters
		sf::Vector2u getAnimationFrameDimensions() const;
		sf::Vector2u getTextureSize() const;
		const FrameIndexAnimationVectorPtr getFrameIndexAnimations() const;

	private:

		// internal storage
		sf::Vector2u textureSize;
		sf::Vector2u animationFrameDimensions;
		FrameIndexAnimationVectorPtr animationFrameIndices;
	};
}
