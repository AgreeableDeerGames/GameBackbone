#include <pair>
#include <vector>

template <class T>
class PriorityVector
{
public:
	// Member Types
	using value_type = T;
	//using allocator_type = Allocator;
	using size_type = std::size_t;
	//using difference_type = Signed integer type(usually std::ptrdiff_t)
	using reference = value_type&;
	using const_reference = const value_type&;
	//using pointer = std::allocator_traits<Allocator>::pointer;
	//using const_pointer = std::allocator_traits<Allocator>::const_pointer;
	using iterator = LegacyRandomAccessIterator;
	using const_iterator = Constant LegacyRandomAccessIterator;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	// Member functions
	PriorityVector();
	~PriorityVector();
	vector& operator=( const vector& other );
	vector& operator=( vector&& other ) noexcept;
	vector& operator=(std::initializer_list<T> ilist);
	void assign(size_type count, const T& value);
	template< class InputIt >
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
	iterator begin() noexcept;
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
	const_reverse_iterator crend() const noexcept;

	// Capacity
	[[nodiscard]] bool empty() const noexcept;
	std::size_t size() const noexcept;
	std::size_t max_size() const noexcept;
	void reserve(std::size_t new_cap);
	std::size_t capacity() const noexcept;
	void shrink_to_fit();
		
	// Modifiers
	void clear() noexcept;
	
	iterator insert(const_iterator pos, const T& value);
	iterator insert(const_iterator pos, T&& value);
	iterator insert(const_iterator pos, size_type count, const T& value);
	template<class InputIt>
	iterator insert(const_iterator pos, InputIt first, InputIt last);
	iterator insert(const_iterator pos, std::initializer_list<T> ilist);

	template<class... Args>
	iterator emplace(const_iterator pos, Args&& ... args);

	iterator erase(const_iterator pos);
	iterator erase(const_iterator first, const_iterator last);

	void push_back(T&& value);
	template<class... Args>
	reference emplace_back(Args&& ... args);
	void pop_back();
	void resize(size_type count);
	void resize(size_type count, const value_type& value);
	void swap(vector& other) noexcept;

private:
	std::vector<std::pair<int, T>>
};