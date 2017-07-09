#include <Backbone\Cluster.h>
#include <Backbone\ClusterGreenhouse.h>
#include <Util\Array2D.h>

#include <SFML\Graphics\Sprite.hpp>

#include <set>
#include <tuple>
#include <map>


using namespace GB;

ClusterGreenhouse::ClusterGreenhouse(std::vector<ClusterGenerationOptions>* generationOptions, Array2D<T>& graphToPopulate) {
	graphDims.first = graphToPopulate.getArraySizeX(); graphDims.second = graphToPopulate.getArraySizeY();
	if (generationOptions->empty()) {
		GenerateRandomOptionsVector(generationOptions);
	}

	int newPercent = 0;
	for (auto i = 0; i < generationOptions->size(); i++) {
		// make an origin for the cluster
		std::pair<int, int> clusterOrigin(rand() % graphToPopulate.getArraySizeX(), rand() % graphToPopulate.getArraySizeY());
		while (pointToClusterMap.find(clusterOrigin) != pointToClusterMap.end()) {
			// make a new one if one is already taken
			// TODO: make sure that it is also ether not within another cluster's border here, or check to make sure that 
			// we are not adding a point to a cluster where the said point is in a different cluster
			clusterOrigin = std::pair<int, int>(rand() % graphToPopulate.getArraySizeX(), rand() % graphToPopulate.getArraySizeY());
		}
		// adjust the frequency of the cluster
		// when the percentages of each cluster are entered, they will be not relative to eachother,
		// ie 25, 25, 10, 40
		// afterwards it will be
		// 25, 50, 60, 100
		newPercent = (*generationOptions)[i].percent + newPercent;
		(*generationOptions)[i].percent = newPercent;

		Cluster clusterToAdd(clusterOrigin, pointToClusterMap, std::pair<int, int>(graphToPopulate.getArraySizeX(), graphToPopulate.getArraySizeY()));
		clusterToAdd.setClusterGenerationOptions(&(*generationOptions)[i]);
		clusterVector.push_back(clusterToAdd);
		pointToClusterMap.insert(std::make_pair(clusterOrigin, clusterToAdd));
	}
	// 2-cluster debug
	/*
	Cluster cluster1(std::pair<int, int>(13, 13), pointToClusterMap, std::pair<int, int>(20, 20));
	cluster1.setClusterDisplayColor(sf::Color::Red);
	clusterVector.push_back(cluster1);
	pointToClusterMap.insert(std::make_pair(std::pair<int, int>(13, 13), cluster1));
	Cluster cluster2(std::pair<int, int>(5, 5), pointToClusterMap, std::pair<int, int>(20, 20));
	cluster2.setClusterDisplayColor(sf::Color::Red);
	clusterVector.push_back(cluster2);
	pointToClusterMap.insert(std::make_pair(std::pair<int, int>(5, 5), cluster2));*/
}

Cluster* ClusterGreenhouse::chooseClusterToAddTo() {
	int rollDie = rand() % 100;
	for (int i = 0; i < clusterVector.size(); i++) {
		// check which cluster will be added to, based on rand number and frequency of cluster
		if (rollDie < clusterVector[i].getClusterGenerationOptions()->percent)
			return &clusterVector[i];
	}
	return &clusterVector[0];
}

bool ClusterGreenhouse::growCluster(Cluster* clusterToAddTo) {
	return clusterToAddTo->addPointToCluster(rand());
}

// If there is no input cluster generation options, then we'll just generate some
// generationOptions should be empty
void ClusterGreenhouse::GenerateRandomOptionsVector(std::vector<ClusterGenerationOptions>* generationOptions) {
	int numberOfClustersToMake = (rand() % 5) + 1;

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
			clusterFrequency = (rand() % (availablePercent + 1)) + (100 - availablePercent);
			availablePercent = availablePercent - clusterFrequency;
		}
		else {
			return;
		}

		// choose a starting point for cluster then make cluster
		std::pair<int, int> originPoint(rand() % graphDims.first, rand() % graphDims.second);
		Cluster cluster(originPoint, pointToClusterMap, std::pair<int, int>(graphDims.first, graphDims.second));

		// create the generation options for cluster made, using 
		ClusterGenerationOptions newGenerationOption;
		int whichClusterType = rand() % 5;
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
