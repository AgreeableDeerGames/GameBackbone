#pragma once

#include <GameBackbone/Util/Array2D.h>
#include <GameBackbone/Util/DllUtil.h>
#include <GameBackbone/Util/SFUtil.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include <set>
#include <tuple>
#include <map>

namespace GB {

	/// <summary>
	/// A collection of unique integer coordinates.
	/// </summary>
    class libGameBackbone Cluster {
    public:
        // constructor
		explicit Cluster(sf::Vector2i firstPoint);

        //getter
		std::set<sf::Vector2i, Vec2Compare<int>> const* const getClusterPoints();
		std::set<sf::Vector2i, Vec2Compare<int>> const* const getBorderPointSet();

		double getClusterFrequency();

        //setter
		void setClusterFrequency(double FrequencyForThisCluster);

		void addPointToCluster(sf::Vector2i newPointToAdd);
		unsigned int getNumberBorderPoints();



    private:
		void UpdateBorder(sf::Vector2i pointToAdd);

        // Set of all points of the Array2D which are owned by this cluster
        std::set<sf::Vector2i, Vec2Compare<int>> clusterPointSet;

        // Set of all points in the cluster's border. Used as potential points to be added.
        std::set<sf::Vector2i, Vec2Compare<int>> borderPointSet;

        // Determines the amount of the map which will be of this cluster.
        double clusterFrequency;
    };
}