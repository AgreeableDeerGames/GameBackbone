#include "stdafx.h"

#include <GameBackbone/Core/GameRegion.h>

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

using namespace GB;




BOOST_AUTO_TEST_SUITE(GameRegion_Tests)

	class MockDrawable : public sf::Drawable {
	public:
		MockDrawable(std::vector<const sf::Drawable*>& newDrawnVector) : drawnVector(newDrawnVector) {};

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
			drawnVector.push_back(this);
		}

		std::vector<const sf::Drawable*>& drawnVector;
	};

	/// This is used to expose the protected member functions from GameRegion
	class GameRegionChild : public GameRegion
	{
	public:
		using GameRegion::GameRegion;
		using GameRegion::addDrawable;
		using GameRegion::removeDrawable;
		using GameRegion::clearDrawables;
	};

	BOOST_AUTO_TEST_SUITE(GameRegion_CTRs)

		// Tests the default constructor
		BOOST_AUTO_TEST_CASE(GameRegion_default_CTR) {
			GameRegion gameRegion{};
			BOOST_CHECK(gameRegion.getDrawableCount() == 0);
		}

	BOOST_AUTO_TEST_SUITE_END() // end GameRegion_CTRs

	BOOST_AUTO_TEST_SUITE(GameRegion_addDrawable_tests)

		// Tests adding Drawables to the GameRegion
		BOOST_AUTO_TEST_CASE(GameRegion_addDrawable) {
			GameRegionChild gameRegion{};
			std::vector<sf::Sprite> drawables(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				gameRegion.addDrawable(0, drawables[ii]);
			}

			// Check that the drawables were added and at the correct priority
			BOOST_CHECK(gameRegion.getDrawableCount(0) == drawables.size());
			BOOST_CHECK(gameRegion.getDrawableCount() == drawables.size());
		}

		// Tests adding Drawables to the GameRegion with different priorities
		BOOST_AUTO_TEST_CASE(GameRegion_addDrawable_differentPriorities) {
			GameRegionChild gameRegion{};
			std::vector<sf::Sprite> drawables(5);
			std::vector<sf::Sprite> drawables2(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				gameRegion.addDrawable(0, drawables[ii]);
			}
			for (int ii = 0; ii < drawables2.size(); ii++) {
				gameRegion.addDrawable(1, drawables2[ii]);
			}

			// Check that the drawables were added and at the correct priority
			BOOST_CHECK(gameRegion.getDrawableCount(0) == drawables.size());
			BOOST_CHECK(gameRegion.getDrawableCount(1) == drawables2.size());
			BOOST_CHECK(gameRegion.getDrawableCount() == drawables.size() + drawables2.size());
		}

		// Tests adding Drawables to the GameRegion in single but overwriting in the same priority
		BOOST_AUTO_TEST_CASE(GameRegion_addDrawable_overwrite_samePriority) {
			GameRegionChild gameRegion{};
			std::vector<sf::Sprite> drawables(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				gameRegion.addDrawable(0, drawables[ii]);
				gameRegion.addDrawable(0, drawables[ii]);
			}

			// Check that the drawables were only added one time
			BOOST_CHECK(gameRegion.getDrawableCount(0) == drawables.size());
			BOOST_CHECK(gameRegion.getDrawableCount() == drawables.size());
		}

		// Tests adding Drawables to the GameRegion but overwriting in the different priority
		BOOST_AUTO_TEST_CASE(GameRegion_addDrawable_overwrite_differentPriority) {
			GameRegionChild gameRegion{};
			std::vector<sf::Sprite> drawables(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				gameRegion.addDrawable(0, drawables[ii]);
				gameRegion.addDrawable(1, drawables[ii]);
			}

			// Check that the drawables were only added one time and at the latter priority
			BOOST_CHECK(gameRegion.getDrawableCount(0) == 0);
			BOOST_CHECK(gameRegion.getDrawableCount(1) == drawables.size());
			BOOST_CHECK(gameRegion.getDrawableCount() == drawables.size());
		}

	BOOST_AUTO_TEST_SUITE_END() // end GameRegion_addDrawable_tests

	BOOST_AUTO_TEST_SUITE(GameRegion_removeDrawable_tests)
		
		// Tests removing Drawables to the GameRegion
		BOOST_AUTO_TEST_CASE(GameRegion_removeDrawable) {
		GameRegionChild gameRegion{};
			std::vector<sf::Sprite> drawables(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				gameRegion.addDrawable(0, drawables[ii]);
				gameRegion.removeDrawable(drawables[ii]);
			}

			// Check that the drawables were removed and at the correct priority
			BOOST_CHECK(gameRegion.getDrawableCount(0) == 0);
			BOOST_CHECK(gameRegion.getDrawableCount() == 0);
		}

		// Tests removing Drawables from the GameRegion but not removing all of them
		BOOST_AUTO_TEST_CASE(GameRegion_removeDrawable_notRemoveAll) {
			GameRegionChild gameRegion{};
			std::vector<sf::Sprite> drawables(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				gameRegion.addDrawable(0, drawables[ii]);
			}

			// Only remove two of the drawables
			std::vector<sf::Drawable*> deleteDrawables{ &drawables[0], &drawables[1] }; 
			for (int ii = 0; ii < deleteDrawables.size(); ii++) {
				gameRegion.removeDrawable(*deleteDrawables[ii]);
			}

			// Check that the drawables were removed and at the correct priority
			BOOST_CHECK(gameRegion.getDrawableCount(0) == drawables.size() - deleteDrawables.size());
			BOOST_CHECK(gameRegion.getDrawableCount() == drawables.size() - deleteDrawables.size());
		}

	BOOST_AUTO_TEST_SUITE_END() // end GameRegion_removeDrawable_tests

	BOOST_AUTO_TEST_SUITE(GameRegion_clearDrawables_tests)

		// Tests clearing Drawables to the GameRegion
		BOOST_AUTO_TEST_CASE(GameRegion_clearDrawables) {
		GameRegionChild gameRegion{};
			std::vector<sf::Sprite> drawables(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				gameRegion.addDrawable(0, drawables[ii]);
				gameRegion.clearDrawables();
			}

			// Check that the drawables were cleared and at the correct priority
			BOOST_CHECK(gameRegion.getDrawableCount(0) == 0);
			BOOST_CHECK(gameRegion.getDrawableCount() == 0);
		}

		// Tests clearing Drawables to the GameRegion with priority
		BOOST_AUTO_TEST_CASE(GameRegion_clearDrawables_priority) {
			GameRegionChild gameRegion{};
			std::vector<sf::Sprite> drawables(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				gameRegion.addDrawable(0, drawables[ii]);
				gameRegion.clearDrawables(0);
			}

			// Check that the drawables were cleared and at the correct priority
			BOOST_CHECK(gameRegion.getDrawableCount(0) == 0);
			BOOST_CHECK(gameRegion.getDrawableCount() == 0);
		}

		// Tests clearing Drawables to the GameRegion with priority	but not removing those in the different priority
		BOOST_AUTO_TEST_CASE(GameRegion_clearDrawables_priority_notRemoveAll) {
			GameRegionChild gameRegion{};
			std::vector<sf::Sprite> drawables(5);
			std::vector<sf::Sprite> drawables2(5);

			for (int ii = 0; ii < drawables.size(); ii++) {
				gameRegion.addDrawable(0, drawables[ii]);
			}
			for (int ii = 0; ii < drawables2.size(); ii++) {
				gameRegion.addDrawable(1, drawables2[ii]);
			}

			gameRegion.clearDrawables(0);

			// Check that the drawables were only cleared at the given priority
			BOOST_CHECK(gameRegion.getDrawableCount(0) == 0);
			BOOST_CHECK(gameRegion.getDrawableCount(1) == drawables2.size());
			BOOST_CHECK(gameRegion.getDrawableCount() == drawables2.size());
		}

	BOOST_AUTO_TEST_SUITE_END() // end GameRegion_clearDrawables_tests


	BOOST_AUTO_TEST_SUITE(GameRegion_priority_drawing_tests)

		// Tests adding Drawables at different priorities
		BOOST_AUTO_TEST_CASE(GameRegion_setDrawables) {
			sf::RenderWindow window(sf::VideoMode(1, 1), "windowName");
			GameRegionChild gameRegion;

			std::vector<const sf::Drawable*> drawnVector;
			std::vector<MockDrawable> drawableVector(6, MockDrawable{ drawnVector });

			// Add priority 0 drawables
			for (int ii = 0; ii < 2; ii++) {
				gameRegion.addDrawable(0, drawableVector[ii]);
			}

			// Add priority 1 drawables
			for (int ii = 2; ii < 4; ii++) {
				gameRegion.addDrawable(1, drawableVector[ii]);
			}

			// Add priority 2 drawables
			for (int ii = 4; ii < 6; ii++) {
				gameRegion.addDrawable(2, drawableVector[ii]);
			}

			// Call draw on the GameRegion to pass it down to the MockDrawables
			window.draw(gameRegion);

			// Ensure that the vectors contain the same elements, but most importantly, in the same order
			BOOST_CHECK(drawableVector.size() == drawnVector.size());
			for (int ii = 0; ii < drawnVector.size(); ii++)
			{
				BOOST_CHECK(drawnVector[ii] == &drawableVector[ii]);
			}
		}

	BOOST_AUTO_TEST_SUITE_END() // end GameRegion_priority_drawing_tests

BOOST_AUTO_TEST_SUITE_END() // end GameRegion_tests