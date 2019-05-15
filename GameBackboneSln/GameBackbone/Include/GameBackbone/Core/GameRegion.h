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
#include <vector>

namespace GB {

	/// <summary> Base class meant to be inherited. Controls game logic and actors for a specific time or space in game. </summary>
	class libGameBackbone GameRegion : public sf::Drawable, public Updatable {
	public:
		//ctr / dtr
		GameRegion();
		explicit GameRegion(sf::RenderWindow & window);

		virtual ~GameRegion();

		//getters / setters
		//setters
		void setUpdatable(bool status, Updatable* object);
		void setDrawable(bool status, sf::Drawable* object);
		void setDrawable(bool status, CompoundSprite* object);
		void setDrawAndUpdateable(bool status, AnimatedSprite* object);
		void setDrawAndUpdateable(bool status, CompoundSprite* object);
		void setParentRegion(GameRegion* newParent);

		//getters
		const std::vector<Updatable*>* const getUpdatables();
		const std::vector<sf::Drawable*>* const getDrawables();
		const std::vector<GameRegion*>* getNeighborRegions();
		const std::vector<GameRegion*>* getChildRegions();

		GameRegion* getParentRegion();
		tgui::Gui* getGUI();


		//internal behavior alteration

		/// <summary>
		/// Resets this instance.
		/// </summary>
		virtual void reset() {}

		/// <summary>
		/// Runs the game behaviors and logic for this instance.
		/// </summary>
		virtual void update(sf::Time currentTime) override {}

		virtual void registerSetActiveRegionCB(std::function<void(GameRegion*)> newSetActiveRegionCB);

		//general operations

		//additions
		void addChildRegion(GameRegion* childToAdd);
		void addNeighborRegion(GameRegion* neighborToAdd);
		//removals
		void removeNeighborRegion(GameRegion* neighborToRemove);
		void removeChildRegion(GameRegion* childToRemove);
		//clears
		void clearUpdatable();
		void clearChildren();
		void clearDrawable();
		void clearNeighborRegions();

	protected:

		//operations
		void clearAssociations(std::function<void(GameRegion*)> dissociationFunction, std::vector<GameRegion*>* container);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		//internal logic members
		std::vector<sf::Drawable*>* drawables;
		std::vector<Updatable*>* updatables;

		//associated regions
		GameRegion* parentRegion;
		std::vector<GameRegion*> childRegions;
		std::vector<GameRegion*> neighborRegions;
		std::function<void(GameRegion*)> setActiveRegionCB;

		//GUI
		tgui::Gui* regionGUI;

	private:
		//deleted copy and assignment ctr
		GameRegion(const GameRegion&) = delete;
		GameRegion& operator=(const GameRegion&) = delete;
		GameRegion(GameRegion&&) = delete;
		GameRegion& operator=(GameRegion&&) = delete;

	};

}
