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
    /// Can be used multiple times for the same Array2D, allowing for layering of graphs.
	/// </summary>
	class libGameBackbone ClusterGreenhouse {
	public:
		ClusterGreenhouse(Point2D<int> dimensions);

		Cluster* chooseClusterToAddTo();

		Point2D<int> growCluster(Cluster* clusterToAddTo);

		void createClustersFromFrequencies(std::vector<double> frequencies);

		std::vector<std::set<Point2D<int>>> generateClusteredGraph(std::vector<double> frequencies);

        // vector holding the clusters in each layer of the graph, each layer being a vector of clusters
		std::vector<std::vector<Cluster>> clusterVectors;

        // vector holding the pointToClusterMap for each layer
        std::vector<std::multimap<Point2D<int>, Cluster>> pointToClusterMaps;

        // Dimensions of the Array2D which is being built upon
		Point2D<int> graphDims;

		RandGen RandomGenerator;

        // How sparse the graph is (in the context of the current layer)
		double sparsity;
	};
}