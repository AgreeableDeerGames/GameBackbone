#include "stdafx.h"
#include <GameBackbone/UserInput/GestureMatchSignaler.h>
#include <GameBackbone/UserInput/EventComparator.h>

using namespace GB;

BOOST_AUTO_TEST_SUITE(GestureMatchSignalerTests)

	// Assert For type traits
	struct AlwaysTrueEventComparator
	{
		bool operator()(const sf::Event&, const sf::Event&) { return true; }
	};
	static_assert(is_event_comparator_v<AlwaysTrueEventComparator>, "GestureMatchSignalerTests SimpleEventComparator does not meet EventComparator requirements");
	static_assert(is_gesture_match_signaler_v<GestureMatchSignaler<AlwaysTrueEventComparator, AnyEventFilter>>, "GestureMatchSignaler does not meet GestureMatchSignalerType requirements");
	static_assert(!is_gesture_match_signaler_v<int>, "int is not a GestureMatchSignalerType");
	struct GestureMatchSignalerWithWrongSignature
	{
		int processEvent(sf::Int64, const sf::Event&) { return true; }
	};
	static_assert(!is_gesture_match_signaler_v<GestureMatchSignalerWithWrongSignature>, "GestureMatchSignalerType type trait failed to check for return value");

	// Gesture Bind type for easy testing
	using TestMatchSignaler = GestureMatchSignaler<AlwaysTrueEventComparator, AnyEventFilter>;

	struct SFEventFixture
	{
		SFEventFixture()
		{
			// Keys
			upPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Up, false, false, false, false };
			upPressed.type = sf::Event::KeyPressed;

			downPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Down, false, false, false, false };
			downPressed.type = sf::Event::KeyPressed;

			upReleased.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Up, false, false, false, false };
			upReleased.type = sf::Event::KeyReleased;

			downReleased.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Down, false, false, false, false };
			downReleased.type = sf::Event::KeyReleased;

			// Mouse
			mouseButton1Pressed.mouseButton = sf::Event::MouseButtonEvent();
			mouseButton1Pressed.mouseButton.button = sf::Mouse::Button::Left;
			mouseButton1Pressed.type = sf::Event::MouseButtonPressed;

			mouseButton1Released.mouseButton = sf::Event::MouseButtonEvent();
			mouseButton1Released.mouseButton.button = sf::Mouse::Button::Left;
			mouseButton1Released.type = sf::Event::MouseButtonReleased;

			// Joystick
			joystickButton1Pressed.joystickButton = sf::Event::JoystickButtonEvent();
			joystickButton1Pressed.joystickButton.button = sf::Joystick::R;
			joystickButton1Pressed.type = sf::Event::JoystickButtonPressed;

			joystickButton1Released.joystickButton = sf::Event::JoystickButtonEvent();
			joystickButton1Released.joystickButton.button = sf::Joystick::R;
			joystickButton1Released.type = sf::Event::JoystickButtonReleased;
		}

		// Keys
		sf::Event upPressed = {};
		sf::Event downPressed = {};
		sf::Event upReleased = {};
		sf::Event downReleased = {};

		// Mouse
		sf::Event mouseButton1Pressed = {};
		sf::Event mouseButton1Released = {};

		// Joystick
		sf::Event joystickButton1Pressed = {};
		sf::Event joystickButton1Released = {};

	};

	BOOST_AUTO_TEST_SUITE(Construction)

		BOOST_AUTO_TEST_CASE(TestFullySpecifiedConstructor)
	{
		sf::Event upPressed = {};
		sf::Event downPressed = {};
		upPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Up, false, false, false, false };
		upPressed.type = sf::Event::KeyPressed;

		downPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Down, false, false, false, false };
		downPressed.type = sf::Event::KeyPressed;

		bool actionFired = false;

		std::vector<sf::Event> gesture{ upPressed, downPressed };
		TestMatchSignaler::EndType gestureMatchSignalerEndType = TestMatchSignaler::EndType::Block;
		sf::Int64 maxTimeBetweenEvents = 20;
		TestMatchSignaler bind(gesture, [&actionFired]() { actionFired = true; }, gestureMatchSignalerEndType, maxTimeBetweenEvents);

		// Check that the gesture was correctly stored
		bool identicalGestures = true;
		for (std::size_t i = 0; i < gesture.size() && i < bind.getGesture().size(); ++i)
		{
			if (gesture[i].key.code != bind.getGesture().at(i).key.code)
			{
				identicalGestures = false;
				break;
			}
		}
		BOOST_TEST(identicalGestures);

		// Check that name was correctly set
		BOOST_CHECK(bind.getEndType() == gestureMatchSignalerEndType);

		// Check that time between inputs is correct
		BOOST_CHECK(bind.getMaxTimeBetweenInputs() == maxTimeBetweenEvents);

		// Check that the bound function is the expected one by running it
		std::invoke(bind.getAction());
		BOOST_CHECK(actionFired);
	}

		BOOST_AUTO_TEST_CASE(TestConstructorWithGestureActionAndEndType)
		{
			sf::Event upPressed = {};
			sf::Event downPressed = {};
			upPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Up, false, false, false, false };
			upPressed.type = sf::Event::KeyPressed;

			downPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Down, false, false, false, false };
			downPressed.type = sf::Event::KeyPressed;

			bool actionFired = false;

			std::vector<sf::Event> gesture{ upPressed, downPressed };
			TestMatchSignaler::EndType gestureMatchSignalerEndType = TestMatchSignaler::EndType::Block;
			TestMatchSignaler bind(gesture, [&actionFired]() { actionFired = true; }, gestureMatchSignalerEndType);

			// Check that the gesture was correctly stored
			bool identicalGestures = true;
			for (std::size_t i = 0; i < gesture.size() && i < bind.getGesture().size(); ++i)
			{
				if (gesture[i].key.code != bind.getGesture().at(i).key.code)
				{
					identicalGestures = false;
					break;
				}
			}
			BOOST_TEST(identicalGestures);

			// Check that name was correctly set
			BOOST_CHECK(bind.getEndType() == gestureMatchSignalerEndType);

			// Check that time between inputs is correct
			BOOST_CHECK(bind.getMaxTimeBetweenInputs() == TestMatchSignaler::defaultMaxTimeBetweenInputs);

			// Check that the bound function is the expected one by running it
			std::invoke(bind.getAction());
			BOOST_CHECK(actionFired);
		}

		BOOST_AUTO_TEST_CASE(TestConstructorWithGestureAndAction)
		{
			sf::Event upPressed = {};
			sf::Event downPressed = {};
			upPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Up, false, false, false, false };
			upPressed.type = sf::Event::KeyPressed;

			downPressed.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Down, false, false, false, false };
			downPressed.type = sf::Event::KeyPressed;

			bool actionFired = false;

			std::vector<sf::Event> gesture{ upPressed, downPressed };
			TestMatchSignaler bind(gesture, [&actionFired]() { actionFired = true; });

			// Check that the gesture was correctly stored
			bool identicalGestures = true;
			for (std::size_t i = 0; i < gesture.size() && i < bind.getGesture().size(); ++i)
			{
				if (gesture[i].key.code != bind.getGesture().at(i).key.code)
				{
					identicalGestures = false;
					break;
				}
			}
			BOOST_TEST(identicalGestures);

			// Check that name was correctly set
			BOOST_CHECK(bind.getEndType() == TestMatchSignaler::EndType::Block);

			// Check that time between inputs is correct
			BOOST_CHECK(bind.getMaxTimeBetweenInputs() == TestMatchSignaler::defaultMaxTimeBetweenInputs);

			// Check that the bound function is the expected one by running it
			std::invoke(bind.getAction());
			BOOST_CHECK(actionFired);
		}


		struct EventCompareNoDefaultCtr
		{
			EventCompareNoDefaultCtr(int) {}
			bool operator()(const sf::Event&, const sf::Event&) { return true; }
		};

		struct FilterNoDefaultCtr
		{
			FilterNoDefaultCtr(int) {}
			bool operator()(const sf::Event&) { return true; }
		};

		BOOST_AUTO_TEST_CASE(TestConstructionCompareAndFilterHaveNoDefaultConstructor)
		{
			// Just check that this compiles and runs with no issue
			using Gesture = GestureMatchSignaler<EventCompareNoDefaultCtr, FilterNoDefaultCtr>;
			Gesture gesture(
				{},
				[] {},
				Gesture::EndType::Block,
				0,
				EventCompareNoDefaultCtr{ 0 },
				FilterNoDefaultCtr{ 0 });

			gesture.processEvent(0, {});
		}

	BOOST_AUTO_TEST_SUITE_END() // Construction

	BOOST_AUTO_TEST_SUITE(SpecializationTests)

		BOOST_FIXTURE_TEST_CASE(TestKeyboardGestureMatchSignaler, SFEventFixture)
		{
			KeyDownMatchSignaler bind({ upPressed, downPressed }, [] {});
			auto result = bind.processEvent(0, upPressed);
			BOOST_TEST(result.inputConsumed);
			bind.reset();

			result = bind.processEvent(0, upReleased);
			BOOST_TEST(!result.inputConsumed);
			BOOST_TEST(result.isReadyForInput);
			bind.reset();

			result = bind.processEvent(0, mouseButton1Pressed);
			BOOST_TEST(!result.inputConsumed);
			BOOST_TEST(result.isReadyForInput);
		}

		BOOST_FIXTURE_TEST_CASE(TestJoystickGestureMatchSignaler, SFEventFixture)
		{
			JoystickButtonDownMatchSignaler bind({ joystickButton1Pressed }, [] {});
			auto result = bind.processEvent(0, joystickButton1Pressed);
			BOOST_TEST(result.inputConsumed);
			bind.reset();

			result = bind.processEvent(0, joystickButton1Released);
			BOOST_TEST(!result.inputConsumed);
			BOOST_TEST(result.isReadyForInput);
			bind.reset();

			result = bind.processEvent(0, mouseButton1Pressed);
			BOOST_TEST(!result.inputConsumed);
			BOOST_TEST(result.isReadyForInput);
		}

		BOOST_FIXTURE_TEST_CASE(TestMouseButtonGestureMatchSignaler, SFEventFixture)
		{
			MouseButtonDownMatchSignaler bind({ mouseButton1Pressed }, [] {});
			auto result = bind.processEvent(0, mouseButton1Pressed);
			BOOST_TEST(result.inputConsumed);
			bind.reset();

			result = bind.processEvent(0, mouseButton1Released);
			BOOST_TEST(!result.inputConsumed);
			BOOST_TEST(result.isReadyForInput);
			bind.reset();

			result = bind.processEvent(0, upPressed);
			BOOST_TEST(!result.inputConsumed);
			BOOST_TEST(result.isReadyForInput);
		}

		BOOST_FIXTURE_TEST_CASE(TestButtonGestureMatchSignaler, SFEventFixture)
		{
			ButtonDownMatchSignaler bind({ mouseButton1Pressed, joystickButton1Pressed, mouseButton1Pressed }, [] {});
			auto result = bind.processEvent(0, mouseButton1Pressed);
			BOOST_TEST(result.inputConsumed);
			result = bind.processEvent(0, joystickButton1Pressed);
			BOOST_TEST(result.inputConsumed);
			result = bind.processEvent(0, mouseButton1Pressed);
			BOOST_TEST(result.inputConsumed);
			bind.reset();

			result = bind.processEvent(0, mouseButton1Released);
			BOOST_TEST(!result.inputConsumed);
			BOOST_TEST(result.isReadyForInput);
			bind.reset();

			result = bind.processEvent(0, upReleased);
			BOOST_TEST(!result.inputConsumed);
			BOOST_TEST(result.isReadyForInput);
		}
	
	BOOST_AUTO_TEST_SUITE_END() //SpecializationTests
	
	BOOST_AUTO_TEST_SUITE(GetSet)

		BOOST_FIXTURE_TEST_CASE(AccessAndMutateGestureEvents, SFEventFixture)
		{
			std::vector eventVec{ upPressed, downPressed };
			TestMatchSignaler gesture(eventVec, [] {});
			auto gestureEvents = gesture.getGesture();
			BOOST_CHECK(eventVec.size() == gestureEvents.size());
			for (std::size_t i = 0; i < eventVec.size(); ++i)
			{
				BOOST_CHECK(ButtonEventComparator{}(eventVec[i], gestureEvents[i]));
			}
			
			// Modify then recheck events
			eventVec.push_back(upPressed);
			gesture.setGesture(eventVec);
			gestureEvents = gesture.getGesture();
			BOOST_CHECK(eventVec.size() == gestureEvents.size());
			for (std::size_t i = 0; i < eventVec.size(); ++i)
			{
				BOOST_CHECK(ButtonEventComparator{}(eventVec[i], gestureEvents[i]));
			}
		}

		struct UniqueAction
		{
			UniqueAction(int& output): m_instanceId(s_instanceId++), m_output(output)
			{
			}

			UniqueAction(const UniqueAction& other) : 
				m_instanceId(s_instanceId++), 
				m_output(other.m_output)
			{
			}

			UniqueAction(UniqueAction&&  other) noexcept :
				m_instanceId(s_instanceId++),
				m_output(other.m_output)
			{
			}

			UniqueAction& operator= (const UniqueAction& other) = delete;
			UniqueAction& operator= (UniqueAction&& other) = delete;

			void operator()()
			{
				m_output = m_instanceId;
			}

			inline static int s_instanceId = 0;
			int m_instanceId;
			int& m_output;
		};

		BOOST_FIXTURE_TEST_CASE(GetActionReturnsTheInstanceOfTheActionThatIsOwnedByTheBind, SFEventFixture)
		{
			std::vector eventVec{ upPressed};
			int id = 0;
			TestMatchSignaler gesture(eventVec, UniqueAction(id));

			// Get the event to fire and set the inId
			auto result = gesture.processEvent(0, upPressed);
			BOOST_TEST(result.actionFired);
			int inId = id;

			// Invoke the returned gesture output to get it to set the ID
			id = 0;
			auto& gestureAction = gesture.getAction();
			gestureAction();

			// Check that the Id is identical
			BOOST_TEST(id == inId);
		}

		BOOST_FIXTURE_TEST_CASE(AccessAndMutateEndType, SFEventFixture)
		{
			// Check initial end type
			std::vector eventVec{ upPressed, downPressed };
			TestMatchSignaler::EndType initialEndType = TestMatchSignaler::EndType::Block;
			TestMatchSignaler gesture(eventVec, [] {}, initialEndType);
			bool equalEndTypes = gesture.getEndType() == initialEndType;
			BOOST_TEST(equalEndTypes);

			// Set and check new end type
			TestMatchSignaler::EndType newEndType = TestMatchSignaler::EndType::Reset;
			gesture.setEndType(newEndType);
			equalEndTypes = gesture.getEndType() == newEndType;
			BOOST_TEST(equalEndTypes);
		}

		BOOST_FIXTURE_TEST_CASE(AccessAndMutateMaxTimeBetweenInputs, SFEventFixture)
		{
			// Check initial value
			std::vector eventVec{ upPressed, downPressed };
			sf::Int64 maxTime = 10;
			TestMatchSignaler gesture(eventVec, [] {}, TestMatchSignaler::EndType::Block, maxTime);
			BOOST_TEST(gesture.getMaxTimeBetweenInputs() == maxTime);

			// Set and check new value
			sf::Int64 newMaxTime = 100;
			gesture.setMaxTimeBetweenInputs(newMaxTime);
			BOOST_TEST(gesture.getMaxTimeBetweenInputs() == newMaxTime);
		}

		BOOST_FIXTURE_TEST_CASE(AccessAndMutateAction, SFEventFixture)
		{
			// setup
			std::vector eventVec{ upPressed, downPressed };
			bool action1Fired;
			TestMatchSignaler gesture(eventVec, [&] { action1Fired = true; });

			// Get and fire the action
			gesture.getAction()();
			BOOST_TEST(action1Fired);

			// Set and check new action
			bool action2Fired = false;
			gesture.setAction([&] { action2Fired = true; });
			gesture.getAction()();
			BOOST_TEST(action2Fired);
		}

	BOOST_AUTO_TEST_SUITE_END() // GetSet

	BOOST_AUTO_TEST_SUITE(ProcessEventTests)

		BOOST_AUTO_TEST_CASE(TestEmptyGestureMatchSignalerIgnoresInput)
		{
			TestMatchSignaler bind({}, [] {});
			auto [actionFired, isReadyForInput, inputConsumed] = bind.processEvent(0, {});
			BOOST_CHECK(!actionFired);
			BOOST_CHECK(!isReadyForInput);
			BOOST_CHECK(!inputConsumed);
		}

		BOOST_AUTO_TEST_CASE(TestEmptyGestureIsNotReadyForInput)
		{
			TestMatchSignaler bind({}, [] {});
			BOOST_CHECK(!bind.isReadyForInput());
		}

		BOOST_FIXTURE_TEST_CASE(ResetMakesTheGestureMatchSignalerReadyToHandleInputAgain, SFEventFixture)
		{
			std::vector eventVec{ upPressed };
			KeyDownMatchSignaler gesture(eventVec, [&] {});

			// Process an incorrect event to disable the gesture
			auto result = gesture.processEvent(0, downPressed);
			BOOST_TEST(!result.isReadyForInput);

			// Reset the gesture
			gesture.reset();

			// Check that the gesture is ready for input now
			BOOST_TEST(gesture.isReadyForInput());
		}

		BOOST_FIXTURE_TEST_CASE(ProcessEventDoesNotFireActionWhenGestureIsNotComplete, SFEventFixture)
		{
			std::vector eventVec{ upPressed, downPressed };
			bool actionFired = false;
			TestMatchSignaler gesture( eventVec, [&] { actionFired = true; });

			// Process part of the gesture
			GestureMatchSignalerProcessEventResult result = gesture.processEvent(0, upPressed);
			BOOST_TEST(!result.actionFired);
			BOOST_TEST(result.inputConsumed);
			BOOST_TEST(result.isReadyForInput);

			// Check that the gesture has not fired
			BOOST_TEST(!actionFired);
		}

		BOOST_FIXTURE_TEST_CASE(ProcessEventFiresActionWhenGestureIsComplete, SFEventFixture)
		{
			std::vector eventVec{ upPressed, downPressed };
			bool actionFired = false;
			TestMatchSignaler gesture(eventVec, [&] { actionFired = true; }, TestMatchSignaler::EndType::Block);

			// Process part of the gesture
			gesture.processEvent(0, upPressed);
			GestureMatchSignalerProcessEventResult result = gesture.processEvent(0, downPressed);
			BOOST_TEST(result.actionFired);
			BOOST_TEST(result.inputConsumed);
			BOOST_TEST(!result.isReadyForInput);

			// Check that the gesture has not fired
			BOOST_TEST(actionFired);
		}

		BOOST_FIXTURE_TEST_CASE(ProcessEventDoesNotConsumeInputWhenNotReadyForInput, SFEventFixture)
		{
			using Gesture = GestureMatchSignaler<ButtonEventComparator, AnyButtonDownEventFilter>;
			std::vector eventVec{ upPressed };
			Gesture gesture(eventVec, [&] {});

			// Process an incorrect event to disable the gesture
			auto result = gesture.processEvent(0, downPressed);
			BOOST_TEST(!result.isReadyForInput);

			// Send the correct event
			result = gesture.processEvent(0, upPressed);

			// Check that the event was not consumed since the gesture is not ready for input
			BOOST_TEST(!result.isReadyForInput);
			BOOST_TEST(!result.inputConsumed);
			BOOST_TEST(!result.actionFired);
		}

		BOOST_FIXTURE_TEST_CASE(ProcessEventDoesNotConsumeInputWhenInputDoesNotPassFilter, SFEventFixture)
		{
			using Gesture = GestureMatchSignaler<ButtonEventComparator, KeyDownEventFilter>;
			std::vector eventVec{ upPressed };
			Gesture gesture(eventVec, [&] {});

			// Process an incorrect event to disable the gesture
			auto result = gesture.processEvent(0, mouseButton1Pressed);

			// Check that the event was not consumed since the event did not pass the filter
			BOOST_TEST(result.isReadyForInput);
			BOOST_TEST(!result.inputConsumed);
			BOOST_TEST(!result.actionFired);
		}

		BOOST_FIXTURE_TEST_CASE(BasicGestureMatchSignalerIsUnreadyToHandleInputAfterProcessingEventThatIsntPartOfTheGesture, SFEventFixture)
		{
			using Gesture = GestureMatchSignaler<ButtonEventComparator, AnyButtonDownEventFilter>;
			std::vector eventVec{ upPressed };
			Gesture gesture(eventVec, [&] {});

			// Process an incorrect event to disable the gesture
			auto result = gesture.processEvent(0, downPressed);
			BOOST_TEST(!result.isReadyForInput);
			BOOST_TEST(!result.inputConsumed);
			BOOST_TEST(!result.actionFired);
		}

		BOOST_FIXTURE_TEST_CASE(BasicGestureMatchSignalerIsUnreadyToHandleInputAfterTheMaxTimeBetweenInputsHasElapsed, SFEventFixture)
		{
			using Gesture = GestureMatchSignaler<ButtonEventComparator, AnyButtonDownEventFilter>;
			std::vector eventVec{ upPressed, downPressed };
			Gesture gesture(eventVec, [&] {}, Gesture::EndType::Block, 5);

			// Process a the first event
			auto result = gesture.processEvent(0, upPressed);
			BOOST_TEST(result.isReadyForInput);
			BOOST_TEST(result.inputConsumed);
			BOOST_TEST(!result.actionFired);

			// Process a the second event after too much time
			result = gesture.processEvent(6, downPressed);
			BOOST_TEST(!result.isReadyForInput);
			BOOST_TEST(!result.inputConsumed);
			BOOST_TEST(!result.actionFired);
		}

	BOOST_AUTO_TEST_SUITE_END() // ProcessEventTests

	BOOST_AUTO_TEST_SUITE(EndTypeTests)

		BOOST_FIXTURE_TEST_CASE(GestureMatchSignalerResetsAfterFiringWithEndTypeReset, SFEventFixture)
		{
			std::vector eventVec{ upPressed, downPressed };
			int actionFiredCount = 0;
			KeyDownMatchSignaler gesture(eventVec, [&] { ++actionFiredCount; }, KeyDownMatchSignaler::EndType::Reset);

			// Process the gesture
			 gesture.processEvent(0, upPressed);
			 GestureMatchSignalerProcessEventResult result = gesture.processEvent(0, downPressed);
			BOOST_TEST(result.actionFired);
			BOOST_TEST(result.inputConsumed);
			BOOST_TEST(result.isReadyForInput);

			// Check that the gesture has fired the correct number of times
			BOOST_TEST(actionFiredCount == 1);

			// Process the gesture again
			result = gesture.processEvent(0, upPressed);
			BOOST_TEST(!result.actionFired);
			BOOST_TEST(result.inputConsumed);
			BOOST_TEST(result.isReadyForInput);

			result = gesture.processEvent(0, downPressed);
			BOOST_TEST(result.actionFired);
			BOOST_TEST(result.inputConsumed);
			BOOST_TEST(result.isReadyForInput);

			// Check that the gesture has fired the correct number of times
			BOOST_TEST(actionFiredCount == 2);
		}

		BOOST_FIXTURE_TEST_CASE(GestureMatchSignalerAcceptsContinuousInputOfLastEventAfterFiringIfEndTypeIsContinuous, SFEventFixture)
		{
			std::vector eventVec{ upPressed, downPressed };
			int actionFiredCount = 0;
			KeyDownMatchSignaler gesture(eventVec, [&] { ++actionFiredCount; }, KeyDownMatchSignaler::EndType::Continuous);

			// Process the gesture
			gesture.processEvent(0, upPressed);
			GestureMatchSignalerProcessEventResult result = gesture.processEvent(0, downPressed);
			BOOST_TEST(result.actionFired);
			BOOST_TEST(result.inputConsumed);
			BOOST_TEST(result.isReadyForInput);

			// Check that the gesture has fired the correct number of times
			BOOST_TEST(actionFiredCount == 1);

			// Process the last event of the gesture again
			result = gesture.processEvent(0, downPressed);
			BOOST_TEST(result.actionFired);
			BOOST_TEST(result.inputConsumed);
			BOOST_TEST(result.isReadyForInput);

			// Check that the gesture has fired the correct number of times
			BOOST_TEST(actionFiredCount == 2);
		}

		BOOST_FIXTURE_TEST_CASE(GestureMatchSignalerDoesNotAcceptRestartingGestureAfterFiringIfEndTypeIsContinuous, SFEventFixture)
		{
			std::vector eventVec{ upPressed, downPressed };
			int actionFiredCount = 0;
			KeyDownMatchSignaler gesture(eventVec, [&] { ++actionFiredCount; }, KeyDownMatchSignaler::EndType::Continuous);

			// Process the gesture
			gesture.processEvent(0, upPressed);
			GestureMatchSignalerProcessEventResult result = gesture.processEvent(0, downPressed);
			BOOST_TEST(result.actionFired);
			BOOST_TEST(result.inputConsumed);
			BOOST_TEST(result.isReadyForInput);

			// Check that the gesture has fired the correct number of times
			BOOST_TEST(actionFiredCount == 1);

			// Process the first event of the gesture again
			result = gesture.processEvent(0, upPressed);
			BOOST_TEST(!result.actionFired);
			BOOST_TEST(!result.inputConsumed);
			BOOST_TEST(!result.isReadyForInput);

			// Check that the gesture has fired the correct number of times
			BOOST_TEST(actionFiredCount == 1);
		}

		BOOST_FIXTURE_TEST_CASE(GestureMatchSignalerStopsAcceptingInputAfterFiringIfEndTypeIsBlock, SFEventFixture)
		{
			std::vector eventVec{ upPressed, downPressed };
			int actionFiredCount = 0;
			KeyDownMatchSignaler gesture(eventVec, [&] { ++actionFiredCount; }, KeyDownMatchSignaler::EndType::Block);

			// Process the gesture
			gesture.processEvent(0, upPressed);
			GestureMatchSignalerProcessEventResult result = gesture.processEvent(0, downPressed);
			BOOST_TEST(result.actionFired);
			BOOST_TEST(result.inputConsumed);
			BOOST_TEST(!result.isReadyForInput);

			// Check that the gesture has fired the correct number of times
			BOOST_TEST(actionFiredCount == 1);

			// Process the last event of the gesture again
			result = gesture.processEvent(0, downPressed);
			BOOST_TEST(!result.actionFired);
			BOOST_TEST(!result.inputConsumed);
			BOOST_TEST(!result.isReadyForInput);

			// Check that the gesture has fired the correct number of times
			BOOST_TEST(actionFiredCount == 1);
		}

	BOOST_AUTO_TEST_SUITE_END() // EndTypeTests

BOOST_AUTO_TEST_SUITE_END() // GestureMatchSignalerTests