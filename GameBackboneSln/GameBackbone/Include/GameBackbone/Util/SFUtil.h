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
	/// Determines if the input type is an iterator.
	/// IsIterator<input>::value is true if the input is an iterator and false if it is not
	/// </summary>
	template <class, class = std::void_t<> >
	struct IsIterator : std::false_type {};

	/// <summary>
	/// Determines if the input type is an iterator.
	/// IsIterator<input>::value is true if the input is an iterator and false if it is not
	/// </summary>
	template <class Iterator>
	struct IsIterator <
		Iterator,
		typename std::enable_if_t<
			!std::is_same_v<typename std::iterator_traits<Iterator>::value_type, void>
		> 
	> : std::true_type {};

	/// <summary>
	/// Determines if the input type is an iterator.
	/// Evaluates to true if the input is an iterator and false if it is not
	/// </summary>
	template <typename T>
	constexpr inline bool IsIterator_v = IsIterator<T>::value;

	/// <summary>
	/// Wraps an input iterator and applies a transform to it whenever it is dereferenced
	/// </summary>
	template <
		class Iterator,
		typename ConversionFuncType,
		class TargetType,
		std::enable_if_t<
			/*Calling function gets result*/
			std::is_invocable_r_v<TargetType, std::decay_t<ConversionFuncType>, Iterator&>,
			bool
		> = true,
		std::enable_if_t<
			/*Iterator is actually an iterator*/ 
			IsIterator_v<Iterator>,
			bool
		> = true
	>
	class IteratorAdapter
	{
	public:
		// std::iterator_traits types
		using value_type = TargetType;
		using difference_type = typename std::iterator_traits<Iterator>::difference_type;
		using pointer = value_type*;
		using reference = value_type;
		using iterator_category = std::input_iterator_tag;
		using WrappedIteratorType = Iterator;

		/// <summary>
		/// True if random access operations are supported by this iterator. Note that this does not make this a random access iterator and it will still not work 
		/// with algorithms that require all the guarantees of a random access iterator.
		/// </summary>
		static inline constexpr bool supportsRandomAccess =
			std::is_same_v< typename std::iterator_traits<Iterator>::iterator_category, std::random_access_iterator_tag >;

		/// <summary>
		/// True if bidirectional operations are supported by this iterator. Note that this does not make this a random access iterator and it will still not work 
		/// with algorithms that require all the guarantees of a random access iterator.
		/// </summary>
		static inline constexpr bool supportsBidirectional =
			supportsRandomAccess ||
			std::is_same_v< typename std::iterator_traits<Iterator>::iterator_category, std::bidirectional_iterator_tag >;

		/// <summary>
		/// Constructor:
		/// Wraps the provided iterator and applies the conversion function to it on every dereference
		/// </summary>
		/// <param name="wrapped"> The iterator to be wrapped.</param>
		/// <param name="conversionFunc"> function applied to the wrapped iterator whenever this IteratorAdapter is dereferenced.</param>
		IteratorAdapter(Iterator wrapped, ConversionFuncType conversionFunc) :
			m_wrappedIt(std::move(wrapped)),
			m_convert(std::move(conversionFunc))
		{
		}

		/// <summary>
		/// Converts this IteratorAdapter to the wrapped iterator
		/// </summary>
		operator Iterator()
		{
			return m_wrappedIt;
		}

		/// <summary>
		/// Apply the unary operation to the wrapped iterator and return the result
		/// </summary>
		/// <return> The result of applying the unary operation to the wrapped iterator. </return>
		reference operator*() const
		{
			return m_convert(m_wrappedIt);
		}

		// Universal iterator member functions

		/// <summary>
		/// Compare this Iterator with a compatible one for equality
		/// </summary>
		/// <return> True if the iterators represent the same element. False otherwise. </return>
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

		/// <summary>
		/// Compare this Iterator with a compatible one for inequality
		/// </summary>
		/// <return> True if the iterators do not represent the same element. False otherwise. </return>
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

		/// <summary>
		/// Moves the iterator forward.
		/// </summary>
		/// <return> The iterator after being moved forward. </return>
		IteratorAdapter& operator++()
		{
			++m_wrappedIt;
			return *this;
		}

		/// <summary>
		/// Moves the iterator forward.
		/// </summary>
		/// <return> A new iterator at the position of the original before it was moved forward. </return>
		IteratorAdapter operator++(int)
		{
			IteratorAdapter out(*this);
			++(*this);
			return out;
		}

		/// <summary>
		/// Moves the iterator backward.
		/// Only available if the wrapped iterator is a bidirectional iterator.
		/// </summary>
		/// <return> A new iterator at the position of the original before it was moved backward. </return>
		template <
			std::enable_if_t<IteratorAdapter::supportsBidirectional, bool> = true
		>
		IteratorAdapter& operator--()
		{
			--m_wrappedIt;
			return *this;
		}

		/// <summary>
		/// Moves the iterator backward.
		/// Only available if the wrapped iterator is a bidirectional iterator.
		/// </summary>
		/// <return> A new iterator at the position of the original before it was moved backward. </return>
		template <
			std::enable_if_t<IteratorAdapter::supportsBidirectional, bool> = true
		>
		IteratorAdapter<Iterator, ConversionFuncType, TargetType> operator--(int)
		{
			IteratorAdapter out(*this);
			--(*this);
			return out;
		}

		/// <summary>
		/// Moves the iterator forward n steps.
		/// Only available if the wrapped iterator is a random access iterator.
		/// </summary>
		/// <param name="n"> The number of steps. </return>
		/// <return> This iterator at its new position. </return>
		template <
			std::enable_if_t<IteratorAdapter::supportsRandomAccess, bool> = true
		>
		IteratorAdapter& operator+=(difference_type n)
		{
			m_wrappedIt += n;
			return *this;
		}

		/// <summary>
		/// Moves the iterator backward n steps.
		/// Only available if the wrapped iterator is a random access iterator.
		/// </summary>
		/// <param name="n"> The number of steps. </return>
		/// <return> This iterator at its new position. </return>
		template <
			std::enable_if_t<IteratorAdapter::supportsRandomAccess, bool> = true
		>
		IteratorAdapter& operator-=(difference_type n)
		{
			m_wrappedIt -= n;
			return *this;
		}

		/// <summary>
		/// Returns a new the iterator n steps forward from this one.
		/// Only available if the wrapped iterator is a random access iterator.
		/// </summary>
		/// <param name="n"> The number of steps. </return>
		/// <return> This iterator at its new position. </return>
		template <
			std::enable_if_t<IteratorAdapter::supportsRandomAccess, bool> = true
		>
		IteratorAdapter operator+(difference_type n) const
		{
			Iterator tempIt = m_wrappedIt;
			tempIt += n;
			return IteratorAdapter(tempIt, m_convert);
		}

		/// <summary>
		/// Returns a new the iterator n steps forward from this one.
		/// Only available if the wrapped iterator is a random access iterator.
		/// </summary>
		/// <param name="lhs"> The number of steps. </return>
		/// <param name="rhs"> The starting point. </return>
		/// <return> This iterator at its new position. </return>
		template <
			std::enable_if_t<IteratorAdapter::supportsRandomAccess, bool> = true
		>
		friend IteratorAdapter operator+(difference_type lhs, const IteratorAdapter& rhs)
		{
			return rhs + lhs;
		}


		/// <summary>
		/// Returns a new the iterator n steps backward from this one.
		/// Only available if the wrapped iterator is a random access iterator.
		/// </summary>
		/// <param name="n"> The number of steps. </return>
		/// <return> This iterator at its new position. </return>
		template <
			std::enable_if_t<IteratorAdapter::supportsRandomAccess, bool> = true
		>
		IteratorAdapter operator-(difference_type n) const
		{
			Iterator tempIt = m_wrappedIt;
			tempIt -= n;
			return IteratorAdapter(tempIt, m_convert);
		}

		/// <summary>
		/// Apply the unary operation to the wrapped iterator n steps forward from its current position and return the result.
		/// This iterator is not moved.
		/// Only available if the wrapped iterator is a random access iterator.
		/// 
		/// Behavior is undefined if  the lifetime of the result of the unary operation is dependent on the
		/// lifetime of the wrapped iterator.
		/// </summary>
		/// <param name="n"> The number of steps. </return>
		/// <return>  The result of applying the unary operation to the wrapped iterator n steps forward from its current position.  </return>
		template <
			std::enable_if_t<IteratorAdapter::supportsRandomAccess, bool> = true
		>
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

	// Deduction guide
	template<class Iterator, class ConversionFunc> IteratorAdapter(Iterator, ConversionFunc) ->
		IteratorAdapter<std::remove_reference_t<Iterator> , std::decay_t<ConversionFunc>, std::invoke_result_t<std::decay_t<ConversionFunc>, std::remove_reference_t<Iterator>&>>;

}
