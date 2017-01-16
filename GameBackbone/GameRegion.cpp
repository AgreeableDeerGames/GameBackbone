#include "GameRegion.h"

#include<algorithm>


GameRegion::GameRegion() {
	updatables = new std::vector<Updatable*>();
	drawables = new std::vector<sf::Sprite*>();
	parentRegion = nullptr;
}


GameRegion::~GameRegion() {
	if (parentRegion) {
		parentRegion->removeChildRegion(this);
	}
	clearChildren();
	clearNeighborRegions();
	delete updatables;
	delete drawables;
}

//getters / setters
	//setters

///<summary> adds or removes a updatable object from the array of updatable objects </summary>
///<param name = "status"> Whether or not the object will be updatable </param>
///<param name = "object"> the object that whose updatability status will be changed </param>
void GameRegion::setUpdatable(bool status, Updatable * object) {
	if (status) {
		updatables->push_back(object);
	} else {
		auto it = std::find(updatables->begin(), updatables->end(), object);
		if (it != updatables->end()) {
			updatables->erase(it);
		}
	}
}

///<summary> adds or removes a drawable object from the array of drawable objects </summary>
///<param name = "status"> Whether or not the object will be drawable </param>
///<param name = "object"> the object that whose draw-ability status will be changed </param>
void GameRegion::setDrawable(bool status, sf::Sprite * object) {
	if (status) {
		drawables->push_back(object);
	} else {
		auto it = std::find(drawables->begin(), drawables->end(), object);
		if (it != drawables->end()) {
			drawables->erase(it);
		}
	}
}

///<summary> adds or removes all drawable object from a GameWorldCompound sprite to the array of drawable objects </summary>
///<param name = "status"> Whether or not the object will be drawable </param>
///<param name = "object"> the object that whose draw-ability status will be changed </param>
void GameRegion::setDrawable(bool status, GameWorldCompoundSprite2 * object) {
	for each (sf::Sprite* sprite in *(object->getSfSprites()) ) {
		setDrawable(status, sprite);
	}
	for each (AnimatedSprite* aSprite in *(object->getaAnimatedSprites())) {
		setDrawable(status, aSprite);
	}
}

///<summary> adds or removes a drawable and updatable object from the arrays of drawable and updatable objects </summary>
///<param name = "status"> Whether or not the object will be drawable and updatable </param>
///<param name = "object"> the object that whose draw-ability and updatability status will be changed </param>
void GameRegion::setDrawAndUpdateable(bool status, GameWorldAnimatedSprite* object) {
	setDrawable(status, object);
	setUpdatable(status, object);
}

///<summary> adds or removes all drawable and updatable object from a GameWorldCompoundSprite to the arrays of drawable and updatable objects </summary>
///<param name = "status"> Whether or not the object will be drawable and updatable </param>
///<param name = "object"> the object that whose draw-ability and updatability status will be changed </param>
void GameRegion::setDrawAndUpdateable(bool status, GameWorldCompoundSprite2 * object) {
	setDrawable(status, object);
	setUpdatable(status, object);
}

///<summary>returns list of the region's updatable objects</summary>
std::vector<Updatable*>* GameRegion::getUpdatables() {
	return updatables;
}

///<summary>return the region's list of drawable objects</summary>
std::vector<sf::Sprite*>* GameRegion::getDrawables() {
	return drawables;
}

//general operations

	//additions

///<summary>sets this GameRegion as the parent of the passed GameRegion</summary>
///<param name = "child">new child region of this region</param>
void GameRegion::addChildRegion(GameRegion * child) {
	//clear any previous parents
	child->parentRegion->removeChildRegion(child);

	//add child
	childRegions.push_back(child);
	child->parentRegion = this;
}

///<summary>Associates  two GameRegions as neighbors of each other.</summary>
///<param name = "neighbor"> GameRegion to associate with</param>
void GameRegion::addNeighborRegion(GameRegion * neighbor) {
	neighborRegions.push_back(neighbor);
	neighbor->neighborRegions.push_back(this);
}

	//removals

///<summary>removes the neighbor association between two GameRegions</summary>
///<param name = "neighbor"> neighbor to be disassociated</param>
void GameRegion::removeNeighborRegion(GameRegion * neighbor) {
	//remove neighbor from this.neighborRegions
	auto it = std::find(neighborRegions.begin(), neighborRegions.end(), neighbor);
	if (it != neighborRegions.end()) {
		neighborRegions.erase(it);
	}

	//remove this from neighbor->neighborRegions
	auto nit = std::find(neighbor->neighborRegions.begin(), neighbor->neighborRegions.end(), this);
	if (nit != neighbor->neighborRegions.end()){
		neighbor->neighborRegions.erase(nit);
	}
}

///<summary>Removes the parent child relationship between two GameRegions</summary>
///<param name = "child"> The child being orphaned <param>
void GameRegion::removeChildRegion(GameRegion * child) {
	auto it = std::find(childRegions.begin(), childRegions.end(), child);
	if (it != childRegions.end()) {
		childRegions.erase(it);
	}
	child->parentRegion = nullptr;
}

///<summary>removes all updatable objects from this GameRegion</summary>
void GameRegion::clearUpdatable() {
	updatables->clear();
}

///<summary>orphans all children GameRegions in this GameRegion</summary>
void GameRegion::clearChildren() {
	for (GameRegion* child : childRegions) {
		removeChildRegion(child);
	}
}

///<summary>removes all drawable objects from this GameRegion</summary>
void GameRegion::clearDrawable() {
	drawables->clear();
}

///<summary>Disassociates all neighbor GameRegions from this GameRegion</summary>
void GameRegion::clearNeighborRegions() {
	for (GameRegion* neighbor : neighborRegions) {
		removeNeighborRegion(neighbor);
	}
}





