#include "stdafx.h"
#include "GameRegion.h"

#include<algorithm>

/// <summary>
/// Initializes a new instance of the <see cref="GameRegion"/> class. All members are initialized empty or null.
/// </summary>
GameRegion::GameRegion() {
	updatables = new std::vector<Updatable*>();
	drawables = new std::vector<sf::Sprite*>();
	parentRegion = nullptr;
}

/// <summary>
/// Finalizes an instance of the <see cref="GameRegion"/> class.
/// </summary>
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

/// <summary>
/// Adds or removes a updatable object from the array of updatable objects.
/// </summary>
/// <param name="status">If set to <c>true</c> the object will be updatable, otherwise the object will be made not updatable. </param>
/// <param name="object">The object that whose updatability status will be changed.</param>
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

/// <summary>
/// Adds or removes a drawable object from the array of drawable objects.
/// </summary>
/// <param name="status">if set to <c>true</c> the object will be drawable, otherwise the object will be made non-drawable.</param>
/// <param name="object">The object.</param>
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


/// <summary>
/// Adds or removes all drawable object from a CompoundSprite to the array of drawable objects.
/// </summary>
/// <param name="status">if set to <c>true</c> the object will be drawable, otherwise the object will be made non-drawable.</param>
/// <param name="object">The object.</param>
void GameRegion::setDrawable(bool status, CompoundSprite * object) {
	for each (sf::Sprite* sprite in *(object->getSfSprites()) ) {
		setDrawable(status, sprite);
	}
	for each (AnimatedSprite* aSprite in *(object->getAnimatedSprites())) {
		setDrawable(status, aSprite);
	}
}

/// <summary>
/// Adds or removes a drawable and updatable object from the arrays of drawable and updatable objects
/// </summary>
/// <param name="status">if set to <c>true</c> the object will be both drawable and updatable, otherwise the object will be neither drawable nor updatable. </param>
/// <param name="object">The object.</param>
void GameRegion::setDrawAndUpdateable(bool status, AnimatedSprite* object) {
	setDrawable(status, object);
	setUpdatable(status, object);
}

/// <summary>
/// Adds or removes all drawable and updatable object from a CompoundSprite to the arrays of drawable and updatable objects.
/// </summary>
/// <param name="status">if set to <c>true</c> the object will be both drawable and updatable, otherwise the object will be neither drawable nor updatable. </param>
/// <param name="object">The object.</param>
void GameRegion::setDrawAndUpdateable(bool status, CompoundSprite * object) {
	setDrawable(status, object);
	setUpdatable(status, object);
}

/// <summary>
/// Returns list of the region's updatable objects.
/// </summary>
/// <returns>std::Vector of the region's updatable objects.</returns>
std::vector<Updatable*>* GameRegion::getUpdatables() {
	return updatables;
}

/// <summary>
/// Return the region's list of drawable objects
/// </summary>
/// <returns>std::vector of drawable objects</returns>
std::vector<sf::Sprite*>* GameRegion::getDrawables() {
	return drawables;
}

std::vector<GameRegion*>* GameRegion::getNeighborRegions() {
    return &neighborRegions;
}

std::vector<GameRegion*>* GameRegion::getChildRegions() {
    return &childRegions;
}

//general operations

	//additions

/// <summary>
/// sets this GameRegion as the parent of the passed GameRegion.
/// </summary>
/// <param name="child">The new child region of this region.</param>
void GameRegion::addChildRegion(GameRegion * child) {
	//clear any previous parents
    if (child->parentRegion) {
        child->parentRegion->removeChildRegion(child);
    }

	//add child
	childRegions.push_back(child);
	child->parentRegion = this;
}

/// <summary>
/// Associates  two GameRegions as neighbors of each other.
/// </summary>
/// <param name="neighbor">The neighbor.</param>
void GameRegion::addNeighborRegion(GameRegion * neighbor) {
	neighborRegions.push_back(neighbor);
	neighbor->neighborRegions.push_back(this);
}

	//removals

/// <summary>
/// Removes the neighbor association between two GameRegions.
/// </summary>
/// <param name="neighbor">The neighbor.</param>
void GameRegion::removeNeighborRegion(GameRegion * neighbor) {
    //remove this from neighbor->neighborRegions
    auto nit = std::find(neighbor->neighborRegions.begin(), neighbor->neighborRegions.end(), this);
    if (nit != neighbor->neighborRegions.end()) {
        neighbor->neighborRegions.erase(nit);
    }

	//remove neighbor from this.neighborRegions
	auto it = std::find(neighborRegions.begin(), neighborRegions.end(), neighbor);
	if (it != neighborRegions.end()) {
		neighborRegions.erase(it);
	}
}

/// <summary>
/// Removes the parent child relationship between two GameRegions.
/// </summary>
/// <param name="child">The child.</param>
void GameRegion::removeChildRegion(GameRegion * child) {
	auto it = std::find(childRegions.begin(), childRegions.end(), child);
	if (it != childRegions.end()) {
		childRegions.erase(it);
	}
	child->parentRegion = nullptr;
}

/// <summary>
/// Removes all updatable objects from this GameRegion.
/// </summary>
void GameRegion::clearUpdatable() {
	updatables->clear();
}

/// <summary>
/// Orphans all children GameRegions in this GameRegion.
/// </summary>
void GameRegion::clearChildren() {
	for (GameRegion* child : childRegions) {
		removeChildRegion(child);
	}
}

/// <summary>
/// Removes all drawable objects from this GameRegion.
/// </summary>
void GameRegion::clearDrawable() {
	drawables->clear();
}

/// <summary>
/// Disassociates all neighbor GameRegions from this GameRegion.
/// </summary>
void GameRegion::clearNeighborRegions() {
    for (int ii = neighborRegions.size() -1 ; ii >= 0; ii--)
    {
        removeNeighborRegion(neighborRegions[ii]);
    }
}

/// <summary>
/// Loops through list of associations, and calls the passed in function on each.
/// <summary>
void GameRegion::removeAssociations(const std::function<void(std::vector<GameRegion*>::iterator)> disassociator, std::vector<GameRegion*>* list) {
    auto it = list->begin();
    while (it != list->end()) {
        // perfoms operation on iterator then increments it
        disassociator(it++);
    }
}



