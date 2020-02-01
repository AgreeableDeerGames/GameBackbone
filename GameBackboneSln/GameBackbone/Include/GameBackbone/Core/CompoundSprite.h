#pragma once

#include <GameBackbone/Core/AnimatedSprite.h>
#include <GameBackbone/Core/Updatable.h>
#include <GameBackbone/Util/DllUtil.h>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <cstddef>
#include <set>
#include <utility>
#include <vector>


namespace GB {

	/// <summary> Checks if a type is drawable. </summary>
	template <class InType>
	struct is_drawable : std::is_base_of<sf::Drawable, InType> {};

	/// <summary> Checks if a type is drawable. </summary>
	template <class InType>
	inline constexpr bool is_drawable_v = is_drawable<InType>::value;

	/// <summary> Checks if a type is transformable. </summary>
	template <class InType>
	struct is_transformable : std::is_base_of<sf::Transformable, InType> {};

	/// <summary> Checks if a type is transformable. </summary>
	template <class InType>
	inline constexpr bool is_transformable_v = is_transformable<InType>::value;

	/// <summary> Checks if a type is updatable. </summary>
	template <class InType>
	struct is_updatable : std::is_base_of<GB::Updatable, InType> {};

	/// <summary> Checks if a type is updatable. </summary>
	template <class InType>
	inline constexpr bool is_updatable_v = is_updatable<InType>::value;

	/// <summary> Checks if a type is fulfills the requirements of a CompoundSprite component. (Drawable and Transformable) </summary>
	template <class InType>
	inline constexpr bool is_component_v = (is_drawable_v<InType> && is_transformable_v<InType>);

	/// <summary> Checks if all types fulfill the requirements of a CompoundSprite component. (Drawable and Transformable) </summary>
	template <class... InTypes>
	inline constexpr bool are_all_components_v = (is_component_v<InTypes> && ...);

	/// <summary> Controls several sf::Drawable and sf::Transformable Components as one logical unit. </summary>
	class libGameBackbone CompoundSprite : public Updatable, public sf::Drawable, public sf::Transformable {
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="CompoundSprite"/>. The CompoundSprite has no components and is located at (0,0).
		/// </summary>
		CompoundSprite() {}

		/// <summary>
		/// Initializes a new instance of the /<see cref="CompoundSprite"/> class. The passed in Components are added to the CompoundSprite.
		/// The position of the CompoundSprite is (0,0).
		/// </summary>
		/// <param name="componentsToAdd">The components.</param>
		template <class... Components,
			std::enable_if_t<are_all_components_v<Components...>, bool> = true
		>
		explicit CompoundSprite(Components... componentsToAdd) : CompoundSprite(sf::Vector2f{ 0,0 }, std::move(componentsToAdd)...) {}

		/// <summary>
		/// Initializes a new instance of the <see cref="CompoundSprite"/> class. The passed in Components are added to the CompoundSprite.
		/// Initializes the CompoundSprite to the passed position.
		/// </summary>
		/// <param name="position">The position.</param>
		/// <param name="componentsToAdd">The components.</param>
		template <class... Components,
			std::enable_if_t<are_all_components_v<Components...>, bool> = true
		>
		CompoundSprite(sf::Vector2f position, Components... componentsToAdd)
		{
			setPosition(position);

			// Add all of the passed components to the CompoundSprite using a fold expression and calling addComponent on each.
			(addComponent(std::move(std::forward<Components>(componentsToAdd))), ...);
		}


		explicit CompoundSprite(sf::Vector2f position);

		/// <summary>
		/// Initializes a new instance of the <see cref="CompoundSprite"/> class. The copy constructor is needed to copy the internal vector.
		/// </summary>
		/// <param name="other">The other CompoundSprite that is being copied.</param>
		CompoundSprite(const CompoundSprite& other) : CompoundSprite()
		{
			this->setPosition(other.getPosition());
			this->setRotation(other.getRotation());
			this->setScale(other.getScale());
			this->setOrigin(other.getOrigin());

			for (auto& component : other.m_internalComponents)
			{
				this->m_internalComponents.emplace_back(
					component->cloneAsUnique()
				);
			}
		}

		/// <summary>
		/// Initializes a new instance of the <see cref="CompoundSprite"/> class and returns it. This forwards to the Copy Constructor.
		/// </summary>
		/// <param name="other">The other CompoundSprite that is being copied.</param>
		CompoundSprite& operator=(const CompoundSprite& other)
		{
			CompoundSprite tempOther{ other };
			*this = std::move(tempOther);
			return *this;
		}

		CompoundSprite(CompoundSprite&&) noexcept = default;

		CompoundSprite& operator=(CompoundSprite&&) noexcept = default;

		virtual ~CompoundSprite() = default;

		// Component Getters
		std::size_t getComponentCount() const;

		bool isEmpty() const;

		/// <summary>
		/// Adds the passed in Component to the CompoundSprite and returns a reference to it.
		/// The position stays the same on screen and the origin is set to the CompoundSprite's origin.
		/// </summary>
		/// <param name="other">The other CompoundSprite that is being copied.</param>
		template <
			class Component,
			std::enable_if_t<is_component_v<Component>, bool> = true
		>
		Component& addComponent(Component component) {
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

			// Add the component to the internalComponents
			std::unique_ptr<InternalType>& returnValue = m_internalComponents.emplace_back(std::make_unique<ComponentAdapter<Component>>(std::move(component)));
		
			// Return the place in the components vector that the new component was placed.
			return static_cast<ComponentAdapter<Component>*>(returnValue.get())->data;
		}

		virtual void removeComponent(std::size_t componentIndex);
		virtual void clearComponents();

		// Transformable API
		void setPosition(float x, float y);
		void setPosition(const sf::Vector2f& position);
		void setRotation(float angle);
		void setScale(float factorX, float factorY);
		void setScale(const sf::Vector2f& factors);
		void setOrigin(float x, float y);
		void setOrigin(const sf::Vector2f& origin);
		void move(float offsetX, float offsetY);
		void move(const sf::Vector2f& offset);
		void rotate(float angle);
		void scale(float factorX, float factorY);
		void scale(const sf::Vector2f& factor);

		// Updatable
		virtual void update(sf::Int64 elapsedTime) override;

	protected:
		
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		// Helper Class used by InternalType to virtually forward calls from sf::Transformables
		// to ComponentAdapter which will then forward the calls nonvirtually to the type erased data. 
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

		// Class that a Component's data in CompoundSprite is stored as. This is a type erased class and works using virtual calls to forward the necessary functions.
		class InternalType : public sf::Drawable, public VirtualTransformable, public GB::Updatable {
		public:
			InternalType(){}
			virtual ~InternalType() = default;

			// Deleting Copy/Move Constructors because InternalType cannot know the type of ComponentAdapter. Instead, using a clone method, which is virtual.
			InternalType(const InternalType&) = delete;
			InternalType& operator=(const InternalType&) = delete;
			InternalType(InternalType&&) noexcept = delete;
			InternalType& operator=(InternalType&&) noexcept = delete;

			// Clones the object as a unique pointer. This is used to virtually forward the clone call to ComponentAdapter.
			virtual std::unique_ptr<InternalType> cloneAsUnique() = 0;
		};

		// Class which actually stores the data of the type erased InternalType. Used primarily to forward calls to the Component data.
		template <class Component>
		class ComponentAdapter final : public InternalType {
		protected:

			// Protected draw call forwards the draw call passing the sf::Drawable data.
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override
			{
				target.draw(data, states);
			}

		public:
			explicit ComponentAdapter(Component x) : data(std::move(x)) { }

			// Deleting Copy/Move Constructors because InternalType cannot know the type of ComponentAdapter. Instead, using a clone method, which is virtual.
			ComponentAdapter(const ComponentAdapter&) = delete;
			ComponentAdapter& operator=(const ComponentAdapter&) = delete;
			ComponentAdapter(ComponentAdapter&&) noexcept = delete;
			ComponentAdapter& operator=(ComponentAdapter&&) noexcept = delete;

			// Routes calls to update for GB::Updatable. Uses SFINAE and ADL to determine which version of update_helper to call. 
			// If the Component is not an GB::Updatable, it is an empty function call.
			void update(sf::Int64 elapsedTime) override
			{
				if constexpr (is_updatable_v<Component>)
				{
					updateHelper(elapsedTime);
				}
			}

			// The update_helper method for anything that inherits from GB::Updatable. Forwards the call to the data.
			void updateHelper(sf::Int64 elapsedTime)
			{
				data.update(elapsedTime);
			}

			// Clones the object as a unique pointer. Always called virtually from InternalType. 
			// It cannot be done in InternalType as the type has already been erased. This can be done here as the type of Component is known.
			std::unique_ptr<InternalType> cloneAsUnique() override
			{
				return std::make_unique<ComponentAdapter<Component>>(data);
			}

			// Overrides for the VirtualTransformable API. Forwards to the data.
			void setPosition(float x, float y) override { data.setPosition(x, y); }
			void setPosition(const sf::Vector2f& position) override { data.setPosition(position); }
			void setRotation(float angle) override { data.setRotation(angle); }
			void setScale(float factorX, float factorY) override { data.setScale(factorX, factorY); }
			void setScale(const sf::Vector2f& factors) override { data.setScale(factors); }
			void setOrigin(float x, float y) override { data.setOrigin(x, y); }
			void setOrigin(const sf::Vector2f& origin) override { data.setOrigin(origin); }
			const sf::Vector2f& getPosition() const override { return data.getPosition(); }
			float getRotation() const override { return data.getRotation(); }
			const sf::Vector2f& getScale() const override { return data.getScale(); }
			const sf::Vector2f& getOrigin() const override { return data.getOrigin(); }
			void move(float offsetX, float offsetY) override { data.move(offsetX, offsetY); }
			void move(const sf::Vector2f& offset) override { data.move(offset); }
			void rotate(float angle) override { data.rotate(angle); }
			void scale(float factorX, float factorY) override { data.scale(factorX, factorY); }
			void scale(const sf::Vector2f& factor) override { data.scale(factor); }
			const sf::Transform& getTransform() const override { return data.getTransform(); }
			const sf::Transform& getInverseTransform() const override { return data.getInverseTransform(); }

			// The Component data stored as a value type.
			Component data;
		};

		// Internal storage of the Components for CompoundSprite
		std::vector<std::unique_ptr<InternalType>> m_internalComponents;	
	};
}
