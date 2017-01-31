#pragma once

#include <sfml/Graphics/Sprite.hpp>
#include <SFML\Graphics.hpp>

#include <vector>
#include <list>

class Pathfinder {
public:
	Pathfinder();
	Pathfinder(sf::Vector2f minFreeSpace);

	virtual ~Pathfinder();

	void pathfind(double startX, double startY, double endX, double endY);
	void pathfind(double startX, double startY, double endX, double endY, sf::Vector2f minFreeSpace);

	//getters / setters
		//setters
	void setMinFreeSpace(sf::Vector2f minFreeSpace);
		//setters
	sf::Vector2f getMinFreeSpace();


private:
	std::vector<sf::Sprite*>* pathBlockers;
};

