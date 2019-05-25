#pragma once

#include <GameBackboneDemo/MainMenuDemoRegion.h>

#include <GameBackbone/Core/CoreEventController.h>

#include <memory>

namespace EXE {
	class DemoCoreEventController : public GB::CoreEventController<DemoCoreEventController> {
	public:
		// Constructors
		DemoCoreEventController();
		DemoCoreEventController(const DemoCoreEventController& other) = delete;
		DemoCoreEventController(DemoCoreEventController&& other) = default;
		DemoCoreEventController& operator=(const DemoCoreEventController& other) = delete;
		DemoCoreEventController& operator=(DemoCoreEventController&& other) = default;
		virtual ~DemoCoreEventController() = default;

		// Event handling
		bool handleCoreEvent(sf::Event& event);

	private:
		sf::View camera;

		std::shared_ptr<MainMenuDemoRegion> mainMenuDemoRegion;
	};
}