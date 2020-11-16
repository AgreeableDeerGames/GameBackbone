#include "stdafx.h"

#include <GameBackbone/UserInput/ButtonGestureHandler.h>
#include <GameBackbone/UserInput/InputHandler.h>
#include <GameBackbone/UserInput/InputRouter.h>

#include <array>
#include <functional>

using namespace GB;

BOOST_AUTO_TEST_SUITE(InputRouterTests)

class TestInputHandler : public InputHandler
{
public:
	TestInputHandler(std::function<bool(sf::Int64, const sf::Event&)> callback) :
		m_callback(std::move(callback))
	{
	}
	bool handleEvent(sf::Int64 elapsedTime, const sf::Event& event)
	{
		return std::invoke(m_callback, elapsedTime, event);
	}

	std::function<bool(sf::Int64, const sf::Event&)> m_callback;
};

BOOST_AUTO_TEST_CASE(InputRouterForwardsEventsToStoredInputHandlers)
{
	bool hasRouterReceivedInput = false;
	InputRouter router
	{
		TestInputHandler
		{
			[&](sf::Int64, const sf::Event&)
			{
				hasRouterReceivedInput = true;
				return true;
			}
		}
	};

	router.handleEvent(0, {});
	BOOST_TEST(hasRouterReceivedInput);
}

BOOST_AUTO_TEST_CASE(InputRouterAppliesEventsToStoredHandlersInTheOrderThatTheyWereAdded)
{
	std::array hasRouterRecievedInput{ false, false, false, false };

	// Set up a Router with multiple handlers that never return true.
	// This will ensure that the event is passed to each of them
	InputRouter router
	{
		TestInputHandler
		{
			[&](sf::Int64, const sf::Event&)
			{
				// Nothing should have received input before this
				BOOST_CHECK(!hasRouterRecievedInput[0]);
				BOOST_CHECK(!hasRouterRecievedInput[1]);
				BOOST_CHECK(!hasRouterRecievedInput[2]);
				BOOST_CHECK(!hasRouterRecievedInput[3]);

				hasRouterRecievedInput[0] = true;
				return false;
			}
		},
		TestInputHandler
		{
			[&](sf::Int64, const sf::Event&)
			{
				// Only preceding handlers should have received input before this.
				BOOST_CHECK(hasRouterRecievedInput[0]);
				BOOST_CHECK(!hasRouterRecievedInput[1]);
				BOOST_CHECK(!hasRouterRecievedInput[2]);
				BOOST_CHECK(!hasRouterRecievedInput[3]);

				hasRouterRecievedInput[1] = true;
				return false;
			}
		},
		TestInputHandler
		{
			[&](sf::Int64, const sf::Event&)
			{
				// Only preceding handlers should have received input before this.
				BOOST_CHECK(hasRouterRecievedInput[0]);
				BOOST_CHECK(hasRouterRecievedInput[1]);
				BOOST_CHECK(!hasRouterRecievedInput[2]);
				BOOST_CHECK(!hasRouterRecievedInput[3]);

				hasRouterRecievedInput[2] = true;
				return false;
			}
		},
		TestInputHandler
		{
			[&](sf::Int64, const sf::Event&)
			{
				// Only preceding handlers should have received input before this.
				BOOST_CHECK(hasRouterRecievedInput[0]);
				BOOST_CHECK(hasRouterRecievedInput[1]);
				BOOST_CHECK(hasRouterRecievedInput[2]);
				BOOST_CHECK(!hasRouterRecievedInput[3]);
				hasRouterRecievedInput[3] = true;
				return false;
			}
		}
	};

	// Send an event
	router.handleEvent(0, {});

	// Everything should have received the input
	for (bool recievedInput : hasRouterRecievedInput)
	{
		BOOST_CHECK(recievedInput);
	}
}

BOOST_AUTO_TEST_CASE(InputRouterOnlyAppliesTheSameEventToAHandlerOneTime)
{
	std::array inputCount{ 0, 0, 0, 0 };

	// Set up a Router with multiple handlers that never return true.
	// This will ensure that the event is passed to each of them
	InputRouter router
	{
		TestInputHandler
		{
			[&](sf::Int64, const sf::Event&)
			{
				++inputCount[0];
				return false;
			}
		},
		TestInputHandler
		{
			[&](sf::Int64, const sf::Event&)
			{
				++inputCount[1];
				return false;
			}
		},
		TestInputHandler
		{
			[&](sf::Int64, const sf::Event&)
			{
				++inputCount[2];
				return false;
			}
		},
		TestInputHandler
		{
			[&](sf::Int64, const sf::Event&)
			{
				++inputCount[3];
				return false;
			}
		}
	};

	// Send an event
	router.handleEvent(0, {});

	// Everything should have received the input
	for (int inputCount : inputCount)
	{
		BOOST_CHECK(inputCount == 1);
	}
}

BOOST_AUTO_TEST_CASE(InputRouterStopsTryingToApplyAnEventToItsHandlersAfterAnyHandlerReturnsTrue)
{
	std::array hasRouterRecievedInput{ false, false, false, false };

	// Set up a Router with multiple handlers that never return true.
	// This will ensure that the event is passed to each of them
	InputRouter router
	{
		TestInputHandler
		{
			[&](sf::Int64, const sf::Event&)
			{
				// Nothing should have received input before this
				BOOST_CHECK(!hasRouterRecievedInput[0]);
				BOOST_CHECK(!hasRouterRecievedInput[1]);
				BOOST_CHECK(!hasRouterRecievedInput[2]);
				BOOST_CHECK(!hasRouterRecievedInput[3]);

				hasRouterRecievedInput[0] = true;
				return false;
			}
		},
		TestInputHandler
		{
			[&](sf::Int64, const sf::Event&)
			{				
				BOOST_CHECK(hasRouterRecievedInput[0]);
				BOOST_CHECK(!hasRouterRecievedInput[1]);
				BOOST_CHECK(!hasRouterRecievedInput[2]);
				BOOST_CHECK(!hasRouterRecievedInput[3]);
				hasRouterRecievedInput[1] = true;
				return true;
			}
		},
		TestInputHandler
		{
			[&](sf::Int64, const sf::Event&)
			{
				hasRouterRecievedInput[2] = true;
				return false;
			}
		},
		TestInputHandler
		{
			[&](sf::Int64, const sf::Event&)
			{
				hasRouterRecievedInput[3] = true;
				return false;
			}
		}
	};

	// Send an event
	router.handleEvent(0, {});

	// Only handlers leading to the one that returned true should have been called
	BOOST_CHECK(hasRouterRecievedInput[0]);
	BOOST_CHECK(hasRouterRecievedInput[1]);
	BOOST_CHECK(!hasRouterRecievedInput[2]);
	BOOST_CHECK(!hasRouterRecievedInput[3]);
}

BOOST_AUTO_TEST_CASE(InputRouterKeepsTrackOfTimeBetweenCalls)
{
	std::array inputCount{ 0, 0 };
	std::array elapsedTimeArray{ sf::Int64{0}, sf::Int64{0} };

	// Set up a Router with multiple handlers that never return true.
	// This will ensure that the event is passed to each of them
	InputRouter router
	{
		TestInputHandler
		{
			[&](sf::Int64 elapsedTime, const sf::Event&)
			{
				elapsedTimeArray[0] = elapsedTime;
				++inputCount[0];
				return inputCount[0] % 3 != 0;
			}
		},
		TestInputHandler
		{
			[&](sf::Int64 elapsedTime, const sf::Event&)
			{
				elapsedTimeArray[1] = elapsedTime;
				++inputCount[1];
				return false;
			}
		}
	};

	// Send an event (First handler called)
	router.handleEvent(1, {});
	BOOST_CHECK(elapsedTimeArray[0] == 1);
	BOOST_CHECK(elapsedTimeArray[1] == 0);
	BOOST_CHECK(inputCount[0] == 1);
	BOOST_CHECK(inputCount[1] == 0);

	// Send an event (first handler called)
	router.handleEvent(1, {});
	BOOST_CHECK(elapsedTimeArray[0] == 1);
	BOOST_CHECK(elapsedTimeArray[1] == 0);
	BOOST_CHECK(inputCount[0] == 2);
	BOOST_CHECK(inputCount[1] == 0);

	// Send an event (now the second handle should actually be called)
	router.handleEvent(1, {});
	BOOST_CHECK(elapsedTimeArray[0] == 1);
	BOOST_CHECK(elapsedTimeArray[1] == 3);
	BOOST_CHECK(inputCount[0] == 3);
	BOOST_CHECK(inputCount[1] == 1);
}

class TestReferenceInputHandler : public InputHandler
{
public:

	bool handleEvent(sf::Int64 elapsedTime, const sf::Event& event)
	{
		m_hasHandledEvent = true;
		return true;
	}
	bool m_hasHandledEvent = false;
};

BOOST_AUTO_TEST_CASE(InputRouterCanStoreDifferentTypesOfInputHandlers)
{
	// Create a lvalue reference input handler to pass to InputRouter
	TestReferenceInputHandler testHandler;
	TestReferenceInputHandler& testHandlerRef = testHandler;

	// Create an input router holding many different types of input handlers
	InputRouter router
	{
		testHandlerRef, // Copy!
		TestInputHandler
		{
			[&](sf::Int64, const sf::Event&)
			{
				return true;
			}
		},
		KeyboardGestureHandler{},
		JoystickButtonGestureHandler{},
		AnyButtonGestureHandler{},
		MouseButtonGestureHandler{}
	};

	router.handleEvent(0, {});

	// InputRouter has made a copy. It owns all of its InputHandlers
	// so the member variable on the external testHandler was not set.
	BOOST_TEST(!testHandler.m_hasHandledEvent);
}


BOOST_AUTO_TEST_SUITE_END() // InputRouterTests

