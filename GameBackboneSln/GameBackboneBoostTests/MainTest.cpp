#define BOOST_TEST_MODULE testTest

#include<boost\test\auto_unit_test.hpp>
#include<boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(test_test_1) {
	int testInt = 1;
	BOOST_CHECK_EQUAL(1, testInt);
}

BOOST_AUTO_TEST_CASE(test_test_2) {
	int testInt = 1;
	BOOST_CHECK_EQUAL(2, testInt);
}