#pragma once

#include <GameBackbone/Util/DllUtil.h>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <cstddef>
#include <memory>
#include <vector>

namespace GB {

    /// <summary>Collection of texture subsections</summary>
    using Animation = std::vector<sf::IntRect>;

    /// <summary> Creates and owns a collection of animations.</summary>
    class libGameBackbone AnimationSet {
    private:
        using InternalContainer = std::vector<Animation>;

    public:
        // Iterator types
        using iterator = InternalContainer::iterator;
        using const_iterator = InternalContainer::const_iterator;
        using reverse_iterator = InternalContainer::reverse_iterator;
        using const_reverse_iterator = InternalContainer::const_reverse_iterator;

        // Pointer type
        /// <summary>shared_ptr to AnimationSet.</summary>
        using Ptr = std::shared_ptr<AnimationSet>;

        // ctrs / dtr
        AnimationSet() = default;
        AnimationSet(std::vector<Animation> animations);
        AnimationSet(const AnimationSet&) = default;
        AnimationSet(AnimationSet&&) = default;
        AnimationSet& operator=(const AnimationSet&) = default;
        AnimationSet& operator=(AnimationSet&&) = default;
        virtual ~AnimationSet() = default;

        // add / remove
        void addAnimation(Animation animation);
        void eraseAnimation(const_iterator animation);
        void eraseAnimations(const_iterator first, const_iterator last);
        void clearAnimations();

        // accessor / mutator
        const Animation& operator[](std::size_t animationIndex) const noexcept;
        const Animation& at(std::size_t animationIndex) const;
        std::size_t getSize() const;
        bool isEmpty() const;

        // Iterator functions
        iterator begin();
        const_iterator begin() const noexcept;
        const_iterator cbegin() const noexcept;
        iterator end();
        const_iterator end() const noexcept;
        const_iterator cend() const noexcept;
        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const noexcept;
        const_reverse_iterator crbegin() const noexcept;
        reverse_iterator rend();
        const_reverse_iterator rend() const noexcept;
        const_reverse_iterator crend() const noexcept;

    private:
        InternalContainer animations;
    };
}
