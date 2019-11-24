#include <GameBackbone/Core/GameRegion.h>

#include <TGUI/TGUI.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <exception>
#include <utility>

using namespace GB;

bool detail::priorityFindComparitor::operator ()(const std::pair<int, std::vector<sf::Drawable*>>& priorityPair) {
	return priorityPair.first == priorityToFind;
}

bool detail::prioritySortComparitor::operator ()(
	const std::pair<int, std::vector<sf::Drawable*>>& leftEl, 
	const std::pair<int, std::vector<sf::Drawable*>>& rightEl) {
	return leftEl.first < rightEl.first;
}

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
/// Add a drawable with a given priority to this GameRegion.
/// If the drawable already exists, its priority will be updated.
/// 
/// This function will throw an std::invalid_argument exception if a nullptr is passed in. 
/// </summary>
/// <param name="priority"> The priority of the drawable </param>
/// <param name="drawablesToRemove"> The drawable that will be added </param>
void GameRegion::addDrawable(int priority, sf::Drawable* drawableToAdd) {
	std::vector<sf::Drawable*> drawablesToAdd = std::vector<sf::Drawable*>{drawableToAdd};
	addDrawable(priority, drawablesToAdd.begin(), drawablesToAdd.end());
}

/// <summary>
/// Remove a drawable from this GameRegion. 
/// If the drawable is not found, nothing will be done.
/// </summary>
/// <param name="drawablesToRemove"> The drawable that will be removed </param>
void GameRegion::removeDrawable(sf::Drawable* drawableToRemove) {
	std::vector<sf::Drawable*> drawablesToRemove = std::vector<sf::Drawable*>{ drawableToRemove };
	removeDrawable(drawablesToRemove.begin(), drawablesToRemove.end());
}

/// <summary>
/// Removes all drawable objects from this GameRegion.
/// </summary>
void GameRegion::clearDrawables() {
	prioritizedDrawables.clear();
}

/// <summary>
/// Removes all drawable objects with a given priority from this GameRegion.
/// </summary>
/// <param name="priority"> The priority of drawables clear</param>
void GameRegion::clearDrawables(int priority) {
	auto it = std::find_if(prioritizedDrawables.begin(), prioritizedDrawables.end(), detail::priorityFindComparitor(priority));

	// If the iterator is not end, then we found a pair with the same priority.
	// Clear the internal vector
	if (it != prioritizedDrawables.end()) {
		std::vector<sf::Drawable*>& tempDrawables = it->second;
		tempDrawables.clear();
	}
}

/// <summary>
/// Returns the count of all drawables stored on this GameRegion.
/// </summary>
/// <return> The number of drawables </param>
std::size_t GameRegion::getDrawableCount() {
	std::size_t count = 0;
	// Loop through each priority of the drawables
	// Add all of the sizes to the count
	for (const auto& priorityPair : prioritizedDrawables) {
		count += priorityPair.second.size();
	}
	return count;
}

/// <summary>
/// Returns the count of all drawables with a given priority stored on this GameRegion.
/// </summary>
/// <param name="priority"> The priority of drawables to count </param>
/// <return> The number of drawables </param>
std::size_t GameRegion::getDrawableCount(int priority) {
	std::size_t count = 0;
	auto it = std::find_if(prioritizedDrawables.begin(), prioritizedDrawables.end(), detail::priorityFindComparitor(priority));

	// If the iterator is not end, then we found a pair with the same priority.
	// Set the count equal to the vectors size
	if (it != prioritizedDrawables.end()) {
		std::vector<sf::Drawable*>& tempDrawables = it->second;
		count = tempDrawables.size();
	}
	return count;
}

/// <summary>
/// Gets the GUI for this region.
/// </summary>
/// <returns>This regions GUI.</returns>
tgui::Gui& GameRegion::getGUI() {
	return regionGUI;
}

/// <summary>
/// Draws every drawable on the region.
/// </summary>
/// <param name="target"> The SFML render target to draw on. </param>
/// <param name="states"> Current render states </param>
void GameRegion::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Loop through each priority of the drawables
	for (const auto& priorityPair : prioritizedDrawables) {
		for (const sf::Drawable* drawable : priorityPair.second) {
			// Draw each drawable stored in the vector
			target.draw(*drawable, states);
		}
	}
}
