#include "stdafx.h"

#include "BackboneExeCoreEventController.h"

#include "AnimatedSprite.h"
#include "AnimationSet.h"
#include "GameRegion.h"
#include "Updatable.h"
#include "CompoundSprite.h"
#include "NavigationDemoRegion.h"
#include "SampleGuiInterface.h"

#include <TGUI/TGUI.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <string>
#include <vector>


using namespace GB;

int main() {
	BackboneExeCoreEventController controller;
	controller.runLoop();

	return 0;
}