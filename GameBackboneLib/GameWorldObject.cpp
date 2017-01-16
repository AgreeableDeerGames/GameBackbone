#include "stdafx.h"
#include "GameWorldObject.h"



GameWorldObject::GameWorldObject() {
	gx = 0;
	gy = 0;
	active = false;
}


GameWorldObject::~GameWorldObject() {
}

///<summary>the x position of the object in the game world.</summary>
double GameWorldObject::getGx() {
	return gx;
}
///<summary>Sets the y position of the object in the game world.</summary>
double GameWorldObject::getGy() {
	return gy;
}
///<summary>Whether or not the GameWorldObject is active in the game world</summary>
double GameWorldObject::isActive() {
	return active;
}
