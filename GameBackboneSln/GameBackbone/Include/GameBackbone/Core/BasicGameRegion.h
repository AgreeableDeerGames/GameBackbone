#pragma once

#include <GameBackbone/Core/AnimationSet.h>
#include <GameBackbone/Core/BackboneBaseExceptions.h>
#include <GameBackbone/Core/CompoundSprite.h>
#include <GameBackbone/Core/Updatable.h>
#include <GameBackbone/Util/DllUtil.h>

#include <TGUI/TGUI.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <functional>
#include <memory>
#include <utility>
#include <vector>

namespace GB {

	/// <summary> Base class meant to be inherited. Controls game logic and actors for a specific time or space in game. </summary>
	class libGameBackbone BasicGameRegion : public sf::Drawable, public Updatable {
	public:
		/// <summary>shared_ptr to GameRegion</summary>
		using Ptr = std::shared_ptr<BasicGameRegion>;

		BasicGameRegion() = default;
		explicit BasicGameRegion(sf::RenderWindow& window);
		BasicGameRegion(const BasicGameRegion&) = default;
		BasicGameRegion& operator=(const BasicGameRegion&) = default;
		BasicGameRegion(BasicGameRegion&&) = default;
		BasicGameRegion& operator=(BasicGameRegion&&) = default;
		virtual ~BasicGameRegion() = default;

		[[nodiscard]]
		tgui::Gui& getGUI();

		void setActiveRegion(BasicGameRegion& activeRegion) const;
		void registerSetActiveRegionCB(std::function<void(BasicGameRegion*)> newSetActiveRegionCB);

		/// <summary>
		/// Implements Updatable::update as a no-op.
		/// </summary>
		/// <param name="elapsedTime"> </param>
		virtual void update(sf::Int64 /*elapsedTime*/) override {}

	private:
		tgui::Gui m_regionGUI;
		std::function<void(BasicGameRegion*)> m_setActiveRegionCB;
	};
}
