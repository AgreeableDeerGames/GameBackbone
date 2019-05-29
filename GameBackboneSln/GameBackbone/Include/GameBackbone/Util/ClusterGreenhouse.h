#pragma once

#include <GameBackbone/Util/Array2D.h>
#include <GameBackbone/Util/Cluster.h>
#include <GameBackbone/Util/RandGen.h>
#include <GameBackbone/Util/SFUtil.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

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
		explicit ClusterGreenhouse(sf::Vector2i dimensions);

		Cluster* chooseClusterToAddTo();

		sf::Vector2i growCluster(Cluster* clusterToAddTo);

		void createClustersFromFrequencies(std::vector<double> frequencies);

		std::vector<std::set<sf::Vector2i, Vec2Compare<int>>> generateClusteredGraph(const std::vector<double>& frequencies);

        // vector holding the clusters in each layer of the graph, each layer being a vector of clusters
		std::vector<std::vector<Cluster>> clusterVectors;

        // vector holding the pointToClusterMap for each layer
        std::vector<std::multimap<sf::Vector2i, Cluster, Vec2Compare<int>>> pointToClusterMaps;

        // Dimensions of the Array2D which is being built upon
		sf::Vector2i graphDims;

		RandGen RandomGenerator;

        // How sparse the graph is (in the context of the current layer)
		double sparsity;
	};
}