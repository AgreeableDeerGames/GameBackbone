#pragma once
#include "stdafx.h"
#include "DllUtil.h"


#include<random>
#include<string>

namespace GB {

	
	class libGameBackbone RandGen {
	public:
		RandGen();
		RandGen(std::string seed);
		RandGen(double min, double max);
		RandGen(std::string seed, double min, double max);

		RandGen(const RandGen& generator) = default;
		RandGen(RandGen&& generator) = default;
		RandGen& operator= (const RandGen& generator) = default;
		RandGen& operator= (RandGen&& generator) = default;
		~RandGen() = default;


		std::string GetSeed();
		void SetSeed(std::string seed);
		void SetUniDistributor(double min, double max);

		double UniDist();
		double UniDist(double min, double max);

	private:
		std::string m_seedString;
		std::default_random_engine m_generator;
		std::uniform_real_distribution<double> m_uniDistributor;

	};
}