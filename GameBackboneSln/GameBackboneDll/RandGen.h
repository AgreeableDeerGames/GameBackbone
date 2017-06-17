#pragma once
#include "stdafx.h"
#include "DllUtil.h"
#include<random>
#include<string>

namespace GB {

	/// <summary>
	/// TODO: Update this thing.
	/// </summary>
	class libGameBackbone RandGen {
	public:
		RandGen();
		RandGen(const RandGen& generator) = default;
		RandGen(RandGen&& generator) = default;
		RandGen& operator= (const RandGen& generator) = default;
		RandGen& operator= (RandGen&& generator) = default;
		~RandGen();


		std::string GetSeed();
		void SetSeed(std::string seed);

		//unsigned int Generate();
		unsigned int UniDist(int min, int max);

	private:
		std::string m_seedString;
		std::default_random_engine m_generator;
		std::uniform_real_distribution<double> UniDistributor;

	};
}