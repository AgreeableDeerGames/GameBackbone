#pragma once

#include "GameWorldSprite.h"
#include "Updatable.h"

#include<SFML/Graphics/Sprite.hpp>

#include<vector>

class GameRegion {
public:
	//ctr / dtr
	GameRegion();

	virtual ~GameRegion();
	
	//getters / setters
		//setters
	void setUpdatable(bool status, Updatable* object);
	void setDrawable(bool status, sf::Sprite* object);
	void setDrawAndUpdateable(bool status, GameWorldSprite* object);

	//internal behavior alteration
	void reset() {}
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

};

