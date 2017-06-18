#include "stdafx.h"
#include "CoreEventController.h"
#include "GameRegion.h"

#include <string>

using namespace GB;

//ctr / dtr

CoreEventController::CoreEventController()
{
	const int WINDOW_WIDTH = 700;
	const int WINDOW_HEIGHT = 700;
	window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GameBackbone");
}

GB::CoreEventController::CoreEventController(const std::string & windowName)
{
}

GB::CoreEventController::CoreEventController(int windowWidth, int windowHeight, const std::string & windowName)
{
}

GB::CoreEventController::CoreEventController(int windowWidth, int windowHeight)
{
}

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
		handleEvent(event);

		draw();

		update();
	}
}

//events

/// <summary>
/// Handles all window and user input events.
/// </summary>
/// <param name="event">The event.</param>
void GB::CoreEventController::handleEvent(sf::Event & event) {
	preHandleEvent(event);
	if (!handleGuiEvent(event)) {
		handleNonGuiEvent(event);
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
bool GB::CoreEventController::handleNonGuiEvent(sf::Event & event)
{
	return false;
}

void GB::CoreEventController::preHandleEvent(sf::Event & event)
{
}

void GB::CoreEventController::postHandleEvent(sf::Event & event)
{
}

//draw

/// <summary>
/// Calls all draw helper functions then displays the window.
/// </summary>
void GB::CoreEventController::draw() {
	preDraw();
	coreDraw();
	postDraw();

	window->display();
}

void GB::CoreEventController::preDraw()
{
}

/// <summary>
/// Primary drawing logic. Draws every drawable object in the game region and the active regions gui.
/// </summary>
void GB::CoreEventController::coreDraw() {
	//draw every drawable object in the active region.
	for (sf::Sprite* drawObject : *(activeRegion->getDrawables())) {
		window->draw(*drawObject);
	}

	activeRegion->getGUI()->draw();
}

void GB::CoreEventController::postDraw() {
}

//update

void GB::CoreEventController::update() {
	preUpdate();
	coreUpdate();
	postUpdate();
}

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

void GB::CoreEventController::postUpdate() {
}
