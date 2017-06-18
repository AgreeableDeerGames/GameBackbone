#include "stdafx.h"
#include "RandGen.h"

using namespace GB;



/// <summary>
/// Initializes a new instance of the <see cref="RandGen"/> class.
/// </summary>
RandGen::RandGen() {
	// This Random device is used to generate the seed if no seed is provided.
	// We then convert the unsigned int that it returns and turn that into a string which we set on our Generator.
	std::random_device rd;
	setSeed(std::to_string(rd()));

	setUniDistributor(0, 1);
}


/// <summary>
/// Initializes a new instance of the <see cref="RandGen"/> class.
/// </summary>
/// <param name="seed">The seed for the Generator.</param>
RandGen::RandGen(std::string seed) {
	setSeed(seed); 
	setUniDistributor(0, 1);
}


/// <summary>
/// Initializes a new instance of the <see cref="RandGen"/> class.
/// </summary>
/// <param name="min">The minimum number that will be set on the UniDistributor.</param>
/// <param name="max">The maximum number that will be set on the UniDistributor.</param>
RandGen::RandGen(double min, double max) {
	// This Random device is used to generate the seed if no seed is provided.
	// We then convert the unsigned int that it returns and turn that into a string which we set on our Generator.
	std::random_device rd;
	setSeed(std::to_string(rd()));

	setUniDistributor(min, max);
}


/// <summary>
/// Initializes a new instance of the <see cref="RandGen"/> class.
/// </summary>
/// <param name="seed">The seed for the Generator.</param>
/// <param name="min">The minimum number that will be set on the UniDistributor.</param>
/// <param name="max">The maximum number that will be set on the UniDistributor.</param>
RandGen::RandGen(std::string seed, double min, double max) {
	setSeed(seed);
	setUniDistributor(min, max);
}

/// <summary>
/// Gets the seed of the Random Generator.
/// </summary>
/// <returns></returns>
std::string RandGen::getSeed() {
	return m_seedString;
}


/// <summary>
/// Sets the seed of the Random Generator.
/// </summary>
/// <param name="seed">New seed that we are setting on the engine.</param>
void RandGen::setSeed(std::string seed) {
	// Save the string
	m_seedString = seed;

	// Set the seed on our engine.
	std::seed_seq tempSeed(m_seedString.begin(), m_seedString.end());
	m_generator.seed(tempSeed);
}

/// <summary>
/// Sets uniDistributor's min and max limits.
/// </summary>
/// <param name="min">The minimum.</param>
/// <param name="max">The maximum.</param>
void RandGen::setUniDistributor(double min, double max) {
	m_uniDistributor = std::uniform_real_distribution<double>(min, max);
}

/// <summary>
/// Creates a uniform distribution between the previously set min and max values.
/// </summary>
/// <returns></returns>
double RandGen::uniDist() {
	double tempNumber = m_uniDistributor(m_generator);
	return tempNumber;
}

/// <summary>
/// Creates a uniform distribution between [min, max)
/// </summary>
/// <param name="min">The minimum number that can be returned.</param>
/// <param name="max">The maximum number that can be returned.</param>
/// <returns></returns>
double RandGen::uniDist(double min, double max) {
	if (min != m_uniDistributor.a() || max != m_uniDistributor.b()) {
		setUniDistributor(min, max);
	}
	return uniDist();
}