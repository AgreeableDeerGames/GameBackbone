#pragma once


#include <Backbone\Cluster.h>
#include <Util\Array2D.h>

#include <SFML\Graphics\Sprite.hpp>

#include <set>
#include <tuple>
#include <map>


namespace GB {

	class libGameBackbone ClusterGreenhouse {
	public:
		ClusterGreenhouse(unsigned int graphSizeX, unsigned int graphSizeY, std::vector<ClusterGenerationOptions>* generationOptions);

		Cluster* chooseClusterToAddTo();

		bool growCluster(Cluster* clusterToAddTo);

		// If there is no input cluster generation options, then we'll just generate some
		// generationOptions should be empty
		void GenerateRandomOptionsVector(std::vector<ClusterGenerationOptions>* generationOptions);

		std::vector<Cluster> clusterVector;
		std::multimap<std::pair<int, int>, Cluster> pointToClusterMap;
		std::pair<int, int> graphDims;
	};
}