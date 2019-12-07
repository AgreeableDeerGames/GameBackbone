#pragma once

#include <GameBackbone/Util/DllUtil.h>

#include <sfml/System/Time.hpp>

#include <chrono>
#include <functional>
#include <memory>
#include <algorithm>
#include <numeric>
#include <vector>

namespace GB {

	template <class ValueType>
    class CircularBufferIterator
    {
    public:
        // Previously provided by std::iterator
        using value_type = ValueType;
        using difference_type = std::size_t;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category = std::random_access_iterator_tag;

        // helper typedefs
        // using ConversionFuncType = std::function<TargetType(const Iterator&)>;

        // explicit CircularBufferIterator(Iterator wrapped) : CircularBufferIterator(std::move(wrapped), ConversionFuncType{}) {}

        CircularBufferIterator(const CircularBuffer<ValueType>& buffer) : m_buffer(buffer)
        {
        }

        reference operator*() const
        {
            return this->m_buffer.at(m_index);
        }

        // Universal iterator member functions

        bool operator==(const CircularBufferIterator<ValueType>& other) const {
            return (this->m_index == other->m_index); // TODO: Make this less gross
        }

        bool operator!=(const CircularBufferIterator<ValueType>& other) const {
            return !(*this == other);
        }

        CircularBufferIterator& operator++()
        {
            ++m_index;
            return *this;
        }

        CircularBufferIterator operator++(int)
        {
            CircularBufferIterator out(*this);
            ++(*this);
            return out;
        }

        // Bidirectional iterator member functions
        CircularBufferIterator& operator--()
        {
            --m_index;
            return *this;
        }

        CircularBufferIterator operator--(int)
        {
            CircularBufferIterator out(this->m_index);
            --(*this);
            return out;
        }

        // Random access iterator member functions https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator#Concept

        CircularBufferIterator& operator+=(difference_type n)
        {
            m_index += n;
            return *this;
        }

        CircularBufferIterator& operator-=(difference_type n)
        {
            m_index -= n;
            return *this;
        }

        CircularBufferIterator operator+(difference_type n) const
        {
            Iterator tempIt = m_index;
            tempIt += n;
            return CircularBufferIterator(tempIt, m_convert);
        }

        friend CircularBufferIterator operator+(difference_type lhs, const CircularBufferIterator& rhs)
        {
            return rhs + lhs;
        }

        CircularBufferIterator operator-(difference_type n) const
        {
            Iterator tempIt = m_index;
            tempIt -= n;
            return CircularBufferIterator(tempIt, m_convert);
        }

        friend difference_type operator-(difference_type lhs, const CircularBufferIterator& rhs)
        {
            return lhs - rhs.m_wram_wrappedIt;
        }

        reference operator[](difference_type n)
        {
            CircularBufferIterator temp = *this;
            temp += n;
            return *temp;
        }

    private:
       const CircularBuffer& m_buffer;
	   std::size_t m_index;
    };


	/// <summary>
	/// Circular buffer data structure that takes in a certain number of elements at
	/// the beginning of the structure, and removes the last element once it exceeds max size.
	/// </summary>
	template <typename T>
	class CircularBuffer {
	public:
		// Constructors ----------------------------------------------------------------------------------
		CircularBuffer();
		CircularBuffer(const size_t& m_maxCount);
		~CircularBuffer();
		
		// Iterators -------------------------------------------------------------------------------------
		/*begin();
		cbegin();
		end();
		cend();
		rbegin();
		crbegin();
		rend();
		crend();*/

		// Capacity --------------------------------------------------------------------------------------

		// Returns true if buffer contains no elements
		bool empty() {
			return data.empty();
		}

		// Returns the number of elements within the buffer
		size_t size() {
			return m_count;
		}

		// Returns the maximum amount of elements the buffer can hold before buffer is full before it 
		// begins overwritting
		size_t max_size() {
			return m_maxCount;
		}

		// Allocates the input amount of storage space for the buffer
		void reserve(const int& size) {
			data.reserve(size);
			m_maxCount = size;
		}

		// Returns the size of the storage space allocated for the buffer
		size_t capacity() {
			return data.capacity();
		}

		// Reduces capacity of the buffer to its current size
		void shrink_to_fit() {
			data.shrink_to_fit();
			m_maxCount = m_count;
		}

		// Modifiers -------------------------------------------------------------------------------------

		// Removes all elements in buffer
		// Resets m_head and m_count
		void clear() {
			data.clear();
			m_count = 0;
			m_head = 0;
		}
		/*
		insert();
		emplace();
		erase();*/

		// Inserts element at the beginning of buffer
		// Removes tailing elements after count surpassing max_size
		template <typename T>
		void push_back(const T& element) {
			// if empty vector
			if (m_count == 0) {
				data.push_back(element);
				m_count++;
			}
			
			// if vector is not full
			else if (m_count < m_maxCount) {
				data.push_back(element);
				m_count++;
				m_head++;
			}

			// if vector is full
			else {
				m_head++;
				data.at(m_head) = element;
			}
		}

		// rvalue overload
		template <typename T>
		void push_back(T&& element) {
			// if empty vector
			if (m_count == 0) {
				data.emplace_back(element);
				m_count++;
			}

			// if vector is not full
			else if (m_count < m_maxCount) {
				data.emplace_back(element);
				m_count++;
				m_head++;
			}

			// if vector is full
			else {
				m_head++;
				data.at(m_head) = element;
			}
		}

		// Constructs and inserts element at the next open space in the buffer
		// After the buffer is full, emplace_back is identical to push_back
		template <typename T>
		void emplace_back(const T& element) {
			// if empty vector
			if (m_count == 0) {
				data.emplace_back(element);
				m_count++;
			}

			// if vector is not full
			else if (m_count < m_maxCount) {
				data.emplace_back(element);
				m_count++;
				m_head++;
			}

			// if vector is full
			else {
				m_head++;
				data.at(m_head) = element;
			}
		}

		// rvalue overload
		template <typename T>
		void emplace_back(T&& element) {
			// if empty vector
			if (m_count == 0) {
				data.emplace_back(element);
				m_count++;
			}

			// if vector is not full
			else if (m_count < m_maxCount) {
				data.emplace_back(element);
				m_count++;
				m_head++;
			}

			// if vector is full
			else {
				m_head++;
				data.at(m_head) = element;
			}
		}

		// Erases the current head of the buffer
		void pop_back() {
			//data.erase(m_head);
			m_head--;
		}

		// STRANGE SO DO AT THE END ONCE I HAVE ITERATORS IMPLEMENTED,
		// AS IT WILL MAKE THIS EASIER
		void resize(size_t n) {
			/*data.resize(n);
			if (n < m_count) {
				m_count = n;
				m_maxCount;
			}

			// Resize to same size
			else if (n == m_count) {
				// Nothing happens
			}

			// Resize to a greater size
			else if (n > m_count) {

				if (m_count > m_maxCount) {
					m_maxCount = m_count;
				}
			}*/
		}

		/*oid resize(size_t n, const T& val) {

		}*/

	private:
		size_t m_count;
		size_t m_maxCount;
		size_t m_head;

	protected:
		std::vector<T> data;
	};
}
