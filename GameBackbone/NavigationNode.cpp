#include "NavigationNode.h"



NavigationNode::NavigationNode() {
}

///<summary>Construct the rectangle from its coordinates.</summary>
///<param name = "rectLeft"> left most position of the rectangle </param>
///<param name = "rectTop"> top most position of the rectangle </param>
///<param name = "rectWidth"> width of the rectangle </param>
///<param name = "rectHeight"> height of the rectangle </param>
NavigationNode::NavigationNode(float rectLeft, float rectTop, float rectWidth, float rectHeight) : sf::FloatRect(rectLeft, rectTop, rectWidth, rectHeight) {
}

///<summary>Construct the rectangle from position and size</summary>
NavigationNode::NavigationNode(const sf::Vector2f & position, const sf::Vector2f & size) : sf::FloatRect(position, size) {
}

NavigationNode::NavigationNode(const sf::FloatRect & other) : sf::FloatRect(other) {
}


NavigationNode::~NavigationNode() {
}
