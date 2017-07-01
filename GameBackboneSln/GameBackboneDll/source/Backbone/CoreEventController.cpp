#include <Backbone\CoreEventController.h>
#include <Backbone\GameRegion.h>

#include <string>

using namespace GB;

//ctr / dtr

static const int DEFAULT_WINDOW_WIDTH = 700;
static const int DEFAULT_WINDOW_HEIGHT = 700;
static const std::string DEFAULT_WINDOW_NAME = "GameBackbone";


/// <summary>
/// Initializes a new instance of the <see cref="CoreEventController"/> class. Window width, height, and name are default.
/// </summary>
CoreEventController::CoreEventController() : CoreEventController(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_NAME){}

/// <summary>
/// Initializes a new instance of the <see cref="CoreEventController"/> class. Window width and height are default.
/// </summary>
/// <param name="windowName">Name of the window.</param>
GB::CoreEventController::CoreEventController(const std::string & windowName) : CoreEventController(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, windowName) {}

/// <summary>
/// Initializes a new instance of the <see cref="CoreEventController"/> class. Window name is default.
/// </summary>
/// <param name="windowWidth">Width of the window.</param>
/// <param name="windowHeight">Height of the window.</param>
GB::CoreEventController::CoreEventController(int windowWidth, int windowHeight) : CoreEventController(windowWidth, windowHeight, DEFAULT_WINDOW_NAME){}

/// <summary>
/// Initializes a new instance of the <see cref="CoreEventController"/> class.
/// </summary>
/// <param name="windowWidth">Width of the window.</param>
/// <param name="windowHeight">Height of the window.</param>
/// <param name="windowName">Name of the window.</param>
GB::CoreEventController::CoreEventController(int windowWidth, int windowHeight, const std::string & windowName) {
	window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), windowName);
}

/// <summary>
/// Finalizes an instance of the <see cref="CoreEventController"/> class.
/// </summary>
CoreEventController::~CoreEventController()
{
	delete window;
}

//operations

/// <summary>
/// Runs all drawing and game logic until the window is closed.
/// </summary>
void CoreEventController::runLoop() {
	sf::Event event;
	while (window->isOpen()) {

		while (window->pollEvent(event)) {
			handleEvent(event);
		}

		draw();

		update();
	}
}


/// <summary>
/// Changes the active region to the passed game region.
/// </summary>
/// <param name="newRegion">The new active game region.</param>
void GB::CoreEventController::setActiveRegion(GameRegion * newRegion) {
	activeRegion = newRegion;
}

//events

/// <summary>
/// Handles all window and user input events.
/// </summary>
/// <param name="event">The event.</param>
void GB::CoreEventController::handleEvent(sf::Event & event) {
	preHandleEvent(event);
	if (!handleGuiEvent(event)) {
		handleCoreEvent(event);
	}
	postHandleEvent(event);
}

/// <summary>
/// Handles the GUI event.
/// </summary>
/// <param name="event">The event.</param>
/// <returns>Returns true if the event was consumed by the GUI. Returns false otherwise.</returns>
bool GB::CoreEventController::handleGuiEvent(sf::Event & event)
{
	return activeRegion->getGUI()->handleEvent(event);
}

/// <summary>
/// Handles the non GUI event.
/// </summary>
/// <param name="event">The event.</param>
/// <returns>Returns true if the event was consumed. Returns false otherwise.</returns>
bool GB::CoreEventController::handleCoreEvent(sf::Event & event)
{
	return false;
}

/// <summary>
/// Called before handleGuiEvent and handleCoreEvent. Place logic to be executed before the main event logic here.
/// </summary>
/// <param name="event">The event.</param>
void GB::CoreEventController::preHandleEvent(sf::Event & event)
{
}

/// <summary>
/// Called after hendleGuiEvent and handleCoreEvent. Place logic to be executed after the main event logic here.
/// </summary>
/// <param name="event">The event.</param>
void GB::CoreEventController::postHandleEvent(sf::Event & event)
{
}

//draw

/// <summary>
/// Calls all draw helper functions then displays the window.
/// </summary>
void GB::CoreEventController::draw() {
	window->clear();

	preDraw();
	coreDraw();
	postDraw();

	window->display();
}

/// <summary>
/// Called before coreDraw. PLace logic to be executed before the main draw logic here.
/// </summary>
void GB::CoreEventController::preDraw()
{
}

/// <summary>
/// Primary drawing logic. Draws every drawable object in the game region and the active regions gui.
/// </summary>
void GB::CoreEventController::coreDraw() {
	//draw every drawable object in the active region.
	for (sf::Sprite*  drawObject : *(activeRegion->getDrawables())) {
		window->draw(*drawObject);
	}

	activeRegion->getGUI()->draw();
}

/// <summary>
/// called after core draw. Place logic to be executed after the main draw logic here.
/// </summary>
void GB::CoreEventController::postDraw() {
}

//update

/// <summary>
/// Calls all update helper functions.
/// </summary>
void GB::CoreEventController::update() {
	preUpdate();
	coreUpdate();
	postUpdate();
}

/// <summary>
/// called before coreUpdate. Place logic meant to execute before the main update logic here.
/// </summary>
void GB::CoreEventController::preUpdate() {
}

/// <summary>
/// Primary update logic. Runs behavior logic for active GameRegion. Updates every updatable object in the active GameRegion.
/// </summary>
void GB::CoreEventController::coreUpdate() {

	activeRegion->behave(updateClock.getElapsedTime());

	for (Updatable* updateObject : *(activeRegion->getUpdatables())) {
		updateObject->update(updateClock.getElapsedTime());
	}
}

/// <summary>
/// Executes after coreUpdate. Place logic meant to update after the main update logic here.
/// </summary>
void GB::CoreEventController::postUpdate() {
}

/// <summary>
/// Used to determine if the protected window in the CoreEventController is open.
/// </summary>
bool GB::CoreEventController::isWindowOpen() {
	return window->isOpen();
}
