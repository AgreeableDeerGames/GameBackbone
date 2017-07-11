#include <Util\Array2D.h>
#include <Util\Cluster.h>
#include <Util\ClusterGreenhouse.h>
#include <Util\Point.h>

#include <SFML\Graphics\Sprite.hpp>

#include <set>
#include <tuple>
#include <map>


using namespace GB;

ClusterGreenhouse::ClusterGreenhouse(Point2D<int> dimensions, std::vector<ClusterGenerationOptions>* generationOptions) {
	graphDims = dimensions;

	if (generationOptions->empty()) {
		GenerateRandomOptionsVector(generationOptions);
	}

	int newPercent = 0;
	for (auto i = 0; i < generationOptions->size(); i++) {
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
		// ie 25, 25, 10, 40
		// afterwards it will be
		// 25, 50, 60, 100
		newPercent = (*generationOptions)[i].percent + newPercent;
		(*generationOptions)[i].percent = newPercent;

		Cluster clusterToAdd(originPoint, graphDims, pointToClusterMap);
		clusterToAdd.setClusterGenerationOptions(&(*generationOptions)[i]);
		clusterVector.push_back(clusterToAdd);
		pointToClusterMap.insert(std::make_pair(originPoint, clusterToAdd));
	}
	// 2-cluster debug
	/*
	Cluster cluster1(Point2D<int>{13, 13}, pointToClusterMap, Point2D<int>{20, 20});
	cluster1.setClusterDisplayColor(sf::Color::Red);
	clusterVector.push_back(cluster1);
	pointToClusterMap.insert(std::make_pair(Point2D<int>{13, 13}, cluster1));
	Cluster cluster2(Point2D<int>{5, 5}, pointToClusterMap, Point2D<int>{20, 20});
	cluster2.setClusterDisplayColor(sf::Color::Red);
	clusterVector.push_back(cluster2);
	pointToClusterMap.insert(std::make_pair(Point2D<int>{5, 5}, cluster2));*/
}

Cluster* ClusterGreenhouse::chooseClusterToAddTo() {
	int rollDie = (int)RandomGenerator.uniDist(0, 100);

	for (int i = 0; i < clusterVector.size(); i++) {
		// check which cluster will be added to, based on rand number and frequency of cluster
		if (rollDie < clusterVector[i].getClusterGenerationOptions()->percent)
			return &clusterVector[i];
	}

	return &clusterVector[0];
}

bool ClusterGreenhouse::growCluster(Cluster* clusterToAddTo) {
	return clusterToAddTo->addPointToCluster((int)RandomGenerator.uniDist(0, clusterToAddTo->getNumberBorderPoints()));
}

// If there is no input cluster generation options, then we'll just generate some
// generationOptions should be empty
void ClusterGreenhouse::GenerateRandomOptionsVector(std::vector<ClusterGenerationOptions>* generationOptions) {
	int numberOfClustersToMake = (int)RandomGenerator.uniDist(1, 6);

	// decide the frequency of this cluster based on how much of the [1, 100] is left
	int availablePercent = 100;
	int clusterFrequency = 0;
	for (int i = 0; i < numberOfClustersToMake; i++) {
		clusterFrequency = 0;
		if (i == 0 && availablePercent > 0) {
			clusterFrequency = 40;
			availablePercent = availablePercent - clusterFrequency;
		}
		else if (availablePercent > 0) {
			clusterFrequency = ((int)RandomGenerator.uniDist(0, availablePercent + 1)) + (100 - availablePercent);
			availablePercent = availablePercent - clusterFrequency;
		}
		else {
			return;
		}

		// choose a starting point for cluster then make cluster
		Point2D<int> originPoint{(int)RandomGenerator.uniDist(0, graphDims.x),(int)RandomGenerator.uniDist(0, graphDims.y)};
		Cluster cluster(originPoint, graphDims, pointToClusterMap);

		// create the generation options for cluster made, using 
		ClusterGenerationOptions newGenerationOption;
		int whichClusterType = (int)RandomGenerator.uniDist(0, 5);
		switch (whichClusterType) {
		case 0:
			newGenerationOption.colorOfCluster = sf::Color::Red; newGenerationOption.percent = clusterFrequency;
			break;
		case 1:
			newGenerationOption.colorOfCluster = sf::Color::Blue; newGenerationOption.percent = clusterFrequency;
			break;
		case 2:
			newGenerationOption.colorOfCluster = sf::Color::Magenta; newGenerationOption.percent = clusterFrequency;
			break;
		case 3:
			newGenerationOption.colorOfCluster = sf::Color::Green; newGenerationOption.percent = clusterFrequency;
			break;
		case 4:
			newGenerationOption.colorOfCluster = sf::Color::Cyan; newGenerationOption.percent = clusterFrequency;
			break;
		default:
			newGenerationOption.colorOfCluster = sf::Color::White; newGenerationOption.percent = clusterFrequency;
			break;
		}
		cluster.setClusterGenerationOptions(&newGenerationOption);
		clusterVector.push_back(cluster);
		pointToClusterMap.insert(std::make_pair(originPoint, cluster)); // always be sure to insert you're origin point kids! :>
	}
}
