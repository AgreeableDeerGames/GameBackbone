#include "stdafx.h"
#include "RandGen.h"

using namespace GB;

RandGen::RandGen(){
	SetSeed("TestString");
	UniDistributor = std::uniform_real_distribution<double>(0, 1);
}

RandGen::~RandGen(){

}

std::string RandGen::GetSeed(){
	return m_seedString;
}

void RandGen::SetSeed(std::string seed){
	// Save the string
	m_seedString = seed;

	// Set the seed on our engine.
	std::seed_seq tempSeed(m_seedString.begin(), m_seedString.end());
	m_generator.seed(tempSeed);
}

unsigned int RandGen::UniDist(int min, int max) {
	double tempNumber = UniDistributor(m_generator);

	return min + tempNumber * (max - min);
}