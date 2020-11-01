#pragma once

#include <GameBackboneDemo/MainMenuDemoRegion.h>

#include <GameBackbone/Core/CoreEventController.h>

#include <memory>

namespace EXE {
	class DemoCoreEventController final : public GB::CoreEventController {
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
		void draw() override;

	private:
		void postDraw();

		std::unique_ptr<MainMenuDemoRegion> m_mainMenuDemoRegion;
	};
}