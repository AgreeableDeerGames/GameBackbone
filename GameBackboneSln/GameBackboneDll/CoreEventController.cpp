#include "stdafx.h"
#include "CoreEventController.h"

using namespace GB;

//ctr / dtr

CoreEventController::CoreEventController()
{
	const int WINDOW_WIDTH = 700;
	const int WINDOW_HEIGHT = 700;
	window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SpriteTests");
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

		preDraw();
		draw();
		postDraw();

		preUpdate();
		update();
		postUpdate();
	}
}

//events

/// <summary>
/// Handles all window and user input events.
/// </summary>
/// <param name="event">The event.</param>
void GB::CoreEventController::handleEvent(sf::Event & event) {
	preHandleEvent();
	if (!handleGuiEvent(event))
	{
		hendleNonGuiEvent(event);
	}
	postHandleEvent();
}

bool GB::CoreEventController::handleGuiEvent(sf::Event & event)
{
	return false;
}

void GB::CoreEventController::hendleNonGuiEvent(sf::Event & event)
{
}

void GB::CoreEventController::preHandleEvent()
{
}

void GB::CoreEventController::postHandleEvent()
{
}

//draw

void GB::CoreEventController::draw()
{
}

void GB::CoreEventController::preDraw()
{
}

void GB::CoreEventController::postDraw()
{
}

//update

void GB::CoreEventController::update()
{
}

void GB::CoreEventController::preUpdate()
{
}

void GB::CoreEventController::postUpdate()
{
}
