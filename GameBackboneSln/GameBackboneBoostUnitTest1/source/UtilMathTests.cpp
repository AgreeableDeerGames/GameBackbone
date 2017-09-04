#include "stdafx.h"

#include <Util/Point.h>
#include <Util/UtilMath.h>

#include <SFML/Graphics.hpp>

using namespace GB;


//keep at start of file

//Contains all of the tests for AnimatedSprite
BOOST_AUTO_TEST_SUITE(UtilMathTests)


//Contains all of the tests for UtilMath CalcDistance 2D
BOOST_AUTO_TEST_SUITE(UtilMath_calcDistance2D)

//Tests the UtilMath CalcDistance 2D function for ints
BOOST_AUTO_TEST_CASE(UtilMath_calcDistance2D_int) {
	Point2D<int> originPoint{ 0, 0 };
	Point2D<int> onePoint{1, 1};
	Point2D<int> negativePoint{-2, -2};

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
	Point2D<double> originPoint{ 0.0, 0.0 };
	Point2D<double> onePoint{ 1.0, 1.0 };
	Point2D<double> negativePoint{ -2.0, -2.0 };

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
	Point2D<float> originPoint{0.0f, 0.0f};
	Point2D<float> onePoint{1.0f, 1.0f};
	Point2D<float> negativePoint{-2.0f, -2.0f};

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
	Point2D<int> originPoint{ 0, 0 };
	Point2D<int> onePoint{1, 1};
	Point2D<int> negativePoint{-2, -2};

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
	Point2D<double> originPoint{0.0, 0.0};
	Point2D<double> onePoint{1.0, 1.0};
	Point2D<double> negativePoint{-2.0, -2.0};

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
	Point2D<float> originPoint{0.0f, 0.0f};
	Point2D<float> onePoint{1.0f, 1.0f};
	Point2D<float> negativePoint{-2.0f, -2.0f};

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


//Contains all of the tests for UtilMath CalcDistance 3D
BOOST_AUTO_TEST_SUITE(UtilMath_calcDistance3D)

//Tests the UtilMath CalcDistance 3D function for ints
BOOST_AUTO_TEST_CASE(UtilMath_calcDistance3D_int) {
	Point3D<int> originPoint{ 0, 0, 0 };
	Point3D<int> onePoint{ 1, 1, 1 };
	Point3D<int> negativePoint{ -2, -2, -2 };

	int distanceResult = calcDistance3D<int>(originPoint, onePoint);
	int controlResult = 1;
	BOOST_CHECK(distanceResult == controlResult);

	distanceResult = calcDistance3D<int>(originPoint, negativePoint);
	controlResult = 3;
	BOOST_CHECK(distanceResult == controlResult);

	distanceResult = calcDistance3D<int>(onePoint, negativePoint);
	controlResult = 5;
	BOOST_CHECK(distanceResult == controlResult);
}

//Tests the UtilMath CalcDistance 3D function for doubles
BOOST_AUTO_TEST_CASE(UtilMath_calcDistance3D_double) {
	Point3D<double> originPoint{0.0, 0.0, 0.0};
	Point3D<double> onePoint{1.0, 1.0, 1.0};
	Point3D<double> negativePoint{-2.0, -2.0, -2.0};

	double distanceResult = calcDistance3D<double>(originPoint, onePoint);
	double controlResult = 1.732051;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = calcDistance3D<double>(originPoint, negativePoint);
	controlResult = 3.464102;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = calcDistance3D<double>(onePoint, negativePoint);
	controlResult = 5.196152;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);
}

//Tests the UtilMath CalcDistance 3D function for floats
BOOST_AUTO_TEST_CASE(UtilMath_calcDistance3D_float) {
	Point3D<float> originPoint{0.0f, 0.0f, 0.0f};
	Point3D<float> onePoint{1.0f, 1.0f, 1.0f};
	Point3D<float> negativePoint{-2.0f, -2.0f, -2.0f};

	float distanceResult = calcDistance3D<float>(originPoint, onePoint);
	float controlResult = 1.732051f;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = calcDistance3D<float>(originPoint, negativePoint);
	controlResult = 3.464102f;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = calcDistance3D<float>(onePoint, negativePoint);
	controlResult = 5.196152f;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);
}

BOOST_AUTO_TEST_SUITE_END() //end UtilMath CalcDistance 3D


//Contains all of the tests for UtilMath CalcDistance 3D
BOOST_AUTO_TEST_SUITE(UtilMath_calcSquaredDistance3D)

//Tests the UtilMath CalcSquaredDistance 3D function for ints
BOOST_AUTO_TEST_CASE(UtilMath_calcSquaredDistance3D_int) {
	Point3D<int> originPoint{ 0, 0, 0 };
	Point3D<int> onePoint{ 1, 1, 1 };
	Point3D<int> negativePoint{ -2, -2, -2 };

	int distanceResult = calcSquaredDistance3D<int>(originPoint, onePoint);
	int controlResult = 3;
	BOOST_CHECK(distanceResult == controlResult);

	distanceResult = calcSquaredDistance3D<int>(originPoint, negativePoint);
	controlResult = 12;
	BOOST_CHECK(distanceResult == controlResult);

	distanceResult = calcSquaredDistance3D<int>(onePoint, negativePoint);
	controlResult = 27;
	BOOST_CHECK(distanceResult == controlResult);
}

//Tests the UtilMath CalcSquaredDistance 3D function for doubles
BOOST_AUTO_TEST_CASE(UtilMath_calcSquaredDistance3D_double) {
	Point3D<double> originPoint{0.0, 0.0, 0.0};
	Point3D<double> onePoint{1.0, 1.0, 1.0};
	Point3D<double> negativePoint{-2.0, -2.0, -2.0};

	double distanceResult = calcSquaredDistance3D<double>(originPoint, onePoint);
	double controlResult = 1.732051*1.732051;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = calcSquaredDistance3D<double>(originPoint, negativePoint);
	controlResult = 3.464102*3.464102;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = calcSquaredDistance3D<double>(onePoint, negativePoint);
	controlResult = 5.196152*5.196152;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);
}

//Tests the UtilMath CalcSquaredDistance 3D function for floats
BOOST_AUTO_TEST_CASE(UtilMath_calcSquaredDistance3D_float) {
	Point3D<float> originPoint{0.0f, 0.0f, 0.0f};
	Point3D<float> onePoint{1.0f, 1.0f, 1.0f};
	Point3D<float> negativePoint{-2.0f, -2.0f, -2.0f};

	float distanceResult = calcSquaredDistance3D<float>(originPoint, onePoint);
	float controlResult = 1.732051f*1.732051f;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = calcSquaredDistance3D<float>(originPoint, negativePoint);
	controlResult = 3.464102f*3.464102f;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);

	distanceResult = calcSquaredDistance3D<float>(onePoint, negativePoint);
	controlResult = 5.196152f*5.196152f;
	BOOST_CHECK_CLOSE(distanceResult, controlResult, 0.01);
}

BOOST_AUTO_TEST_SUITE_END() //end UtilMath calcSquaredDistance3D

//Keep at end of file
BOOST_AUTO_TEST_SUITE_END()