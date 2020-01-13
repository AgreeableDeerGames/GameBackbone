#include <GameBackbone/Core/ActivationProvider.h>
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

bool BasicGameRegion::isActiveRegion()
{
	if (m_provider != nullptr)
	{
		return m_provider->getActiveRegion() == this;
	}
	return false;
}

/// <summary>
/// Attempts to transfer the active state from the target region to this one.
/// </summary>
/// <param name="provider"> The region to take active state from. </param>
/// <returns> True if the active state was successfully transfered. False otherwise. </returns>
bool BasicGameRegion::giveActivation(BasicGameRegion& targetRegion)
{
	// !this->canGiveActivation  (aka, isActiveRegion? + ExtensionPoint)
	if (!isActiveRegion())
	{
		return false;
	}

	this->m_provider->registerActiveRegion(targetRegion);
	m_provider = nullptr;
	return true;
}

void BasicGameRegion::setActivationProvider(ActivationProvider& provider)
{
	// TODO: Throw if cant
	if (!isActiveRegion())
	{
		m_provider = &provider;
	}
}