#pragma once

#include <Util\Array2D.h>
#include <Util\Cluster.h>
#include <Util\Point.h>
#include <Util\RandGen.h>

#include <SFML\Graphics\Sprite.hpp>

#include <set>
#include <tuple>
#include <map>


namespace GB {

	class libGameBackbone ClusterGreenhouse {
	public:
		ClusterGreenhouse(Point2D<int> dimensions, std::vector<ClusterGenerationOptions>* generationOptions);

		Cluster* chooseClusterToAddTo();

		bool growCluster(Cluster* clusterToAddTo);

		// If there is no input cluster generation options, then we'll just generate some
		// generationOptions should be empty
		void GenerateRandomOptionsVector(std::vector<ClusterGenerationOptions>* generationOptions);

		std::vector<Cluster> clusterVector;
		std::multimap<Point2D<int>, Cluster> pointToClusterMap;
		Point2D<int> graphDims;
		RandGen RandomGenerator;
	};
}