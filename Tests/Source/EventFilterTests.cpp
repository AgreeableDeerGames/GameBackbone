#include "stdafx.h"

#include <GameBackbone/UserInput/EventFilter.h>


using namespace GB;

BOOST_AUTO_TEST_SUITE(EventFilterTests)

BOOST_AUTO_TEST_CASE(TestCompile)
{
	KeyDownEventFilter{};
	KeyUpEventFilter{};
	AnyKeyEventFilter{};
	MouseButtonDownEventFilter{};
	MouseButtonUpEventFilter{};
	AnyMouseButtonEventFilter{};
	JoystickButtonDownEventFilter{};
	JoystickButtonUpEventFilter{};
	AnyJoystickButtonEventFilter{};
	AnyButtonDownEventFilter{};
	AnyButtonUpEventFilter{};
}

BOOST_AUTO_TEST_SUITE_END() // EventFilterTests
