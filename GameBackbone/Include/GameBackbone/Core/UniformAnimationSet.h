#pragma once

#include <GameBackbone/Core/AnimationSet.h>
#include <GameBackbone/Util/DllUtil.h>

#include <SFML/System/Vector2.hpp>

#include <vector>

namespace GB {

	/// @brief Collection of texture subsections as frame indices
	using UniformAnimation = std::vector<sf::Vector2i>;
	
	/// @brief Creates and owns a collection of animations that utilize a uniform frame size. 
	///		This size is used to calculate the bounds of each frame and create an appropriate Animation. 
	///		The frames are indexable like an (x, y) coordinate plane.
	class libGameBackbone UniformAnimationSet : public AnimationSet {
	public:
		
		/// @brief shared_ptr to UniformAnimationSet.
		using Ptr = std::shared_ptr<UniformAnimationSet>;

		UniformAnimationSet() = delete;

		/// @brief Construct a new UniformAnimationSet object.
		/// @param frameSize The default frame size for an animation.
		explicit UniformAnimationSet(sf::Vector2i frameSize);

		/// @brief Construct a new UniformAnimationSet object.
		///		The provided animations will all be added to the animation set.
		/// @param frameSize The default frame size for an animation.
		/// @param animations The animations to add. The UniformAnimation is a collection of sf::Vector2i pairs that act as (x, y) coordinates into the texture's frames.
		explicit UniformAnimationSet(sf::Vector2i frameSize, const std::vector<UniformAnimation>& animations);

		/// @brief Copy construct a UniformAnimationSet
		/// @param  The UniformAnimationSet to copy
		UniformAnimationSet(const UniformAnimationSet&) = default;

		/// @brief Move construct a UniformAnimationSet
		/// @param The UniformAnimationSet to move
		UniformAnimationSet(UniformAnimationSet&&) = default;

		/// @brief Copy assign a UniformAnimationSet
		/// @param  The UniformAnimationSet to copy
		/// @return This
		UniformAnimationSet& operator=(const UniformAnimationSet&) = default;

		/// @brief Move assign a UniformAnimationSet
		/// @param  The UniformAnimationSet to move
		/// @return This
		UniformAnimationSet& operator=(UniformAnimationSet&&) = default;

		/// @brief Destroy the UniformAnimationSet
		~UniformAnimationSet() override = default;

		/// @brief Adds the UniformAnimation to the UniformAnimationSet.
		///		The UniformAnimation is a collection of sf::Vector2i pairs that act as (x, y) coordinates into the texture's frames.
		/// @param animation The animation to add.
		void addAnimation(const UniformAnimation& animation);

		// Inherit all addAnimation member function from AnimationSet
		using AnimationSet::addAnimation;

		/// @brief Returns the default size of UniformAnimation frames
		sf::Vector2i getDefaultFrameSize() const;

	private:
		const sf::Vector2i defaultFrameSize;

	};
}