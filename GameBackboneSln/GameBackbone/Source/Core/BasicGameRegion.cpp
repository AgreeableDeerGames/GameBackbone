#include <GameBackbone/Core/BasicGameRegion.h>

#include <TGUI/TGUI.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <exception>
#include <utility>

using namespace GB;


/// <summary>
/// Initializes a new instance of the <see cref="BasicGameRegion"/> class. All members except regionGUI
/// are initialized empty or null. The regions GUI is bound to the passed window.
/// </summary>
/// <param name="window">The window.</param>
BasicGameRegion::BasicGameRegion(sf::RenderWindow& window) : m_regionGUI(window) {
}

/// <summary>
/// Change the 
/// </summary>
/// <param name="window">The window.</param>
void GB::BasicGameRegion::setActiveRegion(BasicGameRegion& activeRegion) const
{
	m_setActiveRegionCB(&activeRegion);
	activeRegion.registerSetActiveRegionCB(m_setActiveRegionCB);
}

/// <summary>
/// Registers the callback function for changing the active region.
/// </summary>
/// <param name="newSetActiveRegionCB">The new callback for changing the active region.</param>
void BasicGameRegion::registerSetActiveRegionCB(std::function<void(BasicGameRegion*)> newSetActiveRegionCB) {
	m_setActiveRegionCB = std::move(newSetActiveRegionCB);
}

/// <summary>
/// Gets the GUI for this region.
/// </summary>
/// <returns>This regions GUI.</returns>
tgui::Gui& BasicGameRegion::getGUI() {
	return m_regionGUI;
}

