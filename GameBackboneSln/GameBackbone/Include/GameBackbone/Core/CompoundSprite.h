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

	// Base Trait for Drawable
	template <class InType>
	struct is_drawable : std::is_base_of<sf::Drawable, InType> {};
	template <class InType>
	inline constexpr bool is_drawable_v = is_drawable<InType>::value;

	// Base Trait for Transformable
	template <class InType>
	struct is_transformable : std::is_base_of<sf::Transformable, InType> {};
	template <class InType>
	inline constexpr bool is_transformable_v = is_transformable<InType>::value;

	// Base Trait for Updatable
	template <class InType, class result_type = void>
	struct is_updatable : std::is_base_of<GB::Updatable, InType> {};
	template <class InType>
	inline constexpr bool is_updatable_v = is_updatable<InType>::value;

	/// <summary> Controls several sprites and animated sprites as one logical unit. </summary>
	class libGameBackbone CompoundSprite : public Updatable, public sf::Drawable, public sf::Transformable {
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="CompoundSprite"/>. The Compound sprite has no components and is located at (0,0).
		/// </summary>
		CompoundSprite() {}

		/// <summary>
		/// Initializes a new instance of the <see cref="CompoundSprite"/> class. The passed Sprites become components of the compound sprite.
		/// The position of the sprite is (0,0).
		/// </summary>
		/// <param name="componentsToAdd">The components.</param>
		template <class... Components>
		explicit CompoundSprite(Components... componentsToAdd) : CompoundSprite(sf::Vector2f{ 0,0 }, std::move(componentsToAdd)...) {}

		/// <summary>
		/// Initializes a new instance of the <see cref="CompoundSprite"/> class. The passed Sprites become components of the compound sprite.
		/// Initializes the CompoundSprite to the passed position.
		/// </summary>
		/// <param name="position">The position.</param>
		/// <param name="componentsToAdd">The components.</param>
		template <class... Components>
		CompoundSprite(sf::Vector2f position, Components... componentsToAdd)
		{
			setPosition(position);

			// Add all of the passed components to the RelativerotationSprite
			(addComponent(std::move(std::forward<Components>(componentsToAdd))), ...);
		}


		explicit CompoundSprite(sf::Vector2f position);
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
		virtual std::size_t getComponentCount() const;
		virtual bool isEmpty() const;

		// Add/Remove Components
		template <
			class Component,
			std::enable_if_t<is_transformable_v<Component>, bool> = true, // must be transformable
			std::enable_if_t<is_drawable_v<Component>, bool> = true // must be drawable
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
			std::unique_ptr<InternalType>& returnValue = m_internalComponents.emplace_back(std::make_unique<ComponentAdapter<Component>>(std::move(component))); // Should this be perfect forwarding?
		
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

		class InternalType : public sf::Drawable, public VirtualTransformable, public GB::Updatable {
		public:
			
			InternalType(){}
			virtual ~InternalType() = default;

			InternalType(const InternalType&) = delete;
			InternalType& operator=(const InternalType&) = delete;
			InternalType(InternalType&&) noexcept = delete;
			InternalType& operator=(InternalType&&) noexcept = delete;

			virtual std::unique_ptr<InternalType> cloneAsUnique() = 0;

		};
		template <class Component>
		class ComponentAdapter final : public InternalType {
		protected:

			void draw(sf::RenderTarget& target, sf::RenderStates states) const override
			{
				target.draw(data, states);
			}

		public:
			explicit ComponentAdapter(Component x) : data(std::move(x)) { }

			ComponentAdapter(const ComponentAdapter&) = delete;
			ComponentAdapter& operator=(const ComponentAdapter&) = delete;
			ComponentAdapter(ComponentAdapter&&) noexcept = delete;
			ComponentAdapter& operator=(ComponentAdapter&&) noexcept = delete;

			void update(sf::Int64 elapsedTime) override
			{
				update_helper<Component>(elapsedTime);
			}

			template <class Component,
			std::enable_if_t<is_updatable_v<Component>, bool> = true // must be Updatable
			>
			void update_helper(sf::Int64 elapsedTime)
			{
				data.update(elapsedTime);
			}

			template <class Component,
			std::enable_if_t<!is_updatable_v<Component>, bool> = true // must NOT be Updatable
			>
			void update_helper(sf::Int64) {}

			std::unique_ptr<InternalType> cloneAsUnique() override
			{
				std::unique_ptr<InternalType> internalName = std::make_unique<ComponentAdapter<Component>>(data);
				return std::unique_ptr<InternalType>();
			}

			// Transformable
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

			Component data;
		};

		std::vector<std::unique_ptr<InternalType>> m_internalComponents;

			
	};
}
