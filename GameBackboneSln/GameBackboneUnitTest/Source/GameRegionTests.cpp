#include "stdafx.h"

#include <GameBackbone/Core/GameRegion.h>

#include <SFML/Graphics.hpp>

#include <list>
#include <memory>

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

		// Tests the window constructor
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

	BOOST_AUTO_TEST_SUITE(GameRegion_addDrawable_tests)

		// Tests adding Drawables to the GameRegion in bulk
		BOOST_AUTO_TEST_CASE(GameRegion_addDrawable_bulk) {
			std::unique_ptr<GameRegion> gameRegion = std::make_unique<GameRegion>();
			std::vector<sf::Drawable*> drawables(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				drawables[ii] = new sf::Sprite();
			}

			gameRegion->addDrawable(0, drawables.begin(), drawables.end());

			// Check that the drawables were added and at the correct priority
			BOOST_CHECK(gameRegion->getDrawableCount(0) == drawables.size());
			BOOST_CHECK(gameRegion->getDrawableCount() == drawables.size());

			// Free drawables
			for (int ii = 0; ii < drawables.size(); ii++) {
				delete drawables[ii];
			}
		}

		// Tests adding Drawables to the GameRegion in bulk
		BOOST_AUTO_TEST_CASE(GameRegion_addDrawable_bulk_list) {
			std::unique_ptr<GameRegion> gameRegion = std::make_unique<GameRegion>();
			std::list<sf::Drawable*> drawables(5);

			for (sf::Drawable*& drawable : drawables)
			{
				drawable = new sf::Sprite();
			}

			gameRegion->addDrawable(0, drawables.begin(), drawables.end());

			// Check that the drawables were added and at the correct priority
			BOOST_CHECK(gameRegion->getDrawableCount(0) == drawables.size());
			BOOST_CHECK(gameRegion->getDrawableCount() == drawables.size());

			// Free drawables
			for (sf::Drawable* drawable : drawables)
			{
				delete drawable;
			}
		}

		// Tests adding Drawables to the GameRegion in bulk with different priorities
		BOOST_AUTO_TEST_CASE(GameRegion_addDrawable_bulk_differentPriorities) {
			std::unique_ptr<GameRegion> gameRegion = std::make_unique<GameRegion>();
			std::vector<sf::Drawable*> drawables(5);
			std::vector<sf::Drawable*> drawables2(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				drawables[ii] = new sf::Sprite();
			}
			for (int ii = 0; ii < drawables2.size(); ii++) {
				drawables2[ii] = new sf::Sprite();
			}

			gameRegion->addDrawable(0, drawables.begin(), drawables.end());
			gameRegion->addDrawable(1, drawables2.begin(), drawables2.end());

			// Check that the drawables were added and at the correct priority
			BOOST_CHECK(gameRegion->getDrawableCount(0) == drawables.size());
			BOOST_CHECK(gameRegion->getDrawableCount(1) == drawables2.size());
			BOOST_CHECK(gameRegion->getDrawableCount() == drawables.size() + drawables2.size());

			// Free drawables
			for (int ii = 0; ii < drawables.size(); ii++) {
				delete drawables[ii];
			}
			for (int ii = 0; ii < drawables2.size(); ii++) {
				delete drawables2[ii];
			}
		}

		// Tests adding Drawables to the GameRegion in bulk with nullptr
		BOOST_AUTO_TEST_CASE(GameRegion_addDrawable_bulk_nullptr) {
			std::unique_ptr<GameRegion> gameRegion = std::make_unique<GameRegion>();
			std::vector<sf::Drawable*> drawables(5);

			// Check that addDrawables throws std::invalid_argument if any Drawables are nullptr
			BOOST_CHECK_THROW(gameRegion->addDrawable(0, drawables.begin(), drawables.end()), std::invalid_argument);

			// Check that nothing was added during the add
			BOOST_CHECK(gameRegion->getDrawableCount(0) == 0);
			BOOST_CHECK(gameRegion->getDrawableCount() == 0);
		}

		// Tests adding Drawables to the GameRegion in bulk but overwriting in the same priority
		BOOST_AUTO_TEST_CASE(GameRegion_addDrawable_bulk_overwrite_samePriority) {
			std::unique_ptr<GameRegion> gameRegion = std::make_unique<GameRegion>();
			std::vector<sf::Drawable*> drawables(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				drawables[ii] = new sf::Sprite();
			}

			gameRegion->addDrawable(0, drawables.begin(), drawables.end());
			gameRegion->addDrawable(0, drawables.begin(), drawables.end());

			// Check that the drawables were only added one time
			BOOST_CHECK(gameRegion->getDrawableCount(0) == drawables.size());
			BOOST_CHECK(gameRegion->getDrawableCount() == drawables.size());

			// Free drawables
			for (int ii = 0; ii < drawables.size(); ii++) {
				delete drawables[ii];
			}
		}

		// Tests adding Drawables to the GameRegion in bulk but overwriting in the different priority
		BOOST_AUTO_TEST_CASE(GameRegion_addDrawable_bulk_overwrite_differentPriority) {
			std::unique_ptr<GameRegion> gameRegion = std::make_unique<GameRegion>();
			std::vector<sf::Drawable*> drawables(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				drawables[ii] = new sf::Sprite();
			}

			gameRegion->addDrawable(0, drawables.begin(), drawables.end());
			gameRegion->addDrawable(1, drawables.begin(), drawables.end());

			// Check that the drawables were only added one time and at the latter priority
			BOOST_CHECK(gameRegion->getDrawableCount(0) == 0);
			BOOST_CHECK(gameRegion->getDrawableCount(1) == drawables.size());
			BOOST_CHECK(gameRegion->getDrawableCount() == drawables.size());

			// Free drawables
			for (int ii = 0; ii < drawables.size(); ii++) {
				delete drawables[ii];
			}
		}

		// Tests adding Drawables to the GameRegion in single
		BOOST_AUTO_TEST_CASE(GameRegion_addDrawable_single) {
			std::unique_ptr<GameRegion> gameRegion = std::make_unique<GameRegion>();
			std::vector<sf::Drawable*> drawables(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				drawables[ii] = new sf::Sprite();
				gameRegion->addDrawable(0, drawables[ii]);
			}

			// Check that the drawables were added and at the correct priority
			BOOST_CHECK(gameRegion->getDrawableCount(0) == drawables.size());
			BOOST_CHECK(gameRegion->getDrawableCount() == drawables.size());

			// Free drawables
			for (int ii = 0; ii < drawables.size(); ii++) {
				delete drawables[ii];
			}
		}

		// Tests adding Drawables to the GameRegion in single with different priorities
		BOOST_AUTO_TEST_CASE(GameRegion_addDrawable_single_differentPriorities) {
			std::unique_ptr<GameRegion> gameRegion = std::make_unique<GameRegion>();
			std::vector<sf::Drawable*> drawables(5);
			std::vector<sf::Drawable*> drawables2(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				drawables[ii] = new sf::Sprite();
				gameRegion->addDrawable(0, drawables[ii]);
			}
			for (int ii = 0; ii < drawables2.size(); ii++) {
				drawables2[ii] = new sf::Sprite();
				gameRegion->addDrawable(1, drawables2[ii]);
			}

			// Check that the drawables were added and at the correct priority
			BOOST_CHECK(gameRegion->getDrawableCount(0) == drawables.size());
			BOOST_CHECK(gameRegion->getDrawableCount(1) == drawables2.size());
			BOOST_CHECK(gameRegion->getDrawableCount() == drawables.size() + drawables2.size());

			// Free drawables
			for (int ii = 0; ii < drawables.size(); ii++) {
				delete drawables[ii];
			}
			for (int ii = 0; ii < drawables2.size(); ii++) {
				delete drawables2[ii];
			}
		}

		// Tests adding Drawables to the GameRegion in single with nullptr
		BOOST_AUTO_TEST_CASE(GameRegion_addDrawable_single_nullptr) {
			std::unique_ptr<GameRegion> gameRegion = std::make_unique<GameRegion>();
			std::vector<sf::Drawable*> drawables(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				// Check that addDrawables throws std::invalid_argument if any Drawables are nullptr
				BOOST_CHECK_THROW(gameRegion->addDrawable(0, drawables.begin(), drawables.end()), std::invalid_argument);
			}

			// Check that nothing was added during the add
			BOOST_CHECK(gameRegion->getDrawableCount(0) == 0);
			BOOST_CHECK(gameRegion->getDrawableCount() == 0);
		}

		// Tests adding Drawables to the GameRegion in single but overwriting in the same priority
		BOOST_AUTO_TEST_CASE(GameRegion_addDrawable_single_overwrite_samePriority) {
			std::unique_ptr<GameRegion> gameRegion = std::make_unique<GameRegion>();
			std::vector<sf::Drawable*> drawables(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				drawables[ii] = new sf::Sprite();
				gameRegion->addDrawable(0, drawables[ii]);
				gameRegion->addDrawable(0, drawables[ii]);
			}

			// Check that the drawables were only added one time
			BOOST_CHECK(gameRegion->getDrawableCount(0) == drawables.size());
			BOOST_CHECK(gameRegion->getDrawableCount() == drawables.size());

			// Free drawables
			for (int ii = 0; ii < drawables.size(); ii++) {
				delete drawables[ii];
			}
		}

		// Tests adding Drawables to the GameRegion in single but overwriting in the different priority
		BOOST_AUTO_TEST_CASE(GameRegion_addDrawable_single_overwrite_differentPriority) {
			std::unique_ptr<GameRegion> gameRegion = std::make_unique<GameRegion>();
			std::vector<sf::Drawable*> drawables(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				drawables[ii] = new sf::Sprite();
				gameRegion->addDrawable(0, drawables[ii]);
				gameRegion->addDrawable(1, drawables[ii]);
			}

			// Check that the drawables were only added one time and at the latter priority
			BOOST_CHECK(gameRegion->getDrawableCount(0) == 0);
			BOOST_CHECK(gameRegion->getDrawableCount(1) == drawables.size());
			BOOST_CHECK(gameRegion->getDrawableCount() == drawables.size());

			// Free drawables
			for (int ii = 0; ii < drawables.size(); ii++) {
				delete drawables[ii];
			}
		}

	BOOST_AUTO_TEST_SUITE_END() // end GameRegion_addDrawable_tests

	BOOST_AUTO_TEST_SUITE(GameRegion_removeDrawable_tests)

		// Tests remove Drawables to the GameRegion in bulk
		BOOST_AUTO_TEST_CASE(GameRegion_removeDrawable_bulk) {
			std::unique_ptr<GameRegion> gameRegion = std::make_unique<GameRegion>();
			std::vector<sf::Drawable*> drawables(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				drawables[ii] = new sf::Sprite();
			}

			gameRegion->addDrawable(0, drawables.begin(), drawables.end());
			gameRegion->removeDrawable(drawables.begin(), drawables.end());

			// Check that the drawables were removed and at the correct priority
			BOOST_CHECK(gameRegion->getDrawableCount(0) == 0);
			BOOST_CHECK(gameRegion->getDrawableCount() == 0);

			// Free drawables
			for (int ii = 0; ii < drawables.size(); ii++) {
				delete drawables[ii];
			}
		}

		// Tests removing Drawables from the GameRegion in bulk but not removing all of them
		BOOST_AUTO_TEST_CASE(GameRegion_removeDrawable_bulk_notRemoveAll) {
			std::unique_ptr<GameRegion> gameRegion = std::make_unique<GameRegion>();
			std::vector<sf::Drawable*> drawables(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				drawables[ii] = new sf::Sprite();
			}

			gameRegion->addDrawable(0, drawables.begin(), drawables.end());

			// Only remove two of the drawables
			std::vector<sf::Drawable*> deleteDrawables{ drawables[0], drawables[1] };
			gameRegion->removeDrawable(deleteDrawables.begin(), deleteDrawables.end());

			// Check that the drawables were removed and at the correct priority
			BOOST_CHECK(gameRegion->getDrawableCount(0) == drawables.size() - deleteDrawables.size());
			BOOST_CHECK(gameRegion->getDrawableCount() == drawables.size() - deleteDrawables.size());

			// Free drawables
			for (int ii = 0; ii < drawables.size(); ii++) {
				delete drawables[ii];
			}
		}

		// Tests removing Drawables from the GameRegion in bulk with nullptr
		BOOST_AUTO_TEST_CASE(GameRegion_removeDrawable_bulk_nullptr) {
			std::unique_ptr<GameRegion> gameRegion = std::make_unique<GameRegion>();
			std::vector<sf::Drawable*> drawables(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				drawables[ii] = new sf::Sprite();
			}

			gameRegion->addDrawable(0, drawables.begin(), drawables.end());

			std::vector<sf::Drawable*> nullDrawables(5);
			gameRegion->removeDrawable(nullDrawables.begin(),nullDrawables.end());

			// Check that nothing was added during the add
			BOOST_CHECK(gameRegion->getDrawableCount(0) == drawables.size());
			BOOST_CHECK(gameRegion->getDrawableCount() == drawables.size());

			// Free drawables
			for (int ii = 0; ii < drawables.size(); ii++) {
				delete drawables[ii];
			}
		}

		// Tests removing Drawables to the GameRegion in single
		BOOST_AUTO_TEST_CASE(GameRegion_removeDrawable_single) {
			std::unique_ptr<GameRegion> gameRegion = std::make_unique<GameRegion>();
			std::vector<sf::Drawable*> drawables(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				drawables[ii] = new sf::Sprite();
				gameRegion->addDrawable(0, drawables[ii]);
				gameRegion->removeDrawable(drawables[ii]);
			}

			gameRegion->addDrawable(0, drawables.begin(), drawables.end());
			gameRegion->removeDrawable(drawables.begin(), drawables.end());

			// Check that the drawables were removed and at the correct priority
			BOOST_CHECK(gameRegion->getDrawableCount(0) == 0);
			BOOST_CHECK(gameRegion->getDrawableCount() == 0);

			// Free drawables
			for (int ii = 0; ii < drawables.size(); ii++) {
				delete drawables[ii];
			}
		}

		// Tests removing Drawables from the GameRegion in single but not removing all of them
		BOOST_AUTO_TEST_CASE(GameRegion_removeDrawable_single_notRemoveAll) {
			std::unique_ptr<GameRegion> gameRegion = std::make_unique<GameRegion>();
			std::vector<sf::Drawable*> drawables(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				drawables[ii] = new sf::Sprite();
			}

			gameRegion->addDrawable(0, drawables.begin(), drawables.end());

			// Only remove two of the drawables
			std::vector<sf::Drawable*> deleteDrawables{ drawables[0], drawables[1] }; 
			for (int ii = 0; ii < deleteDrawables.size(); ii++) {
				gameRegion->removeDrawable(deleteDrawables[ii]);
			}

			// Check that the drawables were removed and at the correct priority
			BOOST_CHECK(gameRegion->getDrawableCount(0) == drawables.size() - deleteDrawables.size());
			BOOST_CHECK(gameRegion->getDrawableCount() == drawables.size() - deleteDrawables.size());

			// Free drawables
			for (int ii = 0; ii < drawables.size(); ii++) {
				delete drawables[ii];
			}
		}

		// Tests removing Drawables from the GameRegion in single with nullptr
		BOOST_AUTO_TEST_CASE(GameRegion_removeDrawable_single_nullptr) {
			std::unique_ptr<GameRegion> gameRegion = std::make_unique<GameRegion>();
			std::vector<sf::Drawable*> drawables(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				drawables[ii] = new sf::Sprite();
			}

			gameRegion->addDrawable(0, drawables.begin(), drawables.end());

			std::vector<sf::Drawable*> nullDrawables(5);
			for (int ii = 0; ii < nullDrawables.size(); ii++) {
				gameRegion->removeDrawable(nullDrawables[ii]);
			}

			// Check that nothing was added during the add
			BOOST_CHECK(gameRegion->getDrawableCount(0) == drawables.size());
			BOOST_CHECK(gameRegion->getDrawableCount() == drawables.size());

			// Free drawables
			for (int ii = 0; ii < drawables.size(); ii++) {
				delete drawables[ii];
			}
		}

	BOOST_AUTO_TEST_SUITE_END() // end GameRegion_removeDrawable_tests

	BOOST_AUTO_TEST_SUITE(GameRegion_clearDrawables_tests)

		// Tests clearing Drawables to the GameRegion
		BOOST_AUTO_TEST_CASE(GameRegion_clearDrawables) {
			std::unique_ptr<GameRegion> gameRegion = std::make_unique<GameRegion>();
			std::vector<sf::Drawable*> drawables(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				drawables[ii] = new sf::Sprite();
			}

			gameRegion->addDrawable(0, drawables.begin(), drawables.end());
			gameRegion->clearDrawables();

			// Check that the drawables were cleared and at the correct priority
			BOOST_CHECK(gameRegion->getDrawableCount(0) == 0);
			BOOST_CHECK(gameRegion->getDrawableCount() == 0);

			// Free drawables
			for (int ii = 0; ii < drawables.size(); ii++) {
				delete drawables[ii];
			}
		}

		// Tests clearing Drawables to the GameRegion with priority
		BOOST_AUTO_TEST_CASE(GameRegion_clearDrawables_priority) {
			std::unique_ptr<GameRegion> gameRegion = std::make_unique<GameRegion>();
			std::vector<sf::Drawable*> drawables(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				drawables[ii] = new sf::Sprite();
			}

			gameRegion->addDrawable(0, drawables.begin(), drawables.end());
			gameRegion->clearDrawables(0);

			// Check that the drawables were cleared and at the correct priority
			BOOST_CHECK(gameRegion->getDrawableCount(0) == 0);
			BOOST_CHECK(gameRegion->getDrawableCount() == 0);

			// Free drawables
			for (int ii = 0; ii < drawables.size(); ii++) {
				delete drawables[ii];
			}
		}

		// Tests clearing Drawables to the GameRegion with priority	but not removing those in the different priority
		BOOST_AUTO_TEST_CASE(GameRegion_clearDrawables_priority_notRemoveAll) {
			std::unique_ptr<GameRegion> gameRegion = std::make_unique<GameRegion>();
			std::vector<sf::Drawable*> drawables(5);
			std::vector<sf::Drawable*> drawables2(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				drawables[ii] = new sf::Sprite();
			}
			for (int ii = 0; ii < drawables2.size(); ii++) {
				drawables2[ii] = new sf::Sprite();
			}

			gameRegion->addDrawable(0, drawables.begin(), drawables.end());
			gameRegion->addDrawable(1, drawables2.begin(), drawables2.end());

			gameRegion->clearDrawables(0);

			// Check that the drawables were only cleared at the given priority
			BOOST_CHECK(gameRegion->getDrawableCount(0) == 0);
			BOOST_CHECK(gameRegion->getDrawableCount(1) == drawables2.size());
			BOOST_CHECK(gameRegion->getDrawableCount() == drawables2.size());

			// Free drawables
			for (int ii = 0; ii < drawables.size(); ii++) {
				delete drawables[ii];
			}
			for (int ii = 0; ii < drawables2.size(); ii++) {
				delete drawables2[ii];
			}
		}

	BOOST_AUTO_TEST_SUITE_END() // end GameRegion_clearDrawables_tests

	BOOST_AUTO_TEST_SUITE(GameRegion_add_remove_clear_tests)

		// Tests adding and removing Drawables from the GameRegion
		BOOST_AUTO_TEST_CASE(GameRegion_addDrawables_removeDrawables) {

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

		// Tests adding nullptr with addDrawables
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