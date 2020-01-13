#pragma once

#include <GameBackbone/Core/BasicGameRegion.h>

namespace GB {
	class ActivationProvider
	{
	public:
		ActivationProvider() = default;
		virtual ~ActivationProvider() = default;

		void registerActiveRegion(BasicGameRegion& regionToAdd)
		{
			regionToAdd.setActivationProvider(*this);
			m_activeRegion = &regionToAdd;
		}

		BasicGameRegion* getActiveRegion() noexcept
		{
			return m_activeRegion;
		}

	private:
		BasicGameRegion* m_activeRegion = nullptr;
	};
}