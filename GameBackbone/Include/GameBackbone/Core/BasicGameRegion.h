#pragma once

#include <GameBackbone/Core/Updatable.h>
#include <GameBackbone/Util/DllUtil.h>
#include <GameBackbone/UserInput/InputHandler.h>

#include <SFML/Graphics/Drawable.hpp>

#include <functional>
#include <memory>

namespace GB {
	
	/// @brief Abstract class providing an interface to control game logic and actors for a specific time or space in game.
	class libGameBackbone BasicGameRegion : public sf::Drawable, public Updatable, public InputHandler{
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
		/// @return A reference to this instance
		BasicGameRegion& operator=(const BasicGameRegion&) = default;

		/// @brief Move Construct a BasicGameRegion
		/// @param The BasicGameRegion to move
		/// @return A reference to this instance
		BasicGameRegion(BasicGameRegion&&) noexcept = default;

		/// @brief Move assign a basicGameRegion
		/// @param The BasicGameRegion to move
		/// @return A reference to this
		BasicGameRegion& operator=(BasicGameRegion&&) noexcept = default;

		/// @brief Destroy this BasicGameRegion
		virtual ~BasicGameRegion() = default;

		/// @brief Gets the game region that should become active after the next update of this one.
		///		Defaults to this instance.
		BasicGameRegion& getNextRegion();

		/// @brief The region that should become active after the next update of this one.
		const BasicGameRegion& getNextRegion() const;

		/// @brief Sets the BasicGameRegion that should become active after the next update of this one.
		/// @param nextRegion The region that should become active.
		void setNextRegion(BasicGameRegion& nextRegion);

	private:
		std::reference_wrapper<BasicGameRegion> m_nextRegion;
	};
}
