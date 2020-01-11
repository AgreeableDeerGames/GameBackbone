#pragma once

#include <GameBackboneDemo/MainMenuDemoRegion.h>

#include <GameBackbone/Core/CoreEventController.h>

#include <memory>

namespace EXE {
	class DemoCoreEventController : public GB::CoreEventController {
	public:
		// Constructors
		DemoCoreEventController();
		DemoCoreEventController(const DemoCoreEventController& other) = delete;
		DemoCoreEventController(DemoCoreEventController&& other) = default;
		DemoCoreEventController& operator=(const DemoCoreEventController& other) = delete;
		DemoCoreEventController& operator=(DemoCoreEventController&& other) = default;
		virtual ~DemoCoreEventController() = default;

	protected:
		// Event handling
		bool handleCoreEvent(sf::Event& event) override;
		void postHandleEvent(sf::Event& event) override;

	private:
		sf::View m_camera;
		std::unique_ptr<MainMenuDemoRegion> m_mainMenuDemoRegion;
	};
}