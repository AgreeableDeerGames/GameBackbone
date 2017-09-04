#include <DemoRegion.h>

using namespace EXE;

// ctr
DemoRegion::DemoRegion(sf::RenderWindow & window) : GameRegion(window){
	initGui();
}

// public handles and callbacks

void DemoRegion::handleMouseMove(sf::Vector2f mousePosition) {}

void DemoRegion::handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button){}

void DemoRegion::handleWheelScroll(float scrollDelta){}


// initialization


/// <summary>
/// Initializes the GUI.
/// </summary>
void DemoRegion::initGui() {
	tgui::Theme::Ptr theme = tgui::Theme::create("TGUI_Widgets/Black.txt");
	// Get a bound version of the window size
	// Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
	tgui::Layout windowWidth = tgui::bindWidth(*regionGUI);
	tgui::Layout windowHeight = tgui::bindHeight(*regionGUI);
	tgui::Layout buttonWidth = windowWidth / 4.0f;
	tgui::Layout buttonHeight = windowHeight / 4.0f;


	// create a button to return to the parent region
	returnToMenuButton = theme->load("Button");
	returnToMenuButton->setSize(buttonWidth, buttonHeight);
	returnToMenuButton->setPosition(windowWidth - buttonWidth, 0);
	returnToMenuButton->setText("Return to Menu");
	returnToMenuButton->connect("pressed", &DemoRegion::returnToMenuCB, this);
	regionGUI->add(returnToMenuButton);

}

// protected handles and callbacks


/// <summary>
/// callback invoked when the returnToMenuButton is pressed. sets the active region to
/// this instances parent region.
/// </summary>
void DemoRegion::returnToMenuCB() {
	if (parentRegion != nullptr) {
		setActiveRegionCB(parentRegion);
	}
}
