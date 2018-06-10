#pragma once

#include <MainMenuDemoRegion.h>

#include <Backbone/CoreEventController.h>


namespace EXE {
	class DemoCoreEventController : public GB::CoreEventController {
	public:
		// ctr / dtr
		DemoCoreEventController();
		DemoCoreEventController(const DemoCoreEventController& other) = delete;
		DemoCoreEventController(DemoCoreEventController&& other) = default;
		DemoCoreEventController& operator=(const DemoCoreEventController& other) = delete;
		DemoCoreEventController& operator=(DemoCoreEventController&& other) = default;
		virtual ~DemoCoreEventController();

		//events
		bool handleCoreEvent(sf::Event& event) override;

	private:
		sf::View camera;
		int oldMouseX;
		int oldMouseY;

		MainMenuDemoRegion* mainMenuDemoRegion;
	};
}