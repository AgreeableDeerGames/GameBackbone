#include "stdafx.h"

#include <GameBackbone/UserInput/GestureBind.h>
#include <GameBackbone/UserInput/EventComparitor.h>

using namespace GB;

BOOST_AUTO_TEST_SUITE(GestureBindTests)

	// Assert For type traits
	struct SimpleEventComparitor
	{
		bool operator()(const sf::Event&, const sf::Event&) { return true; }
	};
	static_assert(is_event_comparitor_v<SimpleEventComparitor>, "GestureBindTests SimpleEventComparitor does not meet EventComparitor requirements");
	static_assert(is_gesture_bind_v<BasicGestureBind<SimpleEventComparitor>>, "BasicGestureBind does not meet GestureBind requirements");
	

	BOOST_AUTO_TEST_CASE(testCompile)
	{
		using GBind = BasicGestureBind<SimpleEventComparitor>;

		GBind bind({}, []() {}, "", 0, GBind::EndType::Block);
		bind.processEvent(sf::Int64{}, sf::Event{});
		static_assert(detail::supports_gesture_bind_process_event<GBind>::value);
	}

BOOST_AUTO_TEST_SUITE_END() // GestureBindTests