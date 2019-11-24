#pragma once

#include <GameBackbone/Core/AnimationSet.h>
#include <GameBackbone/Core/BackboneBaseExceptions.h>
#include <GameBackbone/Core/CompoundSprite.h>
#include <GameBackbone/Core/Updatable.h>
#include <GameBackbone/Util/DllUtil.h>

#include <TGUI/TGUI.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <functional>
#include <memory>
#include <utility>
#include <vector>

namespace GB {
	namespace detail{
		/// <summary>
		/// Functor used to check if the priority of a priorityPair the same as a given Priority.
		/// </summary>
		class libGameBackbone priorityFindComparitor {
		public:
			explicit priorityFindComparitor(int priority) : priorityToFind(priority) {};
			bool operator ()(const std::pair<int, std::vector<sf::Drawable*>>& priorityPair);

		private:
			int priorityToFind;
		};

		/// <summary>
		/// Functor used to check if the priority of a priorityPair is less than another priorityPair's.
		/// </summary>
		class libGameBackbone prioritySortComparitor {
		public:
			bool operator ()(const std::pair<int, std::vector<sf::Drawable*>>& leftEl, const std::pair<int, std::vector<sf::Drawable*>>& rightEl);
		};

		/// <summary>
		/// Functor used to check if a drawable is contained withing a given list of drawables.
		/// </summary>
		template <class It>
		class drawablesRemoveComparitor {
		public:
			explicit drawablesRemoveComparitor(const It first, const It last) : beginIt(std::move(first)), endIt(std::move(last)){};

			bool operator ()(const sf::Drawable* drawable) {
				It workingIt = beginIt;
				while (workingIt != endIt) {
					if (drawable == *workingIt) {
						return true;
					}
					workingIt++;
				}
				return false;
			}

		private:
			const It beginIt;
			const It endIt;
		};

		/// <summary>
		/// Inserts an element into an std::vector, given a sorting predicate, in the sorted location.
		/// This function assumes that the std::vector is already sorted.
		/// </summary>
		/// <param name="vector"> The vector to add to </param>
		/// <param name="item"> The item that will be added to the vector </param>
		/// <param name="pred"> The predicate with which to find the location of the item </param>
		template< typename T, typename Pred >
		typename std::vector<T>::iterator insert_sorted(std::vector<T> & vector, T const& item, Pred pred)
		{
			return vector.insert(std::upper_bound(vector.begin(), vector.end(), item, pred), item);
		}
	}


	/// <summary> Base class meant to be inherited. Controls game logic and actors for a specific time or space in game. </summary>
	class libGameBackbone GameRegion : public sf::Drawable, public Updatable {
	public:
		/// <summary>shared_ptr to GameRegion</summary>
		using Ptr = std::shared_ptr<GameRegion>;
		
		GameRegion() = default;
		explicit GameRegion(sf::RenderWindow & window);
		GameRegion(const GameRegion&) = default;
		GameRegion& operator=(const GameRegion&) = default;
		GameRegion(GameRegion&&) = default;
		GameRegion& operator=(GameRegion&&) = default;
		virtual ~GameRegion() = default;

		// Add/Remove/Clear drawables
		void addDrawable(int priority, sf::Drawable* drawableToAdd);
		/// <summary>
		/// Add drawables with a given priority to this GameRegion.
		/// If the drawables already exist, its priority will be updated.
		/// 
		/// This function will throw an std::invalid_argument exception if a nullptr is passed in. 
		/// </summary>
		/// <param name="priority"> The priority of the drawables </param>
		/// <param name="drawablesToRemove"> The drawables that will be added </param>
		template <class It>
		void addDrawable(int priority, It first, It last) {

			// Null check each of the drawables passed in
			It drawableIt = first;
			while (drawableIt != last) {
				if (*drawableIt++ == nullptr) {
					throw std::invalid_argument("Cannot invoke GameRegion::addDrawable with a drawable equal to nullptr");
				}
			}

			// Remove any instances of the drawables before adding them again
			removeDrawable(first, last);

			auto priorityIt = std::find_if(prioritizedDrawables.begin(), prioritizedDrawables.end(), detail::priorityFindComparitor(priority));

			// If the iterator is not end, then we found a pair with the same priority.
			// Insert the drawable at the same priority
			if (priorityIt != prioritizedDrawables.end()) {
				std::vector<sf::Drawable*>& tempDrawables = priorityIt->second;
				tempDrawables.insert(tempDrawables.end(), first, last);
			}
			else {
				detail::insert_sorted(prioritizedDrawables, std::make_pair(priority, std::vector<sf::Drawable*>{first, last}), detail::prioritySortComparitor());
			}
		}

		void removeDrawable(sf::Drawable* drawableToRemove);

		/// <summary>
		/// Remove a drawable from this GameRegion. 
		/// If the drawable is not found, nothing will be done.
		/// </summary>
		/// <param name="drawablesToRemove"> The drawable that will be removed </param>
		template <class It>
		void removeDrawable(It first, It last) {
			// Go through every pair and remove any of the passed in drawables from their vector
			for (auto& priorityPair : prioritizedDrawables) {
				std::vector<sf::Drawable*>& tempDrawables = priorityPair.second;
				auto it = std::remove_if(tempDrawables.begin(), tempDrawables.end(), detail::drawablesRemoveComparitor(first, last));
				if (it != tempDrawables.end())
				{
					tempDrawables.erase(it, tempDrawables.end());
				}
			}
		}
		//void removeDrawable(const std::vector<sf::Drawable*>& drawablesToRemove);
		void clearDrawables();
		void clearDrawables(int priority);

		[[nodiscard]]
		std::size_t getDrawableCount();
		[[nodiscard]]
		std::size_t getDrawableCount(int priority);

		tgui::Gui& getGUI();

		virtual void registerSetActiveRegionCB(std::function<void(GameRegion*)> newSetActiveRegionCB);

		/// <summary>
		/// Implements Updatable::update as a no-op.
		/// </summary>
		/// <param name="elapsedTime"> </param>
		virtual void update(sf::Int64 /*elapsedTime*/) override {}

	protected:
		// Drawing
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		//associated regions
		std::function<void(GameRegion*)> setActiveRegionCB;


	private:
		std::vector<std::pair<int, std::vector<sf::Drawable*>>> prioritizedDrawables;

		//GUI
		tgui::Gui regionGUI;
	};
}
