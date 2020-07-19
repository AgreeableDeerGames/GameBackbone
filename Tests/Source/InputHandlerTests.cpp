#include "stdafx.h"

#include <GameBackbone/Core/GameRegion.h>
#include <GameBackbone/UserInput/InputHandler.h>
#include <GameBackbone/UserInput/InputRouter.h>
#include <GameBackbone/UserInput/ButtonPressGestureHandler.h>
#include <GameBackbone/UserInput/GestureBind.h>
#include <GameBackbone/UserInput/EventComparitor.h>

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
		InputRouter router{ ButtonPressGestureHandler<BasicGestureBind<KeyEventComparitor>>{}, TestInputHandler{} };
		router.handleEvent(1, sf::Event{});

		BasicGestureBind<KeyEventComparitor> bind({ sf::Event{} }, []() {}, BasicGestureBind<KeyEventComparitor>::EndType::Reset, 1);
		bind.processEvent(1, sf::Event{});
	}

	static_assert(is_event_comparitor<KeyEventComparitor>::value, "wat");
	static_assert(is_event_comparitor_v<KeyEventComparitor>, "wat");

BOOST_AUTO_TEST_SUITE_END() // InputHandlerTests
