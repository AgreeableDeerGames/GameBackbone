#pragma once

#include <GameBackbone/Core/AnimationSet.h>
#include <GameBackbone/Util/DllUtil.h>

#include <SFML/System/Vector2.hpp>

#include <vector>

namespace GB {


	/// <summary>Collection of texture subsections as frame indices</summary>
	using UniformAnimation = std::vector<sf::Vector2i>;

	/// <summary> 
	/// Creates and owns a collection of animations that utilize a uniform frame size. 
	/// This size is used to calculate the bounds of each frame and create an appropriate Animation. 
	/// The frames are indexable like an (x, y) coordinate plane.
	/// </summary>
	class libGameBackbone UniformAnimationSet : public AnimationSet {
	public:
		// Pointer type
		/// <summary>shared_ptr to UniformAnimationSet.</summary>
		using Ptr = std::shared_ptr<UniformAnimationSet>;

		// ctrs / dtr
		UniformAnimationSet() = delete;
		explicit UniformAnimationSet(sf::Vector2i frameSize);
		explicit UniformAnimationSet(sf::Vector2i frameSize, const std::vector<UniformAnimation>& animations);
		UniformAnimationSet(const UniformAnimationSet&) = default;
		UniformAnimationSet(UniformAnimationSet&&) = default;
		UniformAnimationSet& operator=(const UniformAnimationSet&) = default;
		UniformAnimationSet& operator=(UniformAnimationSet&&) = default;
		virtual ~UniformAnimationSet() = default;

		// add / remove
		void addAnimation(const UniformAnimation& animation);
		using AnimationSet::addAnimation;

		// accessor / mutator
		sf::Vector2i getDefaultFrameSize() const;

	private:
		const sf::Vector2i defaultFrameSize;

	};
}