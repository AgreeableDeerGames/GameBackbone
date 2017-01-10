#pragma once

#include "Updatable.h"

class GameWorldObject : public Updatable{
public:

	//ctr / dtr
	GameWorldObject();
	virtual ~GameWorldObject();

	//getters / setters

		//setters
	///<summary>Sets the x position of the object in the game world.</summary>
	virtual void setGx(double x) = 0;
	///<summary>Sets the y position of the object in the game world.</summary>
	virtual void setGy(double y) = 0;
	///<summary>Whether or not the GameWorldObject is active in the game world</summary>
	virtual void setActive(bool active) = 0;

		//getters
	double getGx();
	double getGy();
	double isActive();

	//operations
	virtual void Update(sf::Time currentTime) = 0;

protected:
	double gx;
	double gy;
	bool active;
};

