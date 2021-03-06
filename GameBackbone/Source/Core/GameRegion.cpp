#include <GameBackbone/Core/GameRegion.h>

#include <GameBackbone/Core/BasicGameRegion.h>

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <exception>
#include <utility>

using namespace GB;


/// <summary>
/// Returns the count of all drawables stored on this GameRegion.
/// </summary>
/// <return> The number of drawables </param>
std::size_t GameRegion::getDrawableCount() const  noexcept {
	return prioritizedDrawables.size();
}

/// <summary>
/// Returns the count of all drawables with a given priority stored on this GameRegion.
/// </summary>
/// <param name="priority"> The priority of drawables to count </param>
/// <return> The number of drawables </param>
std::size_t GameRegion::getDrawableCount(int priority) const noexcept {
	return prioritizedDrawables.count(priority);
}


/// <summary>
/// Add a drawable with a given priority to this GameRegion.
/// If the drawable already exists, it will be drawn multiple times.
/// 
/// </summary>
/// <param name="priority"> The priority of the drawable </param>
/// <param name="drawablesToRemove"> The drawable that will be added </param>
void GameRegion::addDrawable(int priority, sf::Drawable& drawableToAdd) {
	// Remove any instances of the drawable before adding it again
	removeDrawable(drawableToAdd);

	// Add the drawable to the internal map
	prioritizedDrawables.emplace(priority, &drawableToAdd);
}

/// <summary>
/// Remove a drawable from this GameRegion. 
/// If the drawable is not found, nothing will be done.
/// </summary>
/// <param name="drawablesToRemove"> The drawable that will be removed </param>
void GameRegion::removeDrawable(sf::Drawable& drawableToRemove) {
	// Find the drawable inside of the internal map.
	auto it = std::find_if(prioritizedDrawables.begin(), prioritizedDrawables.end(),
		[&drawableToRemove](const std::pair<int, sf::Drawable*>& possibleRemoval) -> bool {
			return possibleRemoval.second == &drawableToRemove;
		});

	// If the drawable was found, erase it.
	if (it != prioritizedDrawables.end())
	{
		prioritizedDrawables.erase(it);
	}
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
	prioritizedDrawables.erase(priority);
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
		const sf::Drawable* drawable = priorityPair.second;
		// Draw each drawable stored in the vector
		target.draw(*drawable, states);
	}
}
