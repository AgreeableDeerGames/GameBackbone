#include <GameBackbone/Core/AnimationSet.h>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <cstddef>
#include <exception>
#include <vector>

using namespace GB;

AnimationSet::AnimationSet(std::vector<Animation> animations) {
    this->animations = std::move(animations);
}

void AnimationSet::addAnimation(Animation animation) {
    animations.emplace_back(std::move(animation));
}

void AnimationSet::eraseAnimation(const_iterator animation) {
    animations.erase(animation);
}

void AnimationSet::eraseAnimations(const_iterator first, const_iterator last) {
    animations.erase(first, last);
}

void AnimationSet::clearAnimations() {
    animations.clear();
}

const Animation& AnimationSet::operator[](std::size_t animationIndex) const noexcept {
    return animations[animationIndex];
}

const Animation& AnimationSet::at(std::size_t animationIndex) const {
    return animations.at(animationIndex);
}

std::size_t AnimationSet::getSize() const {
    return animations.size();
}

bool AnimationSet::isEmpty() const {
    return animations.empty();
}

AnimationSet::iterator AnimationSet::begin() {
    return animations.begin();
}

AnimationSet::const_iterator AnimationSet::begin() const noexcept{
    return animations.begin();
}

AnimationSet::const_iterator AnimationSet::cbegin() const noexcept{
    return animations.cbegin();
}

AnimationSet::iterator AnimationSet::end() {
    return animations.end();
}

AnimationSet::const_iterator AnimationSet::end() const noexcept{
    return animations.end();
}

AnimationSet::const_iterator AnimationSet::cend() const noexcept{
    return animations.cend();
}

AnimationSet::reverse_iterator AnimationSet::rbegin(){
    return animations.rbegin();
}

AnimationSet::const_reverse_iterator AnimationSet::rbegin() const noexcept{
    return animations.rbegin();
}

AnimationSet::const_reverse_iterator AnimationSet::crbegin() const noexcept{
    return animations.crbegin();
}

AnimationSet::reverse_iterator AnimationSet::rend(){
    return animations.rend();
}

AnimationSet::const_reverse_iterator AnimationSet::rend() const noexcept{
    return animations.rend();
}

AnimationSet::const_reverse_iterator AnimationSet::crend() const noexcept{
    return animations.crend();
}