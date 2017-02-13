#pragma once
#include "DllUtil.h"
#include "GameWorldAnimatedSprite.h"
#include "Updatable.h"
#include "GameWorldCompoundSprite2.h"

#include<SFML/Graphics/Sprite.hpp>

#include<vector>

/// <summary> Base class meant to be inherited. Controls game logic and actors for a specific time or space in game. </summary>
class libGameBackbone GameRegion {
public:
	//ctr / dtr
	GameRegion();

	virtual ~GameRegion();
	
	//getters / setters
		//setters
	void setUpdatable(bool status, Updatable* object);
	void setDrawable(bool status, sf::Sprite* object);
	void setDrawable(bool status, GameWorldCompoundSprite2* object);
	void setDrawAndUpdateable(bool status, GameWorldAnimatedSprite* object);
	void setDrawAndUpdateable(bool status, GameWorldCompoundSprite2* object);
	std::vector<Updatable*>* getUpdatables();
	std::vector<sf::Sprite*>* getDrawables();


	//internal behavior alteration
	
	/// <summary>
	/// Resets this instance.
	/// </summary>
	void reset() {}
	
	/// <summary>
	/// Runs the game behaviors and logic for this instance.
	/// </summary>
	void behave() {}

	//general operations
		//additions
	void addChildRegion(GameRegion* child);
	void addNeighborRegion(GameRegion* neighbor);
		//removals
	void removeNeighborRegion(GameRegion* neighbor);
	void removeChildRegion(GameRegion* child);
		//clears
	void clearUpdatable();
	void clearChildren();
	void clearDrawable();
	void clearNeighborRegions();

protected:

	//ctr
	void init() {}

	//internal logic members
	std::vector<sf::Sprite*>* drawables;
	std::vector<Updatable*>* updatables;

	//associated regions
	GameRegion* parentRegion;
	std::vector<GameRegion*> childRegions;
	std::vector<GameRegion*> neighborRegions;

private:
	//deleted copy and assignment ctr
	GameRegion(const GameRegion&) = delete;
	GameRegion& operator=(const GameRegion&) = delete;
	GameRegion(GameRegion&&) = delete;
	GameRegion& operator=(GameRegion&&) = delete;

};

