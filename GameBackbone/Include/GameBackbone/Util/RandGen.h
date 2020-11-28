#pragma once

#include <GameBackbone/Util/DllUtil.h>

#include <random>
#include <string>


namespace GB {
	
	/// @brief This class is a shallow wrapper for std::random.
	///		To use this class, make an instance of RandGen with a given seed. Call uniDist anytime you need a random number.
	class libGameBackbone RandGen {
	public:

		/// @brief Initializes a new instance of the RandGen class with a random seed.
		RandGen();

		/// @brief Initializes a new instance of the RandGen class.
		/// @param seed The seed for the Generator.
		explicit RandGen(std::string seed);

		RandGen(const RandGen& generator) = default;
		RandGen(RandGen&& generator) noexcept = default;
		RandGen& operator= (const RandGen& generator) = default;
		RandGen& operator= (RandGen&& generator) noexcept = default;

		/// @brief Destroys an instance of RandGen
		~RandGen() = default;

		/// @brief Gets the seed of the Random Generator.
		/// @return The seed of the Random Generator
		const std::string& getSeed() const noexcept;

		/// @brief Sets the seed of this RandGen instance
		/// @param seed The new seed of the RandGen
		void setSeed(std::string seed);

		/// @brief Creates a uniform distribution between [min, max)
		///		Throws if the provided min is not less than the max.
		/// @param min The minimum number that can be returned.
		/// @param max The maximum number that can be returned.
		/// @throws std::runtime_error if min is greater than or equal to max
		/// @return A random number between min and max
		double uniDist(double min, double max);

	protected:
		std::string m_seedString;

		std::mt19937 m_generator;
		std::uniform_real_distribution<double> m_uniDistributor;

	};
}