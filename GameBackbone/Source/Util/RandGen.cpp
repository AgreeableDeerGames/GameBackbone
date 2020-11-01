#include <GameBackbone/Util/RandGen.h>

#include <stdexcept>

using namespace GB;

RandGen::RandGen() :
	m_seedString(),
	m_generator(),
	m_uniDistributor(std::uniform_real_distribution<double>(0, 1))
{
	// This Random device is used to generate the seed if no seed is provided.
	// We then convert the unsigned int that it returns and turn that into a string which we set on our Generator.
	std::random_device rd;
	setSeed(std::string(std::to_string(rd())));
}

RandGen::RandGen(std::string seed) :
	m_seedString(std::move(seed)),
	m_generator(),
	m_uniDistributor(std::uniform_real_distribution<double>(0, 1))
{
}

const std::string& RandGen::getSeed() const noexcept
{
	return m_seedString;
}

void RandGen::setSeed(std::string seed) 
{
	// Save the string
	m_seedString = std::move(seed);

	// Set the seed on our engine.
	std::seed_seq tempSeed(m_seedString.begin(), m_seedString.end());
	m_generator.seed(tempSeed);
}

double RandGen::uniDist(double min, double max) 
{
	if (min >= max)
	{
		throw std::runtime_error("RandGen::uniDist's min cannot be greater than or equal to min.");
	}


	if (min != m_uniDistributor.a() || max != m_uniDistributor.b()) 
	{
		double tempNumber = m_uniDistributor(m_generator);
		return min + tempNumber * (max - min);
	}
	return m_uniDistributor(m_generator);
}