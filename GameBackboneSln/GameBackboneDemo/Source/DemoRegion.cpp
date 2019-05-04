#include <GameBackboneDemo/DemoRegion.h>

using namespace EXE;

/// <summary>
/// Initializes a new instance of the <see cref="DemoRegion"/> class.
/// </summary>
/// <param name="window">The window.</param>
DemoRegion::DemoRegion(sf::RenderWindow & window) : GameRegion(window) {
	initGui();
}

// public handles and callbacks

void DemoRegion::handleMouseMove(sf::Vector2f mousePosition) {}

void DemoRegion::handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button){}

void DemoRegion::handleWheelScroll(float scrollDelta){}

void DemoRegion::handleKeyPress(sf::Event::KeyEvent key){}

void DemoRegion::handleKeyRelease(sf::Event::KeyEvent key){}

/// <summary>
/// Initializes the GUI.
/// </summary>
void DemoRegion::initGui() {
	tgui::Theme theme("TGUI_Widgets/Black.txt");
	// Get a bound version of the window size
	// Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
	tgui::Layout windowWidth = tgui::bindWidth(*regionGUI);
	tgui::Layout windowHeight = tgui::bindHeight(*regionGUI);
	tgui::Layout buttonWidth = windowWidth / 4.0f;
	tgui::Layout buttonHeight = windowHeight / 4.0f;


	// create a button to return to the parent region
	returnToMenuButton = tgui::Button::create();
	returnToMenuButton->setRenderer(theme.getRenderer("Button"));
	returnToMenuButton->setSize(buttonWidth, buttonHeight);
	returnToMenuButton->setPosition(windowWidth - buttonWidth, 0);
	returnToMenuButton->setText("  Return\n to Menu");
	returnToMenuButton->connect("pressed", &DemoRegion::returnToMenuCB, this);
	regionGUI->add(returnToMenuButton);

	// create a button to reset a region
	resetButton = tgui::Button::create();
	resetButton->setRenderer(theme.getRenderer("Button"));
	resetButton->setSize(buttonWidth, buttonHeight);
	resetButton->setPosition(windowWidth - buttonWidth, buttonHeight + windowHeight / 10);
	resetButton->setText("Reset");
	resetButton->connect("pressed", &DemoRegion::resetRegion, this);
	regionGUI->add(resetButton);

}

/// <summary>
/// Resets this instance.
/// Virtually calls the correct reset for all child classes.
/// </summary>
void DemoRegion::resetRegion() {
	reset();
}

/// <summary>
/// Callback invoked when the returnToMenuButton is pressed.
/// Sets the active region to this instances parent region.
/// </summary>
void DemoRegion::returnToMenuCB() {
	if (parentRegion != nullptr) {
		setActiveRegionCB(parentRegion);
	}
}
