#pragma once
#include "stdafx.h"
#include "GameRegion.h"
#include "Array2D.h"
#include "PathFinder.h"

#include<SFML/Graphics/Sprite.hpp>

/// <summary>
/// GameRegion with logic for demonstrating basic path-finding demonstrations.
/// </summary>
/// <seealso cref="GameRegion" />
class libGameBackbone NavigationDemoRegion : public GameRegion {
public:

	// ctr / dtr

	NavigationDemoRegion();
	virtual ~NavigationDemoRegion();

	//behavior

	virtual void behave(sf::Time currentTime) override;



private:
	//helper functions
	void initMaze();
	sf::Vector2f gridCoordToWorldCoord(const IntPair& gridCoordinate);
	IntPair worldCoordToGridCoord(const sf::Vector2f& worldCoordinate);

	//movement functions
	void moveSpriteTowardsPoint(sf::Sprite* sprite, sf::Vector2f destination, float distance);
	void moveSpriteAlongPath(sf::Sprite* sprite, std::list<IntPair>* path, unsigned int msPassed, float speed);


	// sprite textures
	sf::Texture* navigatorTexture;
	sf::Texture* gridTexture;

	//	store visual representation of maze and maze solvers
	Array2D<sf::Sprite*>* visualNavigationGrid;
	std::vector<sf::Sprite*> navigators;

	//path-finding
	Pathfinder regionPathfinder;
	NavigationGrid* navGrid;
	const unsigned int NAV_GRID_DIM = 20;
	const float VISUAL_GRID_SCALE = 1.0f;
};

