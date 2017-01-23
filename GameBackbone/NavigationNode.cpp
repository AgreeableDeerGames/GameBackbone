#include "NavigationNode.h"


//Ctr / dtr
NavigationNode::NavigationNode() : NavigationNode(0, 0) {
}

///<summary> creates a navigation node at the specified location.</summary>
///<param name = "x"> the x location of the new navigation node </param>
///<param name = "y"> the y location of the new navigation node </param>
NavigationNode::NavigationNode(double x, double y) {
	this->x = x;
	this->y = y;

	childNodes = new std::vector<NavigationNode*>();
}

///<summary> deletes pointers for this navigation node only. Does not free memory of related navigation nodes</summary>
NavigationNode::~NavigationNode() {
	delete childNodes;
	childNodes = nullptr;
	parentNode = nullptr;
}

//getters / setters

	//setters

///<summary> sets the position of the node on the x axis </summary>
///<param name = "x"> the new position of the node on the x axis </param>
void NavigationNode::setX(double x) {
	this->x = x;
}

///<summary> sets the position of the node on the y axis </summary>
///<param name = "y"> the new position of the node on the y axis </param>
void NavigationNode::setY(double y) {
	this->y = y;
}


///<summary> Tags the node as blocked </summary>
///<param name = "blocked"> the new blocked status of the node </param>
void NavigationNode::setBlocked(bool blocked) {
	this->blocked = blocked;
}

	//getters

///<summary> returns the position of the navigation node on the x axis </summary>
double NavigationNode::getX() {
	return x;
}

///<summary> returns the position of the navigation node on the y axis </summary>
double NavigationNode::getY() {
	return y;
}


///<summary> returns the blocked status of the node </summary>
bool NavigationNode::isBlocked() {
	return false;
}

///<summary>returns the parent of this navigation node </summary>
NavigationNode * NavigationNode::getParentNode() {
	return parentNode;
}

///<summary> returns the vector of child nodes for this navigation node </summary>
std::vector<NavigationNode*>* NavigationNode::getChildNodes() {
	return childNodes;
}

//operations

///<summary> adds a child node to this navigation node. Sets this navigation node as parent to the child node </summary>
///<param name = "child"> new child of this navigation node </param>
void NavigationNode::addChildNode(NavigationNode * child) {
	childNodes->push_back(child);
	child->parentNode = this;
}

///<summary> sets the parent node of this navigation node. Adds this node as a child of the new parent node. </summary>
///<param name = "parent"> the new parent of this navigation node </param>
void NavigationNode::setParentNode(NavigationNode * parent) {
	parent->childNodes->push_back(this);
	this->parentNode = parent;
}


