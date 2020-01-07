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
/// Gets the GUI for this region.
/// </summary>
/// <returns>This regions GUI.</returns>
tgui::Gui& BasicGameRegion::getGUI() {
	return m_regionGUI;
}

/// <summary>
/// Attempts to transfer the active state from the target region to this one.
/// </summary>
/// <param name="targetRegion"> The region to request active state transfer from. </param>
/// <returns> True if the active state was successfully transfered. False otherwise. </returns>
bool BasicGameRegion::requestActivationFrom(BasicGameRegion& targetRegion)
{
	bool success = targetRegion.m_activateRegion(*this);
	if (success)
	{
		// This region is no longer active and can no longer give
		// its active state to another region
		targetRegion.m_activateRegion = [] (BasicGameRegion&) { return false; };
	}
	return success;
}

