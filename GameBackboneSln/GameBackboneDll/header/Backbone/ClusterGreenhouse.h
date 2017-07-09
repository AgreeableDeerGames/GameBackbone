#pragma once


#include <Backbone\Cluster.h>
#include <Util\Array2D.h>

#include <SFML\Graphics\Sprite.hpp>

#include <set>
#include <tuple>
#include <map>


namespace GB {

	class ClusterGreenhouse {
	public:
		ClusterGreenhouse(std::vector<ClusterGenerationOptions>* generationOptions, Array2D<T>& graphToPopulate);

		Cluster* chooseClusterToAddTo();

		bool growCluster(Cluster* clusterToAddTo);

		// If there is no input cluster generation options, then we'll just generate some
		// generationOptions should be empty
		void GenerateRandomOptionsVector(std::vector<ClusterGenerationOptions>* generationOptions);
}