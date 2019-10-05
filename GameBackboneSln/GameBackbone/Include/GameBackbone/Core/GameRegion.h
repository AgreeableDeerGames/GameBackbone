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
#include <vector>

namespace GB {

	/// <summary> Base class meant to be inherited. Controls game logic and actors for a specific time or space in game. </summary>
	class libGameBackbone GameRegion : public sf::Drawable, public Updatable {
	public:
		/// <summary>shared_ptr to GameRegion</summary>
		using Ptr = std::shared_ptr<GameRegion>;
		
		GameRegion() = default;
		explicit GameRegion(sf::RenderWindow & window);
		GameRegion(const GameRegion&) = default;
		GameRegion& operator=(const GameRegion&) = default;
		GameRegion(GameRegion&&) = default;
		GameRegion& operator=(GameRegion&&) = default;
		virtual ~GameRegion() = default;

		//getters / setters
		void setDrawable(bool status, sf::Drawable* object);
		const std::vector<sf::Drawable*>& getDrawables() const;
		tgui::Gui& getGUI();

		virtual void registerSetActiveRegionCB(std::function<void(GameRegion*)> newSetActiveRegionCB);
		void clearDrawable();

		/// <summary>
		/// Implements Updatable::update as a no-op.
		/// </summary>
		/// <param name="elapsedTime"> </param>
		virtual void update(sf::Int64 /*elapsedTime*/) override {}

	protected:
		// Drawing
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		std::vector<sf::Drawable*> drawables;

		//associated regions
		std::function<void(GameRegion*)> setActiveRegionCB;

		//GUI
		tgui::Gui regionGUI;
	};
}
