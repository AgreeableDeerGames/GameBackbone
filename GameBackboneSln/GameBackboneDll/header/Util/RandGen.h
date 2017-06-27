#pragma once

#include <Util\DllUtil.h>

#include <random>
#include <string>


namespace GB {

	class libGameBackbone RandGen {
	public:
		RandGen();
		RandGen(std::string* seed);

		RandGen(const RandGen& generator) = default;
		RandGen(RandGen&& generator) = default;
		RandGen& operator= (const RandGen& generator) = default;
		RandGen& operator= (RandGen&& generator) = default;
		~RandGen();


		std::string getSeed();
		void setSeed(std::string* seed);

		double uniDist(double min, double max);

	protected:
		// This is being made a pointer to remove the VS warning about declspecing seed.
		// Everyone is going to have to compile this anyway witht he same compiler as their project so they won't have issues.
		std::string* m_seedString;

		std::mt19937* m_generator;
		std::uniform_real_distribution<double>* m_uniDistributor;

	};
}