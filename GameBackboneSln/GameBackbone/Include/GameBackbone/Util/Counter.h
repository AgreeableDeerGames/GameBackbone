#pragma once

#include <GameBackbone/Util/DllUtil.h>

#include <sfml/System/Time.hpp>

#include <chrono>
#include <functional>
#include <memory>
#include <vector>

namespace GB {

	class libGameBackbone Counter { // TODO: Rename TickCounter
	public:
		using Ptr = std::shared_ptr<Counter>;
		using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
		// using TimePoint = sf::Time;

		Counter();
		Counter(int bufferSize);

		TimePoint tick();

		[[nodiscard]]
		float getAverageTimePerTick();

		[[nodiscard]]
		float getAverageTimePerTick(std::size_t ticks);

		[[nodiscard]]
		float getAverageTickRate();

		[[nodiscard]]
		float getAverageTickRate(std::size_t ticks);

		[[nodiscard]]
		std::size_t getTicksSinceTime(TimePoint time);

	private:

		void forEachElementInBuffer(std::function<bool(std::size_t)> operation);

		std::vector<TimePoint> m_ticks;
		std::size_t m_tail;
		std::size_t m_tickCount;
	};
}