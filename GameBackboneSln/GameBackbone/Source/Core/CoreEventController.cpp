#include <GameBackbone/Core/CoreEventController.h>

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
CoreEventController::CoreEventController(int windowWidth, int windowHeight, const std::string& windowName) : m_window(sf::VideoMode(windowWidth, windowHeight), windowName)
{
	m_activeRegion = nullptr;
}

/// <summary>
/// Finalizes an instance of the <see cref="CoreEventController"/> class.
/// </summary>
CoreEventController::~CoreEventController() {}

/// <summary>
/// The main loop of the <see cref="CoreEventController"/>. This loop is blocking.
/// </summary>
void CoreEventController::runLoop() {
	sf::Event event;

	// Ensure the window is fully opened before we do any work on it.
	while (m_window.isOpen() == false) {
		continue;
	}

	while (m_window.isOpen()) {
		while (m_window.pollEvent(event)) {
			handleEvent(event);
		}

		draw();
		update();
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
/// Handles all window and user input events.
/// </summary>
/// <param name="event">The event.</param>
void CoreEventController::handleEvent(sf::Event& event) {
	if (!handleGuiEvent(event)) {
		handleCoreEvent(event);
	}
}

/// <summary>
/// Handles the GUI event.
/// </summary>
/// <param name="event">The event.</param>
/// <returns>Returns true if the event was consumed by the GUI. Returns false otherwise.</returns>
 bool CoreEventController::handleGuiEvent(sf::Event& event) {
	return getActiveRegion()->getGUI().handleEvent(event);
}

/// <summary>
/// Handles the non GUI event.
/// </summary>
/// <param name="event">The event.</param>
/// <returns>Returns true if the event was consumed. Returns false otherwise.</returns>
 bool CoreEventController::handleCoreEvent(sf::Event& /*event*/) {
	return false;
}

/// <summary>
/// Primary drawing logic. Draws every drawable object in the game region and the active regions gui.
/// </summary>
 void CoreEventController::draw() {
	 m_window.clear();

	 // Draw m_activeRegion so it can draw its drawables.
	m_window.draw(*getActiveRegion());
	getActiveRegion()->getGUI().draw();

	m_window.display();
}

/// <summary>
/// Primary update logic. Runs behavior logic for active GameRegion. Updates every Updatable object in the active GameRegion.
/// </summary>
 void CoreEventController::update() {
	sf::Time elapsedTime = m_updateClock.restart();
	getActiveRegion()->update(elapsedTime.asMicroseconds());
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