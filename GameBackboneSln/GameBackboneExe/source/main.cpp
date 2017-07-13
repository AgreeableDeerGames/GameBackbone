#include <Backbone\AnimatedSprite.h>
#include <Backbone\AnimationSet.h>
#include <Backbone\CompoundSprite.h>
#include <Backbone\GameRegion.h>
#include <Backbone\Updatable.h>
#include <NavigationDemoRegion.h>
#include <BackboneExeCoreEventController.h>
#include <SampleGuiInterface.h>

#include <TGUI\TGUI.hpp>

#include <SFML\System\Clock.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Sprite.hpp>

#include <string>
#include <vector>

#include <Util\FileManager.h>


using namespace GB;

int main() {
	BackboneExeCoreEventController controller;
	controller.runLoop();

	return 0;
}