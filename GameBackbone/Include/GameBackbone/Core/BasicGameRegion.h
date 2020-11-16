#pragma once

#include <GameBackbone/Core/Updatable.h>
#include <GameBackbone/Util/DllUtil.h>
#include <GameBackbone/UserInput/InputHandler.h>

#include <SFML/Graphics/Drawable.hpp>

#include <functional>
#include <memory>

namespace GB {
	/// <summary> Base class meant to be inherited. Controls game logic and actors for a specific time or space in game. </summary>
	class libGameBackbone BasicGameRegion : public sf::Drawable, public Updatable, public InputHandler{
	public:
		/// <summary>shared_ptr to BasicGameRegion</summary>
		using Ptr = std::shared_ptr<BasicGameRegion>;

		BasicGameRegion();
		BasicGameRegion(const BasicGameRegion&) = default;
		BasicGameRegion& operator=(const BasicGameRegion&) = default;
		BasicGameRegion(BasicGameRegion&&) noexcept = default;
		BasicGameRegion& operator=(BasicGameRegion&&) noexcept = default;
		virtual ~BasicGameRegion() = default;

		BasicGameRegion& getNextRegion();
		const BasicGameRegion& getNextRegion() const;
		void setNextRegion(BasicGameRegion& nextRegion);

	private:
		std::reference_wrapper<BasicGameRegion> m_nextRegion;
	};
}
