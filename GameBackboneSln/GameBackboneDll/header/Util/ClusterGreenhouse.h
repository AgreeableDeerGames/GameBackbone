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

	/// <summary>
	/// Grows existing clusters. Ensures that the sets of points added to each cluster are disjointed.
	/// </summary>
	class libGameBackbone ClusterGreenhouse {
	public:
		ClusterGreenhouse(Point2D<int> dimensions, std::vector<double>& generationOptions);

		Cluster* chooseClusterToAddTo();

		Point2D<int> growCluster(Cluster* clusterToAddTo);

		std::vector<double> generateRandomFrequencyVector();

		std::vector<std::set<Point2D<int>>> generateClusteredGraph(std::vector<double>& generationOptions);

		std::vector<Cluster> clusterVector;
		std::multimap<Point2D<int>, Cluster> pointToClusterMap;
		Point2D<int> graphDims;
		RandGen RandomGenerator;
		double sparcity;
	};
}