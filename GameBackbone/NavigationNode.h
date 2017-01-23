#pragma once

#include <SFML/Graphics/Rect.hpp>


#include <vector>



class NavigationNode : public sf::FloatRect {
public:

	//ctr / dtr
	NavigationNode();
	NavigationNode(float rectLeft, float rectTop, float rectWidth, float rectHeight);
	NavigationNode(const sf::Vector2f &position, const sf::Vector2f &size);
	NavigationNode(const sf::FloatRect& other);
	virtual ~NavigationNode();


	//getters
	NavigationNode* getParentNode();
	std::vector<NavigationNode*>* getChildNodes();

	//operations
	void addChildNode(NavigationNode* child);
	void setParentNode(NavigationNode* parent);
	void scale(double scaleFactor);
	


private:
	std::vector<NavigationNode*>* childNodes;
	NavigationNode* parentNode

};

