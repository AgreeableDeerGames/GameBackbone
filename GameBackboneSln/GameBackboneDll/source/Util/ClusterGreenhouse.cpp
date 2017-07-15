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
	std::vector<ClusterGenerationOptions> generationOptions; // This is temporary while we transition to passing in some other form of options
	if (generationOptions.empty()) {
		GenerateRandomOptionsVector(generationOptions);
		return;
	}
	// TODO: it is uncertain how we are going to let the greenhouse know what kinds of cluster are to be made.  For now
	// just call GenerateRandomOptionsVector (see above).
	int newPercent = 0;
	for (auto i = 0; i < generationOptions.size(); i++) {
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
		newPercent = generationOptions[i].percent + newPercent;
		generationOptions[i].percent = newPercent;

		Cluster clusterToAdd(originPoint, graphDims, pointToClusterMap);
		clusterToAdd.setClusterGenerationOptions(&(generationOptions)[i]);
		clusterVector.push_back(clusterToAdd);
		pointToClusterMap.insert(std::make_pair(originPoint, clusterToAdd));
	}
}

/// <summary>
/// Chooses a cluster to add a point to, based on the frequency each Cluster has been assigned.
/// </summary>
/// <return> The cluster which will get a new point added to it. </return>
Cluster* ClusterGreenhouse::chooseClusterToAddTo() {
	double rollDie = RandomGenerator.uniDist(0, 1);
	if (rollDie < sparcity) {
		return nullptr;
	}
	Cluster* currentWinner = &clusterVector[0];
	for (int i = 0; i < clusterVector.size(); i++) {
		// check which cluster will be added to, based on random number and frequency of cluster
		if(rollDie > clusterVector[i].getClusterGenerationOptions()->percent &&
			currentWinner->getClusterGenerationOptions()->percent < clusterVector[i].getClusterGenerationOptions()->percent){
			currentWinner = &clusterVector[i];
		}
	}

	return currentWinner;
}

/// <summary>
/// Calls the Cluster's addPointToCluster.
/// </summary>
/// <param name="clusterToAddTo">Cluster which will have a point added to it.</param>
/// <return> The Point which was added to the cluster. </return>
Point2D<int> ClusterGreenhouse::growCluster(Cluster* clusterToAddTo) {
	// If the there were no point which could be added to the cluster, we are given a flag Point2D{-1, -1}.
	return clusterToAddTo->addPointToCluster((int)RandomGenerator.uniDist(0, clusterToAddTo->getNumberBorderPoints()));
}

// If there is no input cluster generation options, then we'll just generate some (only the frequency is used right now)
// generationOptions should be empty
/// <summary>
/// Generates some random options to be used be the clusters during generation (only frequency is useed.
/// </summary>
/// <param name="generationOptions">Empty ClusterGenerationOptions vector .</param>
void ClusterGreenhouse::GenerateRandomOptionsVector(std::vector<ClusterGenerationOptions>& generationOptions) {
	int numberOfClustersToMake = (int)RandomGenerator.uniDist(5, 10);

	// decide the frequency of this cluster based on how much of 0 through 1 (non-descrete) is left
	double availablePercent = .15;
	sparcity = 1 - availablePercent;
	double clusterFrequency = 0;
	for (int i = 0; i < numberOfClustersToMake; i++) {
		if (availablePercent < 0)
			break;

	    clusterFrequency = RandomGenerator.uniDist(1 - availablePercent, 1);
		availablePercent = 1 - clusterFrequency;

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
	// whatever percent is left over will be added to sparcity
	if(availablePercent>0)
		sparcity += availablePercent;
}
