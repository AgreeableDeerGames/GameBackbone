#include "stdafx.h"

#include <GameBackbone/Core/GameRegion.h>

#include <SFML/Graphics.hpp>

using namespace GB;

BOOST_AUTO_TEST_SUITE(GameRegion_Tests)

BOOST_AUTO_TEST_SUITE(GameRegion_CTRs)

// Tests the default constructor
BOOST_AUTO_TEST_CASE(GameRegion_default_CTR) {

    GameRegion* gameRegion = new GameRegion();

    BOOST_CHECK(gameRegion->getDrawableCount() == 0 );
    delete gameRegion;
}

//Tests the window constructor
BOOST_AUTO_TEST_CASE(GameRegion_window_CTR) {

	const int WINDOW_HEIGHT = 700;
	const int WINDOW_WIDTH = 700;

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TestWindow");
	GameRegion* gameRegion = new GameRegion(*window);

	BOOST_CHECK(gameRegion->getDrawableCount() == 0);
	BOOST_CHECK(gameRegion->getGUI().getTarget() == window);

	delete window;
	delete gameRegion;
}

BOOST_AUTO_TEST_SUITE_END() // end GameRegion_CTRs

BOOST_AUTO_TEST_SUITE(GameRegion_get_set_tests)

// Tests getting Drawables with getDrawables
BOOST_AUTO_TEST_CASE(GameRegion_getDrawables) {

    GameRegion* gameRegion = new GameRegion();
    sf::Sprite* compoundSpriteVector[10];

    for (int i = 0; i < 10; i++) {
        compoundSpriteVector[i] = new sf::Sprite();
        gameRegion->addDrawable(0, compoundSpriteVector[i]);
    }

    BOOST_CHECK(gameRegion->getDrawableCount() == 10);

    for (int i = 0; i < 5; i++) {
        gameRegion->removeDrawable(compoundSpriteVector[9 - i]);
        delete compoundSpriteVector[9 - i];
    }
    BOOST_CHECK(gameRegion->getDrawableCount() == 5);

    for (int i = 0; i < 5; i++) {
        gameRegion->removeDrawable(compoundSpriteVector[4 - i]);
        delete compoundSpriteVector[4 - i];
    }
    BOOST_CHECK(gameRegion->getDrawableCount() == 0);

    delete gameRegion;
}

// Tests adding and removing with setDrawables
BOOST_AUTO_TEST_CASE(GameRegion_setDrawables) {
    GameRegion* gameRegion = new GameRegion();
    sf::Sprite* sprite = new sf::Sprite();

    gameRegion->addDrawable(0, sprite);

    BOOST_CHECK(gameRegion->getDrawableCount() == 1);

    gameRegion->removeDrawable(sprite);

    BOOST_CHECK(gameRegion->getDrawableCount() == 0);

    delete sprite;
    delete gameRegion;
}

// Tests adding nullptr with setDrawables
BOOST_AUTO_TEST_CASE(GameRegion_addDrawable_nullptr) {
	GameRegion* gameRegion = new GameRegion();
	sf::Sprite* sprite = nullptr;

	BOOST_CHECK_THROW(gameRegion->addDrawable(0, sprite), std::invalid_argument);

	delete gameRegion;
}

//Tests getting GUI with getGUI
BOOST_AUTO_TEST_CASE(GameRegion_getGUI) {
	GameRegion* gameRegion = new GameRegion();

	sf::RenderWindow* newWindow = new sf::RenderWindow(sf::VideoMode(1, 1), "NewWindow");

	//get reference to gameRegion's GUI, then change the reference's window.
	tgui::Gui& regionGUI = gameRegion->getGUI();
	regionGUI.setTarget(*newWindow);

	//If the GUI reference is mutable, then newWindow will be gameRegion's window
	BOOST_CHECK(gameRegion->getGUI().getTarget() == newWindow);

	delete newWindow;
	delete gameRegion;
}

BOOST_AUTO_TEST_SUITE_END() // end GameRegion_get_set_tests

BOOST_AUTO_TEST_SUITE_END() // end GameRegion_tests