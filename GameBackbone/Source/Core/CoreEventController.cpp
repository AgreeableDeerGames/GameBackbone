#include <GameBackbone/Core/CoreEventController.h>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

using namespace GB;

static const int DEFAULT_WINDOW_HEIGHT = 700;
static const int DEFAULT_WINDOW_WIDTH = 700;
static const std::string DEFAULT_WINDOW_NAME = "GameBackbone";

CoreEventController::CoreEventController() : CoreEventController(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_NAME) {}

CoreEventController::CoreEventController(const std::string& windowName) : CoreEventController(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, windowName) {}

CoreEventController::CoreEventController(int windowWidth, int windowHeight) : CoreEventController(windowWidth, windowHeight, DEFAULT_WINDOW_NAME) {}

CoreEventController::CoreEventController(int windowWidth, int windowHeight, const std::string& windowName) :
	m_activeRegion(nullptr),
	m_window(sf::VideoMode(windowWidth, windowHeight), windowName),
	m_updateClock(),
	m_timeSinceLastHandledEvent(0)
{
}

CoreEventController::~CoreEventController() {}

void CoreEventController::runLoop() 
{
	// Ensure the window is fully opened before we do any work on it.
	while (m_window.isOpen() == false)
	{
		continue;
	}

	while (m_window.isOpen())
	{
		sf::Time elapsedTime = m_updateClock.restart();
		handleEvents(elapsedTime.asMicroseconds());
		update(elapsedTime.asMicroseconds());
		repaint();
		swapRegion();
	}
}

BasicGameRegion* CoreEventController::getActiveRegion()
{
	return m_activeRegion;
}

sf::RenderWindow& CoreEventController::getWindow()
{
	return m_window;
}

void CoreEventController::setActiveRegion(BasicGameRegion* activeRegion)
{
	m_activeRegion = activeRegion;
}

void CoreEventController::repaint()
{
	m_window.clear();
	draw();
	m_window.display();
}

void CoreEventController::draw()
{
	// Draw m_activeRegion so it can draw its drawables.
	m_window.draw(*getActiveRegion());
}

void CoreEventController::handleEvents(sf::Int64 elapsedTime)
{
	m_timeSinceLastHandledEvent += elapsedTime;

	sf::Event event;
	while (m_window.pollEvent(event))
	{
		getActiveRegion()->handleEvent(elapsedTime, event);
		m_timeSinceLastHandledEvent = 0;

		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

void CoreEventController::update(sf::Int64 elapsedTime)
{
	getActiveRegion()->update(elapsedTime);
}

void CoreEventController::swapRegion()
{
	BasicGameRegion& newRegion = getActiveRegion()->getNextRegion();
	if (m_activeRegion != &newRegion)
	{
		m_activeRegion->setNextRegion(*m_activeRegion);
		m_activeRegion = &newRegion;
	}
}