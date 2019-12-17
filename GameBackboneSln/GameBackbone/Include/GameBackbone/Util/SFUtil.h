#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <functional>
#include <iterator>
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

	struct test
	{
		auto operator()(std::vector<int>::iterator& it)
		{
			return float{};
		}
	};

	template <class Iterator, typename ConversionFuncType, class TargetType>
	class IteratorAdapter
	{
	public:
		// std::iterator_traits types
		using value_type = TargetType;
		using difference_type = typename std::iterator_traits<Iterator>::difference_type;
		using pointer = value_type*;
		using reference = value_type;
		using iterator_category = std::input_iterator_tag;

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

		template <
			class OtherIterator,
			std::enable_if_t <
				std::is_convertible_v<OtherIterator, const Iterator&>,
				bool
			> = true
		>
		bool operator==(const OtherIterator& other) const {
			return (this->m_wrappedIt == (const Iterator&)other); // TODO: Make this less gross
		}

		template <
			class OtherIterator,
			std::enable_if_t <
				std::is_convertible_v<OtherIterator, const Iterator&>,
				bool
			> = true
		>
		bool operator!=(const OtherIterator& other) const {
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

		//template<
		//	std::enable_if_t<
		//		std::is_same_v<
		//			std::bidirectional_iterator_tag,
		//			std::iterator_traits<typename Iterator>::iterator_category
		//		>,/* ||
		//		std::is_same_v<std::random_access_iterator_tag, std::iterator_traits<Iterator>::iterator_category>>,*/
		//		bool
		//	> = true
		//>
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

		// Random access iterator member functions https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator#Concept

		IteratorAdapter& operator+=(difference_type n)
		{
			m_wrappedIt += n;
			return *this;
		}

		IteratorAdapter& operator-=(difference_type n)
		{
			m_wrappedIt -= n;
			return *this;
		}

		IteratorAdapter operator+(difference_type n) const
		{
			Iterator tempIt = m_wrappedIt;
			tempIt += n;
			return IteratorAdapter(tempIt, m_convert);
		}

		friend IteratorAdapter operator+(difference_type lhs, const IteratorAdapter& rhs)
		{
			return rhs + lhs;
		}

		IteratorAdapter operator-(difference_type n) const
		{
			Iterator tempIt = m_wrappedIt;
			tempIt -= n;
			return IteratorAdapter(tempIt, m_convert);
		}

		friend difference_type operator-(difference_type lhs, const IteratorAdapter& rhs)
		{
			return lhs - rhs.m_wram_wrappedIt;
		}

		reference operator[](difference_type n)
		{
			IteratorAdapter temp = *this;
			temp += n;
			return *temp;
		}

	private:
		Iterator m_wrappedIt;
		ConversionFuncType m_convert;
	};

	// TODO: Use SFINAE here to allow user to create IteratorAdapter for end without providing
	// this really needs to be tested on Linux. SFINAE in deduction guides is a very new feature that MSVC
	// only started supporting in 2019

	// Deduction guides
	template<class Iterator, class ConversionFunc> IteratorAdapter(Iterator, ConversionFunc) ->
		IteratorAdapter<std::remove_reference_t<Iterator> , std::decay_t<ConversionFunc>, std::invoke_result_t<std::decay_t<ConversionFunc>, Iterator&>>;

}
