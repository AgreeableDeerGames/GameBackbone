#include "stdafx.h"

#include <GameBackbone/Util/UtilMath.h>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

using namespace GB;


//keep at start of file

//Contains all of the tests for AnimatedSprite
BOOST_AUTO_TEST_SUITE(UtilMathTests)


//Contains all of the tests for UtilMath CalcDistance 2D
BOOST_AUTO_TEST_SUITE(UtilMath_calcDistance2D)

//Tests the UtilMath CalcDistance 2D function for ints
BOOST_AUTO_TEST_CASE(UtilMath_calcDistance2D_int) {
	sf::Vector2i originPoint{ 0, 0 };
	sf::Vector2i onePoint{1, 1};
	sf::Vector2i negativePoint{-2, -2};

	int distanceResult = calcDistance2D<int>(originPoint, onePoint);
	int controlResult = 1;
	BOOST_CHECK(distanceResult == controlResult);

	distanceResult = calcDistance2D<int>(originPoint, negativePoint);
	controlResult = 2;
	BOOST_CHECK(distanceResult == controlResult);

	distanceResult = calcDistance2D<int>(onePoint, negativePoint);
	controlResult = 4;
	BOOST_CHECK(distanceResult == controlResult);
}

//Tests the UtilMath CalcDistance 2D function for doubles
BOOST_AUTO_TEST_CASE(UtilMath_calcDistance2D_double) {
	sf::Vector2<double> originPoint{ 0.0, 0.0 };
	sf::Vector2<double> onePoint{ 1.0, 1.0 };
	sf::Vector2<double> negativePoint{ -2.0, -2.0 };

	double distanceResult = calcDistance2D<double>(originPoint, onePoint);
	double controlResult = 1.414214;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = calcDistance2D<double>(originPoint, negativePoint);
	controlResult = 2.828427;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = calcDistance2D<double>(onePoint, negativePoint);
	controlResult = 4.242641;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);
}

//Tests the UtilMath CalcDistance 2D function for floats
BOOST_AUTO_TEST_CASE(UtilMath_calcDistance2D_float) {
	sf::Vector2f originPoint{0.0f, 0.0f};
	sf::Vector2f onePoint{1.0f, 1.0f};
	sf::Vector2f negativePoint{-2.0f, -2.0f};

	float distanceResult = calcDistance2D<float>(originPoint, onePoint);
	float controlResult = 1.414214f;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = calcDistance2D<float>(originPoint, negativePoint);
	controlResult = 2.828427f;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = calcDistance2D <float> (onePoint, negativePoint);
	controlResult = 4.242641f;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);
}

BOOST_AUTO_TEST_SUITE_END() //end UtilMath calcDistance2D


//Contains all of the tests for UtilMath CalcSquaredDistance 2D
BOOST_AUTO_TEST_SUITE(UtilMath_calcSquaredDistance2D)

//Tests the UtilMath CalcSquaredDistance 2D function for ints
BOOST_AUTO_TEST_CASE(UtilMath_calcSquaredDistance2D_int) {
	sf::Vector2i originPoint{ 0, 0 };
	sf::Vector2i onePoint{1, 1};
	sf::Vector2i negativePoint{-2, -2};

	int distanceResult = calcSquaredDistance2D<int>(originPoint, onePoint);
	int controlResult = 2;
	BOOST_CHECK(distanceResult == controlResult);

	distanceResult = calcSquaredDistance2D<int>(originPoint, negativePoint);
	controlResult = 8;
	BOOST_CHECK(distanceResult == controlResult);

	distanceResult = calcSquaredDistance2D<int>(onePoint, negativePoint);
	controlResult = 18;
	BOOST_CHECK(distanceResult == controlResult);
}

//Tests the UtilMath CalcSquaredDistance 2D function for doubles
BOOST_AUTO_TEST_CASE(UtilMath_calcSquaredDistance2D_double) {
	sf::Vector2<double> originPoint{0.0, 0.0};
	sf::Vector2<double> onePoint{1.0, 1.0};
	sf::Vector2<double> negativePoint{-2.0, -2.0};

	double distanceResult = calcSquaredDistance2D<double>(originPoint, onePoint);
	double controlResult = 1.414214*1.414214;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = calcSquaredDistance2D<double>(originPoint, negativePoint);
	controlResult = 2.828427*2.828427;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = calcSquaredDistance2D<double>(onePoint, negativePoint);
	controlResult = 4.242641*4.242641;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);
}

//Tests the UtilMath CalcSquaredDistance 2D function for floats
BOOST_AUTO_TEST_CASE(UtilMath_calcSquaredDistance2D_float) {
	sf::Vector2f originPoint{0.0f, 0.0f};
	sf::Vector2f onePoint{1.0f, 1.0f};
	sf::Vector2f negativePoint{-2.0f, -2.0f};

	float distanceResult = calcSquaredDistance2D<float>(originPoint, onePoint);
	float controlResult = 1.414214f*1.414214f;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = calcSquaredDistance2D<float>(originPoint, negativePoint);
	controlResult = 2.828427f*2.828427f;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = calcSquaredDistance2D<float>(onePoint, negativePoint);
	controlResult = 4.242641f*4.242641f;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);
}

BOOST_AUTO_TEST_SUITE_END() //end UtilMath calcSquaredDistance2D

//Keep at end of file
BOOST_AUTO_TEST_SUITE_END()