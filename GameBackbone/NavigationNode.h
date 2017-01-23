#pragma once

#include <SFML/Graphics/Rect.hpp>


#include <vector>



class NavigationNode {
public:

	//ctr / dtr
	NavigationNode();
	NavigationNode(double x, double y);
	
	virtual ~NavigationNode();

	//getters / setters
		
		//setters
	void setX( double x );
	void setY( double y );
	void setBlocked(bool blocked);

		//getters
	double getX();
	double getY();
	bool isBlocked();
	NavigationNode* getParentNode();
	std::vector<NavigationNode*>* getChildNodes();

	//operations
	void addChildNode(NavigationNode* child);
	void setParentNode(NavigationNode* parent);

	


private:
	//position
	double x;
	double y;

	//status
	bool blocked;

	//tree structure
	std::vector<NavigationNode*>* childNodes;
	NavigationNode* parentNode;

};

