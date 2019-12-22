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

	template <class, class = std::void_t<> >
	struct IsIterator : std::false_type {};

	template <class Iterator>
	struct IsIterator <
		Iterator,
		typename std::enable_if_t<
			!std::is_same_v<typename std::iterator_traits<Iterator>::value_type, void>
		> 
	> : std::true_type {};

	template <typename T>
	constexpr inline bool IsIterator_v = IsIterator<T>::value;

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

		// Supporting SFINAE checks
		static inline constexpr bool supportsRandomAccess =
			std::is_same_v< typename std::iterator_traits<Iterator>::iterator_category, std::random_access_iterator_tag >;
		static inline constexpr bool supportsBidirectional =
			supportsRandomAccess ||
			std::is_same_v< typename std::iterator_traits<Iterator>::iterator_category, std::bidirectional_iterator_tag >;

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
			IteratorAdapter out(*this);
			++(*this);
			return out;
		}

		// Bidirectional iterator member functions

		template <
			std::enable_if_t<IteratorAdapter::supportsBidirectional, bool> = true
		>
		IteratorAdapter& operator--()
		{
			--m_wrappedIt;
			return *this;
		}

		template <
			std::enable_if_t<IteratorAdapter::supportsBidirectional, bool> = true
		>
		IteratorAdapter<Iterator, ConversionFuncType, TargetType> operator--(int)
		{
			IteratorAdapter out(*this);
			--(*this);
			return out;
		}

		// Random access iterator member functions

		template <
			std::enable_if_t<IteratorAdapter::supportsRandomAccess, bool> = true
		>
		IteratorAdapter& operator+=(difference_type n)
		{
			m_wrappedIt += n;
			return *this;
		}

		template <
			std::enable_if_t<IteratorAdapter::supportsRandomAccess, bool> = true
		>
		IteratorAdapter& operator-=(difference_type n)
		{
			m_wrappedIt -= n;
			return *this;
		}

		template <
			std::enable_if_t<IteratorAdapter::supportsRandomAccess, bool> = true
		>
		IteratorAdapter operator+(difference_type n) const
		{
			Iterator tempIt = m_wrappedIt;
			tempIt += n;
			return IteratorAdapter(tempIt, m_convert);
		}

		template <
			std::enable_if_t<IteratorAdapter::supportsRandomAccess, bool> = true
		>
		friend IteratorAdapter operator+(difference_type lhs, const IteratorAdapter& rhs)
		{
			return rhs + lhs;
		}

		template <
			std::enable_if_t<IteratorAdapter::supportsRandomAccess, bool> = true
		>
		IteratorAdapter operator-(difference_type n) const
		{
			Iterator tempIt = m_wrappedIt;
			tempIt -= n;
			return IteratorAdapter(tempIt, m_convert);
		}

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
