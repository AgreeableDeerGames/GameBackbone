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

template< typename T, typename Pred >
typename std::vector<T>::iterator insert_sorted(std::vector<T> & vec, T const& item, Pred pred)
{
	return vec.insert(std::upper_bound(vec.begin(), vec.end(), item, pred), item);
}

void GameRegion::addDrawable(int priority, sf::Drawable* objectToAdd) {
	addDrawable(priority, std::vector<sf::Drawable*>{objectToAdd});
}

void GameRegion::addDrawable(int priority, const std::vector<sf::Drawable*>& objectsToAdd) {
	/*if (object == nullptr) {
		throw std::invalid_argument("Cannot invoke GameRegion::setDrawable on nullptr");
	}*/

	removeDrawable(objectsToAdd);

	auto equalPredicate = [&priority](const std::pair<int, std::vector<sf::Drawable*>>& priorityPair) {
		return priorityPair.first == priority;
	};

	auto lessThanPredicate = [](const std::pair<int, std::vector<sf::Drawable*>>& leftEl, const std::pair<int, std::vector<sf::Drawable*>>& rightEl) {
		return leftEl.first < rightEl.first;
	};

	auto it = std::find_if(prioritizedDrawables.begin(), prioritizedDrawables.end(), equalPredicate);

	// If the iterator is not end, then we found a pair with the same priority.
	// Insert the drawable at the same priortiy
	if (it != prioritizedDrawables.end()) {
		std::vector<sf::Drawable*>& tempDrawables = it->second;
		tempDrawables.insert(tempDrawables.end(), objectsToAdd.begin(), objectsToAdd.end());
	}
	else {
		insert_sorted(prioritizedDrawables, std::pair(priority, objectsToAdd), lessThanPredicate);
	}
}

void GameRegion::removeDrawable(sf::Drawable* objectToRemove) {
	removeDrawable(std::vector<sf::Drawable*>{objectToRemove});
}

void GameRegion::removeDrawable(const std::vector<sf::Drawable*>& objectsToRemove) {
	auto removePredicate = [&objectsToRemove](const sf::Drawable* drawable) {
		for (auto& object : objectsToRemove) {
			if (drawable == object) {
				return true;
			}
		}
		return false;
	};

	for (auto& priorityPair : prioritizedDrawables) {
		std::vector<sf::Drawable*>& tempDrawables = priorityPair.second;
		auto it = std::remove_if(tempDrawables.begin(), tempDrawables.end(), removePredicate);
		if (it != tempDrawables.end())
		{
			tempDrawables.erase(it);
		}
	}
}

/// <summary>
/// Removes all drawable objects from this GameRegion.
/// </summary>
void GameRegion::clearDrawable(int priority) {
	auto equalPredicate = [&priority](const std::pair<int, std::vector<sf::Drawable*>>& priorityPair) {
		return priorityPair.first == priority;
	};

	auto it = std::find_if(prioritizedDrawables.begin(), prioritizedDrawables.end(), equalPredicate);

	// If the iterator is not end, then we found a pair with the same priority.
	// Clear the internal vector
	if (it != prioritizedDrawables.end()) {
		std::vector<sf::Drawable*>& tempDrawables = it->second;
		tempDrawables.clear();
	}
}

/// <summary>
/// Removes all drawable objects from this GameRegion.
/// </summary>
void GameRegion::clearDrawable() {
	prioritizedDrawables.clear();
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
	for (auto& priorityPair : prioritizedDrawables) {
		for (const sf::Drawable* drawable : priorityPair.second) {
			// Draw each drawable stored in the vector
			target.draw(*drawable, states);
		}
	}
}

