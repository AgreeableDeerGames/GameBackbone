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
ClusterGreenhouse::ClusterGreenhouse(Point2D<int> dimensions, std::vector<double>& clusterFrequencies) {
	graphDims = dimensions;

	if (clusterFrequencies.empty()) {
		clusterFrequencies = generateRandomFrequencyVector();
		return;
	}

	double percentAdjustment = 0;
	for (auto i = 0; i < clusterFrequencies.size(); i++) {
		// make an origin for the cluster
		Point2D<int> originPoint{(int)RandomGenerator.uniDist(0, graphDims.x),(int)RandomGenerator.uniDist(0, graphDims.y)};

		while (pointToClusterMap.find(originPoint) != pointToClusterMap.end()) {
			// make a new one if one is already taken
			// TODO: make sure that it is also ether not within another cluster's border here, or check to make sure that 
			// we are not adding a point to a cluster where the said point is in a different cluster
			originPoint = Point2D<int>{(int)RandomGenerator.uniDist(0, graphDims.x),(int)RandomGenerator.uniDist(0, graphDims.y)};
		}
		// adjust the frequency of the cluster
		// when the percentages of each cluster are entered, they will be not relative to each other,
		// ie .20, .10, .04
		// afterwards it will be
		// .20, .30, .34
		// sparcity is the leftover percent, so .16
		percentAdjustment = clusterFrequencies[i] + percentAdjustment;
		clusterFrequencies[i] = percentAdjustment;

		Cluster clusterToAdd(originPoint);
		clusterToAdd.setClusterFrequency(clusterFrequencies[i]);
		clusterVector.push_back(clusterToAdd);
		pointToClusterMap.insert(std::make_pair(originPoint, clusterToAdd));
	}
    sparcity = 1 - clusterFrequencies[clusterFrequencies.size() - 1];
}

/// <summary>
/// Chooses a cluster to add a point to, based on the frequency each Cluster has been assigned.
/// </summary>
/// <return> The cluster which will get a new point added to it. </return>
Cluster* ClusterGreenhouse::chooseClusterToAddTo() {
	double rollDie = RandomGenerator.uniDist(0, 1);
	if (rollDie > (1 - sparcity)) {
		return nullptr;
	}
	for (int i = 0; i < clusterVector.size(); i++) {
		// check which cluster will be added to, based on random number and frequency of cluster
		if(rollDie < clusterVector[i].getClusterFrequency()){
			return &clusterVector[i];
		}
	}
	return nullptr;
}

/// <summary>
/// Finds a point for the cluster to add to, then has the cluster add it.
/// </summary>
/// <param name="clusterToAddTo">Cluster which will have a point added to it.</param>
/// <return> The Point which was added to the cluster. </return>
Point2D<int> ClusterGreenhouse::growCluster(Cluster* clusterToAddTo) {
	const std::set<Point2D<int>>* clusterBorderPointSet = clusterToAddTo->getBorderPointSet();
	auto borderPointSetIter = clusterBorderPointSet->begin();
	std::advance(borderPointSetIter, RandomGenerator.uniDist(0, (double)clusterBorderPointSet->size()));

	for (int i = 0; i < clusterBorderPointSet->size(); i++) {
		// If the point is not already in a different cluster and also not on the edge
		// of the graph, we're good
		if (pointToClusterMap.find(*borderPointSetIter) == pointToClusterMap.end() &&
			graphDims.x > borderPointSetIter->x && graphDims.y > borderPointSetIter->y &&
			0 <= borderPointSetIter->x && 0 <= borderPointSetIter->y) {
			Point2D<int> pointToAdd = *borderPointSetIter;
			clusterToAddTo->addPointToCluster(pointToAdd);

			pointToClusterMap.insert(std::make_pair(pointToAdd, *clusterToAddTo));
			return pointToAdd;
		}
		// Otherwise, check the next point in the set
		else {
			borderPointSetIter++;
			if (borderPointSetIter == clusterBorderPointSet->end()) {
				borderPointSetIter = clusterBorderPointSet->begin();
			}
		}
	}
	// If the there were no point which could be added to the cluster, we are given a flag Point2D{-1, -1}.
	return Point2D<int>{-1, -1};
}

/// <summary>
/// Generates some random frequencies to be used be the clusters during generation (only frequency is used).
/// </summary>
/// <param name="frequencies">Empty frequency vector .</param>
std::vector<double> ClusterGreenhouse::generateRandomFrequencyVector() {

	std::vector<double> frequencies;

	int numberOfClustersToMake = (int)RandomGenerator.uniDist(4, 8);

	// decide the frequency of this cluster based on how much of 0 through 1 (non-discrete) is left
	double availablePercent = .15;
	sparcity = 1 - availablePercent;
	double clusterFrequency = 0;
	for (int i = 0; i < numberOfClustersToMake; i++) {
		if (availablePercent < 0) {
			break;
		}

	    clusterFrequency = RandomGenerator.uniDist(1 - availablePercent, 1);
		availablePercent = 1 - clusterFrequency;

		// choose a starting point for cluster then make cluster
		Point2D<int> originPoint{(int)RandomGenerator.uniDist(0, graphDims.x),(int)RandomGenerator.uniDist(0, graphDims.y)};
		Cluster cluster(originPoint);

		// create the generation options for cluster made
		double newGenerationOption = clusterFrequency;
		frequencies.push_back(newGenerationOption);

		cluster.setClusterFrequency(newGenerationOption);
		clusterVector.push_back(cluster);
		pointToClusterMap.insert(std::make_pair(originPoint, cluster)); // always be sure to insert you're origin point kids! :>
	}
	// whatever percent is left over will be added to sparsity
	if (availablePercent > 0) {
		sparcity += availablePercent;
	}

	return frequencies;
}

/// <summary>
/// Generates the clusters for an Array2D
/// </summary>
/// <param name="frequencies">The frequencies which will be used in generating the clusters.</param>
/// <returns>A vector of sets.  A single set represents a single cluster, the items in said said being the Point2D's in the Cluster.</returns>
std::vector<std::set<Point2D<int>>> ClusterGreenhouse::generateClusteredGraph(std::vector<double>& frequencies) {
	if (frequencies.empty()) {
		// If there is no input cluster generation options, then we'll just generate some
		// frequencies should be empty
		frequencies = generateRandomFrequencyVector();
	}
	int Array2DArea = graphDims.x*graphDims.y;
	for (int i = 0; i < Array2DArea; i++) {
		Cluster* clusterToAddTo = chooseClusterToAddTo();
		// clusterToAddTo will be nullptr if none of the clusters were chosen.
		// this will happen frequently if the graph is sparse.
		if (clusterToAddTo != nullptr)
			Point2D<int> pointAdded = growCluster(clusterToAddTo); // In the future, maybe do something if the cluster isn't grown (pointAdded.x != -1).
	}
	std::vector<std::set<Point2D<int>>> vectorOfPointSets;
	for (auto cluster : this->clusterVector) {
		vectorOfPointSets.push_back(std::move(*(cluster.getClusterPoints())));
	}
	return vectorOfPointSets;
}
