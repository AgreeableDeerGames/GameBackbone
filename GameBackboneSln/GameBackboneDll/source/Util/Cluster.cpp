#include <Util\Array2D.h>
#include <Util\Cluster.h>
#include <Util\Point.h>

#include <SFML\Graphics\Sprite.hpp>

#include <set>
#include <tuple>
#include <map>

using namespace GB;

/// <summary>
/// Constructor 
/// </summary>
/// <param name="pointToClusterMap">The map of all of the points in the graph to their clusters.</param>
Cluster::Cluster(Point2D<int> firstPoint, Point2D<int> dimensions, std::multimap<Point2D<int>, Cluster>& pointToClusterMap) {
    this->pointToClusterMap = &pointToClusterMap;
    dimensionsOfGrid = dimensions;
    clusterPointSet.insert(firstPoint);
    UpdateBorder(firstPoint);
    //this->pointToClusterMap->insert(std::make_pair(firstPoint, *this));
}

//getter
std::set<Point2D<int>>* Cluster::getClusterPoints() {
    return &clusterPointSet;
}

ClusterGenerationOptions* Cluster::getClusterGenerationOptions() {
    return &clusterOptions;
}

//setter
void Cluster::setClusterGenerationOptions(ClusterGenerationOptions* OptionsForThisCluster) {
    clusterOptions = *OptionsForThisCluster;
}

/// <summary>
/// Adds a random point to the cluster.
/// </summary>
/// <param name="randomNumber">A random number, which will be used to determine which point in the border will be added to the cluster.</param>
/// <returns>The point which was added.</returns>
Point2D<int> Cluster::addPointToCluster(int randomNumber) {
    moveIterator(randomNumber);

    for (int i = 0; i < borderPointSet.size(); i++) {
        // If the point is not already in a different cluster and also not on the edge
        // of the graph, we're good
        if (pointToClusterMap->find(*borderPointSetIter) == pointToClusterMap->end() &&
            dimensionsOfGrid.x > borderPointSetIter->x && dimensionsOfGrid.y > borderPointSetIter->y &&
			0 <= borderPointSetIter->x && 0 <= borderPointSetIter->y) {
			Point2D<int> pointToAdd = *borderPointSetIter;
            clusterPointSet.insert(pointToAdd);
            UpdateBorder(pointToAdd);
            pointToClusterMap->insert(std::make_pair(pointToAdd, *this));
			return pointToAdd;
        }
        // Otherwise, check the next point in the set
        else {
            borderPointSetIter++;
            if (borderPointSetIter == borderPointSet.end()) {
                borderPointSetIter = borderPointSet.begin();
            }
        }
    }
	// There were not points to add
	return Point2D<int>{-1, -1};
}        

/// <summary>
/// This moves the border's iterator some number, maintaining the circular property of the border.
/// </summary>
/// <param name="numberToMove">The number of times the iterator will move.</param>
// This moves the border's iterator some number, maintaining the circular border
void Cluster::moveIterator(int numberToMove) {
    if (numberToMove >= 0) {
        borderPointSetIter = borderPointSet.begin();
        std::advance(borderPointSetIter, numberToMove);
    }
    else {
        borderPointSetIter = borderPointSet.end();
        std::advance(borderPointSetIter, numberToMove - 1);
    }
}

/// <summary>
/// When a point is added to the border, this is called to add the new points to the border (and remove the old point).
/// </summary>
/// <param name="pointToAdd">The point which is to be added to the cluster, from the border.</param>
void Cluster::UpdateBorder(Point2D<int> pointToAdd) {
    borderPointSet.insert(Point2D<int>{pointToAdd.x, pointToAdd.y + 1});
    borderPointSet.insert(Point2D<int>{pointToAdd.x + 1, pointToAdd.y});
    borderPointSet.insert(Point2D<int>{pointToAdd.x, pointToAdd.y - 1});
    borderPointSet.insert(Point2D<int>{pointToAdd.x - 1, pointToAdd.y});
    borderPointSet.erase(pointToAdd);
    borderPointSetIter = borderPointSet.begin();
}

int Cluster::getNumberBorderPoints() {
	return (int)borderPointSet.size();
}