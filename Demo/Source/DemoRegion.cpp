#include <GameBackboneDemo/DemoRegion.h>

using namespace EXE;

/// <summary>
/// Initializes a new instance of the <see cref="DemoRegion"/> class.
/// </summary>
/// <param name="window">The window.</param>
DemoRegion::DemoRegion(sf::RenderWindow & window) : regionGUI(window), renderWindow(window){
	initGui();
	camera.reset(sf::FloatRect(0, 0, (float)getWindow().getSize().x, (float)getWindow().getSize().y));
}

// public handles and callbacks

bool EXE::DemoRegion::handleEvent(sf::Int64 elapsedTime, const sf::Event& event)
{
	// Give the GUI the chance to handle events first
	if (getGUI().handleEvent(event))
	{
		getGUI().unfocusAllWidgets();
		return true;
	}

	// Handle events not handled by the GUI
	switch (event.type) {
	case sf::Event::MouseMoved:
	{
		// Get the pixel position and map it to coordinates
		sf::Vector2i mousePos(event.mouseMove.x, event.mouseMove.y);
		sf::Vector2f actualPosition = getWindow().mapPixelToCoords(mousePos);
		// Pass the event to the active region to handle
		this->handleMouseMove(actualPosition);
		return true;
	}
	case sf::Event::MouseButtonPressed:
	{
		// Get the pixel position and map it to coordinates
		sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
		sf::Vector2f actualPosition = getWindow().mapPixelToCoords(mousePos);
		// Pass the event to the active region to handle
		this->handleMouseClick(actualPosition, event.mouseButton.button);
		return true;
	}
	case sf::Event::MouseWheelScrolled:
	{
		// Pass the event to the active region to handle
		this->handleWheelScroll(event.mouseWheelScroll.delta);
		return true;
	}
	case sf::Event::KeyPressed:
	{
		// Pass the event to the active region to handle
		this->handleKeyPress(event.key);
		return true;
	}
	case sf::Event::KeyReleased:
	{
		// Pass the event to the active region to handle
		this->handleKeyRelease(event.key);
		return true;
	}
	case sf::Event::Resized:
	{
		// Reset the camera to the same as the window
		camera.reset(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height));
		// Set the view on the window to be the reset camera
		getWindow().setView(camera);
		// Set the view on the GUI to be the reset camera
		this->getGUI().setView(camera);
		return true;
	}
	default:
	{
		return false;
	}
	}
	return false;
}

void DemoRegion::handleMouseMove(sf::Vector2f /*mousePosition*/) {}

void DemoRegion::handleMouseClick(sf::Vector2f /*newPosition*/, sf::Mouse::Button /*button*/){}

void DemoRegion::handleWheelScroll(float /*scrollDelta*/){}

void DemoRegion::handleKeyPress(sf::Event::KeyEvent /*key*/){}

void DemoRegion::handleKeyRelease(sf::Event::KeyEvent /*key*/){}

/// <summary>
/// Takes ownership of the passed DemoRegion.
/// Sets this as the parent of the child.
/// </summary>
/// <param name="child"> </param>
void DemoRegion::addChild(DemoRegion::Ptr child) {
	child->parent = this;
	children.emplace_back(std::move(child));
}

sf::RenderWindow& DemoRegion::getWindow()
{
	return renderWindow;
}

/// <summary>
/// Gets the GUI for this region.
/// </summary>
/// <returns>This regions GUI.</returns>
tgui::Gui& DemoRegion::getGUI() {
	return regionGUI;
}

/// <summary>
/// Initializes the GUI.
/// </summary>
void DemoRegion::initGui() {
	tgui::Theme theme("TGUI_Widgets/Black.txt");
	// Get a bound version of the window size
	// Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
	tgui::Layout windowWidth = tgui::bindWidth(this->getGUI());
	tgui::Layout windowHeight = tgui::bindHeight(this->getGUI());
	tgui::Layout buttonWidth = windowWidth / 4.0f;
	tgui::Layout buttonHeight = windowHeight / 4.0f;

	// Create a button to return to the parent region
	returnToMenuButton = tgui::Button::create();
	returnToMenuButton->setRenderer(theme.getRenderer("Button"));
	returnToMenuButton->setSize(buttonWidth, buttonHeight);
	returnToMenuButton->setPosition(windowWidth - buttonWidth, 0);
	returnToMenuButton->setText("  Return\n to Menu");
	returnToMenuButton->connect("pressed", &DemoRegion::returnToMenuCB, this);
	this->getGUI().add(returnToMenuButton);

	// Create a button to reset a region
	resetButton = tgui::Button::create();
	resetButton->setRenderer(theme.getRenderer("Button"));
	resetButton->setSize(buttonWidth, buttonHeight);
	resetButton->setPosition(windowWidth - buttonWidth, buttonHeight + windowHeight / 10);
	resetButton->setText("Reset");
	resetButton->connect("pressed", &DemoRegion::reset, this);
	this->getGUI().add(resetButton);

}

/// <summary>
/// Resets this instance.
/// </summary>
void DemoRegion::reset() {}

/// <summary>
/// Callback invoked when the returnToMenuButton is pressed.
/// Sets the active region to this instances parent region.
/// </summary>
void DemoRegion::returnToMenuCB() {
	// Ensure that the parent is not null
	if (parent != nullptr) {
		// Set parent as the new active region
		setNextRegion(*parent);
	}
}
