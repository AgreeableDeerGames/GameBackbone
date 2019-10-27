#include <GameBackbone/Util/Counter.h>

#include <numeric>
#include <vector>

using namespace GB;

Counter::Counter() : Counter(15) {};

Counter::Counter(std::size_t bufferSize) :
	m_ticks(bufferSize)

{
}

Counter::TimePoint Counter::tick() {

	TimePoint currentTime = TimePoint::clock::now();
	tick(currentTime.time_since_epoch());
	return currentTime;
}

void Counter::tick(Counter::TimePoint::duration elapsedTime)
{
	m_ticks.push_back(elapsedTime);
}

float Counter::getAverageTimePerTick() {
	return getAverageTimePerTick(m_ticks.size());
}

float Counter::getAverageTimePerTick(std::size_t ticks) {
	auto tickSum = std::accumulate(
		m_ticks.begin(),
		m_ticks.begin() + ticks,
		TimePoint::duration::rep{}, 
		[](const TimePoint::duration::rep& lastValue, const TimePoint::duration& tick) {
			return lastValue + tick.count();
		}
	);

	return tickSum / (float)ticks;
}

float Counter::getAverageTickRate() {
	return getAverageTickRate(m_ticks.size());
}

float Counter::getAverageTickRate(std::size_t ticks) {
	return 0;
}

std::size_t Counter::getTicksSinceTime(Counter::TimePoint time) {
	return 0;
}
