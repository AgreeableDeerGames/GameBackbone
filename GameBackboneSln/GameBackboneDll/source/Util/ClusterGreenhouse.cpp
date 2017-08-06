#include <Backbone\BackboneBaseExceptions.h>
#include <Util\Array2D.h>
#include <Util\Cluster.h>
#include <Util\ClusterGreenhouse.h>
#include <Util\Point.h>

#include <SFML\Graphics\Sprite.hpp>

#include <set>
#include <tuple>
#include <map>


using namespace GB;

/// <summary>
/// Constructor
/// </summary>
/// <param name="dimensions">The dimension of the Array2D which is being used.</param>
ClusterGreenhouse::ClusterGreenhouse(Point2D<int> dimensions) {
	graphDims = dimensions;
}

/// <summary>
/// Chooses a cluster to add a point to, based on the frequency each Cluster has been assigned.
/// </summary>
/// <return> The cluster which will get a new point added to it. </return>
Cluster* ClusterGreenhouse::chooseClusterToAddTo() {
	double rollDie = RandomGenerator.uniDist(0, 1);
	if (rollDie > (1 - sparsity)) {
		return nullptr;
	}
	for (int i = 0; i < clusterVectors[clusterVectors.size() - 1].size(); i++) {
		// check which cluster will be added to, based on random number and frequency of cluster
		if(rollDie < clusterVectors[clusterVectors.size()-1][i].getClusterFrequency()){
			return &clusterVectors[clusterVectors.size() - 1][i];
		}
	}
	return nullptr;
}

/// <summary>
/// Finds a point for the given cluster to add to, then has the cluster add it.
/// </summary>
/// <param name="clusterToAddTo">Cluster which will have a point added to it.</param>
/// <return> The Point which was added to the cluster. </return>
Point2D<int> ClusterGreenhouse::growCluster(Cluster* clusterToAddTo) {
    // Create and iterator and put it to some random Point2D of the cluster's border
	const std::set<Point2D<int>>* clusterBorderPointSet = clusterToAddTo->getBorderPointSet();
	auto borderPointSetIter = clusterBorderPointSet->begin();
	std::advance(borderPointSetIter, RandomGenerator.uniDist(0, (double)clusterBorderPointSet->size()));

	for (int i = 0; i < clusterBorderPointSet->size(); i++) {
		// If the point is not already in a different cluster and also not on the edge
		// of the graph, then it's okay to be added to this Cluster
		if (pointToClusterMaps[pointToClusterMaps.size()-1].find(*borderPointSetIter) == pointToClusterMaps[pointToClusterMaps.size()-1].end() &&
			graphDims.x > borderPointSetIter->x && graphDims.y > borderPointSetIter->y &&
			0 <= borderPointSetIter->x && 0 <= borderPointSetIter->y) {
			Point2D<int> pointToAdd = *borderPointSetIter;
			clusterToAddTo->addPointToCluster(pointToAdd);

            pointToClusterMaps[pointToClusterMaps.size() - 1].insert(std::make_pair(pointToAdd, *clusterToAddTo));
			return pointToAdd;
		}
		// Otherwise, check the next point in the border
		else {
			borderPointSetIter++;
			if (borderPointSetIter == clusterBorderPointSet->end()) {
				borderPointSetIter = clusterBorderPointSet->begin();
			}
		}
	}
	// If the there were no points which could be added to the cluster, we are given a flag Point2D{-1, -1}.
	return Point2D<int>{-1, -1};
}

/// <summary>
/// Generates the clusters for a round of generation by using the given frequencies. If no frequencies are given, some will be generated.
/// </summary>
/// <param name="frequencies">Frequencies according to which the clusters are to be made.</param>
void ClusterGreenhouse::createClustersFromFrequencies(std::vector<double> frequencies) {
    // If the input frequency vector is not empty...
    if (!frequencies.empty()) {
        std::multimap<Point2D<int>, Cluster > layerPointToClusterMap;
        std::vector<Cluster> layerClusterVector;
        double percentAdjustment = 0;
        for (auto i = 0; i < frequencies.size(); i++) {
            // make an origin for the cluster
            Point2D<int> originPoint{ (int)RandomGenerator.uniDist(0, graphDims.x),(int)RandomGenerator.uniDist(0, graphDims.y) };

            // If that point is already in a different cluster, choose a different one
            while (layerPointToClusterMap.find(originPoint) != layerPointToClusterMap.end()) {
                originPoint = Point2D<int>{ (int)RandomGenerator.uniDist(0, graphDims.x),(int)RandomGenerator.uniDist(0, graphDims.y) };
            }
            // Adjust the frequency of the cluster
            // When the percentages of each cluster are entered, they will be not relative to each other,
            // ie .20, .10, .04
            // They will be added to each other, so:
            // .20, .30, .34
            // sparsity is the leftover percent, so .16
            percentAdjustment = frequencies[i] + percentAdjustment;
            frequencies[i] = percentAdjustment;

            Cluster clusterToAdd(originPoint);
            clusterToAdd.setClusterFrequency(frequencies[i]);
            layerClusterVector.push_back(clusterToAdd);
            layerPointToClusterMap.insert(std::make_pair(originPoint, clusterToAdd));
        }
        pointToClusterMaps.push_back(layerPointToClusterMap);
        clusterVectors.push_back(layerClusterVector);
        sparsity = 1 - frequencies[frequencies.size() - 1];
    }
    // if the frequencies vector is empty, generate a random one and then just call this function again.
    else {
        int numberOfClustersToMake = (int)RandomGenerator.uniDist(4, 8);

        // decide the frequency of this cluster based on how much of 0 through 1 (non-discrete) is left
        double availablePercent = .15;
        double clusterFrequency = 0;
        for (int i = 0; i < numberOfClustersToMake; i++) {
            if (availablePercent < 0) {
                break;
            }

            clusterFrequency = RandomGenerator.uniDist(0, availablePercent);
            availablePercent -= clusterFrequency;

            // add the frequency
            frequencies.push_back(clusterFrequency);
        }
        // call again with the newly generated percents
        createClustersFromFrequencies(frequencies);
    }
}

/// <summary>
/// Generates and grows the clusters for an Array2D.  This can be called multiple times for the same Array2D, with different/same generation options.
/// </summary>
/// <param name="frequencies">The frequencies which will be used in generating the clusters.</param>
/// <returns>A vector of sets.  A single set represents a single cluster, the items in said set being the Point2D's in the Cluster.</returns>
std::vector<std::set<Point2D<int>>> ClusterGreenhouse::generateClusteredGraph(std::vector<double> frequencies) {
    createClustersFromFrequencies(frequencies);

	int Array2DArea = graphDims.x*graphDims.y;
	for (int i = 0; i < Array2DArea; i++) {
		Cluster* clusterToAddTo = chooseClusterToAddTo();
		// clusterToAddTo will be nullptr if none of the clusters were chosen.
		// this will happen frequently if the graph is sparse.
		if (clusterToAddTo != nullptr)
			Point2D<int> pointAdded = growCluster(clusterToAddTo); // In the future, maybe do something if the cluster isn't grown (pointAdded.x != -1).
	}
	std::vector<std::set<Point2D<int>>> Point2DVectorSet;
    // move the clusters' points to the output vector of Point2D sets
	for (auto cluster : this->clusterVectors[clusterVectors.size() - 1]) {
		Point2DVectorSet.push_back(std::move(*(cluster.getClusterPoints())));
	}
	return Point2DVectorSet;
}
