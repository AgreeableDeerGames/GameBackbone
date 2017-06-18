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

bool GB::CoreEventController::handleGuiEvent(sf::Event & event)
{
	return false;
}

bool GB::CoreEventController::handleNonGuiEvent(sf::Event & event)
{
	return true;
}

void GB::CoreEventController::preHandleEvent(sf::Event & event)
{
}

void GB::CoreEventController::postHandleEvent(sf::Event & event)
{
}

//draw

void GB::CoreEventController::draw() {
	preDraw();
	coreDraw();
	postDraw();
}

void GB::CoreEventController::preDraw()
{
}

void GB::CoreEventController::coreDraw()
{
}

void GB::CoreEventController::postDraw()
{
}

//update

void GB::CoreEventController::update() {
	preUpdate();
	coreUpdate();
	postUpdate();
}

void GB::CoreEventController::preUpdate()
{
}

void GB::CoreEventController::coreUpdate()
{
}

void GB::CoreEventController::postUpdate()
{
}
