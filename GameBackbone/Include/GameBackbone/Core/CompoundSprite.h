#pragma once

#include <GameBackbone/Core/AnimatedSprite.h>
#include <GameBackbone/Core/Updatable.h>
#include <GameBackbone/Util/DllUtil.h>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <cstddef>
#include <map>
#include <set>
#include <utility>
#include <vector>


namespace GB 
{
	/// @brief Checks if a type is drawable. 
	/// @tparam InType The type to check
	template <class InType>
	struct is_drawable : std::is_base_of<sf::Drawable, InType> {};

	/// @brief Checks if a type is drawable. 
	/// @tparam InType The type to check
	template <class InType>
	inline constexpr bool is_drawable_v = is_drawable<InType>::value;

	/// @brief Checks if a type is transformable.
	/// @tparam InType The type to check
	template <class InType>
	struct is_transformable : std::is_base_of<sf::Transformable, InType> {};

	/// @brief Checks if a type is transformable.
	/// @tparam InType The type to check
	template <class InType>
	inline constexpr bool is_transformable_v = is_transformable<InType>::value;

	/// @brief Checks if a type is updatable.
	/// @tparam InType The type to check
	template <class InType>
	struct is_updatable : std::is_base_of<GB::Updatable, InType> {};

	/// @brief Checks if a type is updatable.
	/// @tparam InType The type to check
	template <class InType>
	inline constexpr bool is_updatable_v = is_updatable<InType>::value;

	/// @brief Checks if a type is fulfills the requirements of a CompoundSprite component. (Drawable and Transformable)
	/// @tparam InType The type to check
	template <class InType>
	inline constexpr bool is_component_v = (is_drawable_v<InType> && is_transformable_v<InType>);

	/// @brief Checks if all types fulfill the requirements of a CompoundSprite component. (Drawable and Transformable)
	/// @tparam ...InTypes The types to check
	template <class... InTypes>
	inline constexpr bool are_all_components_v = (is_component_v<InTypes> && ...);

	/// @brief Controls several sf::Drawable and sf::Transformable Components as one logical unit.
	class libGameBackbone CompoundSprite : public Updatable, public sf::Drawable, public sf::Transformable {
	public:
		
		/// @brief Initializes a new instance of the <see cref="CompoundSprite"/>. The CompoundSprite has no components and is located at (0,0).
		CompoundSprite() {}

		// Forward declare ComponentWrapper to be used in the iterators
		class ComponentWrapper;

		using iterator = std::multimap<int, std::unique_ptr<ComponentWrapper>>::iterator;
		using const_iterator = std::multimap<int, std::unique_ptr<ComponentWrapper>>::const_iterator;

		/// @brief Get an iterator to the beginning of the Components.
		iterator begin() 
		{
			return m_prioritizedComponents.begin();
		}

		/// @brief Get an iterator to the end of the Components.
		iterator end()
		{
			return m_prioritizedComponents.end();
		}

		/// @brief Get a const_iterator to the beginning of the Components.
		const const_iterator cbegin()
		{
			return m_prioritizedComponents.cbegin();
		}

		/// @brief Get a const_iterator to the end of the Components.
		const const_iterator cend()
		{
			return m_prioritizedComponents.cend();
		}

		/// @brief Returns all Components for a given priority
		/// @param priority The priority of the Components to get
		std::vector<ComponentWrapper*> getComponentsWithPriorty(int priority)
		{
			std::vector<ComponentWrapper*> components;
			for (iterator iter = m_prioritizedComponents.begin(); iter != m_prioritizedComponents.end(); ++iter)
			{
				if (iter->first == priority)
				{
					components.push_back(iter->second.get());
				}
			}
			return components;
		}
		
		/// @brief Returns a vector of all prioties within the CompoundSprite
		std::vector<int> getComponentPriorties()
		{
			std::vector<int> priorities;
			for (iterator iter = m_prioritizedComponents.begin(); iter != m_prioritizedComponents.end(); ++iter)
			{
				priorities.push_back(iter->first);
			}
			return priorities;
		}

		/// @brief Initializes a new instance of the CompoundSprite class. The passed in Components are added to the CompoundSprite.
		///		The position of the CompoundSprite is (0,0).
		/// @tparam ...Components 
		/// @param priority The priority of the added components. Higher priority components will be drawn on top of components with lower priority.
		/// @param ...componentsToAdd The components.
		template <class... Components,
			std::enable_if_t<are_all_components_v<Components...>, bool> = true
		>
		explicit CompoundSprite(int priority, Components... componentsToAdd) : CompoundSprite(sf::Vector2f{ 0,0 }, priority, std::move(componentsToAdd)...) {}

		/// @brief Initializes a new instance of the CompoundSprite class. The provided Components are added to the CompoundSprite at the given priority.
		///		Initializes the CompoundSprite to the passed position.
		/// @tparam ...Components 
		/// @param position The position.
		/// @param priority The priority of the added components. Higher priority components will be drawn on top of components with lower priority.
		/// @param ...componentsToAdd The components.
		template <class... Components,
			std::enable_if_t<are_all_components_v<Components...>, bool> = true
		>
		CompoundSprite(sf::Vector2f position, int priority, Components... componentsToAdd)
		{
			setPosition(position);

			// Add all of the passed components to the CompoundSprite using a fold expression and calling addComponent on each.
			(addComponent(priority, std::move(std::forward<Components>(componentsToAdd))), ...);
		}

		/// @brief Initializes a new instance of the <see cref="CompoundSprite"/> class. Sets the initial position of the CompoundSprite to the passed value.
		/// @param position The initial position.
		explicit CompoundSprite(sf::Vector2f position);

		/// @brief Initializes a new instance of the CompoundSprite class. 
		///		The copy constructor is needed to copy the internal vector.
		/// @param other The CompoundSprite to copy
		CompoundSprite(const CompoundSprite& other);

		/// @brief Copy assignment operator for the CompoundSprite class. 
		/// @param other The CompoundSprite to copy
		/// @return this
		CompoundSprite& operator=(const CompoundSprite& other);

		/// @brief Move construct a CompoundSprite. The new CompoundSprite takes ownership of the Components of
		///		the moved from CompoundSprite.
		/// @param other The CompoundSprite being moved.
		CompoundSprite(CompoundSprite&& other) noexcept;

		/// @brief Move assign a CompoundSprite. The new CompoundSprite takes ownership of the components of
		///		the moved from CompoundSprite
		/// @param other The CompoundSprite being moved.
		/// @return this
		CompoundSprite& operator=(CompoundSprite&& other) noexcept;

		/// @brief Destroy this CompoundSprite
		virtual ~CompoundSprite() = default;

		// Component Getters

		/// @brief Gets the number of components owned by the CompoundSprite
		/// @return The number of components owned by the CompoundSprite
		std::size_t getComponentCount() const;

		/// @brief Gets the number of components owned by the CompoundSprite with a given priority.
		/// @param priority The priority.
		/// @return The number of components owned by the CompoundSprite with the given priority.
		std::size_t getComponentCount(int priority) const;

		/// @brief True if this CompoundSprite holds no components. False otherwise.
		bool isEmpty() const;

		/// @brief Adds the passed in Component to the CompoundSprite and returns a reference to it.
		///		The position stays the same on screen and the origin is set to the CompoundSprite's origin.
		/// @tparam Component A class that satisfies the requirements of is_component_v
		/// @param priority The priority of the added component. Higher priority components will be drawn on top of components with lower priority.
		/// @param component The component to add.
		/// @return A reference to the added component.
		template <
			class Component,
			std::enable_if_t<is_component_v<Component>, bool> = true
		>
		Component& addComponent(int priority, Component component) {
			/* Moving the origin moves the drawn entity in the opposite direction.
			 * Move the origin of the component to the current position of the CompoundSprite
			 * and offset it by the origin of the CompoundSprite (this keeps things in the right place
			 * if the origin has been changed before the component is added).
			 *
			 * Setting the position of the component to the position of the compound sprite will then
			 * make the entity appear in the same place but rotate around the origin of the compound sprite
			 * instead of its own origin.
			 */
			component.setOrigin(getPosition().x + getOrigin().x - component.getPosition().x, getPosition().y + getOrigin().y - component.getPosition().y);
			component.setPosition(getPosition().x, getPosition().y);


			// Add the component to the prioritizedComponents
			auto it = m_prioritizedComponents.emplace(priority, std::make_unique<ComponentAdapter<Component>>(std::move(component)));
			std::unique_ptr<ComponentWrapper>& returnValue = it->second;
		
			// Return the place in the components vector that the new component was placed.
			return static_cast<Component&>(returnValue->getDataAsDrawable());
		}

		/// @brief Removes the component from the CompoundSprite.
		///		This invalidates all indices returned by addComponent
		/// @tparam Component 
		/// @param componentToRemove The component to remove from the CompoundSprite 
		template <
			class Component,
			std::enable_if_t<is_component_v<Component>, bool> = true
		>
		void removeComponent(Component& componentToRemove)
		{
			// Find the drawable inside of the internal map.
			auto it = std::find_if(m_prioritizedComponents.begin(), m_prioritizedComponents.end(),
				[&componentToRemove](const std::pair<int, std::unique_ptr<ComponentWrapper>>& possibleRemoval) -> bool {
					sf::Drawable& underlyingData = possibleRemoval.second->getDataAsDrawable();
					return &(underlyingData) == &componentToRemove;
				});

			// If the drawable was found, erase it.
			if (it != m_prioritizedComponents.end())
			{
				m_prioritizedComponents.erase(it);
			}
		}

		/// @brief Removes all components from the compound sprite
		void clearComponents();

		// Transformable API

		/// @brief Sets the position.
		/// @param x The new x.
		/// @param y The new y.
		void setPosition(float x, float y);

		/// @brief Sets the rotation of the CompoundSprite and all of its components.
		///		The components will rotate about the origin of the CompoundSprite.
		/// @param position The value.
		void setPosition(const sf::Vector2f& position);

		/// @brief Sets the rotation of the CompoundSprite and all of its components.
		///		The components will rotate about the origin of the CompoundSprite.
		/// @param angle Angle of rotation, in degrees.
		void setRotation(float angle);

		/// @brief Sets the scale factor of the CompoundSprite and all of its components.
		/// @param factorX The scale factor in the x direction.
		/// @param factorY The scale factor in the y direction.
		void setScale(float factorX, float factorY);

		/// @brief Sets the scale factor of the CompoundSprite and all of its components.
		/// @param factors The new scale.
		void setScale(const sf::Vector2f& factors);

		/// @brief Sets the origin of the compound sprite.
		///		Sets the origin of all components relative to the new origin.
		/// @param x The x coordinate of the new origin.
		/// @param y The y coordinate of the new origin.
		void setOrigin(float x, float y);

		/// @brief Sets the origin of the compound sprite.
		///		Sets the origin of all components relative to the new origin.
		/// @param origin The new position of the origin.
		void setOrigin(const sf::Vector2f& origin);

		/// @brief Moves the CompoundSprite and all of its components by the same offset.
		/// @param offsetX The offset x.
		/// @param offsetY The offset y.
		void move(float offsetX, float offsetY);

		/// @brief Moves the CompoundSprite and all of its components by the same offset.
		/// @param offset The offset.
		void move(const sf::Vector2f& offset);

		/// @brief Rotates the CompoundSprite and all of its components.
		///		The components will rotate about the origin of the CompoundSprite.
		/// @param angle The offset to the current rotation.
		void rotate(float angle);

		/// @brief Scales the CompoundSprite and all of its components.
		/// @param factorX The horizontal scale factor.
		/// @param factorY The vertical scale factor.
		void scale(float factorX, float factorY);

		/// @brief Scales the CompoundSprite and all of its components.
		/// @param factor The scale factors.
		void scale(const sf::Vector2f& factor);

		/// @brief Updates each animated sprite in the compound sprite.
		/// @param elapsedTime The elapsed time.
		virtual void update(sf::Int64 elapsedTime) override;

	protected:

		/// @brief Draw all the component sprites of the compound sprite.
		/// @param target The render target to be drawn to. 
		/// @param states Current render states.
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		/// @brief Helper Class used by ComponentWrapper to virtually forward calls from sf::Transformables
		///  to ComponentAdapter which will then forward the calls nonvirtually to the type erased data. 
		class VirtualTransformable : public sf::Transformable {
		public:
			virtual ~VirtualTransformable() = default;

			virtual void setPosition(float x, float y) = 0;
			virtual void setPosition(const sf::Vector2f& position) = 0;
			virtual void setRotation(float angle) = 0;
			virtual void setScale(float factorX, float factorY) = 0;
			virtual void setScale(const sf::Vector2f& factors) = 0;
			virtual void setOrigin(float x, float y) = 0;
			virtual void setOrigin(const sf::Vector2f& origin) = 0;
			virtual const sf::Vector2f& getPosition() const = 0;
			virtual float getRotation() const = 0;
			virtual const sf::Vector2f& getScale() const = 0;
			virtual const sf::Vector2f& getOrigin() const = 0;
			virtual void move(float offsetX, float offsetY) = 0;
			virtual void move(const sf::Vector2f& offset) = 0;
			virtual void rotate(float angle) = 0;
			virtual void scale(float factorX, float factorY) = 0;
			virtual void scale(const sf::Vector2f& factor) = 0;
			virtual const sf::Transform& getTransform() const = 0;
			virtual const sf::Transform& getInverseTransform() const = 0;
		};


	public: 
		/// @brief Class that a Component's data in CompoundSprite is stored as. 
		/// This is a type erased class and works using virtual calls to forward the necessary functions.
		class ComponentWrapper : public sf::Drawable, public VirtualTransformable, public GB::Updatable {
		public:
			ComponentWrapper() = default;
			virtual ~ComponentWrapper() = default;

			// Deleting Copy/Move Constructors because ComponentWrapper cannot know the type of ComponentAdapter. Instead, using a clone method, which is virtual.
			ComponentWrapper(const ComponentWrapper&) = delete;
			ComponentWrapper& operator=(const ComponentWrapper&) = delete;
			ComponentWrapper(ComponentWrapper&&) noexcept = delete;
			ComponentWrapper& operator=(ComponentWrapper&&) noexcept = delete;

			/// @brief An exception of this type is thrown when a Component cannot be cast to the expected type.
			class BadComponentCast : public std::bad_cast {
			public:
				BadComponentCast() noexcept : bad_cast() {}
				const char* what() const noexcept override
				{
					return "Bad Component Cast";
				}
			};

			/// @brief Clones the object as a unique pointer. This is used to virtually forward the clone call to ComponentAdapter.
			virtual std::unique_ptr<ComponentWrapper> cloneAsUnique() = 0;

			/// @brief Returns the data stored within the ComponentWrapper as an sf::Drawable&
			virtual sf::Drawable& getDataAsDrawable() = 0;

			/// @brief Returns the data stored within the ComponentWrapper cast to the passed in type.
			/// @tparam ExpectedComponentType The type of the data within the ComponentWrapper. The type to return the data as.
			/// @throws BadComponentCast Thrown when the data is not of ExpectedComponentType.
			template <
				class ExpectedComponentType,
				std::enable_if_t<is_component_v<ExpectedComponentType>, bool> = true
			>
			ExpectedComponentType& getDataAs()
			{
				ExpectedComponentType* data = dynamic_cast<ExpectedComponentType*>(&this->getDataAsDrawable());
				if (data == nullptr)
				{
					throw BadComponentCast{};
				}
				return *data;
			}
		};

	private:
		/// @brief Class which actually stores the data of the type erased ComponentWrapper. Used primarily to forward calls to the Component data.
		/// @tparam Component The type of the Component to store.
		template <class Component>
		class ComponentAdapter final : public ComponentWrapper {
		protected:
			// Protected draw call forwards the draw call passing the sf::Drawable data.
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override
			{
				target.draw(m_data, states);
			}

		public:
			explicit ComponentAdapter(Component x) : m_data(std::move(x)) { }

			// Deleting Copy/Move Constructors because ComponentWrapper cannot know the type of ComponentAdapter. Instead, using a clone method, which is virtual.
			ComponentAdapter(const ComponentAdapter&) = delete;
			ComponentAdapter& operator=(const ComponentAdapter&) = delete;
			ComponentAdapter(ComponentAdapter&&) noexcept = delete;
			ComponentAdapter& operator=(ComponentAdapter&&) noexcept = delete;

			// Routes calls to update for GB::Updatable. Uses SFINAE and ADL to determine which version of update_helper to call. 
			// If the Component is not an GB::Updatable, it is an empty function call.
			void update([[maybe_unused]] sf::Int64 elapsedTime) override
			{
				if constexpr (is_updatable_v<Component>)
				{
					updateHelper(elapsedTime);
				}
			}

			// The update_helper method for anything that inherits from GB::Updatable. Forwards the call to the data.
			void updateHelper(sf::Int64 elapsedTime)
			{
				m_data.update(elapsedTime);
			}

			// Clones the object as a unique pointer. Always called virtually from ComponentWrapper. 
			// It cannot be done in ComponentWrapper as the type has already been erased. This can be done here as the type of Component is known.
			std::unique_ptr<ComponentWrapper> cloneAsUnique() override
			{
				return std::make_unique<ComponentAdapter<Component>>(m_data);
			}

			sf::Drawable& getDataAsDrawable() override
			{
				return m_data;
			}

			// Overrides for the VirtualTransformable API. Forwards to the data.
			void setPosition(float x, float y) override { m_data.setPosition(x, y); }
			void setPosition(const sf::Vector2f& position) override { m_data.setPosition(position); }
			void setRotation(float angle) override { m_data.setRotation(angle); }
			void setScale(float factorX, float factorY) override { m_data.setScale(factorX, factorY); }
			void setScale(const sf::Vector2f& factors) override { m_data.setScale(factors); }
			void setOrigin(float x, float y) override { m_data.setOrigin(x, y); }
			void setOrigin(const sf::Vector2f& origin) override { m_data.setOrigin(origin); }
			const sf::Vector2f& getPosition() const override { return m_data.getPosition(); }
			float getRotation() const override { return m_data.getRotation(); }
			const sf::Vector2f& getScale() const override { return m_data.getScale(); }
			const sf::Vector2f& getOrigin() const override { return m_data.getOrigin(); }
			void move(float offsetX, float offsetY) override { m_data.move(offsetX, offsetY); }
			void move(const sf::Vector2f& offset) override { m_data.move(offset); }
			void rotate(float angle) override { m_data.rotate(angle); }
			void scale(float factorX, float factorY) override { m_data.scale(factorX, factorY); }
			void scale(const sf::Vector2f& factor) override { m_data.scale(factor); }
			const sf::Transform& getTransform() const override { return m_data.getTransform(); }
			const sf::Transform& getInverseTransform() const override { return m_data.getInverseTransform(); }

			// The Component data stored as a value type.
			Component m_data;
		};

		// Internal storage of the Components for CompoundSprite
		std::multimap<int, std::unique_ptr<ComponentWrapper>> m_prioritizedComponents;
	};
}
