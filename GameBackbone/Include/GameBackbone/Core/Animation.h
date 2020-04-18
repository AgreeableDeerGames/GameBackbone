#pragma once

#include <GameBackbone/Util/DllUtil.h>

#include <SFML/Graphics/Rect.hpp>

#include <vector>

namespace GB {

    class libGameBackbone Animation {
    public:
        Animation() = default;
        Animation(std::vector<sf::IntRect> frames);

        void setFrames(std::vector<sf::IntRect> frames);
        const std::vector<sf::IntRect>& getFrames() const;

    private:
        std::vector<sf::IntRect> frames;
    };
}