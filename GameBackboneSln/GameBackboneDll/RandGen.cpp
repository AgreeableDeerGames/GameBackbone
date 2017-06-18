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
	SetSeed(std::to_string(rd()));

	SetUniDistributor(0, 1);
}


/// <summary>
/// Initializes a new instance of the <see cref="RandGen"/> class.
/// </summary>
/// <param name="seed">The seed for the Generator.</param>
RandGen::RandGen(std::string seed) {
	SetSeed(seed); 
	SetUniDistributor(0, 1);
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
	SetSeed(std::to_string(rd()));

	SetUniDistributor(min, max);
}


/// <summary>
/// Initializes a new instance of the <see cref="RandGen"/> class.
/// </summary>
/// <param name="seed">The seed for the Generator.</param>
/// <param name="min">The minimum number that will be set on the UniDistributor.</param>
/// <param name="max">The maximum number that will be set on the UniDistributor.</param>
RandGen::RandGen(std::string seed, double min, double max) {
	SetSeed(seed);
	SetUniDistributor(min, max);
}

/// <summary>
/// Gets the seed of the Random Generator.
/// </summary>
/// <returns></returns>
std::string RandGen::GetSeed() {
	return m_seedString;
}


/// <summary>
/// Sets the seed of the Random Generator.
/// </summary>
/// <param name="seed">New seed that we are setting on the engine.</param>
void RandGen::SetSeed(std::string seed) {
	// Save the string
	m_seedString = seed;

	// Set the seed on our engine.
	std::seed_seq tempSeed(m_seedString.begin(), m_seedString.end());
	m_generator.seed(tempSeed);
}

/// <summary>
/// Sets uniDistributor's min and max limits.
/// 
/// Note: if you change the min and max limits using this function, 
///		  the UniDist function will give bad results.
/// </summary>
/// <param name="min">The minimum.</param>
/// <param name="max">The maximum.</param>
void RandGen::SetUniDistributor(double min, double max) {
	m_uniDistributor = std::uniform_real_distribution<double>(min, max);
}

/// <summary>
/// Creates a uniform distribution between [0, 1)
/// </summary>
/// <returns></returns>
double RandGen::UniDist() {
	double tempNumber = m_uniDistributor(m_generator);
	return tempNumber;
}

/// <summary>
/// Creates a uniform distribution between [min, max)
/// </summary>
/// <param name="min">The minimum number that can be returned.</param>
/// <param name="max">The maximum number that can be returned.</param>
/// <returns></returns>
double RandGen::UniDist(double min, double max) {
	double tempNumber = m_uniDistributor(m_generator);

	return min + tempNumber * (max - min);
}