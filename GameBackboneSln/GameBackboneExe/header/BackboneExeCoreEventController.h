#pragma once

#include <Backbone\CoreEventController.h>
#include <NavigationDemoRegion.h>
#include <SwirlyDemoRegion.h>

class BackboneExeCoreEventController : public GB::CoreEventController {
public:
	// ctr / dtr
	BackboneExeCoreEventController();
	BackboneExeCoreEventController(const BackboneExeCoreEventController& other) = delete;
	BackboneExeCoreEventController(BackboneExeCoreEventController&& other) = default;
	BackboneExeCoreEventController& operator=(const BackboneExeCoreEventController& other) = delete;
	BackboneExeCoreEventController& operator=(BackboneExeCoreEventController&& other) = default;
	virtual ~BackboneExeCoreEventController();

	//events
	bool handleCoreEvent (sf::Event& event) override;

private:
	sf::View camera;
	int oldMouseX;
	int oldMouseY;

	GB::NavigationDemoRegion* navigationRegion;
	GB::SwirlyDemoRegion* swirlyRegion;

};

