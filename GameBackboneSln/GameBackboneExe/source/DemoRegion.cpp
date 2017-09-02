#include <DemoRegion.h>

using namespace EXE;


DemoRegion::DemoRegion(sf::RenderWindow & window) : GameRegion(window){}

void DemoRegion::handleMouseMove(sf::Vector2f mousePosition) {}

void DemoRegion::handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button){}

void DemoRegion::handleWheelScroll(float scrollDelta){}