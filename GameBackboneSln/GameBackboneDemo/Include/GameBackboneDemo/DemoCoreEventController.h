#pragma once

#include <GameBackboneDemo/MainMenuDemoRegion.h>

#include <GameBackbone/Core/CoreEventController.h>


namespace EXE {
	class DemoCoreEventController : public GB::CoreEventController<DemoCoreEventController> {
	public:
		// ctr / dtr
		DemoCoreEventController();
		DemoCoreEventController(const DemoCoreEventController& other) = delete;
		DemoCoreEventController(DemoCoreEventController&& other) = default;
		DemoCoreEventController& operator=(const DemoCoreEventController& other) = delete;
		DemoCoreEventController& operator=(DemoCoreEventController&& other) = default;
		virtual ~DemoCoreEventController();

		//events
		bool handleCoreEvent(sf::Event& event);

	private:
		sf::View camera;

		MainMenuDemoRegion* mainMenuDemoRegion;
	};
}