#include "stdafx.h"

#include <GameBackbone/UserInput/ButtonPressGestureHandler.h>
#include <GameBackbone/UserInput/EventComparitor.h>
#include <GameBackbone/UserInput/GestureBind.h>

using namespace GB;

BOOST_AUTO_TEST_SUITE(ButtonPressGestureHandlerTests)

	struct InputHandlerConsumeEventFixture
	{
		InputHandlerConsumeEventFixture()
		{
			upPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Up, false, false, false, false };
			upPressed.type = sf::Event::KeyPressed;
	
			downPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Down, false, false, false, false };
			downPressed.type = sf::Event::KeyPressed;
	
			upReleased.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Up, false, false, false, false };
			upReleased.type = sf::Event::KeyReleased;
	
			downReleased.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Down, false, false, false, false };
			downReleased.type = sf::Event::KeyReleased;

			aPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::A, false, false, false, false };
			aPressed.type = sf::Event::KeyPressed;

			bPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::B, false, false, false, false };
			bPressed.type = sf::Event::KeyPressed;

			cPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::C, false, false, false, false };
			cPressed.type = sf::Event::KeyPressed;

			dPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::D, false, false, false, false };
			dPressed.type = sf::Event::KeyPressed;

			ePressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::E, false, false, false, false };
			ePressed.type = sf::Event::KeyPressed;

			wPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::W, false, false, false, false };
			wPressed.type = sf::Event::KeyPressed;
		}
	
		using TestGestureBind = BasicGestureBind<KeyEventComparitor>;

		// Event for gesture
		sf::Event upPressed = {};
		sf::Event downPressed = {};
		sf::Event upReleased = {};
		sf::Event downReleased = {};

		sf::Event aPressed = {};
		sf::Event bPressed = {};
		sf::Event cPressed = {};
		sf::Event dPressed = {};
		sf::Event ePressed = {};
		sf::Event wPressed = {};
	
		// Create handler
		int gesture1Count = 0;
		int gesture2Count = 0;

		// ButtonPressGestureHandler<BasicGestureBind<MouseButtonEventComparitor>> handler;
		ButtonPressGestureHandler<TestGestureBind> handler;
	};

	struct GestureAccessorFixture : InputHandlerConsumeEventFixture
	{
		GestureAccessorFixture()
		{
			// Prepare a set of gestures with unique sizes
			for (int i = 0; i < gestureCount; ++i)
			{
				std::vector<sf::Event> rawGesture;
				for (int j = 0; j < i; ++j)
				{
					rawGesture.push_back(upPressed);
				}

				inputGestures.push_back(
					TestGestureBind(
						rawGesture,
						[] {},
						TestGestureBind::EndType::Block,
						10));
			}
		}
		const std::size_t gestureCount = 5;
		std::vector<TestGestureBind> inputGestures;
	};

	BOOST_AUTO_TEST_SUITE(HandleEventResults)

		BOOST_FIXTURE_TEST_CASE(HandleEventFalseWhenNoGesturesAreBound, InputHandlerConsumeEventFixture)
		{
			BOOST_TEST(!handler.handleEvent(0, upPressed));
		}

		BOOST_FIXTURE_TEST_CASE(HandleEventReturnsTrueWhenEventMatchesGesture, InputHandlerConsumeEventFixture)
		{
			TestGestureBind bind({ upPressed, upPressed }, []() {});

			handler.addGesture(bind);
			BOOST_TEST(handler.handleEvent(0, upPressed));
		}

		BOOST_FIXTURE_TEST_CASE(HandleEventReturnsFalseWhenEventDoesNotMatchGesture, InputHandlerConsumeEventFixture)
		{
			TestGestureBind bind({ upPressed, upPressed }, []() {});

			handler.addGesture(bind);
			BOOST_TEST(!handler.handleEvent(0, downPressed));
		}

		BOOST_FIXTURE_TEST_CASE(CompletingGestureFiresAction, InputHandlerConsumeEventFixture)
		{
			bool actionFired = false;
			TestGestureBind bind({ upPressed }, [&actionFired]() { actionFired = true; });

			handler.addGesture(bind);
			handler.handleEvent(0, upPressed);
			BOOST_TEST(actionFired == true);
		}

		BOOST_FIXTURE_TEST_CASE(UnboundEventDoesNotFireAction, InputHandlerConsumeEventFixture)
		{
			bool actionFired = false;
			TestGestureBind bind({ upPressed }, [&actionFired]() { actionFired = true; });

			handler.handleEvent(0, downPressed);
			BOOST_TEST(actionFired == false);
		}

		BOOST_FIXTURE_TEST_CASE(CompletingGestureFiresActionForMultiInputGesture, InputHandlerConsumeEventFixture)
		{
			bool actionFired = false;
			TestGestureBind bind({ upPressed, upPressed, downPressed, downPressed }, [&actionFired]() { actionFired = true; });

			handler.addGesture(bind);
			handler.handleEvent(0, upPressed);
			BOOST_TEST(actionFired == false);
			handler.handleEvent(0, upPressed);
			BOOST_TEST(actionFired == false);
			handler.handleEvent(0, downPressed);
			BOOST_TEST(actionFired == false);
			handler.handleEvent(0, downPressed);

			BOOST_TEST(actionFired == true);
		}

		BOOST_FIXTURE_TEST_CASE(CompletingGestureFiresCorrectActionWithMultipleGesturesBound, InputHandlerConsumeEventFixture)
		{
			bool correctActionFired = false;
			bool wrongActionFired = false;

			TestGestureBind bind({ upPressed }, [&correctActionFired]() { correctActionFired = true; });
			TestGestureBind bind2( { downPressed }, [&wrongActionFired]() { wrongActionFired = true; });

			handler.addGesture(bind);
			handler.addGesture(bind2);
			handler.handleEvent(0, upPressed);
			BOOST_TEST(correctActionFired == true);
			BOOST_TEST(wrongActionFired == false);
		}

		BOOST_FIXTURE_TEST_CASE(GestureDoesNotCompleteWhenTimeExpires, InputHandlerConsumeEventFixture)
		{
			bool actionFired = false;

			TestGestureBind bind({ upPressed, upPressed }, [&actionFired]() { actionFired = true; }, TestGestureBind::EndType::Block, 10);

			handler.addGesture(bind);
			handler.handleEvent(0, upPressed);
			handler.handleEvent(20, upPressed);
			BOOST_TEST(actionFired == false);
		}

		BOOST_FIXTURE_TEST_CASE(GestureCanRestartAfterTimeExpires, InputHandlerConsumeEventFixture)
		{
			bool actionFired = false;

			TestGestureBind bind({ upPressed, upPressed }, [&actionFired]() { actionFired = true; }, TestGestureBind::EndType::Block, 10);

			handler.addGesture(bind);
			handler.handleEvent(0, upPressed);

			// This fails the first attempt at the gesture, but starts the second one
			handler.handleEvent(20, upPressed);
			BOOST_TEST(actionFired == false);

			// This finishes the second attempt at the gesture
			handler.handleEvent(0, upPressed);
			BOOST_TEST(actionFired == true);
		}

	BOOST_AUTO_TEST_SUITE_END() // HandleEventResults

	BOOST_AUTO_TEST_SUITE(GestureAccess)

		BOOST_FIXTURE_TEST_CASE(AddGestureReturnsReferenceToAddedgesture, GestureAccessorFixture)
		{

			BOOST_CHECK(handler.getGestureCount() == 0);
			auto& outGesture = handler.addGesture(inputGestures[0]);

			// Each gesture has a unique size. Use this to verify that they match
			BOOST_CHECK(outGesture.getGesture().size() == inputGestures[0].getGesture().size());
		}


		BOOST_FIXTURE_TEST_CASE(IterationReturnsGesturesInTheOrderThatTheyWereAdded, GestureAccessorFixture)
		{

			for (const auto& gesture : inputGestures)
			{
				handler.addGesture(gesture);
			}

			// Iterate over the gestures in the handler and verify that they match
			// the input gestures and are in the correct order.
			BOOST_CHECK(handler.getGestureCount() == inputGestures.size());
			std::size_t iteration = 0;
			for (auto& gesture : handler)
			{
				// Each gesture has a unique size. Use this to verify that they match
				BOOST_CHECK(gesture.getGesture().size() == inputGestures[iteration].getGesture().size());
				++iteration;
			}
		}

		BOOST_FIXTURE_TEST_CASE(IterationWithConstHandlerReturnsGesturesInTheOrderThatTheyWereAdded, GestureAccessorFixture)
		{
			for (const auto& gesture : inputGestures)
			{
				handler.addGesture(gesture);
			}

			// Make the handler const to test const iteration
			const auto constHandler = const_cast<const ButtonPressGestureHandler<TestGestureBind>&>(handler);

			// Iterate over the gestures in the handler and verify that they match
			// the input gestures and are in the correct order.
			BOOST_CHECK(constHandler.getGestureCount() == inputGestures.size());
			std::size_t iteration = 0;
			for (auto& gesture : constHandler)
			{
				// Each gesture has a unique size. Use this to verify that they match
				BOOST_CHECK(gesture.getGesture().size() == inputGestures[iteration].getGesture().size());
				++iteration;
			}
		}

		BOOST_FIXTURE_TEST_CASE(IterationWithConstHandlerReturnsGesturesInTheOrderThatTheyWereAddedUsingCBeginAndCEnd, GestureAccessorFixture)
		{
			for (const auto& gesture : inputGestures)
			{
				handler.addGesture(gesture);
			}

			// Make the handler const to test const iteration
			const auto constHandler = const_cast<const ButtonPressGestureHandler<TestGestureBind>&>(handler);

			// Iterate over the gestures in the handler and verify that they match
			// the input gestures and are in the correct order.
			BOOST_CHECK(constHandler.getGestureCount() == inputGestures.size());
			std::size_t iteration = 0;
			for (auto it = constHandler.cbegin(); it != constHandler.cend(); ++it)
			{
				// Each gesture has a unique size. Use this to verify that they match
				BOOST_CHECK(it->getGesture().size() == inputGestures[iteration].getGesture().size());
				++iteration;
			}
		}

		BOOST_FIXTURE_TEST_CASE(GetGestureReturnsCorrectGestureWhenRequestedPositionIsWithinBounds, GestureAccessorFixture)
		{

			for (const auto& gesture : inputGestures)
			{
				handler.addGesture(gesture);
			}

			// Verify that the gestures are the same by checking the sizes
			for (int i = 0; i < gestureCount; ++i)
			{
				BOOST_CHECK(handler.getGesture(i).getGesture().size() == inputGestures[i].getGesture().size());
			}

			// Verify that the gestures are the same by checking the sizes with a const handler
			const auto constHandler = const_cast<const ButtonPressGestureHandler<TestGestureBind>&>(handler);
			for (int i = 0; i < gestureCount; ++i)
			{
				BOOST_CHECK(constHandler.getGesture(i).getGesture().size() == inputGestures[i].getGesture().size());
			}
		}

		BOOST_FIXTURE_TEST_CASE(GetGestureThrowsOutOfRangeExceptionWhenRequestedPositionIsNotWithinBounds, GestureAccessorFixture)
		{

			for (const auto& gesture : inputGestures)
			{
				handler.addGesture(gesture);
			}

			// Verify that the gestures are the same by checking the sizes
			BOOST_CHECK_THROW(handler.getGesture(gestureCount), std::out_of_range);

			// Verify that the gestures are the same by checking the sizes with a const handler
			const auto constHandler = const_cast<const ButtonPressGestureHandler<TestGestureBind>&>(handler);
			BOOST_CHECK_THROW(constHandler.getGesture(gestureCount), std::out_of_range);
		}

		BOOST_FIXTURE_TEST_CASE(RemoveGestureRemovesCorrectGestureWhenRequestedPositionIsWithinBounds, GestureAccessorFixture)
		{
			for (const auto& gesture : inputGestures)
			{
				handler.addGesture(gesture);
			}

			// remove the same element from the handler and the inputGestures vector
			std::size_t elementToErase = 2;
			handler.removeGesture(elementToErase);
			inputGestures.erase(inputGestures.begin() + elementToErase);
			BOOST_CHECK(handler.getGestureCount() == inputGestures.size());

			// Verify that the gestures are the same by checking the sizes
			for (int i = 0; i < handler.getGestureCount(); ++i)
			{
				BOOST_CHECK(handler.getGesture(i).getGesture().size() == inputGestures[i].getGesture().size());
			}
		}

		BOOST_FIXTURE_TEST_CASE(RemoveGestureThrowsOutOfRangeExceptionWhenRequestedPositionIsNotWithinBounds, GestureAccessorFixture)
		{

			for (const auto& gesture : inputGestures)
			{
				handler.addGesture(gesture);
			}

			// remove the same element from the handler and the inputGestures vector
			std::size_t elementToErase = gestureCount;
			BOOST_CHECK_THROW(handler.removeGesture(elementToErase), std::out_of_range);
			elementToErase = gestureCount + 1;
			BOOST_CHECK_THROW(handler.removeGesture(elementToErase), std::out_of_range);
		
		}

		BOOST_FIXTURE_TEST_CASE(GetGestureCountMaintainsCorrectCount, GestureAccessorFixture)
		{
			// Count should be zero before anything is added to it
			int count = 0;
			BOOST_TEST(handler.getGestureCount() == count);

			// Count should go up with each gesture added
			for (const auto& gesture : inputGestures)
			{
				handler.addGesture(gesture);
				++count;
				BOOST_TEST(handler.getGestureCount() == count);

			}

			// Count should go down after removing gesture
			handler.removeGesture(0);
			--count;
			BOOST_TEST(handler.getGestureCount() == count);
		}

	BOOST_AUTO_TEST_SUITE_END() // GestureAccess

	BOOST_AUTO_TEST_SUITE(GestureIOCases)

		/*
		 *	# Case 1
		 * 
		 *	|     gesture       | bound action |
		 *	|       :----:      | :----:       |
		 *	|  a -> b -> c ->d  | Action 1     |
		 *	|         e         | Action 2     |
		 *
		 *  User inputs:
		 *  `a -> b -> c -> e`
		 *  
		 *  Result:
		 *  Action 2 is fired
		 */
		BOOST_FIXTURE_TEST_CASE(Case1, InputHandlerConsumeEventFixture)
		{
			bool correctActionFired = false;
			bool wrongActionFired = false;

			TestGestureBind bind({ aPressed, bPressed, cPressed, dPressed }, [&wrongActionFired]() { wrongActionFired = true; });
			TestGestureBind bind2({ ePressed }, [&correctActionFired]() { correctActionFired = true; });

			handler.addGesture(bind);
			handler.addGesture(bind2);
			handler.handleEvent(0, aPressed);
			handler.handleEvent(0, bPressed);
			handler.handleEvent(0, cPressed);
			handler.handleEvent(0, ePressed);
			BOOST_TEST(correctActionFired == true);
			BOOST_TEST(wrongActionFired == false);
		}

		/*
		 *  # Case 2
		 * 
		 *  |  gesture | bound action |
		 *	|  :----:  |    :----:    |
		 *	|  a -> b  |    Action 1  |
		 *	|     c    |    Action 2  |
		 *
		 * 	User inputs:
		 *	`a -> b -> c -> a -> b`
		 * 
		 *  Result:
		 *  Action 1 Fires
		 *  Action 2 Fires
		 *  Action 1 Fires
		 */
		BOOST_FIXTURE_TEST_CASE(Case2, InputHandlerConsumeEventFixture)
		{
			int action1Fired = 0;
			int action2Fired = 0;

			TestGestureBind bind({ aPressed, bPressed }, [&action1Fired]() { ++action1Fired; });
			TestGestureBind bind2({ cPressed }, [&action2Fired]() { ++action2Fired; });

			handler.addGesture(bind);
			handler.addGesture(bind2);

			// Action 1 should fire
			handler.handleEvent(0, aPressed);
			handler.handleEvent(0, bPressed);
			BOOST_TEST(action1Fired == 1);

			// Action 2 should fire
			handler.handleEvent(0, cPressed);
			BOOST_TEST(action2Fired == 1);

			// Action 1 should fire again
			handler.handleEvent(0, aPressed);
			handler.handleEvent(0, bPressed);

			// Make sure final counts are correct
			BOOST_TEST(action1Fired == 2);
			BOOST_TEST(action2Fired == 1);
		}

		/*
		 *  # Case 3
		 *
		 *  |   gesture    |   bound action   |   End Type  |
		 *  |    :----:    |      :----:      |    :---:    |
		 *  |      w       |     Action 1     |    Block    |
		 *  |    w -> w    |     Action 2     |    Block    |
		 *  | w -> w -> w  |     Action 3     |    Block    |
		 *
		 *
		 *  User Inputs
		 *  `w -> w -> w`
		 *
		 *  Result:
		 *  Action 1 fires
		 *  Action 2 fires
		 *  Action 3 fires
		 */
		BOOST_FIXTURE_TEST_CASE(Case3, InputHandlerConsumeEventFixture)
		{
			int action1Fired = 0;
			int action2Fired = 0;
			int action3Fired = 0;

			TestGestureBind bind({ wPressed }, [&action1Fired]() { ++action1Fired; });
			TestGestureBind bind2({ wPressed, wPressed }, [&action2Fired]() { ++action2Fired; });
			TestGestureBind bind3({ wPressed, wPressed, wPressed }, [&action3Fired]() { ++action3Fired; });

			handler.addGesture(bind);
			handler.addGesture(bind2);
			handler.addGesture(bind3);

			handler.handleEvent(0, wPressed);
			BOOST_CHECK(action1Fired == 1);
			BOOST_CHECK(action2Fired == 0);
			BOOST_CHECK(action3Fired == 0);
			handler.handleEvent(0, wPressed);
			BOOST_CHECK(action1Fired == 1);
			BOOST_CHECK(action2Fired == 1);
			BOOST_CHECK(action3Fired == 0);
			handler.handleEvent(0, wPressed);
			BOOST_CHECK(action1Fired == 1);
			BOOST_CHECK(action2Fired == 1);
			BOOST_CHECK(action3Fired == 1);
		}

		/*
		 *  # Case 3.1
		 *  
		 *  |    gesture   | bound action |  End Type  |
		 *  |    :----:    |    :----:    |    :---:   |
		 *  |      w       |   Action 1   | Continuous |
		 *  |    w -> w    |   Action 2   | Continuous |
		 *  | w -> w -> w  |   Action 3   | Continuous |
		 *  
		 *  User Inputs
		 *  `w -> w -> w`
		 *  
		 *  Result:
		 *  Action 1 fires
		 *  Action 1 fires
		 *  Action 2 fires
		 *  Action 1 fires
		 *  Action 2 fires
		 *  Action 3 fires
		 */
		BOOST_FIXTURE_TEST_CASE(Case3_1, InputHandlerConsumeEventFixture)
		{
			int action1Fired = 0;
			int action2Fired = 0;
			int action3Fired = 0;

			TestGestureBind bind({ wPressed }, [&action1Fired]() { ++action1Fired; }, TestGestureBind::EndType::Continuous);
			TestGestureBind bind2({ wPressed, wPressed }, [&action2Fired]() { ++action2Fired; }, TestGestureBind::EndType::Continuous);
			TestGestureBind bind3({ wPressed, wPressed, wPressed }, [&action3Fired]() { ++action3Fired; }, TestGestureBind::EndType::Continuous);

			handler.addGesture(bind);
			handler.addGesture(bind2);
			handler.addGesture(bind3);

			handler.handleEvent(0, wPressed);
			BOOST_CHECK(action1Fired == 1);
			BOOST_CHECK(action2Fired == 0);
			BOOST_CHECK(action3Fired == 0);
			handler.handleEvent(0, wPressed);
			BOOST_CHECK(action1Fired == 2);
			BOOST_CHECK(action2Fired == 1);
			BOOST_CHECK(action3Fired == 0);
			handler.handleEvent(0, wPressed);
			BOOST_CHECK(action1Fired == 3);
			BOOST_CHECK(action2Fired == 2);
			BOOST_CHECK(action3Fired == 1);
		}

		/*
		 *  # Case 3.2
		 *  
		 *  |   gesture    | bound action  | End Type |
		 *  |    :----:    |    :----:     |   :---:  |
		 *  |      w       |    Action 1   |   Block   |
		 *  |    w -> w    |    Action 2   |   Reset  |
		 *  | w -> w -> w  |    Action 3   |   Reset  |
		 *  
		 *  User Inputs
		 *  `w -> w -> w -> w -> w`
		 *  	
		 *  Result:
		 *  Action 1 fires
		 *  Action 2 fires
		 *  Action 3 fires
		 *  Action 2 fires
		 */
		BOOST_FIXTURE_TEST_CASE(Case3_2, InputHandlerConsumeEventFixture)
		{
			int action1Fired = 0;
			int action2Fired = 0;
			int action3Fired = 0;

			TestGestureBind bind({ wPressed }, [&action1Fired]() { ++action1Fired; }, TestGestureBind::EndType::Block);
			TestGestureBind bind2({ wPressed, wPressed }, [&action2Fired]() { ++action2Fired; }, TestGestureBind::EndType::Reset);
			TestGestureBind bind3({ wPressed, wPressed, wPressed }, [&action3Fired]() { ++action3Fired; }, TestGestureBind::EndType::Reset);

			handler.addGesture(bind);
			handler.addGesture(bind2);
			handler.addGesture(bind3);

			handler.handleEvent(0, wPressed);
			BOOST_CHECK(action1Fired == 1);
			BOOST_CHECK(action2Fired == 0);
			BOOST_CHECK(action3Fired == 0);

			handler.handleEvent(0, wPressed);
			BOOST_CHECK(action1Fired == 1);
			BOOST_CHECK(action2Fired == 1);
			BOOST_CHECK(action3Fired == 0);

			handler.handleEvent(0, wPressed);
			BOOST_CHECK(action1Fired == 1);
			BOOST_CHECK(action2Fired == 1);
			BOOST_CHECK(action3Fired == 1);

			handler.handleEvent(0, wPressed);
			BOOST_CHECK(action1Fired == 1);
			BOOST_CHECK(action2Fired == 2);
			BOOST_CHECK(action3Fired == 1);

			handler.handleEvent(0, wPressed);
			BOOST_CHECK(action1Fired == 1);
			BOOST_CHECK(action2Fired == 2);
			BOOST_CHECK(action3Fired == 1);

		}

		/*
		 *  # Case 4
		 *  |      gesture      | bound action |
		 *  |       :----:      |     :----:   |
		 *  |  a -> b -> c ->d  |   Action 1   |
		 *  |         d         |   Action 2   |
		 *  
		 *  User inputs:
		 *  `a -> b -> c -> d`
		 *  
		 *  Result:
		 *  Action 1 fires
		 *  Action 2 does NOT fire
		 */
		BOOST_FIXTURE_TEST_CASE(Case4, InputHandlerConsumeEventFixture)
		{
			int action1Fired = 0;
			int action2Fired = 0;

			TestGestureBind bind({ aPressed, bPressed, cPressed, dPressed }, [&action1Fired]() { ++action1Fired; });
			TestGestureBind bind2({ dPressed }, [&action2Fired]() { ++action2Fired; });

			handler.addGesture(bind);
			handler.addGesture(bind2);

			handler.handleEvent(0, aPressed);
			BOOST_CHECK(action1Fired == 0);
			BOOST_CHECK(action2Fired == 0);

			handler.handleEvent(0, bPressed);
			BOOST_CHECK(action1Fired == 0);
			BOOST_CHECK(action2Fired == 0);

			handler.handleEvent(0, cPressed);
			BOOST_CHECK(action1Fired == 0);
			BOOST_CHECK(action2Fired == 0);

			handler.handleEvent(0, dPressed);
			BOOST_CHECK(action1Fired == 1);
			BOOST_CHECK(action2Fired == 0);
		}

		/*
		 *  # Case 5
		 *  |    gesture    | bound action |
		 *  |     :----:    |    :----:    |
		 *  |  a -> b -> c  |   Action 1   |
		 *  
		 *  User inputs:
		 *  `a -> b -> a -> b -> c`
		 *  
		 *  Result:
		 *  Action 1 fires 1 time
		 */
		BOOST_FIXTURE_TEST_CASE(Case5, InputHandlerConsumeEventFixture)
		{
			int action1Fired = 0;

			TestGestureBind bind({ aPressed, bPressed, cPressed }, [&action1Fired]() { ++action1Fired; });

			handler.addGesture(bind);

			handler.handleEvent(0, aPressed);
			BOOST_CHECK(action1Fired == 0);

			handler.handleEvent(0, bPressed);
			BOOST_CHECK(action1Fired == 0);

			handler.handleEvent(0, aPressed);
			BOOST_CHECK(action1Fired == 0);

			handler.handleEvent(0, bPressed);
			BOOST_CHECK(action1Fired == 0);

			handler.handleEvent(0, cPressed);
			BOOST_CHECK(action1Fired == 1);
		}

		/*
		 *  # Case 5.1
		 *  |     gesture    | bound action |
		 *  |     :----:     |    :----:    |
		 *  |  a -> b -> c   |   Action 1   |
		 *  |       a        |   Action 2   |
		 *  
		 *  User inputs:
		 *  `a -> a -> b -> c`
		 *  
		 *  Result:
		 *  Action 2 fires n times, Action 1 fires 1 time
		 */
		BOOST_FIXTURE_TEST_CASE(Case5_1, InputHandlerConsumeEventFixture)
		{
			int action1Fired = 0;
			int action2Fired = 0;

			TestGestureBind bind({ aPressed, bPressed, cPressed }, [&action1Fired]() { ++action1Fired; });
			TestGestureBind bind2({ aPressed }, [&action2Fired]() { ++action2Fired; });

			handler.addGesture(bind);
			handler.addGesture(bind2);

			handler.handleEvent(0, aPressed);
			BOOST_CHECK(action1Fired == 0);
			BOOST_CHECK(action2Fired == 1);

			handler.handleEvent(0, aPressed);
			BOOST_CHECK(action1Fired == 0);
			BOOST_CHECK(action2Fired == 2);

			handler.handleEvent(0, bPressed);
			BOOST_CHECK(action1Fired == 0);
			BOOST_CHECK(action2Fired == 2);

			handler.handleEvent(0, cPressed);
			BOOST_CHECK(action1Fired == 1);
			BOOST_CHECK(action2Fired == 2);
		}

		/*
		 *  
		 *  # Case 5.2
		 *  |     gesture    | bound action |
		 *  |     :----:     |    :----:    |
		 *  |  a -> b -> c   |   Action 1   |
		 *  |     a  -> b    |   Action 2   |
		 *  
		 *  User inputs:
		 *  `a -> a -> b -> c`
		 *  
		 *  Result:
		 *  Action 2 fires 1 time, Action 1 fires 1 time
		 */
		BOOST_FIXTURE_TEST_CASE(Case5_2, InputHandlerConsumeEventFixture)
		{
			int action1Fired = 0;
			int action2Fired = 0;

			TestGestureBind bind({ aPressed, bPressed, cPressed }, [&action1Fired]() { ++action1Fired; });
			TestGestureBind bind2({ aPressed, bPressed }, [&action2Fired]() { ++action2Fired; });

			handler.addGesture(bind);
			handler.addGesture(bind2);

			handler.handleEvent(0, aPressed);
			BOOST_CHECK(action1Fired == 0);
			BOOST_CHECK(action2Fired == 0);

			handler.handleEvent(0, aPressed);
			BOOST_CHECK(action1Fired == 0);
			BOOST_CHECK(action2Fired == 0);

			handler.handleEvent(0, bPressed);
			BOOST_CHECK(action1Fired == 0);
			BOOST_CHECK(action2Fired == 1);

			handler.handleEvent(0, cPressed);
			BOOST_CHECK(action1Fired == 1);
			BOOST_CHECK(action2Fired == 1);
		}

	BOOST_AUTO_TEST_SUITE_END() // GestureIOCases

BOOST_AUTO_TEST_SUITE_END() // ButtonPressGestureHandlerTests
