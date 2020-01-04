#pragma once

#include <type_traits>
#include <iterator>

namespace GB {

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
	
	namespace Detail
	{

		/// <summary>
		/// True if random access convenience operations are supported by this iterator.
		/// </summary>
		template <class Iterator>
		inline constexpr bool SupportsRandomAccess_v =
			std::is_same_v< typename std::iterator_traits<Iterator>::iterator_category, std::random_access_iterator_tag >;

		/// <summary>
		/// True if bidirectional convenience operations are supported by this iterator.
		/// </summary>
		template <class Iterator>
		inline constexpr bool SupportsBidirectional_v = 
			 SupportsRandomAccess_v<Iterator> ||
			 std::is_same_v< typename std::iterator_traits<Iterator>::iterator_category, std::bidirectional_iterator_tag >;

		/// <summary>
		/// Determines the iterator category of a transform iterator based on the category of the wrapped iterator
		/// and the result type of the transform.
		/// </summary>
		template <class Iterator, class UnaryOperation, class = std::void_t<>>
		struct TransformIteratorCategory
		{
			using type = std::input_iterator_tag;
		};

		/// <summary>
		/// Determines the iterator category of a transform iterator based on the category of the wrapped iterator
		/// and the result type of the transform.
		/// </summary>
		template <class Iterator, class UnaryOperation>
		struct TransformIteratorCategory<Iterator, UnaryOperation, std::enable_if_t<std::is_reference_v<std::invoke_result_t<std::decay_t<UnaryOperation>, Iterator&>>>>
		{
			using type = typename std::iterator_traits<Iterator>::iterator_category;
		};

		template <class Iterator, class UnaryOperation>
		using TransformIteratorCategory_t = typename TransformIteratorCategory<Iterator, UnaryOperation>::type;

		template <class Iterator, typename UnaryOperation>
		class TransformIteratorTraitProvider 
		{
		public:
			// Sanity checks
			static_assert(std::is_invocable_v<std::decay_t<UnaryOperation>, Iterator&>, "TransformIterator must be provided a UnaryOperation that operates on a reference to the type of its wrapped iterator.");
			static_assert(IsIterator_v<Iterator>, "TransformIterator must be provided a valid iterator type to wrap.");

			/// <summary>
			/// The type of the wrapped iterator.
			/// </summary>
			using WrappedIteratorType = Iterator;

			// std::iterator_traits types
			using reference = std::invoke_result_t<std::decay_t<UnaryOperation>, WrappedIteratorType&>;
			using value_type = std::remove_reference_t<reference>;
			using difference_type = typename std::iterator_traits<WrappedIteratorType>::difference_type;
			using pointer = value_type*;
			using iterator_category = TransformIteratorCategory_t<WrappedIteratorType, UnaryOperation>;
		};

		template <
			class CrtpChildIterator,
			class WrappedIterator,
			class UnaryOperation,
			class = std::void_t<>
		>
		class TransformIteratorBidirectionalHelper : public TransformIteratorTraitProvider<WrappedIterator, UnaryOperation> {};

		template <
			class CrtpChildIterator,
			class WrappedIterator,
			class UnaryOperation
		>
		class TransformIteratorBidirectionalHelper <CrtpChildIterator, WrappedIterator, UnaryOperation, std::enable_if_t<SupportsBidirectional_v<WrappedIterator>>> :
			public TransformIteratorTraitProvider<WrappedIterator, UnaryOperation>
		{
		private:
			using TraitProvider = TransformIteratorTraitProvider<WrappedIterator, UnaryOperation>;

		public:
			
			// Iterator types
			using typename TraitProvider::WrappedIteratorType;
			using typename TraitProvider::value_type;
			using typename TraitProvider::difference_type;
			using typename TraitProvider::pointer;
			using typename TraitProvider::reference;
			using typename TraitProvider::iterator_category;

			/// <summary>
			/// Moves the iterator backward.
			/// Only available if the wrapped iterator is a bidirectional iterator.
			/// </summary>
			/// <return> A new iterator at the position of the original before it was moved backward. </return>
			CrtpChildIterator& operator--()
			{
				--getCrtpThis->getWrappedIterator();
				return *getCrtpThis();
			}

			/// <summary>
			/// Moves the iterator backward.
			/// Only available if the wrapped iterator is a bidirectional iterator.
			/// </summary>
			/// <return> A new iterator at the position of the original before it was moved backward. </return>
			[[nodiscard]]
			CrtpChildIterator operator--(int)
			{
				CrtpChildIterator out(*this);
				--(*getCrtpThis());
				return out;
			}

		private:

			[[nodiscard]]
			CrtpChildIterator* getCrtpThis()
			{
				return static_cast<CrtpChildIterator*>(this);
			}
		};

		template <
			class CrtpChildIterator,
			class WrappedIterator,
			class UnaryOperation,
			class = std::void_t<>
		>
		class TransformIteratorRandomAccessHelper : public TransformIteratorBidirectionalHelper<CrtpChildIterator, WrappedIterator, UnaryOperation> {};

		template <
			class CrtpChildIterator,
			class WrappedIterator,
			class UnaryOperation
		>
		class TransformIteratorRandomAccessHelper <CrtpChildIterator, WrappedIterator, UnaryOperation, std::enable_if_t<SupportsRandomAccess_v<WrappedIterator>>> :
			public TransformIteratorBidirectionalHelper<CrtpChildIterator, WrappedIterator, UnaryOperation>
		{
		private:
			using TraitProvider = TransformIteratorTraitProvider<WrappedIterator, UnaryOperation>;

		public:

			// Iterator types
			using typename TraitProvider::WrappedIteratorType;
			using typename TraitProvider::value_type;
			using typename TraitProvider::difference_type;
			using typename TraitProvider::pointer;
			using typename TraitProvider::reference;
			using typename TraitProvider::iterator_category;

			/// <summary>
			/// Moves the iterator forward n steps.
			/// Only available if the wrapped iterator is a random access iterator.
			/// </summary>
			/// <param name="n"> The number of steps. </return>
			/// <return> This iterator at its new position. </return>
			CrtpChildIterator& operator+=(difference_type n)
			{
				getCrtpThis()->getWrappedIterator() += n;
				return *this;
			}

			/// <summary>
			/// Moves the iterator backward n steps.
			/// Only available if the wrapped iterator is a random access iterator.
			/// </summary>
			/// <param name="n"> The number of steps. </return>
			/// <return> This iterator at its new position. </return>
			CrtpChildIterator& operator-=(difference_type n)
			{
				getCrtpThis()->getWrappedIterator() -= n;
				return *this;
			}

			/// <summary>
			/// Returns a new the iterator n steps forward from this one.
			/// Only available if the wrapped iterator is a random access iterator.
			/// </summary>
			/// <param name="n"> The number of steps. </return>
			/// <return> This iterator at its new position. </return>
			[[nodiscard]]
			CrtpChildIterator operator+(difference_type n) const
			{
				WrappedIterator tempIt = getCrtpThis()->getWrappedIterator();
				tempIt += n;
				return CrtpChildIterator(tempIt, m_transform);
			}

			/// <summary>
			/// Returns a new the iterator n steps forward from this one.
			/// Only available if the wrapped iterator is a random access iterator.
			/// </summary>
			/// <param name="lhs"> The number of steps. </return>
			/// <param name="rhs"> The starting point. </return>
			/// <return> This iterator at its new position. </return>
			[[nodiscard]]
			friend CrtpChildIterator operator+(difference_type lhs, const CrtpChildIterator& rhs)
			{
				return rhs + lhs;
			}

			/// <summary>
			/// Returns a new the iterator n steps backward from this one.
			/// Only available if the wrapped iterator is a random access iterator.
			/// </summary>
			/// <param name="n"> The number of steps. </return>
			/// <return> This iterator at its new position. </return>
			[[nodiscard]]
			CrtpChildIterator operator-(difference_type n) const
			{
				WrappedIterator tempIt = getCrtpThis()->getWrappedIterator();
				tempIt -= n;
				return CrtpChildIterator(tempIt, m_transform);
			}

			/// <summary>
			/// Apply the transform to the wrapped iterator n steps forward from its current position and return the result.
			/// This iterator is not moved.
			/// Only available if the wrapped iterator is a random access iterator.
			/// 
			/// Behavior is undefined if  the lifetime of the result of the unary operation is dependent on the
			/// lifetime of the wrapped iterator.
			/// </summary>
			/// <param name="n"> The number of steps. </return>
			/// <return>  The result of applying the unary operation to the wrapped iterator n steps forward from its current position.  </return>
			[[nodiscard]]
			reference operator[](difference_type n)
			{
				CrtpChildIterator temp = *getCrtpThis();
				temp += n;
				return *temp;
			}

		private:
			[[nodiscard]]
			CrtpChildIterator* getCrtpThis()
			{
				return static_cast<CrtpChildIterator*>(this);
			}
		};
	}

	/// <summary>
	/// Wraps an input iterator and applies a transform to it whenever it is dereferenced.
	/// 
	/// TransormIterator is never more than an input iterator even if the wrapped iterator
	/// is a bidirectional or random access iterator. TransformIterator provides convenience functions
	/// when wrapping bidirectional and random access iterators, but never fully fulfills the requirements of
	/// these iterator types.
	/// </summary>
	template <class Iterator, typename UnaryOperation>
	class TransformIterator : public Detail::TransformIteratorRandomAccessHelper<TransformIterator<Iterator, UnaryOperation>, Iterator, UnaryOperation>
	{
	private:
		using TraitProvider = Detail::TransformIteratorTraitProvider<Iterator, UnaryOperation>;

	public:

		// Iterator types
		using typename TraitProvider::WrappedIteratorType;
		using typename TraitProvider::value_type;
		using typename TraitProvider::difference_type;
		using typename TraitProvider::pointer;
		using typename TraitProvider::reference;
		using typename TraitProvider::iterator_category;

		/// <summary>
		/// Constructor:
		/// Wraps the provided iterator and applies a transform to it on every dereference
		/// </summary>
		/// <param name="wrapped"> The iterator to be wrapped.</param>
		/// <param name="transform"> function applied to the wrapped iterator whenever this TransformIterator is dereferenced.</param>
		TransformIterator(Iterator wrapped, UnaryOperation transform) :
			m_wrappedIt(std::move(wrapped)),
			m_transform(std::move(transform))
		{
		}

		/// <summary>
		/// Converts this TransformIterator to the wrapped iterator
		/// </summary>
		[[nodiscard]]
		explicit operator WrappedIteratorType()
		{
			return m_wrappedIt;
		}

		/// <summary>
		/// Gets the iterator wrapped by this transform iterator
		/// </summary>
		/// <return> The iterator wrapped by this transform iterator. </return>
		[[nodiscard]]
		WrappedIteratorType& getWrappedIterator()
		{
			return m_wrappedIt;
		}

		/// <summary>
		/// Apply the transform to the wrapped iterator and return the result
		/// </summary>
		/// <return> The result of applying the unary operation to the wrapped iterator. </return>
		[[nodiscard]]
		reference operator*() const
		{
			return std::invoke(m_transform, m_wrappedIt);
		}

		/// <summary>
		/// Compare transform iterators for equality.
		/// </summary>
		/// <return> True if the wrapped iterators are equal. False otherwise. </return>
		[[nodiscard]]
		bool operator==(const TransformIterator& other)
		{
			return m_wrappedIt == other.m_wrappedIt;
		}

		/// <summary>
		/// Compare with wrapped iterator for equality. 
		/// </summary>
		/// <return> True if the wrapped iterator is equal to the other iterator. False otherwise. </return>
		[[nodiscard]]
		bool operator==(const WrappedIteratorType& other)
		{
			return m_wrappedIt == other;
		}

		/// <summary>
		/// Compare transform iterators for inequality.
		/// </summary>
		/// <return> True if the wrapped iterators are not equal. False otherwise. </return>
		[[nodiscard]]
		bool operator!=(const TransformIterator& other)
		{
			return m_wrappedIt != other.m_wrappedIt;
		}

		/// <summary>
		/// Compare with wrapped iterator for inequality. 
		/// </summary>
		/// <return> True if the wrapped iterator is not equal to the other iterator. False otherwise. </return>
		[[nodiscard]]
		bool operator!=(const WrappedIteratorType& other)
		{
			return m_wrappedIt != other;
		}

		/// <summary>
		/// Moves the iterator forward.
		/// </summary>
		/// <return> The iterator after being moved forward. </return>
		TransformIterator& operator++()
		{
			++m_wrappedIt;
			return *this;
		}

		/// <summary>
		/// Moves the iterator forward.
		/// </summary>
		/// <return> A new iterator at the position of the original before it was moved forward. </return>
		[[nodiscard]]
		TransformIterator operator++(int)
		{
			TransformIterator out(*this);
			++(*this);
			return out;
		}

	private:
		WrappedIteratorType m_wrappedIt;
		UnaryOperation m_transform;
	};
}