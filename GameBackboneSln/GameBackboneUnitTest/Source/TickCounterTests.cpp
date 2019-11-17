#include "stdafx.h"

#include <GameBackbone/Util/TickCounter.h>

#include <vector>

using namespace GB;

BOOST_AUTO_TEST_SUITE(TickCounter_Tests)

BOOST_AUTO_TEST_CASE(TickCounter_averageTimePerTick_test)
{
	TickCounter<std::vector> counter(5);
	counter.tick();
	counter.tick();
	counter.tick();
	counter.tick();
	counter.tick();
	auto result = counter.getAverageTimePerTick();
}

BOOST_AUTO_TEST_CASE(TickCounter_averageTimePerTick_test_with_specific_times)
{
	TickCounter<std::vector> counter(5);
	counter.tick(std::chrono::nanoseconds(5));
	counter.tick(std::chrono::nanoseconds(4));
	counter.tick(std::chrono::nanoseconds(6));
	counter.tick(std::chrono::nanoseconds(5));
	counter.tick(std::chrono::nanoseconds(4));
	counter.tick(std::chrono::nanoseconds(6));
	auto result = counter.getAverageTimePerTick();
	BOOST_CHECK_CLOSE_FRACTION(result, 5, 0.1);
}

BOOST_AUTO_TEST_SUITE_END() // TickCounter_Tests