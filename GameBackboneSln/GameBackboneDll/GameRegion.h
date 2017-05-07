#pragma once
#include "stdafx.h"
#include "AnimatedSprite.h"
#include "BackboneBaseExceptions.h"
#include "CompoundSprite.h"
#include "DllUtil.h"
#include "Updatable.h"

#include<SFML/Graphics/Sprite.hpp>

#include<vector>
#include<functional>

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
	void setDrawable(bool status, CompoundSprite* object);
	void setDrawAndUpdateable(bool status, AnimatedSprite* object);
	void setDrawAndUpdateable(bool status, CompoundSprite* object);
        //getters
	std::vector<Updatable*>* getUpdatables();
	std::vector<sf::Sprite*>* getDrawables();
    std::vector<GameRegion*>* getNeighborRegions();
    std::vector<GameRegion*>* getChildRegions();


	//internal behavior alteration
	
	/// <summary>
	/// Resets this instance.
	/// </summary>
	virtual void reset() {}
	
	/// <summary>
	/// Runs the game behaviors and logic for this instance.
	/// </summary>
	virtual void behave(sf::Time currentTime) {}

	//general operations
		//getters/setters
	GameRegion* getParentRegion();
	void setParentRegion(GameRegion* newParent);
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

	//ctr
	void init() {}

    //operations
    void removeAssociations(std::function<void(std::vector<GameRegion*>::iterator)> disassociator, std::vector<GameRegion*>* list);

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

