#pragma once

#include <GameBackbone/Util/DllUtil.h>

#include <sfml/System/Time.hpp>

#include <chrono>
#include <functional>
#include <memory>
#include <algorithm>
#include <numeric>

namespace GB {

	template <template <class...> class Container>
	class TickCounter {
	public:
		using Ptr = std::shared_ptr<TickCounter>;
		using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
		// using TimePoint = sf::Time;

		TickCounter() : TickCounter(15) {};
		TickCounter(std::size_t bufferSize) :
			m_ticks(bufferSize)
		{
		}

		TimePoint tick()
		{
			TimePoint currentTime = TimePoint::clock::now();
			tick(currentTime.time_since_epoch());
			return currentTime;
		}

		void tick(TimePoint::duration elapsedTime)
		{
			m_ticks.push_back(elapsedTime);
		}

		[[nodiscard]]
		float getAverageTimePerTick()
		{
			return getAverageTimePerTick(m_ticks.size());
		}

		[[nodiscard]]
		float getAverageTimePerTick(std::size_t ticks)
		{
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

		[[nodiscard]]
		float getAverageTickRate()
		{
			return getAverageTickRate(m_ticks.size());
		}

		[[nodiscard]]
		float getAverageTickRate(std::size_t ticks)
		{
			return 0;
		}

		[[nodiscard]]
		std::size_t getTicksSinceTime(TimePoint time)
		{
			return 0;
		}

	private:
		Container<TimePoint::duration> m_ticks;
	};
}