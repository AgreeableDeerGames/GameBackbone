#include "stdafx.h"

#include <GameBackbone/Core/GameRegion.h>

#include <SFML/Graphics.hpp>

#include <vector>

using namespace GB;

class MockDrawable : public sf::Drawable {
public:
	MockDrawable(std::vector<const sf::Drawable*>* newDrawnVector) : drawnVector(newDrawnVector) {};

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		drawnVector->push_back(this);
	}

	std::vector<const sf::Drawable*>* drawnVector;
};


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


BOOST_AUTO_TEST_SUITE(GameRegion_priority_drawing_tests)

// Tests adding Drawables at different priorities
BOOST_AUTO_TEST_CASE(GameRegion_setDrawables) {
	sf::RenderWindow window(sf::VideoMode(1, 1), "windowName");
	GameRegion gameRegion;

	std::vector<sf::Drawable*> drawableVector;
	std::vector<const sf::Drawable*> drawnVector;

	// Add priority 0 drawables
	for (int ii = 0; ii < 2; ii++) {
		MockDrawable* mockDrawable = new MockDrawable(&drawnVector);
		drawableVector.emplace_back(mockDrawable);
		gameRegion.addDrawable(0, mockDrawable);
	}

	// Add priority 1 drawables
	for (int ii = 0; ii < 2; ii++) {
		MockDrawable* mockDrawable = new MockDrawable(&drawnVector);
		drawableVector.push_back(mockDrawable);
		gameRegion.addDrawable(1, mockDrawable);
	}

	// Add priority 2 drawables
	for (int ii = 0; ii < 2; ii++) {
		MockDrawable* mockDrawable = new MockDrawable(&drawnVector);
		drawableVector.push_back(mockDrawable);
		gameRegion.addDrawable(2, mockDrawable);
	}

	// Call draw on the GameRegion to pass it down to the MockDrawables
	window.draw(gameRegion);

	// Ensure that the vectors contain the same elements, but most importantly, in the same order
	BOOST_CHECK(drawableVector.size() == drawnVector.size());
	BOOST_CHECK_EQUAL_COLLECTIONS(drawnVector.begin(), drawnVector.end(), drawableVector.begin(), drawableVector.end());

	// Free all MockDrawables
	for (int ii = 0; ii < drawableVector.size(); ii++) {
		delete drawableVector[ii];
	}
}

BOOST_AUTO_TEST_SUITE_END() // end GameRegion_priority_drawing_tests

BOOST_AUTO_TEST_SUITE_END() // end GameRegion_tests