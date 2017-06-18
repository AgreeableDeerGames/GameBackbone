#pragma once
#include "stdafx.h"
#include "DllUtil.h"


#include<random>
#include<string>

//template class libGameBackbone std::mersenne_twister_engine<unsigned int,32,624,397,31,2567483615,11,4294967295,7,2636928640,15,4022730752,18,1812433253>;
//template class __declspec(dllexport) std::string;
template class libGameBackbone std::uniform_real_distribution<double>;

namespace GB {

	class libGameBackbone RandGen {
	public:
		RandGen();
		RandGen(std::string seed);

		RandGen(const RandGen& generator) = default;
		RandGen(RandGen&& generator) = default;
		RandGen& operator= (const RandGen& generator) = default;
		RandGen& operator= (RandGen&& generator) = default;
		~RandGen() = default;


		std::string getSeed();
		void setSeed(std::string seed);

		double uniDist(double min, double max);

	private:
		std::string m_seedString;
		std::mt19937 m_generator;
		std::uniform_real_distribution<double> m_uniDistributor;

	};
}