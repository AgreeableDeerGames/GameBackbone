//#include <GameBackbone/Util/CircularBuffer.h>
//
//#include <vector>
//
//using namespace GB;
//
//// Constructors -----------------------------------------
//CircularBuffer::CircularBuffer() {
//	data.reserve(4);
//	m_count = 0;
//	m_maxCount = 4;
//	m_headIndex = 0;
//}
//
//CircularBuffer::CircularBuffer(const size_t& maxCount) {
//	data.reserve(m_maxCount);
//	m_count = 0;
//	m_maxCount = m_maxCount;
//	m_headIndex = 0;
//}
//
//CircularBuffer::~CircularBuffer() {
//}
//
//// iterators --------------------------------------------
//// Returns iterator 
//CircularBuffer::begin() {
//	if (m_count == 0) {
//		//error
//	}
//	else if (m_count < m_maxCount) {
//		return m_head;
//	}
//	else if () {
//		return m_head(m_head - m_maxCount) % m_maxCount;
//	}
//}
//
//CircularBuffer::cbegin() {
//	if (m_count == 0) {
//		//error
//	}
//	else if (m_count < m_maxCount) {
//		return 0;
//	}
//	else {
//		return (m_count - m_maxCount) % m_maxCount;
//	}
//}
//
//CircularBuffer::end();
//CircularBuffer::cend();
//CircularBuffer::rbegin();
//CircularBuffer::crbegin();
//CircularBuffer::rend();
//CircularBuffer::crend();
//
//// Capacity ---------------------------------------------
//bool CircularBuffer::empty();
//size_t CircularBuffer::size();
//CircularBuffer::max_size();
//CircularBuffer::reserve();
//CircularBuffer::capacity();
//CircularBuffer::shrink_to_fit();
//
//// Modifiers --------------------------------------------
//void CircularBuffer::clear();
//CircularBuffer::insert();
//CircularBuffer::emplace();
//CircularBuffer::erase();
//CircularBuffer::emplace_back();
//CircularBuffer::pop_back();
//CircularBuffer::resize();