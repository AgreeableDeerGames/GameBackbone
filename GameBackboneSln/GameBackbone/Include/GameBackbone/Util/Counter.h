#pragma once

#include <GameBackbone/Util/DllUtil.h>

#include <sfml/System/Time.hpp>

#include <boost/circular_buffer.hpp>

#include <chrono>
#include <functional>
#include <memory>

namespace GB {

	class libGameBackbone Counter { // TODO: Rename TickCounter
	public:
		using Ptr = std::shared_ptr<Counter>;
		using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
		// using TimePoint = sf::Time;

		Counter();
		Counter(std::size_t bufferSize);

		TimePoint tick();

		void tick(TimePoint::duration elapsedTime);

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
		boost::circular_buffer<TimePoint::duration> m_ticks;
	};
}