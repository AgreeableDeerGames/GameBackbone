#include "GameWorldObject.h"



GameWorldObject::GameWorldObject() {
	gwPosition.x = 0;
	gwPosition.y = 0;
	active = false;
}


GameWorldObject::~GameWorldObject() {
}

///<summary>the x position of the object in the game world.</summary>
double GameWorldObject::getGx() {
	return gwPosition.x;
}
///<summary>Sets the y position of the object in the game world.</summary>
double GameWorldObject::getGy() {
	return gwPosition.y;
}
///<summary>Whether or not the GameWorldObject is active in the game world</summary>
double GameWorldObject::isActive() {
	return active;
}
