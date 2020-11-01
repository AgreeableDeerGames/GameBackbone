#pragma once

#include <GameBackbone/Util/DllUtil.h>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <cstddef>
#include <memory>
#include <vector>

namespace GB {

    /// @brief Collection of texture subsections
    using Animation = std::vector<sf::IntRect>;

    /// @brief Creates and owns a collection of animations.
    class libGameBackbone AnimationSet {
    private:
        using InternalContainer = std::vector<Animation>;

    public:
        // Iterator types
        using iterator = InternalContainer::iterator;
        using const_iterator = InternalContainer::const_iterator;
        using reverse_iterator = InternalContainer::reverse_iterator;
        using const_reverse_iterator = InternalContainer::const_reverse_iterator;

        /// @brief shared_ptr to AnimationSet.
        using Ptr = std::shared_ptr<AnimationSet>;

        /// @brief Construct an empty AnimationSet
        AnimationSet() = default;

        /// @brief Construct a new AnimationSet object.
        ///     The provided animations will all be added to the animation set.
        /// @param animations The animations to add.
        AnimationSet(std::vector<Animation> animations);

        /// @brief Copy construct an AnimationSet
        /// @param  The AnimationSet to copy
        AnimationSet(const AnimationSet&) = default;

        /// @brief Move construct an AnimationSet
        /// @param  The AnimationSet to move
        AnimationSet(AnimationSet&&) = default;

        /// @brief Copy assign an AnimationSet
        /// @param  The AnimationSet to copy
        /// @return This
        AnimationSet& operator=(const AnimationSet&) = default;

        /// @brief Move assign an AnimationSet
        /// @param  The AnimationSet to move
        /// @return this
        AnimationSet& operator=(AnimationSet&&) = default;

        /// @brief Destroy the AnimationSet
        virtual ~AnimationSet() = default;

        /// @brief Adds the animation to the AnimationSet.
        /// @param animation The animation to add.
        void addAnimation(Animation animation);

        /// @brief Removes an animation from the AnimationSet.
        /// @param animation The animation to remove.
        void eraseAnimation(const_iterator animation);

        /// @brief Removes a range of animations form the AnimationSet.
        /// @param first The first animation to erase.
        /// @param last The last animation to erase.
        void eraseAnimations(const_iterator first, const_iterator last);

        /// @brief Remove all animations from the AnimationSet.
        void clearAnimations();

        /// @brief Access the animation at the given index.
        /// @param animationIndex The index of the animation to return.
        /// @return The animation at the provided index.
        /// @note Does no runtime safety checks
        const Animation& operator[](std::size_t animationIndex) const noexcept;

        /// @brief Access the animation at the given index.
        /// @param animationIndex The index of the animation to return. 
        /// @return The animation at the provided index. 
        /// @throws Throws out_of_range exception if the provided index is greater than the
        ///     number of animations stored by the AnimationSet.
        const Animation& at(std::size_t animationIndex) const;

        /// @brief Returns the number of Animations stored by the AnimationSet.
        std::size_t getSize() const;

        /// @brief Returns true if the AnimationSet holds no animations. Returns false otherwise.
        bool isEmpty() const;

        /// @brief Iterator to the beginning of the AnimationSet.
        iterator begin();

        /// @brief Const iterator to the beginning of the AnimationSet.
        const_iterator begin() const noexcept;

        /// @brief Const iterator to the beginning of the AnimationSet.
        const_iterator cbegin() const noexcept;

        /// @brief Iterator to the end of the AnimationSet.
        iterator end();

        /// @brief Const iterator to the end of the AnimationSet.
        const_iterator end() const noexcept;

        /// @brief Const iterator to the end of the AnimationSet.
        const_iterator cend() const noexcept;

        /// @brief Reverse iterator to the beginning of the AnimationSet.
        reverse_iterator rbegin();

        /// @brief Reverse const iterator to the beginning of the AnimationSet.
        const_reverse_iterator rbegin() const noexcept;

        /// @brief Reverse const iterator to the beginning of the AnimationSet.
        const_reverse_iterator crbegin() const noexcept;

        /// @brief Reverse iterator to the end of the AnimationSet.
        reverse_iterator rend();

        /// @brief Reverse const iterator to the end of the AnimationSet.
        const_reverse_iterator rend() const noexcept;

        /// @brief Reverse const iterator to the end of the AnimationSet.
        const_reverse_iterator crend() const noexcept;

    private:
        InternalContainer animations;
    };
}
