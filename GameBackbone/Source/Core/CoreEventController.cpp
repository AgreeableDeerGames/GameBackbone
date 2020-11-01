#include <GameBackbone/Core/CoreEventController.h>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

using namespace GB;

static const int DEFAULT_WINDOW_HEIGHT = 700;
static const int DEFAULT_WINDOW_WIDTH = 700;
static const std::string DEFAULT_WINDOW_NAME = "GameBackbone";

/// <summary>
/// Initializes a new instance of the <see cref="CoreEventController"/> class. Window width, height, and name are default.
/// </summary>
CoreEventController::CoreEventController() : CoreEventController(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_NAME) {}

/// <summary>
/// Initializes a new instance of the <see cref="CoreEventController"/> class. Window width and height are default.
/// </summary>
/// <param name="windowName">Name of the window.</param>
CoreEventController::CoreEventController(const std::string& windowName) : CoreEventController(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, windowName) {}

/// <summary>
/// Initializes a new instance of the <see cref="CoreEventController"/> class. Window name is default.
/// </summary>
/// <param name="windowWidth">Width of the window.</param>
/// <param name="windowHeight">Height of the window.</param>
CoreEventController::CoreEventController(int windowWidth, int windowHeight) : CoreEventController(windowWidth, windowHeight, DEFAULT_WINDOW_NAME) {}

/// <summary>
/// Initializes a new instance of the <see cref="CoreEventController"/> class.
/// </summary>
/// <param name="windowWidth">Width of the window.</param>
/// <param name="windowHeight">Height of the window.</param>
/// <param name="windowName">Name of the window.</param>
CoreEventController::CoreEventController(int windowWidth, int windowHeight, const std::string& windowName) :
	m_activeRegion(nullptr),
	m_window(sf::VideoMode(windowWidth, windowHeight), windowName),
	m_updateClock(),
	m_timeSinceLastHandledEvent(0)
{
}

/// <summary>
/// Finalizes an instance of the <see cref="CoreEventController"/> class.
/// </summary>
CoreEventController::~CoreEventController() {}

/// <summary>
/// The main loop of the <see cref="CoreEventController"/>. This loop is blocking.
/// </summary>
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

/// <summary>
/// Returns the currently active game region, on which all of the operation are being performed.
/// </summary>
/// <returns>The currently active game region.</returns>
BasicGameRegion* CoreEventController::getActiveRegion()
{
	return m_activeRegion;
}

/// <summary>
/// Returns the window owned by the <see cref="CoreEventController"/>.
/// </summary>
/// <returns>The window.</returns>
sf::RenderWindow& CoreEventController::getWindow()
{
	return m_window;
}

/// <summary>
/// Set the active region on the <see cref="CoreEventController"/>.
/// </summary>
/// <param name="activeRegion">The region that will become the active region</param>
void CoreEventController::setActiveRegion(BasicGameRegion* activeRegion)
{
	m_activeRegion = activeRegion;
}

/// <summary>
/// Primary drawing logic. Draws every drawable object in the game region.
/// </summary>
void CoreEventController::repaint()
{
	m_window.clear();
	draw();
	m_window.display();
}

/// <summary>
/// Primary drawing logic. Draws every drawable object in the game region.
/// </summary>
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

/// <summary>
/// Primary update logic. Runs behavior logic for active GameRegion. Updates every Updatable object in the active GameRegion.
/// </summary>
void CoreEventController::update(sf::Int64 elapsedTime)
{
	getActiveRegion()->update(elapsedTime);
}

/// <summary>
/// Changes to the next active region if prompted by the current active region.
/// </summary>
void CoreEventController::swapRegion()
{
	BasicGameRegion& newRegion = getActiveRegion()->getNextRegion();
	if (m_activeRegion != &newRegion)
	{
		m_activeRegion->setNextRegion(*m_activeRegion);
		m_activeRegion = &newRegion;
	}
}