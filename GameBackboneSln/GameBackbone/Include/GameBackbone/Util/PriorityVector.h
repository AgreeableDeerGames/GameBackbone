#include <algorithm>
#include <vector>
#include <utility>


namespace GB {
	template <class T>
	class PriorityVector
	{
		/// <summary>
		/// Functor used to check if the priority of a priorityPair the same as a given Priority.
		/// </summary>
		class priorityFindComparitor {
		public:
			explicit priorityFindComparitor(int priority) : priorityToFind(priority) {};

			bool operator ()(const std::pair<int, std::vector<T>>& priorityPair) {
				return priorityPair.first == priorityToFind;
			}

		private:
			int priorityToFind;
		};

	public:
		// Member Types
		using value_type = T;
		//using allocator_type = Allocator;
		using size_type = std::size_t;
		//using difference_type = Signed integer type(usually std::ptrdiff_t)
		using reference = value_type &;
		using const_reference = const value_type &;
		//using pointer = std::allocator_traits<Allocator>::pointer;
		//using const_pointer = std::allocator_traits<Allocator>::const_pointer;
		/*using iterator = LegacyRandomAccessIterator;
		using const_iterator = Constant LegacyRandomAccessIterator;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;*/

		// Member functions
		PriorityVector() = default;
		~PriorityVector() = default;
		PriorityVector<T>& operator=(const PriorityVector<T>& other);
		PriorityVector<T>& operator=(PriorityVector<T>&& other) noexcept;
		PriorityVector<T>& operator=(std::initializer_list<T> ilist);
		void assign(size_type count, const T& value);
		template<class InputIt>
		void assign(InputIt first, InputIt last);
		void assign(std::initializer_list<T> ilist);
		//allocator_type get_allocator() const;

		// Element access
		reference at(size_type pos);
		const_reference at(size_type pos) const;
		reference operator[](size_type pos);
		const_reference operator[](size_type pos) const;
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;
		T* data() noexcept;
		const T* data() const noexcept;

		// Iterators
		/*iterator begin() noexcept;
		const_iterator begin() const noexcept;
		const_iterator cbegin() const noexcept;
		iterator end() noexcept;
		const_iterator end() const noexcept;
		const_iterator cend() const noexcept;
		reverse_iterator rbegin() noexcept;
		const_reverse_iterator rbegin() const noexcept;
		const_reverse_iterator crbegin() const noexcept;
		reverse_iterator rend() noexcept;
		const_reverse_iterator rend() const noexcept;
		const_reverse_iterator crend() const noexcept;*/

		// Capacity
		[[nodiscard]] bool empty() const noexcept
		{
			return internalVector.empty();
		}
		size_type size() const noexcept 
		{
			std::size_t count = 0;
			// Loop through each priority of the drawables
			// Add all of the sizes to the count
			for (const auto& priorityPair : internalVector) {
				count += priorityPair.second.size();
			}
			return count;
		}
		size_type max_size() const noexcept;
		void reserve(std::size_t new_cap);
		size_type capacity() const noexcept;
		void shrink_to_fit();

		// Modifiers
		void clear() noexcept
		{
			internalVector.clear();
		}
		void clear(int priority) noexcept
		{
			auto it = std::find_if(internalVector.begin(), internalVector.end(), priorityFindComparitor(priority));

			// If the iterator is not end, then we found a pair with the same priority.
			// Clear the internal vector
			if (it != prioritizedDrawables.end()) {
				std::vector<sf::Drawable*>& tempDrawables = it->second;
				tempDrawables.clear();
			}
		}
		/*iterator insert(const_iterator pos, const T& value);
		iterator insert(const_iterator pos, T&& value);
		iterator insert(const_iterator pos, size_type count, const T& value);
		template<class InputIt>
		iterator insert(const_iterator pos, InputIt first, InputIt last);
		iterator insert(const_iterator pos, std::initializer_list<T> ilist);
		template<class... Args>
		iterator emplace(const_iterator pos, Args&& ... args);
		iterator erase(const_iterator pos);
		iterator erase(const_iterator first, const_iterator last);*/

		void insert(int priority, std::initializer_list<T> ilist)
		{
			// Remove any instances of the drawables before adding them again
			removeDrawable(drawablesToAdd);

			auto it = std::find_if(prioritizedDrawables.begin(), prioritizedDrawables.end(), priorityFindComparitor(priority));

			// If the iterator is not end, then we found a pair with the same priority.
			// Insert the drawable at the same priority
			if (it != prioritizedDrawables.end()) {
				std::vector<sf::Drawable*>& tempDrawables = it->second;
				tempDrawables.insert(tempDrawables.end(), drawablesToAdd.begin(), drawablesToAdd.end());
			}
			else {
				insert_sorted(prioritizedDrawables, std::make_pair(priority, drawablesToAdd), prioritySortComparitor());
			}
		}

		void push_back(T&& value)
		{
			// Null check each of the drawables passed in
			for (sf::Drawable* drawable : drawablesToAdd)
			{
				if (drawable == nullptr) {
					throw std::invalid_argument("Cannot invoke GameRegion::addDrawable with a drawable equal to nullptr");
				}
			}

			// Remove any instances of the drawables before adding them again
			removeDrawable(drawablesToAdd);

			auto it = std::find_if(prioritizedDrawables.begin(), prioritizedDrawables.end(), priorityFindComparitor(priority));

			// If the iterator is not end, then we found a pair with the same priority.
			// Insert the drawable at the same priority
			if (it != prioritizedDrawables.end()) {
				std::vector<sf::Drawable*>& tempDrawables = it->second;
				tempDrawables.insert(tempDrawables.end(), drawablesToAdd.begin(), drawablesToAdd.end());
			}
			else {
				insert_sorted(prioritizedDrawables, std::make_pair(priority, drawablesToAdd), prioritySortComparitor());
			}
		}
		template<class... Args>
		reference emplace_back(Args&& ... args);
		void pop_back();
		void resize(size_type count);
		void resize(size_type count, const value_type& value);
		void swap(PriorityVector<T>& other) noexcept;

	private:
		std::vector<std::pair<int, std::vector<T>>> internalVector;
	};
}