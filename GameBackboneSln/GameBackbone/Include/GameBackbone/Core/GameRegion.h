#pragma once

#include <GameBackbone/Core/BackboneBaseExceptions.h>
#include <GameBackbone/Core/BasicGameRegion.h>
#include <GameBackbone/Core/Updatable.h>
#include <GameBackbone/Util/DllUtil.h>

#include <SFML/Graphics/Drawable.hpp>

#include <map>
#include <memory>
#include <utility>
#include <vector>

namespace GB {

	/// <summary> Base class meant to be inherited. Controls game logic and actors for a specific time or space in game. </summary>
	class libGameBackbone GameRegion : public BasicGameRegion {
	public:
		/// <summary>shared_ptr to GameRegion</summary>
		using Ptr = std::shared_ptr<GameRegion>;
		
		GameRegion() = default;
		GameRegion(const GameRegion&) = default;
		GameRegion& operator=(const GameRegion&) = default;
		GameRegion(GameRegion&&) = default;
		GameRegion& operator=(GameRegion&&) = default;
		virtual ~GameRegion() = default;

		// Add/Remove/Clear drawables
		void addDrawable(int priority, sf::Drawable* drawableToAdd);
		void addDrawable(int priority, const std::vector<sf::Drawable*>& drawablesToAdd);
		void removeDrawable(sf::Drawable* drawableToRemove);
		void removeDrawable(const std::vector<sf::Drawable*>& drawablesToRemove);
		void clearDrawables();
		void clearDrawables(int priority);

		[[nodiscard]]
		std::size_t getDrawableCount() const noexcept;
		[[nodiscard]]
		std::size_t getDrawableCount(int priority) const noexcept;

		/// <summary>
		/// Implements Updatable::update as a no-op.
		/// </summary>
		/// <param name="elapsedTime"> </param>
		virtual void update(sf::Int64 /*elapsedTime*/) override {}

	protected:
		// Drawing
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		std::multimap<int, sf::Drawable*> prioritizedDrawables;
		//std::vector<std::pair<int, std::vector<sf::Drawable*>>> prioritizedDrawables;
	};
}
