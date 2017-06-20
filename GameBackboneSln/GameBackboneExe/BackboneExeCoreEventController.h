#pragma once

#include "CoreEventController.h"

class BackboneExeCoreEventController :
	public GB::CoreEventController {
public:


	// ctr / dtr
	BackboneExeCoreEventController();
	BackboneExeCoreEventController(const BackboneExeCoreEventController& other) = delete;
	BackboneExeCoreEventController(BackboneExeCoreEventController&& other) = default;
	BackboneExeCoreEventController& operator=(const BackboneExeCoreEventController& other) = delete;
	BackboneExeCoreEventController& operator=(BackboneExeCoreEventController&& other) = default;
	virtual ~BackboneExeCoreEventController();

	//events
	virtual bool handleNonGuiEvent(sf::Event& event);

private:
	sf::View camera;
	int oldMouseX;
	int oldMouseY;

};

