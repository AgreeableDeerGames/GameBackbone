#include <stdafx.h>

#include <Util/UtilMath.h>

#include <SFML/Graphics.hpp>

using namespace GB;


//keep at start of file

//Contains all of the tests for AnimatedSprite
BOOST_AUTO_TEST_SUITE(UtilMathTests)


//Contains all of the tests for UtilMath CalcDistance 2D
BOOST_AUTO_TEST_SUITE(UtilMath_CalcDistance_2D)

//Tests the UtilMath CalcDistance 2D function for ints
BOOST_AUTO_TEST_CASE(UtilMath_CalcDistance_2D_int) {
	std::pair<int, int> originPoint(0, 0);
	std::pair<int, int> onePoint(1, 1);
	std::pair<int, int> negativePoint(-2, -2);

	int distanceResult = CalcDistance(originPoint, onePoint);
	int controlResult = 1;
	BOOST_CHECK(distanceResult == controlResult);

	distanceResult = CalcDistance(originPoint, negativePoint);
	controlResult = 2;
	BOOST_CHECK(distanceResult == controlResult);

	distanceResult = CalcDistance(onePoint, negativePoint);
	controlResult = 4;
	BOOST_CHECK(distanceResult == controlResult);
}

//Tests the UtilMath CalcDistance 2D function for doubles
BOOST_AUTO_TEST_CASE(UtilMath_CalcDistance_2D_double) {
	std::pair<double, double> originPoint(0.0, 0.0);
	std::pair<double, double> onePoint(1.0, 1.0);
	std::pair<double, double> negativePoint(-2.0, -2.0);

	double distanceResult = CalcDistance(originPoint, onePoint);
	double controlResult = 1.414214;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = CalcDistance(originPoint, negativePoint);
	controlResult = 2.828427;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = CalcDistance(onePoint, negativePoint);
	controlResult = 4.242641;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);
}

//Tests the UtilMath CalcDistance 2D function for floats
BOOST_AUTO_TEST_CASE(UtilMath_CalcDistance_2D_float) {
	std::pair<float, float> originPoint(0.0f, 0.0f);
	std::pair<float, float> onePoint(1.0f, 1.0f);
	std::pair<float, float> negativePoint(-2.0f, -2.0f);

	float distanceResult = CalcDistance(originPoint, onePoint);
	float controlResult = 1.414214f;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = CalcDistance(originPoint, negativePoint);
	controlResult = 2.828427f;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = CalcDistance(onePoint, negativePoint);
	controlResult = 4.242641f;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);
}

BOOST_AUTO_TEST_SUITE_END() //end UtilMath CalcDistance 2D


//Contains all of the tests for UtilMath CalcSquaredDistance 2D
BOOST_AUTO_TEST_SUITE(UtilMath_CalcSquaredDistance_2D)

//Tests the UtilMath CalcSquaredDistance 2D function for ints
BOOST_AUTO_TEST_CASE(UtilMath_CalcSquaredDistance_2D_int) {
	std::pair<int, int> originPoint(0, 0);
	std::pair<int, int> onePoint(1, 1);
	std::pair<int, int> negativePoint(-2, -2);

	int distanceResult = CalcSquaredDistance(originPoint, onePoint);
	int controlResult = 2;
	BOOST_CHECK(distanceResult == controlResult);

	distanceResult = CalcSquaredDistance(originPoint, negativePoint);
	controlResult = 8;
	BOOST_CHECK(distanceResult == controlResult);

	distanceResult = CalcSquaredDistance(onePoint, negativePoint);
	controlResult = 18;
	BOOST_CHECK(distanceResult == controlResult);
}

//Tests the UtilMath CalcSquaredDistance 2D function for doubles
BOOST_AUTO_TEST_CASE(UtilMath_CalcSquaredDistance_2D_double) {
	std::pair<double, double> originPoint(0.0, 0.0);
	std::pair<double, double> onePoint(1.0, 1.0);
	std::pair<double, double> negativePoint(-2.0, -2.0);

	double distanceResult = CalcSquaredDistance(originPoint, onePoint);
	double controlResult = 1.414214*1.414214;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = CalcSquaredDistance(originPoint, negativePoint);
	controlResult = 2.828427*2.828427;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = CalcSquaredDistance(onePoint, negativePoint);
	controlResult = 4.242641*4.242641;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);
}

//Tests the UtilMath CalcSquaredDistance 2D function for floats
BOOST_AUTO_TEST_CASE(UtilMath_CalcSquaredDistance_2D_float) {
	std::pair<float, float> originPoint(0.0f, 0.0f);
	std::pair<float, float> onePoint(1.0f, 1.0f);
	std::pair<float, float> negativePoint(-2.0f, -2.0f);

	float distanceResult = CalcSquaredDistance(originPoint, onePoint);
	float controlResult = 1.414214f*1.414214f;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = CalcSquaredDistance(originPoint, negativePoint);
	controlResult = 2.828427f*2.828427f;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = CalcSquaredDistance(onePoint, negativePoint);
	controlResult = 4.242641f*4.242641f;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);
}

BOOST_AUTO_TEST_SUITE_END() //end UtilMath CalcSquaredDistance 2D


//Contains all of the tests for UtilMath CalcDistance 3D
BOOST_AUTO_TEST_SUITE(UtilMath_CalcDistance_3D)

//Tests the UtilMath CalcDistance 3D function for ints
BOOST_AUTO_TEST_CASE(UtilMath_CalcDistance_3D_int) {
	sf::Vector3<int> originPoint(0, 0, 0);
	sf::Vector3<int> onePoint(1, 1, 1);
	sf::Vector3<int> negativePoint(-2, -2, -2);

	int distanceResult = CalcDistance(originPoint, onePoint);
	int controlResult = 1;
	BOOST_CHECK(distanceResult == controlResult);

	distanceResult = CalcDistance(originPoint, negativePoint);
	controlResult = 3;
	BOOST_CHECK(distanceResult == controlResult);

	distanceResult = CalcDistance(onePoint, negativePoint);
	controlResult = 5;
	BOOST_CHECK(distanceResult == controlResult);
}

//Tests the UtilMath CalcDistance 3D function for doubles
BOOST_AUTO_TEST_CASE(UtilMath_CalcDistance_3D_double) {
	sf::Vector3<double> originPoint(0.0, 0.0, 0.0);
	sf::Vector3<double> onePoint(1.0, 1.0, 1.0);
	sf::Vector3<double> negativePoint(-2.0, -2.0, -2.0);

	double distanceResult = CalcDistance(originPoint, onePoint);
	double controlResult = 1.732051;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = CalcDistance(originPoint, negativePoint);
	controlResult = 3.464102;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = CalcDistance(onePoint, negativePoint);
	controlResult = 5.196152;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);
}

//Tests the UtilMath CalcDistance 3D function for floats
BOOST_AUTO_TEST_CASE(UtilMath_CalcDistance_3D_float) {
	sf::Vector3<float> originPoint(0.0f, 0.0f, 0.0f);
	sf::Vector3<float> onePoint(1.0f, 1.0f, 1.0f);
	sf::Vector3<float> negativePoint(-2.0f, -2.0f, -2.0f);

	float distanceResult = CalcDistance(originPoint, onePoint);
	float controlResult = 1.732051f;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = CalcDistance(originPoint, negativePoint);
	controlResult = 3.464102f;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = CalcDistance(onePoint, negativePoint);
	controlResult = 5.196152f;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);
}

BOOST_AUTO_TEST_SUITE_END() //end UtilMath CalcDistance 3D


//Contains all of the tests for UtilMath CalcDistance 3D
BOOST_AUTO_TEST_SUITE(UtilMath_CalcSquaredDistance_3D)

//Tests the UtilMath CalcSquaredDistance 3D function for ints
BOOST_AUTO_TEST_CASE(UtilMath_CalcSquaredDistance_3D_int) {
	sf::Vector3<int> originPoint(0, 0, 0);
	sf::Vector3<int> onePoint(1, 1, 1);
	sf::Vector3<int> negativePoint(-2, -2, -2);

	int distanceResult = CalcSquaredDistance(originPoint, onePoint);
	int controlResult = 3;
	BOOST_CHECK(distanceResult == controlResult);

	distanceResult = CalcSquaredDistance(originPoint, negativePoint);
	controlResult = 12;
	BOOST_CHECK(distanceResult == controlResult);

	distanceResult = CalcSquaredDistance(onePoint, negativePoint);
	controlResult = 27;
	BOOST_CHECK(distanceResult == controlResult);
}

//Tests the UtilMath CalcSquaredDistance 3D function for doubles
BOOST_AUTO_TEST_CASE(UtilMath_CalcSquaredDistance_3D_double) {
	sf::Vector3<double> originPoint(0.0, 0.0, 0.0);
	sf::Vector3<double> onePoint(1.0, 1.0, 1.0);
	sf::Vector3<double> negativePoint(-2.0, -2.0, -2.0);

	double distanceResult = CalcSquaredDistance(originPoint, onePoint);
	double controlResult = 1.732051*1.732051;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = CalcSquaredDistance(originPoint, negativePoint);
	controlResult = 3.464102*3.464102;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = CalcSquaredDistance(onePoint, negativePoint);
	controlResult = 5.196152*5.196152;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);
}

//Tests the UtilMath CalcSquaredDistance 3D function for floats
BOOST_AUTO_TEST_CASE(UtilMath_CalcSquaredDistance_3D_float) {
	sf::Vector3<float> originPoint(0.0f, 0.0f, 0.0f);
	sf::Vector3<float> onePoint(1.0f, 1.0f, 1.0f);
	sf::Vector3<float> negativePoint(-2.0f, -2.0f, -2.0f);

	float distanceResult = CalcSquaredDistance(originPoint, onePoint);
	float controlResult = 1.732051f*1.732051f;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = CalcSquaredDistance(originPoint, negativePoint);
	controlResult = 3.464102f*3.464102f;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = CalcSquaredDistance(onePoint, negativePoint);
	controlResult = 5.196152f*5.196152f;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);
}

BOOST_AUTO_TEST_SUITE_END() //end UtilMath CalcSquaredDistance 3D

//Keep at end of file
BOOST_AUTO_TEST_SUITE_END()