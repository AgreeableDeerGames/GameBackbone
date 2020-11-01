#pragma once

#include <GameBackbone/Core/Updatable.h>
#include <GameBackbone/Util/DllUtil.h>

#include <SFML/Graphics/Drawable.hpp>

#include <functional>
#include <memory>

namespace GB {
	
	/// @brief Base class meant to be inherited. Controls game logic and actors for a specific time or space in game.
	class libGameBackbone BasicGameRegion : public sf::Drawable, public Updatable {
	public:
		
		/// @brief shared_ptr to BasicGameRegion
		using Ptr = std::shared_ptr<BasicGameRegion>;

		/// @brief Initializes a new instance of the BasicGameRegionclass.
		BasicGameRegion();

		/// @brief Copy construct a BasicGameRegion
		/// @param  The BasicGameRegion to copy
		BasicGameRegion(const BasicGameRegion&) = default;

		/// @brief Copy assign a BasicGameRegion
		/// @param  The BasicGameRegion to copy
		/// @return This
		BasicGameRegion& operator=(const BasicGameRegion&) = default;

		/// @brief Move Construct a BasicGameRegion
		/// @param The BasicGameRegion to move
		/// @return This
		BasicGameRegion(BasicGameRegion&&) noexcept = default;

		/// @brief Move assign a basicGameRegion
		/// @param The BasicGameRegion to move
		/// @return this
		BasicGameRegion& operator=(BasicGameRegion&&) noexcept = default;

		/// @brief Destroy this BasicGameRegion
		virtual ~BasicGameRegion() = default;

		/// @brief Gets the game region that should become active after the next update of this one.
		BasicGameRegion& getNextRegion();

		/// @brief The region that should become active after the next update of this one.
		const BasicGameRegion& getNextRegion() const;

		/// @brief Sets the BasicGameRegion that should become active after the next update of this one.
		/// @param nextRegion The region that should become active.
		void setNextRegion(BasicGameRegion& nextRegion);

		/// @brief Implements Updatable::update as a no-op.
		void update(sf::Int64 /*elapsedTime*/) override {}

	private:
		std::reference_wrapper<BasicGameRegion> m_nextRegion;
	};
}
