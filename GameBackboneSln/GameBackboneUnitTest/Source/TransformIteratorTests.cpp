#include "stdafx.h"

#include <GameBackbone/Util/TransformIterator.h>

#include <SFML/Graphics/Sprite.hpp>

#include <algorithm>
#include <type_traits>
#include <vector>
#include <list>
#include <forward_list>
#include <unordered_map>

using namespace GB;

BOOST_AUTO_TEST_SUITE(TransformIteratorTests)

BOOST_AUTO_TEST_SUITE(CoreFunctionality)
struct CoreFunctionalityFixture
{
	struct TransformFunctor
	{
		template <class Iterator>
		int operator()(const Iterator& input) const
		{
			return (*input) + 1;
		}
	};

	TransformFunctor transform;
	std::vector<int> container = { 1, 2, 3, 4, 5 };
	std::vector<int>::iterator beginIt{ container.begin() };
	std::vector<int>::iterator endIt{ container.end() };
};

// Ensure that the transform iterator correctly wraps the iterator provided on construction
BOOST_FIXTURE_TEST_CASE(TransformIterator_Constructor, CoreFunctionalityFixture)
{
	TransformIterator transformIt(beginIt, [](auto& it) {return *it; } );
	// BOOST_CHECK_EQUAL(*transformIt, *beginIt);

	//TransformIterator transformIt2(beginIt + 1, [](auto& it) {return *it; });
	//BOOST_CHECK_EQUAL(*transformIt2, *(beginIt + 1));
}

//// Ensure that the transform operation is correctly applied when the iterator is dereferenced
//BOOST_FIXTURE_TEST_CASE(TransformIterator_CorrectlyAppliesTransformOnDereference, CoreFunctionalityFixture)
//{
//	auto iteratorToWrap = beginIt;
//
//	TransformIterator transformIt(iteratorToWrap, transform);
//	BOOST_CHECK_EQUAL(*transformIt, transform(iteratorToWrap));
//}
//
//// Ensure that TransformIterator correctly returns the wrapped iterator when converted to the wrapped iterator type
//BOOST_FIXTURE_TEST_CASE(TransformIterator_CorrectlyConvertsToWrappedIterator, CoreFunctionalityFixture)
//{
//	auto iteratorToWrap = beginIt;
//
//	TransformIterator transformIt(iteratorToWrap, transform);
//	BOOST_CHECK(iteratorToWrap == (decltype(iteratorToWrap))transformIt);
//}
//
//// Ensure that TransformIterator returns true when compared for equality against an identical TransformIterator
//BOOST_FIXTURE_TEST_CASE(TransformIterator_CorrectlyEqualityComparesToEqualTransformIterator, CoreFunctionalityFixture)
//{
//	auto iteratorToWrap = beginIt;
//
//	TransformIterator transformIt(iteratorToWrap, transform);
//	TransformIterator transformIt2(iteratorToWrap, transform);
//	BOOST_CHECK(transformIt == transformIt2);
//}
//
//// Ensure that TransformIterator returns false when compared for equality against a non identical TransformIterator
//BOOST_FIXTURE_TEST_CASE(TransformIterator_CorrectlyEqualityComparesToNonEqualTransformIterator, CoreFunctionalityFixture)
//{
//	TransformIterator transformIt(beginIt, transform);
//	TransformIterator transformIt2(endIt, transform);
//	BOOST_CHECK(!(transformIt == transformIt2));
//}
//
//// Ensure that TransformIterator returns true when compared for equality against an identical WrappedIterator
//BOOST_FIXTURE_TEST_CASE(TransformIterator_CorrectlyEqualityComparesToEqualWrappedIterator, CoreFunctionalityFixture)
//{
//	auto iteratorToWrap = beginIt;
//
//	TransformIterator transformIt(iteratorToWrap, transform);
//	BOOST_CHECK(transformIt == iteratorToWrap);
//}
//
//// Ensure that TransformIterator returns false when compared for equality against a non identical WrappedIterator
//BOOST_FIXTURE_TEST_CASE(TransformIterator_CorrectlyEqualityComparesToNonEqualWrappedIterator, CoreFunctionalityFixture)
//{
//	TransformIterator transformIt(beginIt, transform);
//	BOOST_CHECK(!(transformIt == endIt));
//}
//
//// Ensure that TransformIterator returns true when compared for equality against an identical TransformIterator
//BOOST_FIXTURE_TEST_CASE(TransformIterator_CorrectlyInequalityComparesToEqualTransformIterator, CoreFunctionalityFixture)
//{
//	auto iteratorToWrap = beginIt;
//
//	TransformIterator transformIt(iteratorToWrap, transform);
//	TransformIterator transformIt2(iteratorToWrap, transform);
//	BOOST_CHECK(!(transformIt != transformIt2));
//}
//
//// Ensure that TransformIterator returns false when compared for equality against a non identical TransformIterator
//BOOST_FIXTURE_TEST_CASE(TransformIterator_CorrectlyInequalityComparesToNonEqualTransformIterator, CoreFunctionalityFixture)
//{
//	TransformIterator transformIt(beginIt, transform);
//	TransformIterator transformIt2(endIt, transform);
//	BOOST_CHECK(transformIt != transformIt2);
//}
//
//// Ensure that TransformIterator returns true when compared for equality against an identical WrappedIterator
//BOOST_FIXTURE_TEST_CASE(TransformIterator_CorrectlyInequalityComparesToEqualWrappedIterator, CoreFunctionalityFixture)
//{
//	auto iteratorToWrap = beginIt;
//
//	TransformIterator transformIt(iteratorToWrap, transform);
//	BOOST_CHECK(!(transformIt != iteratorToWrap));
//}
//
//// Ensure that TransformIterator returns false when compared for equality against a non identical WrappedIterator
//BOOST_FIXTURE_TEST_CASE(TransformIterator_CorrectlyInequalityComparesToNonEqualWrappedIterator, CoreFunctionalityFixture)
//{
//	TransformIterator transformIt(beginIt, transform);
//	BOOST_CHECK(transformIt != endIt);
//}
//
//// Ensure that prefix increment operator correctly moves the iterator
//BOOST_FIXTURE_TEST_CASE(TransformIterator_PrefixIncrementCorrectlyMovesIterator, CoreFunctionalityFixture)
//{
//	TransformIterator transformIt(beginIt, transform);
//	auto& result = ++transformIt;
//
//	// the iterator is moved forward
//	BOOST_CHECK_EQUAL(*transformIt, transform(++container.begin()));
//
//	// the returned iterator is a reference to the original and should also be moved forward
//	BOOST_CHECK(&result == &transformIt);
//	BOOST_CHECK_EQUAL(*result, transform(++container.begin()));
//}
//
//// Ensure that postfix increment operator correctly moves the iterator
//BOOST_FIXTURE_TEST_CASE(TransformIterator_PostfixIncrementCorrectlyMovesIterator, CoreFunctionalityFixture)
//{
//	TransformIterator transformIt(beginIt, transform);
//	auto result = transformIt++;
//
//	// the iterator is moved forward
//	BOOST_CHECK_EQUAL(*transformIt, transform(++container.begin()));
//
//	// the returned iterator at the original position
//	BOOST_CHECK_EQUAL(*result, transform(container.begin()));
//}
//
//// Ensure that TransformIterator works with algorithms
//BOOST_FIXTURE_TEST_CASE(TransformIterator_IsStandardAlgorithmsCompatible, CoreFunctionalityFixture)
//{
//	TransformIterator transformBegin(beginIt, transform);
//	TransformIterator transformEnd(endIt, transform);
//
//	std::vector<int> outputVec;
//	std::for_each(transformBegin, transformEnd, [&](const auto& i)
//	{
//		outputVec.push_back(i);
//	});
//
//	std::transform(beginIt, endIt, beginIt, [](auto i) {return i + 1; });
//	BOOST_CHECK_EQUAL_COLLECTIONS(outputVec.begin(), outputVec.end(), beginIt, endIt);
//}
//
//// Ensure that TransformIterator works with std::vector<int>::insert
//BOOST_FIXTURE_TEST_CASE(TransformIterator_IsVectorInsertCompatible, CoreFunctionalityFixture)
//{
//	TransformIterator transformBegin(beginIt, transform);
//	TransformIterator transformEnd(endIt, transform);
//
//	std::vector<int> outputVec;
//	outputVec.insert(std::end(outputVec), transformBegin, transformEnd);
//
//	std::transform(beginIt, endIt, beginIt, [](auto i) {return i + 1; });
//	BOOST_CHECK_EQUAL_COLLECTIONS(outputVec.begin(), outputVec.end(), beginIt, endIt);
//}
//
BOOST_AUTO_TEST_SUITE_END() // CoreFunctionality
//
//BOOST_AUTO_TEST_SUITE(Bidirectional)
//
//BOOST_AUTO_TEST_CASE(test)
//{
//	std::list<int> container{1, 2, 3, 4, 5, 6, 7};
//	TransformIterator transformBegin(container.begin(), [](auto& it) {return (*it) + 1; });
//	//transformBegin[10];
//
//	std::forward_list<int> flist;
//	TransformIterator transformBegin2(flist.begin(), [](auto& it) {return 1; });
//}
//
//BOOST_AUTO_TEST_SUITE_END() // Bidirectional
//
//
//BOOST_AUTO_TEST_SUITE(RandomAccess)
//BOOST_AUTO_TEST_SUITE_END() // RandomAccess



BOOST_AUTO_TEST_SUITE_END() // TransformIteratorTests
