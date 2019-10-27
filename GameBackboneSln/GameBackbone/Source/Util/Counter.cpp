#include <GameBackbone/Util/Counter.h>

#include <numeric>

using namespace GB;

Counter::Counter() : Counter(15) {};

Counter::Counter(int bufferSize) :
	m_ticks(bufferSize),
	m_tail(0),
	m_tickCount(0) 
{
}

Counter::TimePoint Counter::tick() {

	TimePoint currentTime = TimePoint::clock::now();

	if (m_tickCount == m_ticks.size()) {
		m_ticks[m_tail] = currentTime;

		m_tail++;

		if (m_tail == m_tickCount) {
			m_tail = 0;
		}
	} else {
		m_ticks[m_tickCount] = currentTime;
		m_tickCount++;
	}

	return currentTime;
}

float Counter::getAverageTimePerTick() {
	return getAverageTimePerTick(m_ticks.size());
}

float Counter::getAverageTimePerTick(std::size_t ticks) {

	float sum = 0;
	forEachElementInBuffer([&sum, ticks]()
	{
		sum++;
		return sum != ticks;
	});

	return sum / ticks;
}

float Counter::getAverageTickRate() {
	return getAverageTickRate(m_ticks.size());
}

float Counter::getAverageTickRate(std::size_t ticks) {
	TimePoint sum;
	std::size_t count = 0;
	forEachElementInBuffer([&sum, ticks, &count, this](std::size_t index) mutable -> bool
	{
		// TODO: find the average of the ticks 
	});

	return 0;
}

std::size_t Counter::getTicksSinceTime(Counter::TimePoint time) {
	return 0;
}

void Counter::forEachElementInBuffer(std::function<bool(std::size_t)> operation) {
	if (m_tickCount > 0) {
		std::size_t counter = m_tail;
		do {
			if (operation(counter))
			{
				if (counter == 0)
				{
					counter = m_tickCount;
				}
				counter--;
			} 
			else
			{
				break;
			}

		} while (counter % m_tickCount != m_tail);
	}
}