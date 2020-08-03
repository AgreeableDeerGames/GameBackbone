#include "stdafx.h"

#include <GameBackbone/Core/GameRegion.h>
#include <GameBackbone/UserInput/InputHandler.h>
#include <GameBackbone/UserInput/InputRouter.h>
#include <GameBackbone/UserInput/ButtonPressGestureHandler.h>
#include <GameBackbone/UserInput/GestureBind.h>
#include <GameBackbone/UserInput/EventComparator.h>

using namespace GB;

BOOST_AUTO_TEST_SUITE(InputHandlerTests)

	class TestInputHandler : public InputHandler
	{
	public:
		bool handleEvent(sf::Int64 /*elapsedTime*/, const sf::Event& /*event*/) override
		{
			std::cout << "button hold" << std::endl;
			return true;
		}
	};

	BOOST_AUTO_TEST_CASE(TestCompile)
	{
		InputRouter router{ ButtonPressGestureHandler<BasicGestureBind<KeyEventComparator, AnyEventFilter>>{}, TestInputHandler{} };
		router.handleEvent(1, sf::Event{});

		BasicGestureBind<KeyEventComparator, AnyEventFilter> bind({ sf::Event{} }, []() {}, BasicGestureBind<KeyEventComparator, AnyEventFilter>::EndType::Reset, 1);
		bind.processEvent(1, sf::Event{});
	}

	static_assert(is_event_comparator<KeyEventComparator>::value, "wat");
	static_assert(is_event_comparator_v<KeyEventComparator>, "wat");

BOOST_AUTO_TEST_SUITE_END() // InputHandlerTests
