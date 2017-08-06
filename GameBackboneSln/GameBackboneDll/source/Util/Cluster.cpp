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
/// <param name="firstPoint">Point which will be the origin of the cluster</param>
Cluster::Cluster(Point2D<int> firstPoint) {
    clusterPointSet.insert(firstPoint);
    UpdateBorder(firstPoint);
}

//getter

/// <summary>
/// Returns the points contained by this clusters.
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
/// <param name="newPoint">A point which is to be added to this cluster</param>
void Cluster::addPointToCluster(Point2D<int> newPoint) {
	clusterPointSet.insert(newPoint);
	UpdateBorder(newPoint);
}

/// <summary>
/// When a point is added to the border, this is called to add the new points to the border (and remove the old point).
/// </summary>
/// <param name="newPoint">The point which is to be added to the cluster, from the border.</param>
void Cluster::UpdateBorder(Point2D<int> newPoint) {
    borderPointSet.insert(Point2D<int>{newPoint.x, newPoint.y + 1});
    borderPointSet.insert(Point2D<int>{newPoint.x + 1, newPoint.y});
    borderPointSet.insert(Point2D<int>{newPoint.x, newPoint.y - 1});
    borderPointSet.insert(Point2D<int>{newPoint.x - 1, newPoint.y});
    borderPointSet.erase(newPoint);
}

/// <summary>
/// Gets the number of points in the cluster's border.
/// </summary>
/// <returns></returns>
unsigned int Cluster::getNumberBorderPoints() {
	return (unsigned int)borderPointSet.size();
}

/// <summary>
/// Gets the set of points that are in this cluster's border.
/// </summary>
/// <returns>the borderPointSet</returns>
std::set<Point2D<int>> const* const Cluster::getBorderPointSet() {
	return &borderPointSet;
}