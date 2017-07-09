#pragma once
#include <Backbone\Cluster.h>
#include <Backbone\ClusterGreenhouse.h>
#include <Util\DllUtil.h>
#include <Util\Point.h>

#include <SFML\System\Vector3.hpp>

#include <chrono>
#include <math.h>

namespace GB {

	//vector operations

	/// <summary>
	/// Determines the distance between two points in an three dimensional space.
	/// </summary>
	/// <param name="point1">The first point</param>
	/// <param name="point2">The second point</param>
	/// <returns>The distance between the two points</returns>
	template<class T>
	libGameBackbone T CalcDistance(const Point3D<T> & point1, const Point3D<T> & point2) {
		return (T)sqrt(CalcSquaredDistance(point1, point2));
	}

	/// <summary>
	/// Determines the square of the distance between two three dimensional points.
	/// </summary>
	/// <param name="point1">The first point.</param>
	/// <param name="point2">The second point.</param>
	/// <returns>The square of the distance between two three dimensional points.</returns>
	template<class T>
	libGameBackbone T CalcSquaredDistance(const Point3D<T> & point1, const Point3D<T> & point2) {
		return (T)(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2) + pow(point1.z - point2.z, 2));
	}

	/// <summary>
	/// Determines the distance between two points in an two dimensional space.
	/// </summary>
	/// <param name="point1">The first point</param>
	/// <param name="point2">The second point</param>
	/// <returns>the distance between the two points</returns>
	template<class T>
	libGameBackbone T CalcDistance(const Point2D<T> & point1, const Point2D<T> & point2) {
		return (T)sqrt(CalcSquaredDistance(point1, point2));
	}

	/// <summary>
	/// Determines the square of the distance between two 2 dimensional points.
	/// </summary>
	/// <param name="point1">The first point.</param>
	/// <param name="point2">The second point.</param>
	/// <returns>The square of the distance between two three dimensional points.</returns>
	template<class T>
	libGameBackbone T CalcSquaredDistance(const Point2D<T> & point1, const Point2D<T> & point2) {
		return (T)(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
	}

    /// <summary>
    /// Generates Clusters in the graph.
    /// </summary>
    /// <param name="graph">The graph to be clustered.</param>
    /// <param name="graphOptions">Graph options/settings.</param>
    /// <returns>Vector of clusters in the graph.</returns>
    libGameBackbone std::multimap<std::pair<int, int>, Cluster> GenerateClusteredGraph(unsigned int graphSizeX, unsigned int graphSizeY, std::vector<ClusterGenerationOptions>* generationOptionsVector) {
        srand((unsigned int)time(NULL));

        ClusterGreenhouse* graphGenerator = new ClusterGreenhouse(graphSizeX, graphSizeY, generationOptionsVector);
        for (int i = 0; i < 20; i++) {
            Cluster* clusterToAddTo = graphGenerator->chooseClusterToAddTo();
            bool clusterGrew = graphGenerator->growCluster(clusterToAddTo);
        }
        return graphGenerator->pointToClusterMap;
    }// end GenerateClusteredGraph
    
}
