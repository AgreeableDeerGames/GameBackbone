#include <GameBackbone/Core/GameRegion.h>

#include <TGUI/TGUI.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <exception>

using namespace GB;


/// <summary>
/// Initializes a new instance of the <see cref="GameRegion"/> class. All members except regionGUI
/// are initialized empty or null. The regions GUI is bound to the passed window.
/// </summary>
/// <param name="window">The window.</param>
GameRegion::GameRegion(sf::RenderWindow & window) : regionGUI(window) {
}

/// <summary>
/// Registers the callback function for changing the active region.
/// </summary>
/// <param name="newSetActiveRegionCB">The new callback for changing the active region.</param>
void GameRegion::registerSetActiveRegionCB(std::function<void(GameRegion*)> newSetActiveRegionCB) {
	setActiveRegionCB = std::move(newSetActiveRegionCB);
}

/// <summary>
/// Adds or removes a drawable object from the list of drawable objects.
/// </summary>
/// <param name="status">if set to <c>true</c> the object will be drawable, otherwise the object will be made non-drawable.</param>
/// <param name="object">The object. Passing nullptr results in an std::invalid_argument exception.</param>
void GameRegion::setDrawable(bool status, sf::Drawable* object) {
	if (object == nullptr) {
		throw std::invalid_argument("Cannot invoke GameRegion::setDrawable on nullptr");
	}

	if (status) {
		drawables.push_back(object);
	} else {
		auto it = std::find(drawables.begin(), drawables.end(), object);
		if (it != drawables.end()) {
			drawables.erase(it);
		}
	}
}

/// <summary>
/// Return the region's list of drawable objects
/// </summary>
/// <returns>std::vector of drawable objects</returns>
const std::vector<sf::Drawable*>& GameRegion::getDrawables() const {
	return drawables;
}

/// <summary>
/// Gets the GUI for this region.
/// </summary>
/// <returns>This regions GUI.</returns>
tgui::Gui& GameRegion::getGUI() {
	return regionGUI;
}

/// <summary>
/// Removes all drawable objects from this GameRegion.
/// </summary>
void GameRegion::clearDrawable() {
	drawables.clear();
}

/// <summary>
/// Draws every drawable on the region.
/// </summary>
/// <param name="target"> The SFML render target to draw on. </param>
/// <param name="states"> Current render states </param>
void GameRegion::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const sf::Drawable* drawable : drawables) {
		// Draw m_objectSprite that is stored on the GameObject
		target.draw(*drawable, states);
	}
}

