#include <iostream>
#include <GameBackbone/Core/GameRegion.h>

int main(int, char**) {
    std::cout << "Hello, world!\n";

    GB::GameRegion region;
    region.behave(sf::Time::Zero);
}
