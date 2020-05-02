#include <GameBackbone/Core/AnimationSet.h>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <cstddef>
#include <exception>
#include <vector>

using namespace GB;
/// <summary>
/// Construct a new AnimationSet object.
/// The provided animations will all be added to the animation set.
/// </summary>
/// <param name="animations"> The animations to add. </param>
AnimationSet::AnimationSet(std::vector<Animation> animations) {
    this->animations = std::move(animations);
}

/// <summary>
/// Adds the animation to the AnimationSet.
/// </summary>
/// <param name="animation"> The animation to add. </param>
void AnimationSet::addAnimation(Animation animation) {
    animations.emplace_back(std::move(animation));
}

/// <summary>
/// Removes an animation from the AnimationSet.
/// </summary>
/// <param name="animation"> The animation to remove. </param>
void AnimationSet::eraseAnimation(const_iterator animation) {
    animations.erase(animation);
}

/// <summary>
/// Removes a range of animations form the AnimationSet.
/// </summary>
/// <param name="first"> The first animation to erase. </param>
/// <param name="last"> The last animation to erase. </param>
void AnimationSet::eraseAnimations(const_iterator first, const_iterator last) {
    animations.erase(first, last);
}

/// <summary>
/// Remove all animations from the AnimationSet.
/// </summary>
void AnimationSet::clearAnimations() {
    animations.clear();
}

/// <summary>
/// Access the animation at the given index.
/// </summary>
/// <param name="animationIndex"> The index of the animation to return. </param>
/// <return> The animation at the provided index. </return>
const Animation& AnimationSet::operator[](std::size_t animationIndex) const noexcept {
    return animations[animationIndex];
}

/// <summary>
/// Access the animation at the given index.
/// Throws out_of_range exception if the provided index is greater than the
/// number of animations stored by the AnimationSet.
/// </summary>
/// <param name="animationIndex"> The index of the animation to return. </param>
/// <return> The animation at the provided index. </return>
const Animation& AnimationSet::at(std::size_t animationIndex) const {
    return animations.at(animationIndex);
}

/// <summary>
/// Returns the number of Animations stored by the AnimationSet.
/// </summary>
std::size_t AnimationSet::getSize() const {
    return animations.size();
}

/// <summary>
/// Returns true if the AnimationSet holds no animations. Returns false otherwise.
/// </summary>
bool AnimationSet::isEmpty() const {
    return animations.empty();
}

/// <summary>
/// Iterator to the beginning of the AnimationSet.
/// </summary>
AnimationSet::iterator AnimationSet::begin() {
    return animations.begin();
}

/// <summary>
/// Const iterator to the beginning of the AnimationSet.
/// </summary>
AnimationSet::const_iterator AnimationSet::begin() const noexcept{
    return animations.begin();
}

/// <summary>
/// Const iterator to the beginning of the AnimationSet.
/// </summary>
AnimationSet::const_iterator AnimationSet::cbegin() const noexcept{
    return animations.cbegin();
}

/// <summary>
/// Iterator to the end of the AnimationSet.
/// </summary>
AnimationSet::iterator AnimationSet::end() {
    return animations.end();
}

/// <summary>
/// Const iterator to the end of the AnimationSet.
/// </summary>
AnimationSet::const_iterator AnimationSet::end() const noexcept{
    return animations.end();
}

/// <summary>
/// Const iterator to the end of the AnimationSet.
/// </summary>
AnimationSet::const_iterator AnimationSet::cend() const noexcept{
    return animations.cend();
}

/// <summary>
/// Reverse iterator to the beginning of the AnimationSet.
/// </summary>
AnimationSet::reverse_iterator AnimationSet::rbegin(){
    return animations.rbegin();
}

/// <summary>
/// Reverse const iterator to the beginning of the AnimationSet.
/// </summary>
AnimationSet::const_reverse_iterator AnimationSet::rbegin() const noexcept{
    return animations.rbegin();
}

/// <summary>
/// Reverse const iterator to the beginning of the AnimationSet.
/// </summary>
AnimationSet::const_reverse_iterator AnimationSet::crbegin() const noexcept{
    return animations.crbegin();
}

/// <summary>
/// Reverse iterator to the end of the AnimationSet.
/// </summary>
AnimationSet::reverse_iterator AnimationSet::rend(){
    return animations.rend();
}

/// <summary>
/// Reverse const iterator to the end of the AnimationSet.
/// </summary>
AnimationSet::const_reverse_iterator AnimationSet::rend() const noexcept{
    return animations.rend();
}

/// <summary>
/// Reverse const iterator to the end of the AnimationSet.
/// </summary>
AnimationSet::const_reverse_iterator AnimationSet::crend() const noexcept{
    return animations.crend();
}