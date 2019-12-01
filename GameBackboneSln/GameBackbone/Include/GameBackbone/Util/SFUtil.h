#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <type_traits>
#include <functional>

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

	template <class Iterator, class TargetType>
	class IteratorAdapter
	{
	public:
		// Previously provided by std::iterator
		using value_type = TargetType;
		using difference_type = typename std::iterator_traits<Iterator>::difference_type;
		using pointer = value_type*;
		using reference = value_type&;
		using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;

		// helper typedefs
		using ConversionFuncType = std::function<TargetType & (const Iterator&)>;

		explicit IteratorAdapter(Iterator wrapped) : IteratorAdapter(std::move(wrapped), ConversionFuncType{}) {}

		IteratorAdapter(Iterator wrapped, ConversionFuncType conversionFunc) :
			m_wrappedIt(std::move(wrapped)),
			m_convert(std::move(conversionFunc))
		{
		}

		operator Iterator()
		{
			return m_wrappedIt;
		}

		reference operator*() const
		{
			return m_convert(m_wrappedIt);
		}

		// Universal iterator member functions

		template <class OtherIteratorAdapter>
		bool operator==(const OtherIteratorAdapter& other) const {
			return (this->m_wrappedIt == (Iterator)other);
		}

		template <class OtherIteratorAdapter>
		bool operator!=(const OtherIteratorAdapter& other) const {
			return ! ((*this) == other);
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

		// Bidirectional iterator member functions

		// Random access iterator member functions

	private:
		Iterator m_wrappedIt;
		ConversionFuncType m_convert;
	};

	// Deduction guides
	template<class Iterator, class ConversionFunc> IteratorAdapter(Iterator, ConversionFunc) ->
		IteratorAdapter<Iterator, std::invoke_result_t<ConversionFunc>>;

}
