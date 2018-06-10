#pragma once

#include <Util/Array2D.h>
#include <Util/DllUtil.h>
#include <Util/Point.h>

#include <SFML/Graphics/Sprite.hpp>

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
		explicit Cluster(Point2D<int> firstPoint);

        //getter
		std::set<Point2D<int>> const* const getClusterPoints();
		std::set<Point2D<int>> const* const getBorderPointSet();

		double getClusterFrequency();

        //setter
		void setClusterFrequency(double FrequencyForThisCluster);

		void addPointToCluster(Point2D<int> newPointToAdd);
		unsigned int getNumberBorderPoints();



    private:
		void UpdateBorder(Point2D<int> pointToAdd);

        // Set of all points of the Array2D which are owned by this cluster
        std::set<Point2D<int>> clusterPointSet;

        // Set of all points in the cluster's border. Used as potential points to be added.
        std::set<Point2D<int>> borderPointSet;

        // Determines the amount of the map which will be of this cluster.
        double clusterFrequency;
    };
}