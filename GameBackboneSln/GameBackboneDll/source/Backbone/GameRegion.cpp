#include <Backbone/GameRegion.h>

#include <TGUI/TGUI.hpp>

#include <algorithm>

using namespace GB;

/// <summary>
/// Initializes a new instance of the <see cref="GameRegion"/> class. All members are initialized empty or null.
/// </summary>
GameRegion::GameRegion() {
	updatables = new std::list<Updatable*>();
	drawables = new std::list<sf::Sprite*>();
	parentRegion = nullptr;
	regionGUI = new tgui::Gui();
}

/// <summary>
/// Initializes a new instance of the <see cref="GameRegion"/> class. All members except regionGUI
/// are initialized empty or null. The regions GUI is bound to the passed window.
/// </summary>
/// <param name="window">The window.</param>
GameRegion::GameRegion(sf::RenderWindow & window) : GameRegion() {
	regionGUI->setWindow(window);
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

	if (regionGUI) {
		delete regionGUI;
	}
}

//getters / setters
	//setters

/// <summary>
/// Adds or removes a updatable object from the list of updatable objects.
/// </summary>
/// <param name="status">If set to <c>true</c> the object will be updatable, otherwise the object will be made not updatable. </param>
/// <param name="object">The object whose updatability status will be changed.</param>
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
/// Adds or removes a drawable object from the list of drawable objects.
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
/// Adds or removes all drawable object from a CompoundSprite to the list of drawable objects.
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
/// Adds or removes a drawable and updatable object from the lists of drawable and updatable objects
/// </summary>
/// <param name="status">if set to <c>true</c> the object will be both drawable and updatable, otherwise the object will be neither drawable nor updatable. </param>
/// <param name="object">The object.</param>
void GameRegion::setDrawAndUpdateable(bool status, AnimatedSprite* object) {
	setDrawable(status, object);
	setUpdatable(status, object);
}

/// <summary>
/// Adds or removes all drawable and updatable object from a CompoundSprite to the lists of drawable and updatable objects.
/// </summary>
/// <param name="status">if set to <c>true</c> the object will be both drawable and updatable, otherwise the object will be neither drawable nor updatable. </param>
/// <param name="object">The object.</param>
void GameRegion::setDrawAndUpdateable(bool status, CompoundSprite * object) {
	setDrawable(status, object);
	setUpdatable(status, object);
}

/// <summary>
/// Sets the parent region.
/// </summary>
/// <param name="newParent">The new parent.</param>
void GameRegion::setParentRegion(GameRegion* newParent) {
	if (parentRegion != newParent)
	{
		newParent->addChildRegion(this);
	}
}

/// <summary>
/// Returns list of the region's updatable objects.
/// </summary>
/// <returns>std::list of the region's updatable objects.</returns>
std::list<Updatable*>* GameRegion::getUpdatables() {
	return updatables;
}

/// <summary>
/// Return the region's list of drawable objects
/// </summary>
/// <returns>std::list of drawable objects</returns>
std::list<sf::Sprite*>* GameRegion::getDrawables() {
	return drawables;
}

std::list<GameRegion*>* GameRegion::getNeighborRegions() {
    return &neighborRegions;
}

std::list<GameRegion*>* GameRegion::getChildRegions() {
    return &childRegions;
}

/// <summary>
/// Gets the parent region.
/// </summary>
GameRegion* GameRegion::getParentRegion() {
	return parentRegion;
}

/// <summary>
/// Gets the GUI for this region.
/// </summary>
/// <returns>This regions GUI.</returns>
tgui::Gui* GameRegion::getGUI() {
	return regionGUI;
}

//general operations

	//additions

/// <summary>
/// sets this GameRegion as the parent of the passed GameRegion.
/// </summary>
/// <param name="childToAdd">The new child region of this region.</param>
void GameRegion::addChildRegion(GameRegion * childToAdd) {
	//clear any previous parents
    if (childToAdd->parentRegion) {
		childToAdd->parentRegion->removeChildRegion(childToAdd);
    }

	//add child
	childRegions.push_back(childToAdd);
	childToAdd->parentRegion = this;
}

/// <summary>
/// Associates  two GameRegions as neighbors of each other.
/// </summary>
/// <param name="neighborToAdd">The neighbor that is being added to the region.</param>
void GameRegion::addNeighborRegion(GameRegion * neighborToAdd) {
	neighborRegions.push_back(neighborToAdd);
	neighborToAdd->neighborRegions.push_back(this);
}

	//removals

/// <summary>
/// Removes the neighbor association between two GameRegions.
/// 
/// Throws GameRegion_BadDissociation if the GameRegions are not neighbors.
/// </summary>
/// <param name="neighborToRemove">The neighbor that is being removed from this GameRegion.</param>
void GameRegion::removeNeighborRegion(GameRegion * neighborToRemove) {
    //remove this from neighbor->neighborRegions
    auto nit = std::find(neighborToRemove->neighborRegions.begin(), neighborToRemove->neighborRegions.end(), this);
    if (nit != neighborToRemove->neighborRegions.end()) {
		neighborToRemove->neighborRegions.erase(nit);
	} else {
		throw Error::GameRegion_BadDissociation();
	}

	//remove neighbor from this.neighborRegions
	auto it = std::find(neighborRegions.begin(), neighborRegions.end(), neighborToRemove);
	if (it != neighborRegions.end()) {
		neighborRegions.erase(it);
	} else {
		throw Error::GameRegion_BadDissociation();
	}
}

/// <summary>
/// Removes the parent child relationship between two GameRegions.
/// 
/// Throws GameRegion_BadDissociation if childToRemove is not a child.
/// </summary>
/// <param name="childToRemove">The child that is being removed from the Parent Region.</param>
void GameRegion::removeChildRegion(GameRegion * childToRemove) {
	auto it = std::find(childRegions.begin(), childRegions.end(), childToRemove);
	if (it != childRegions.end()) {
		childRegions.erase(it);
		childToRemove->parentRegion = nullptr;
	} else {
		throw Error::GameRegion_BadDissociation();
	}
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
	std::function<void(GameRegion*)> disassociator = std::bind(&GameRegion::removeChildRegion, this, std::placeholders::_1);
	clearAssociations(disassociator, getChildRegions());
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

    std::function<void(GameRegion*)> disassociator = std::bind(&GameRegion::removeNeighborRegion, this, std::placeholders::_1);
    clearAssociations(disassociator, getNeighborRegions());
}

/// <summary>
/// Loops through list of associations, and calls the passed in function on each.
/// </summary>
/// <example>
/// <pre>
/// \b Example
/// \code{.cpp}
/// void GameRegion::clearNeighborRegions() {
///     std::function <void(GameRegion*)> disassociator = std::bind(&aClass::FunctionWhichDisassociates, this, std::placeholders::_1);
///     clearAssociations(disassociator, getNeighborRegions());
/// }
/// \endcode
/// </pre>
/// </example>
/// <param name="memberFunctionPointer">Function used to disassociate individual elements of the list</param>
/// <param name="list">List of GameRegions to clear associations from.</param>
void GameRegion::clearAssociations(std::function<void(GameRegion*)> memberFunctionPointer, std::list<GameRegion*>* list) {
	auto iter = list->begin();
	while (iter != list->end())
	{
		//Move iterator to next element before altering the list
		auto tempIter = iter;
		++iter;

		//disassociate element and remove from the list
        memberFunctionPointer(*tempIter);
    }
}


