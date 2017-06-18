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

	m_uniDistributor = std::uniform_real_distribution<double>(0, 1);
}


/// <summary>
/// Initializes a new instance of the <see cref="RandGen"/> class.
/// </summary>
/// <param name="seed">The seed for the Generator.</param>
RandGen::RandGen(std::string seed) {
	setSeed(seed); 
	m_uniDistributor = std::uniform_real_distribution<double>(0, 1);
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
/// Creates a uniform distribution between [min, max)
/// </summary>
/// <param name="min">The minimum number that can be returned.</param>
/// <param name="max">The maximum number that can be returned.</param>
/// <returns></returns>
double RandGen::uniDist(double min, double max) {
	if (min >= max)
	{
		//TODO: THROW ERROR!;;;
	}


	if (min != m_uniDistributor.a() || max != m_uniDistributor.b()) {
		return m_uniDistributor(m_generator);
	}
	else {
		double tempNumber = m_uniDistributor(m_generator);
		return min + tempNumber * (max - min);
	}
}