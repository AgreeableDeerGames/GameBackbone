#include "GameWorldAnchor.h"
#include "SFML/Graphics/Sprite.hpp"


//ctr / dtr

///<summary>  Initializes a new instance of the <see cref="GameWorldAnchor"/> class with no GameRegion at location 0,0. </summary>
GameWorldAnchor::GameWorldAnchor() : GameWorldAnchor(nullptr) {}

/// <summary>
/// Initializes a new instance of the <see cref="GameWorldAnchor"/> class at location 0,0.
/// </summary>
/// <param name="anchoredRegion"> Region attached to this anchor. Every drawable item will be drawn relative to the anchors position. </param>
GameWorldAnchor::GameWorldAnchor(GameRegion * anchoredRegion) : GameWorldAnchor(anchoredRegion, 0, 0) {}

/// <summary>
/// Initializes a new instance of the <see cref="GameWorldAnchor"/> class for the passed region at the passed starting location.
/// </summary>
/// <param name="anchoredRegion">The region attached to this anchor. Every drawable item will be drawn relative to the anchors position.</param>
/// <param name="gx"> The x starting position of the anchor. Used to determine the initial offset of drawable items. </param>
/// <param name="gy"> The y starting position of the anchor. Used to determine the initial offset of drawable items. </param>
GameWorldAnchor::GameWorldAnchor(GameRegion * anchoredRegion, double gx, double gy) {
	this->gwPosition.x = 0;
	this->gwPosition.y = 0;
	this->anchoredRegion = anchoredRegion;
	if (anchoredRegion) { //this is more lines of code than just copying gMove over, but it should be better maintainable.
		gMove(gx, gy);
	} else {
		this->gwPosition.x = gx;
		this->gwPosition.y = gy;
	}
}

/// <summary>
/// Finalizes an instance of the <see cref="GameWorldAnchor"/> class.
/// </summary>
GameWorldAnchor::~GameWorldAnchor() {}


// operations

/// <summary>
///  'Moves' the anchor my moving all drawable objects sf::sprite.x and sf::sprite.y in the opposite direction
/// </summary>
/// <param name="xOffset">The x offset.</param>
/// <param name="yOffset">The y offset.</param>
void GameWorldAnchor::gMove(double xOffset, double yOffset) {
	for each (sf::Sprite* object in *(anchoredRegion->getDrawables()) ) {
		object->move(-(float)xOffset, -(float)yOffset);
	}
	gwPosition.x += xOffset;
	gwPosition.y += yOffset;
}

/// <summary>
/// Sets the GameWorldAnchor active.
/// </summary>
/// <param name="active">if set to <c>true</c> [active].</param>
void GameWorldAnchor::setActive(bool active) {
	this->active = active;
}
