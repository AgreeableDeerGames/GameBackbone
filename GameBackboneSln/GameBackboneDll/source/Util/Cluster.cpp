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
Cluster::Cluster(Point2D<int> firstPoint) {
    clusterPointSet.insert(firstPoint);
    UpdateBorder(firstPoint);
}

//getter

/// <summary>
/// Returns the coordinates contained by this clusters.
/// </summary>
/// <returns></returns>
std::set<Point2D<int>> const* const Cluster::getClusterPoints() {
    return &clusterPointSet;
}


double Cluster::getClusterFrequency() {
    return clusterFrequency;
}

//setter
void Cluster::setClusterFrequency(double FrequencyForCluster) {
    clusterFrequency = FrequencyForCluster;
}

/// <summary>
/// Adds a given point to the cluster.
/// </summary>
/// <param name="newPointToAdd">A point which is to be added to this cluster</param>
void Cluster::addPointToCluster(Point2D<int> newPointToAdd) {
	clusterPointSet.insert(newPointToAdd);
	UpdateBorder(newPointToAdd);
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
}

/// <summary>
/// Gets the number of coordinates bordering this cluster.
/// </summary>
/// <returns></returns>
unsigned int Cluster::getNumberBorderPoints() {
	return (unsigned int)borderPointSet.size();
}

/// <summary>
/// Gets the set of coordinates that are bordering this cluster.
/// </summary>
/// <returns></returns>
std::set<Point2D<int>> const* const Cluster::getBorderPointSet() {
	return &borderPointSet;
}