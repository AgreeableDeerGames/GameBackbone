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


    /// <summary> Creates and owns a set of animations comprised of several frames. </summary>
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
}
