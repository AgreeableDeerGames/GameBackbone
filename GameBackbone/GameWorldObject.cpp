#include "GameWorldObject.h"


/// <summary>
/// Initializes a new instance of the <see cref="GameWorldCompoundSprite2"/> class. The game world position defaults to 0,0.
/// </summary>
GameWorldObject::GameWorldObject() {
	gwPosition.x = 0;
	gwPosition.y = 0;
	active = false;
}

/// <summary>
/// Finalizes an instance of the <see cref="GameWorldObject"/> class.
/// </summary>
GameWorldObject::~GameWorldObject() {
}

/// <summary>
/// The x position of the object in the game world.
/// </summary>
/// <returns></returns>
double GameWorldObject::getGx() {
	return gwPosition.x;
}

/// <summary>
/// Sets the y position of the object in the game world.
/// </summary>
/// <returns></returns>
double GameWorldObject::getGy() {
	return gwPosition.y;
}

/// <summary>
/// Whether or not the GameWorldObject is active in the game world.
/// </summary>
/// <returns></returns>
double GameWorldObject::isActive() {
	return active;
}
