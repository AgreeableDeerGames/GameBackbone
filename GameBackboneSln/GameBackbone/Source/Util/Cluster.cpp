#include <GameBackbone/Util/Array2D.h>
#include <GameBackbone/Util/Cluster.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include <set>
#include <tuple>
#include <map>

using namespace GB;

/// <summary>
/// Constructor
/// </summary>
/// <param name="firstPoint">Point which will be the origin of the cluster</param>
Cluster::Cluster(sf::Vector2i firstPoint) {
	clusterFrequency = 0;
    clusterPointSet.insert(firstPoint);
    UpdateBorder(firstPoint);
}

//getter

/// <summary>
/// Returns the points contained by this clusters.
/// </summary>
/// <returns></returns>
std::set<sf::Vector2i, IsVector2Less<int>> const* const Cluster::getClusterPoints() {
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
void Cluster::addPointToCluster(sf::Vector2i newPoint) {
	clusterPointSet.insert(newPoint);
	UpdateBorder(newPoint);
}

/// <summary>
/// When a point is added to the border, this is called to add the new points to the border (and remove the old point).
/// </summary>
/// <param name="newPoint">The point which is to be added to the cluster, from the border.</param>
void Cluster::UpdateBorder(sf::Vector2i newPoint) {
    borderPointSet.insert(sf::Vector2i{newPoint.x, newPoint.y + 1});
    borderPointSet.insert(sf::Vector2i{newPoint.x + 1, newPoint.y});
    borderPointSet.insert(sf::Vector2i{newPoint.x, newPoint.y - 1});
    borderPointSet.insert(sf::Vector2i{newPoint.x - 1, newPoint.y});
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
std::set<sf::Vector2i, IsVector2Less<int>> const* const Cluster::getBorderPointSet() {
	return &borderPointSet;
}