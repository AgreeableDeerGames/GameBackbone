#include "stdafx.h"

#include <GameBackbone/Core/GameRegion.h>

#include <SFML/Graphics.hpp>

using namespace GB;

BOOST_AUTO_TEST_SUITE(GameRegion_Tests)

BOOST_AUTO_TEST_SUITE(GameRegion_CTRs)

// Tests the default constructor
BOOST_AUTO_TEST_CASE(GameRegion_default_CTR) {

    GameRegion* gameRegion = new GameRegion();

    BOOST_CHECK(gameRegion->getDrawables().size() == 0 );
    delete gameRegion;
}

//Tests the window constructor
BOOST_AUTO_TEST_CASE(GameRegion_window_CTR) {

	const int WINDOW_HEIGHT = 700;
	const int WINDOW_WIDTH = 700;

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TestWindow");
	GameRegion* gameRegion = new GameRegion(*window);

	BOOST_CHECK(gameRegion->getDrawables().size() == 0);
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
        gameRegion->setDrawable(true, compoundSpriteVector[i]);
    }

    BOOST_CHECK(gameRegion->getDrawables().size() == 10);

    for (int i = 0; i < 5; i++) {
        gameRegion->setDrawable(false, compoundSpriteVector[9 - i]);
        delete compoundSpriteVector[9 - i];
    }
    BOOST_CHECK(gameRegion->getDrawables().size() == 5);

    for (int i = 0; i < 5; i++) {
        gameRegion->setDrawable(false, compoundSpriteVector[4 - i]);
        delete compoundSpriteVector[4 - i];
    }
    BOOST_CHECK(gameRegion->getDrawables().size() == 0);

    delete gameRegion;
}

// Tests SFML's ability to draw backbones drawables.
BOOST_AUTO_TEST_CASE(GameRegion_getDrawables_sfml_can_draw) {
	sf::RenderWindow window(sf::VideoMode(1, 1), "windowName");
	GameRegion gameRegion;

	// if this compiles we know that sfml can draw what GameRegion stores as drawables.
	for (auto& drawable : gameRegion.getDrawables())
	{
		window.draw(*drawable);
	}
	BOOST_CHECK(true);
}

// Tests adding and removing with setDrawables
BOOST_AUTO_TEST_CASE(GameRegion_setDrawables) {
    GameRegion* gameRegion = new GameRegion();
    sf::Sprite* sprite = new sf::Sprite();

    gameRegion->setDrawable(true, sprite);

    BOOST_CHECK(gameRegion->getDrawables().size() == 1);

    gameRegion->setDrawable(false, sprite);

    BOOST_CHECK(gameRegion->getDrawables().size() == 0);

    delete sprite;
    delete gameRegion;
}

// Tests adding nullptr with setDrawables
BOOST_AUTO_TEST_CASE(GameRegion_setDrawables_nullptr) {
	GameRegion* gameRegion = new GameRegion();
	sf::Sprite* sprite = nullptr;

	BOOST_CHECK_THROW(gameRegion->setDrawable(true, sprite), std::invalid_argument);

	BOOST_CHECK_THROW(gameRegion->setDrawable(false, sprite), std::invalid_argument);

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