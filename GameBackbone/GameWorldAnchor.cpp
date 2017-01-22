#include "GameWorldAnchor.h"
#include "SFML/Graphics/Sprite.hpp"


//ctr / dtr

///<summary> create a GameWorldAnchor with no GameRegion at location 0,0</summary>
GameWorldAnchor::GameWorldAnchor() : GameWorldAnchor(nullptr) {}

///<summary> create a GameWorldAnchor for the passed region at location 0,0</summary>
///<param name = "anchoredRegion"> region attached to this anchor. Every drawable item will be drawn relative to the anchors position.</param>
GameWorldAnchor::GameWorldAnchor(GameRegion * anchoredRegion) : GameWorldAnchor(anchoredRegion, 0, 0) {}

///<summary> create a GameWorldAnchor for the passed region at the passed starting location</summary>
///<param name = "anchoredRegion"> region attached to this anchor. Every drawable item will be drawn relative to the anchors position.</param>
///<param name = "gx"> the x starting position of the anchor. Used to determine the initial offset of drawable items.</param>
///<param name = "gx"> the y starting position of the anchor. Used to determine the initial offset of drawable items.</param>
GameWorldAnchor::GameWorldAnchor(GameRegion * anchoredRegion, double gx, double gy) {
	this->gx = 0;
	this->gy = 0;
	this->anchoredRegion = anchoredRegion;
	if (anchoredRegion) { //this is more lines of code than just copying gMove over, but it should be better maintainable.
		gMove(gx, gy);
	} else {
		this->gx = gx;
		this->gy = gy;
	}
}

GameWorldAnchor::~GameWorldAnchor() {}


// operations

///<summary> "Moves" the anchor my moving all drawable objects sf::sprite.x and sf::sprite.y in the opposite direction</summary>
///<param name = "xOffset"> x offset of the new position</param>
///<param name = "YOffset"> y offset of the new position</param>
void GameWorldAnchor::gMove(double xOffset, double yOffset) {
	for each (sf::Sprite* object in *(anchoredRegion->getDrawables()) ) {
		object->move(-(float)xOffset, -(float)yOffset);
	}
	gx += xOffset;
	gy += yOffset;
}

void GameWorldAnchor::setActive(bool active) {
	this->active = active;
}
