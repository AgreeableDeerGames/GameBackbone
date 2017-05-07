#include "stdafx.h"

#include <GameRegion.h>

#include <SFML/Graphics.hpp>
/*
/// <summary>
/// Struct to store objects that can be reused for all or nearly all 
/// of the unit tests in this file. This struct is meant to be used with fixtures
/// at the unit test level.
/// </summary>
struct ReusableObjects
{
    ReusableObjects() {
        std::string testTexturePath = "..\\..\\Textures\\testSprite.png";
        aSpriteTexture->loadFromFile(testTexturePath);

        //create animation set
        sf::Vector2u textureDim = aSpriteTexture->getSize();
        std::vector<std::vector<unsigned int>> aSpriteAnims;
        std::vector<unsigned int> aSpriteAnim1 = { 0, 1, 2, 3 };
        aSpriteAnims.push_back(aSpriteAnim1);
        animSet = new AnimationSet(aSpriteAnims, textureDim.x, textureDim.y, 2, 2);

        compSprite = new CompoundSprite();

        for (int i = 0; i < 10 ; i++) {
            animSpriteWithAnimVector[i] = new AnimatedSprite(*aSpriteTexture, animSet);
            compSprite->addAnimatedSprite(animSpriteWithAnimVector[i]);
            compSprite->addSprite(&sf::Sprite());
        }

    }

    ~ReusableObjects() {
        delete animSet;
        delete aSpriteTexture;
        delete[] animSpriteWithAnimVector;
        delete compSprite;
    }

    AnimatedSprite* animSpriteWithAnimVector[10];
    AnimationSet* animSet;
    sf::Texture* aSpriteTexture;
    CompoundSprite* compSprite;
};*/

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

    BOOST_ASSERT(gameRegion->getUpdatables()->size() == 1);

    gameRegion->setUpdatable(false, animSpriteWithAnim);

    BOOST_ASSERT(gameRegion->getUpdatables()->size() == 0);

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

    BOOST_ASSERT(gameRegion->getDrawables()->size() == 1);

    gameRegion->setDrawable(false, sprite);

    BOOST_ASSERT(gameRegion->getDrawables()->size() == 0);

    delete sprite;
    delete gameRegion;
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
    std::vector<GameRegion*>* region1neighbors = region1->getNeighborRegions();
    std::vector<GameRegion*>* region7neighbors = region7->getNeighborRegions();
    BOOST_ASSERT(std::find(region1neighbors->begin(), region1neighbors->end(), region7) == region1neighbors->end());
    BOOST_ASSERT(std::find(region7neighbors->begin(), region7neighbors->end(), region1) == region7neighbors->end());

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
    std::vector<GameRegion*>* region1neighbors = region1->getNeighborRegions();
    std::vector<GameRegion*>* region7neighbors = region7->getNeighborRegions();
    BOOST_ASSERT(std::find(region1neighbors->begin(), region1neighbors->end(), region7) == region1neighbors->end());
    BOOST_ASSERT(std::find(region7neighbors->begin(), region7neighbors->end(), region1) == region7neighbors->end());
    BOOST_ASSERT(region1neighbors->size() == 2);

    region5->addNeighborRegion(region2);//     1 - 2
	region5->addNeighborRegion(region4);//     |   |
	delete region4;						//     4 - 5

    region5->addNeighborRegion(region7);//     1 - 2 - 3 - 6
	region3->addNeighborRegion(region2);//         |   
	region3->addNeighborRegion(region6);//         5 - 7  
    region5->removeNeighborRegion(region7);

    region3->clearNeighborRegions();
    std::vector<GameRegion*>* region3neighbors = region3->getNeighborRegions();
    BOOST_ASSERT(region3neighbors->size() == 0);

    delete region1; delete region2; delete region3; delete region5; delete region6; delete region7;
}

BOOST_AUTO_TEST_CASE(GameRegion_neighbor_t6) {
    GameRegion* region1 = new GameRegion();
    GameRegion* region2 = new GameRegion();
    GameRegion* region3 = new GameRegion();

    region1->addNeighborRegion(region2);//    3 - 1 - 2
    region1->addNeighborRegion(region3);

    std::vector<GameRegion*>* region1neighbors = region1->getNeighborRegions();
    BOOST_ASSERT(region1neighbors->size() == 2);
    BOOST_ASSERT(std::find(region1neighbors->begin(), region1neighbors->end(), region2) != region1neighbors->end());
    BOOST_ASSERT(std::find(region1neighbors->begin(), region1neighbors->end(), region3) != region1neighbors->end());
    
    region1->clearNeighborRegions();
    region1neighbors = region1->getNeighborRegions();
    BOOST_ASSERT(region1neighbors->size() == 0);

    region1->addNeighborRegion(region2);//    3 - 1 - 2
    region1->addNeighborRegion(region3);
    delete region2;
    region1neighbors = region1->getNeighborRegions();
    BOOST_ASSERT(region1neighbors->size() == 1);


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
	BOOST_CHECK(returnedChildRegions->at(0) == childRegion);

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
	BOOST_CHECK(returnedChildRegions->at(0) == childRegion2);

	delete gameRegion;
	delete childRegion1;
	delete childRegion2;
}

// Test that exception is thrown when child is not a child of parent
BOOST_AUTO_TEST_CASE(GameRegion_remove_child_child_not_in_children) {
	GameRegion* gameRegion = new GameRegion();
	GameRegion* childRegion = new GameRegion();

	//add and remove the region

	//BOOST_CHECK_THROW(gameRegion->removeChildRegion(childRegion), GameRegion_BadDissociation);

	delete gameRegion;
	delete childRegion;
}

BOOST_AUTO_TEST_SUITE_END() // end GameRegion_child_tests

BOOST_AUTO_TEST_SUITE_END() // end GameRegion_tests