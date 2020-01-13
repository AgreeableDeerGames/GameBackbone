#pragma once

#include <GameBackbone/Core/Updatable.h>
#include <GameBackbone/Util/DllUtil.h>

#include <TGUI/TGUI.hpp>

#include <SFML/Graphics/Drawable.hpp>

#include <memory>

namespace GB {
	class ActivationProvider;

	/// <summary> Base class meant to be inherited. Controls game logic and actors for a specific time or space in game. </summary>
	class libGameBackbone BasicGameRegion : public sf::Drawable, public Updatable {
	public:
		/// <summary>shared_ptr to BasicGameRegion</summary>
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

		[[nodiscard]]
		bool giveActivation(BasicGameRegion& targetRegion);
		void setActivationProvider(ActivationProvider& provider);

		[[nodiscard]]
		bool isActiveRegion();

		/// <summary>
		/// Implements Updatable::update as a no-op.
		/// </summary>
		/// <param name="elapsedTime"> </param>
		void update(sf::Int64 /*elapsedTime*/) override {}

	private:
		tgui::Gui m_regionGUI;
		ActivationProvider* m_provider;
	};
}
