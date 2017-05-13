#include "stdafx.h"

#include <GameRegion.h>

#include <SFML/Graphics.hpp>

using namespace GB;

BOOST_AUTO_TEST_SUITE(GameRegion_Tests)

BOOST_AUTO_TEST_SUITE(GameRegion_ctrs)

// Tests the default constructor
BOOST_AUTO_TEST_CASE(GameRegion_default_ctr_test) {

    GameRegion* gameRegion = new GameRegion();

    BOOST_CHECK(gameRegion->getDrawables()->size() == 0 );
    BOOST_CHECK(gameRegion->getUpdatables()->size() == 0);

    delete gameRegion;
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(GameRegion_get_set_tests)

// Tests getting Updatables with getUpdatables
BOOST_AUTO_TEST_CASE(GameRegion_getUpdatables_test) {

    GameRegion* gameRegion = new GameRegion();
    AnimatedSprite* animSpriteWithAnimVector[10];

    for (int i = 0; i < 10; i++) {
        animSpriteWithAnimVector[i] = new AnimatedSprite();
        gameRegion->setUpdatable(true, animSpriteWithAnimVector[i]);
    }
    BOOST_CHECK(gameRegion->getUpdatables()->size() == 10);

    for (int i = 0; i < 5; i++) {
        gameRegion->setUpdatable(false, animSpriteWithAnimVector[9-i]);
        delete animSpriteWithAnimVector[9 - i];
    }
    BOOST_CHECK(gameRegion->getUpdatables()->size() == 5);

    for (int i = 0; i < 5; i++) {
        gameRegion->setUpdatable(false, animSpriteWithAnimVector[4 - i]);
        delete animSpriteWithAnimVector[4 - i];
    }
    BOOST_CHECK(gameRegion->getUpdatables()->size() == 0);

    delete gameRegion;
}

// Tests adding and removing with setUpdatables
BOOST_AUTO_TEST_CASE(GameRegion_setUpdatables_test) {
    GameRegion* gameRegion = new GameRegion();
    AnimatedSprite* animSpriteWithAnim = new AnimatedSprite();

    gameRegion->setUpdatable(true, animSpriteWithAnim);

    BOOST_CHECK(gameRegion->getUpdatables()->size() == 1);

    gameRegion->setUpdatable(false, animSpriteWithAnim);

    BOOST_CHECK(gameRegion->getUpdatables()->size() == 0);

    delete animSpriteWithAnim;
    delete gameRegion;
}

// Tests getting Drawables with getDrawables
BOOST_AUTO_TEST_CASE(GameRegion_getDrawables_test) {

    GameRegion* gameRegion = new GameRegion();
    sf::Sprite* compoundSpriteVector[10];

    for (int i = 0; i < 10; i++) {
        compoundSpriteVector[i] = new sf::Sprite();
        gameRegion->setDrawable(true, compoundSpriteVector[i]);
    }

    BOOST_CHECK(gameRegion->getDrawables()->size() == 10);

    for (int i = 0; i < 5; i++) {
        gameRegion->setDrawable(false, compoundSpriteVector[9 - i]);
        delete compoundSpriteVector[9 - i];
    }
    BOOST_CHECK(gameRegion->getDrawables()->size() == 5);

    for (int i = 0; i < 5; i++) {
        gameRegion->setDrawable(false, compoundSpriteVector[4 - i]);
        delete compoundSpriteVector[4 - i];
    }
    BOOST_CHECK(gameRegion->getDrawables()->size() == 0);

    delete gameRegion;
}

// Tests adding and removing with setDrawables
BOOST_AUTO_TEST_CASE(GameRegion_setDrawables_test) {
    GameRegion* gameRegion = new GameRegion();
    sf::Sprite* sprite = new sf::Sprite();

    gameRegion->setDrawable(true, sprite);

    BOOST_CHECK(gameRegion->getDrawables()->size() == 1);

    gameRegion->setDrawable(false, sprite);

    BOOST_CHECK(gameRegion->getDrawables()->size() == 0);

    delete sprite;
    delete gameRegion;
}

// Tests getting Parent with getParentRegion
BOOST_AUTO_TEST_CASE(GameRegion_getParent_test) {
	GameRegion* gameRegion = new GameRegion();
	GameRegion* childRegion = new GameRegion();

	gameRegion->addChildRegion(childRegion);

	GameRegion* returnedParentRegion = childRegion->getParentRegion();

	//ensure that the correct Parent region has been stored
	BOOST_CHECK(returnedParentRegion == gameRegion);

	delete gameRegion;
	delete childRegion;
}

// Tests setting Parent with setParentRegion
BOOST_AUTO_TEST_CASE(GameRegion_setParent_test) {
	GameRegion* gameRegion = new GameRegion();
	GameRegion* childRegion = new GameRegion();

	childRegion->setParentRegion(gameRegion);

	GameRegion* returnedParentRegion = childRegion->getParentRegion();
	auto returnedChildRegions = gameRegion->getChildRegions();

	//ensure that the correct child region has been stored
	BOOST_CHECK(returnedParentRegion == gameRegion);

	//ensure that exactly one child is found
	BOOST_CHECK(returnedChildRegions->size() == 1);

	//ensure the region not removed is still present
	BOOST_CHECK(returnedChildRegions->front() == childRegion);

	delete gameRegion;
	delete childRegion;
}

BOOST_AUTO_TEST_SUITE_END() // end GameRegion_get_set_tests

////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(GameRegion_neighbor_tests)
//////////////////////////////////////////////

// Tests add and destructor
BOOST_AUTO_TEST_CASE(GameRegion_neighbor_t1) {
    GameRegion* region1 = new GameRegion(); 
    GameRegion* region2 = new GameRegion(); 
    GameRegion* region3 = new GameRegion(); 
    GameRegion* region4 = new GameRegion();
    GameRegion* region5 = new GameRegion(); 
    GameRegion* region6 = new GameRegion();
    GameRegion* region7 = new GameRegion();

    region1->addNeighborRegion(region2);//     1 - 2 - 3 - 6
	region1->addNeighborRegion(region4);//     |   |   
	region5->addNeighborRegion(region2);//     4 - 5 - 7  
	region5->addNeighborRegion(region4);
	region5->addNeighborRegion(region7);
    region3->addNeighborRegion(region2);
    region3->addNeighborRegion(region6);


    delete region1; delete region2; delete region3; delete region4; delete region5; delete region6; delete region7;
}

// Tests remove
BOOST_AUTO_TEST_CASE(GameRegion_neighbor_t2) {
    GameRegion* region1 = new GameRegion(); 
	GameRegion* region2 = new GameRegion(); 
	GameRegion* region3 = new GameRegion(); 
	GameRegion* region4 = new GameRegion();    
	GameRegion* region5 = new GameRegion(); 
    GameRegion* region6 = new GameRegion();
    GameRegion* region7 = new GameRegion();

    region1->addNeighborRegion(region2);//     1 - 2 - 3 - 6
	region1->addNeighborRegion(region4);//     |   |   
	region5->addNeighborRegion(region2);//     4 - 5 - 7  
	region5->addNeighborRegion(region4);    
	region5->addNeighborRegion(region7);
    region3->addNeighborRegion(region2);
    region3->addNeighborRegion(region6);
    region5->removeNeighborRegion(region7);
    region5->removeNeighborRegion(region4);


    delete region1; delete region2; delete region3; delete region4; delete region5; delete region6; delete region7;
}

// Tests delete
BOOST_AUTO_TEST_CASE(GameRegion_neighbor_t3) {
    GameRegion* region1 = new GameRegion(); 
	GameRegion* region2 = new GameRegion(); 
	GameRegion* region3 = new GameRegion(); 
	GameRegion* region4 = new GameRegion(); 
	GameRegion* region5 = new GameRegion(); 
    GameRegion* region6 = new GameRegion();
    GameRegion* region7 = new GameRegion();

    region1->addNeighborRegion(region2);//     1 - 2
	region1->addNeighborRegion(region4);//     |   |
	region5->addNeighborRegion(region2);//     4 - 5
    region5->addNeighborRegion(region4);
    delete region4;
    region5->addNeighborRegion(region7);//     1 - 2 - 3 - 6
    region3->addNeighborRegion(region2);//         |   
    region3->addNeighborRegion(region6);//         5 - 7  
    region5->removeNeighborRegion(region7);


    delete region1; delete region2; delete region3; delete region5; delete region6; delete region7;
}

// Tests that things are actually removed
BOOST_AUTO_TEST_CASE(GameRegion_neighbor_t4) {
    GameRegion* region1 = new GameRegion();  
	GameRegion* region2 = new GameRegion(); 
	GameRegion* region3 = new GameRegion(); 
	GameRegion* region4 = new GameRegion();              
	GameRegion* region5 = new GameRegion();          
    GameRegion* region6 = new GameRegion();
    GameRegion* region7 = new GameRegion();

    region1->addNeighborRegion(region2);//    7 - 1 - 2
	region1->addNeighborRegion(region4);//        | 
	region1->addNeighborRegion(region7);//        4 
    region1->removeNeighborRegion(region7);

    //make sure region7 was removed
    std::list<GameRegion*>* region1neighbors = region1->getNeighborRegions();
    std::list<GameRegion*>* region7neighbors = region7->getNeighborRegions();
    BOOST_CHECK(std::find(region1neighbors->begin(), region1neighbors->end(), region7) == region1neighbors->end());
    BOOST_CHECK(std::find(region7neighbors->begin(), region7neighbors->end(), region1) == region7neighbors->end());

    region5->addNeighborRegion(region2);//     1 - 2
	region5->addNeighborRegion(region4);//     |   |   
	delete region4;						//     4 - 5   

    region5->addNeighborRegion(region7);//     1 - 2 - 3 - 6
	region3->addNeighborRegion(region2);//         |   
	region3->addNeighborRegion(region6);//         5 - 7  
    region5->removeNeighborRegion(region7);


    delete region1; delete region2; delete region3; delete region5; delete region6; delete region7;
}

// Tests that sizing after removal is ok
BOOST_AUTO_TEST_CASE(GameRegion_neighbor_t5) {
    GameRegion* region1 = new GameRegion();
    GameRegion* region2 = new GameRegion();
    GameRegion* region3 = new GameRegion();
    GameRegion* region4 = new GameRegion();
    GameRegion* region5 = new GameRegion();
    GameRegion* region6 = new GameRegion();
    GameRegion* region7 = new GameRegion();

    region1->addNeighborRegion(region2);//    7 - 1 - 2
	region1->addNeighborRegion(region4);//        | 
	region1->addNeighborRegion(region7);//        4 
    region1->removeNeighborRegion(region7);

    //make sure region7 was removed
    std::list<GameRegion*>* region1neighbors = region1->getNeighborRegions();
    std::list<GameRegion*>* region7neighbors = region7->getNeighborRegions();
    BOOST_CHECK(std::find(region1neighbors->begin(), region1neighbors->end(), region7) == region1neighbors->end());
    BOOST_CHECK(std::find(region7neighbors->begin(), region7neighbors->end(), region1) == region7neighbors->end());
    BOOST_CHECK(region1neighbors->size() == 2);

    region5->addNeighborRegion(region2);//     1 - 2
	region5->addNeighborRegion(region4);//     |   |
	delete region4;						//     4 - 5

    region5->addNeighborRegion(region7);//     1 - 2 - 3 - 6
	region3->addNeighborRegion(region2);//         |   
	region3->addNeighborRegion(region6);//         5 - 7  
    region5->removeNeighborRegion(region7);

    region3->clearNeighborRegions();
    std::list<GameRegion*>* region3neighbors = region3->getNeighborRegions();
    BOOST_CHECK(region3neighbors->size() == 0);

    delete region1; delete region2; delete region3; delete region5; delete region6; delete region7;
}

BOOST_AUTO_TEST_CASE(GameRegion_neighbor_t6) {
    GameRegion* region1 = new GameRegion();
    GameRegion* region2 = new GameRegion();
    GameRegion* region3 = new GameRegion();

    region1->addNeighborRegion(region2);//    3 - 1 - 2
    region1->addNeighborRegion(region3);

    std::list<GameRegion*>* region1neighbors = region1->getNeighborRegions();
    BOOST_CHECK(region1neighbors->size() == 2);
    BOOST_CHECK(std::find(region1neighbors->begin(), region1neighbors->end(), region2) != region1neighbors->end());
    BOOST_CHECK(std::find(region1neighbors->begin(), region1neighbors->end(), region3) != region1neighbors->end());
    
    region1->clearNeighborRegions();
    region1neighbors = region1->getNeighborRegions();
    BOOST_CHECK(region1neighbors->size() == 0);

    region1->addNeighborRegion(region2);//    3 - 1 - 2
    region1->addNeighborRegion(region3);
    delete region2;
    region1neighbors = region1->getNeighborRegions();
    BOOST_CHECK(region1neighbors->size() == 1);


    delete region1; delete region3;
}

// Tests attempting to remove a non-neighbor
BOOST_AUTO_TEST_CASE(GameRegion_neighbor_t7) {
	GameRegion* region1 = new GameRegion();
	GameRegion* region2 = new GameRegion();
	
	//BOOST_CHECK_THROW(region1->removeNeighborRegion(region1), GameRegion_BadDissociation);

	delete region1; 
	delete region2;
}

BOOST_AUTO_TEST_SUITE_END() // end GameRegion_neighbor_tests

////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(GameRegion_child_tests)
//////////////////////////////////////////////


// Tests add and destructor
BOOST_AUTO_TEST_CASE(GameRegion_add_child) {
    GameRegion* gameRegion = new GameRegion();
    GameRegion* childRegion = new GameRegion();

    gameRegion->addChildRegion(childRegion);

	auto returnedChildRegions = gameRegion->getChildRegions();

	//ensure that exactly one child is found
	BOOST_CHECK(returnedChildRegions->size() == 1);

	//ensure that the correct child region has been stored
	BOOST_CHECK(returnedChildRegions->front() == childRegion);

	delete gameRegion;
	delete childRegion;

}

// Test removing a child
BOOST_AUTO_TEST_CASE(GameRegion_remove_child) {
	GameRegion* gameRegion = new GameRegion();
	GameRegion* childRegion = new GameRegion();

	//add and remove the region
	gameRegion->addChildRegion(childRegion);
	gameRegion->removeChildRegion(childRegion);

	auto returnedChildRegions = gameRegion->getChildRegions();

	//ensure that the child has been removed
	BOOST_CHECK(returnedChildRegions->empty());

	delete gameRegion;
	delete childRegion;
}

// Test that the correct child is removed in removeChildRegion
BOOST_AUTO_TEST_CASE(GameRegion_remove_correct_child) {
	GameRegion* gameRegion = new GameRegion();
	GameRegion* childRegion1 = new GameRegion();
	GameRegion* childRegion2 = new GameRegion();

	//add and remove the region
	gameRegion->addChildRegion(childRegion1);
	gameRegion->addChildRegion(childRegion2);

	gameRegion->removeChildRegion(childRegion1);

	auto returnedChildRegions = gameRegion->getChildRegions();

	//ensure that the child has been removed
	BOOST_CHECK(returnedChildRegions->size() == 1);

	//ensure the region not removed is still present
	BOOST_CHECK(returnedChildRegions->front() == childRegion2);

	delete gameRegion;
	delete childRegion1;
	delete childRegion2;
}

// Test that exception is thrown when child is not a child of parent
BOOST_AUTO_TEST_CASE(GameRegion_remove_child_child_not_in_children) {
	GameRegion* gameRegion = new GameRegion();
	GameRegion* childRegion = new GameRegion();

	// ensure exception is thrown when attempting to remove a region that is not a child
	BOOST_CHECK_THROW(gameRegion->removeChildRegion(childRegion), Error::GameRegion_BadDissociation);

	delete gameRegion;
	delete childRegion;
}

// Test that setting a parent for the first time successfully creates the parent child relation
BOOST_AUTO_TEST_CASE(GameRegion_setParentRegion_new_parent_no_existing_parent) {
	GameRegion* gameRegion = new GameRegion();
	GameRegion* childRegion = new GameRegion();

	// ensure that the child does not already have a parent
	BOOST_CHECK(childRegion->getParentRegion() == nullptr);

	childRegion->setParentRegion(gameRegion);

	// ensure that the child has the correct parent assigned
	BOOST_CHECK(childRegion->getParentRegion() == gameRegion);

	// ensure that the child region is a child of the parent region
	BOOST_CHECK(gameRegion->getChildRegions()->front() == childRegion);

	delete gameRegion;
	delete childRegion;
}

// Test that setting a parent will disacociate any previous parent relationship
BOOST_AUTO_TEST_CASE(GameRegion_setParentRegion_new_parent_existing_parent) {
	GameRegion* gameRegion = new GameRegion();
	GameRegion* gameRegion2 = new GameRegion();
	GameRegion* childRegion = new GameRegion();

	childRegion->setParentRegion(gameRegion);
	childRegion->setParentRegion(gameRegion2);
	
	// ensure that the child has the correct parent assigned
	BOOST_CHECK(childRegion->getParentRegion() == gameRegion2);

	// ensure that the child region is a child of the parent region
	BOOST_CHECK(gameRegion2->getChildRegions()->front() == childRegion);

	// ensure that the previous parent region has no association to the child
	BOOST_CHECK(gameRegion->getChildRegions()->empty());

	delete gameRegion;
	delete gameRegion2;
	delete childRegion;
}

// Test that setting a parent for two child regions correctly creates the relationship for both
BOOST_AUTO_TEST_CASE(GameRegion_setParentRegion_two_children) {
	GameRegion* gameRegion = new GameRegion();
	GameRegion* childRegion1 = new GameRegion();
	GameRegion* childRegion2 = new GameRegion();

	childRegion1->setParentRegion(gameRegion);
	childRegion2->setParentRegion(gameRegion);

	// ensure that the child has the correct parent assigned
	BOOST_CHECK(childRegion1->getParentRegion() == gameRegion);
	BOOST_CHECK(childRegion2->getParentRegion() == gameRegion);

	// ensure that the child region is a child of the parent region
	BOOST_CHECK(gameRegion->getChildRegions()->front() == childRegion1);
	BOOST_CHECK(gameRegion->getChildRegions()->back() == childRegion2);

	delete gameRegion;
	delete childRegion1;
	delete childRegion2;
}

// Test that setting a parent twice only adds the relationship once
BOOST_AUTO_TEST_CASE(GameRegion_setParentRegion_same_parent) {
	GameRegion* gameRegion = new GameRegion();
	GameRegion* childRegion = new GameRegion();

	childRegion->setParentRegion(gameRegion);
	childRegion->setParentRegion(gameRegion);

	// ensure that the child has the correct parent assigned
	BOOST_CHECK(childRegion->getParentRegion() == gameRegion);

	// ensure that the child region is a child of the parent region
	BOOST_CHECK(gameRegion->getChildRegions()->front() == childRegion);

	// ensure that the child region has only been added once
	BOOST_CHECK(gameRegion->getChildRegions()->size() == 1);


	delete gameRegion;
	delete childRegion;
}

// Test that clearing children successfully removes all parent child relationships
BOOST_AUTO_TEST_CASE(GameRegion_clearChildren) {
	GameRegion* gameRegion = new GameRegion();
	GameRegion* childRegion1 = new GameRegion();
	GameRegion* childRegion2 = new GameRegion();

	childRegion1->setParentRegion(gameRegion);
	childRegion2->setParentRegion(gameRegion);

	gameRegion->clearChildren();

	// ensure that the parent region has no children
	BOOST_CHECK(gameRegion->getChildRegions()->empty());
	
	//ensure that the children no longer have a parent
	BOOST_CHECK(childRegion1->getParentRegion() == nullptr);
	BOOST_CHECK(childRegion2->getParentRegion() == nullptr);

	delete gameRegion;
	delete childRegion1;
	delete childRegion2;
}


BOOST_AUTO_TEST_SUITE_END() // end GameRegion_child_tests

BOOST_AUTO_TEST_SUITE_END() // end GameRegion_tests