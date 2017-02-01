#pragma once
#include "Point2D.h"
#include "GameWorldAnchor.h"

#include <sfml/Graphics/Sprite.hpp>
#include <SFML\Graphics.hpp>

#include <vector>
#include <list>

class Pathfinder {
public:
	Pathfinder();
	Pathfinder(sf::Vector2f minFreeSpace);

	virtual ~Pathfinder();

	//operations
	std::list<Point2D>* pathfind(double startX, double startY, double endX, double endY);
	std::list<Point2D>* pathfind(double startX, double startY, double endX, double endY, sf::Vector2f minFreeSpace);
	void addPathBlocker(sf::Sprite* blocker);
	void removePathBlocker(sf::Sprite* blocker);

	//getters / setters
		//setters
	void setMinFreeSpace(sf::Vector2f minFreeSpace);
	void setPathBlockers(std::vector<sf::Sprite*>* blockers);
	void setAnchor(GameWorldAnchor* anchor);

		//getters
	sf::Vector2f getMinFreeSpace();
	std::list<Point2D> getLasFoundPath();
	std::vector<sf::Sprite*>* getPathBlockers();
	GameWorldAnchor* getAnchor();


private:

	//storage
	std::vector<sf::Sprite*>* pathBlockers;
	std::list<Point2D> lastFoundPath;
	sf::Vector2f minFreeSpace;
	GameWorldAnchor* anchor;
	
	//logic helper
	sf::FloatRect positionChecker;

	//deleted copy and assignment
	Pathfinder(const Pathfinder&) = delete;
	Pathfinder(Pathfinder&&) = delete;
	Pathfinder& operator=(const Pathfinder&) = delete;
	Pathfinder& operator=(Pathfinder&&) = delete;
};

