#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <type_traits>

namespace GB {

	/// <summary>
	/// Used to compare which of two sf::Vector2 is less
	/// Designed to facilitate map and set use of sf::Vector2
	/// </summary>
	template <typename T>
	class IsVector2Less {
	public:
		constexpr bool operator()(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs) const {
			return lhs.x < rhs.x || (!(rhs.x < lhs.x) && lhs.y < rhs.y);
		}
	};

	/// <summary>
	/// Used to create new Drawable* vectors using Drawable child pointer vectors
	/// Designed to improve compatibility between vectors of Drawable and Drawable children
	/// </summary>
	template <
		class T,
		std::enable_if_t <
			std::is_pointer_v<T> &&
			!std::is_const_v<std::remove_pointer_t<T>> &&
			std::is_base_of_v<sf::Drawable, std::remove_pointer_t<T>>,
			bool
		> = true
	>
	std::vector<sf::Drawable*> toDrawableVector(const std::vector<T>& DrawableChild)
	{
		// Create vector of drawable
		std::vector<sf::Drawable*> drawableVector(DrawableChild.begin(), DrawableChild.end());
		return drawableVector;
	}

	/// <summary>
	/// Used to create new Drawable* vectors using Drawable child vectors
	/// Designed to improve compatibility between vectors of Drawable and Drawable children
	/// </summary>
	template <
		class T,
		std::enable_if_t<
			!std::is_pointer_v<T> &&
			!std::is_reference_v<T> &&
			!std::is_const_v<T> &&
			std::is_base_of_v<sf::Drawable, T>,
			bool
		> = true
	>
	std::vector<sf::Drawable*> toDrawableVector(const std::vector<T>& drawableChildren)
	{
		// Create vector of drawable
		std::vector<sf::Drawable*> drawableVector(drawableChildren.size());
		auto getPointer = [](const T& drawableChild)
		{ 
			// Strip const (its only there because of the vector API) and
			// cast to base class pointer
			return static_cast<sf::Drawable*>(&const_cast<std::remove_const_t<T&>>(drawableChild));  
		};
		std::transform(drawableChildren.begin(), drawableChildren.end(), drawableVector.begin(), getPointer);
		return drawableVector;
	}

	template <class T>
	class IteratorAdapter
	{
	public:
		// Previously provided by std::iterator
		typedef typename T::value_type::element_type*     value_type;
		typedef typename T::difference_type				 difference_type;
		typedef typename T::value_type::element_type**    pointer;
		typedef typename T::value_type::element_type*&    reference;
		typedef typename T::iterator_category			 iterator_category;

		explicit IteratorAdapter(T wrapped) : m_wrappedIt(std::move(wrapped)) {}
		//operator IteratorAdapter<T>()
		value_type operator*() const
		{
			return m_wrappedIt->get();
		}

		template <
			class U
		>
		bool operator==(const U& other)
		{
			return other == this->m_wrappedIt;
		}

		bool operator==(const T& other)
		{
			return this->m_wrappedIt == other;
		}

		//bool operator==(const IteratorAdapter& other) const {
		//	return m_wrappedIt == other.m_wrappedIt;
		//}

		bool operator!=(const IteratorAdapter& other) const {
			return !(*this == other.m_wrappedIt); 
		}

		IteratorAdapter& operator++()
		{
			++m_wrappedIt;
			return *this;
		}
		IteratorAdapter operator++(int)
		{
			IteratorAdapter out(this->m_wrappedIt);
			++(*this);
			return out;
		}

		IteratorAdapter& operator--()
		{
			--m_wrappedIt;
			return *this;
		}
		IteratorAdapter operator--(int)
		{
			IteratorAdapter out(this->m_wrappedIt);
			--(*this);
			return out;
		}

		difference_type operator-(const IteratorAdapter& other)
		{
			return this->m_wrappedIt - other.m_wrappedIt;
		}

		difference_type operator+(const IteratorAdapter& other)
		{
			return this->m_wrappedIt + other.m_wrappedIt;
		}

	private:
		T m_wrappedIt;
	};

}
