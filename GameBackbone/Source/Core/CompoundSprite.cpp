#include <GameBackbone/Core/CompoundSprite.h>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <algorithm>
#include <cstddef>
#include <map>
#include <set>
#include <stdexcept>
#include <vector>

using namespace GB;

CompoundSprite::CompoundSprite(sf::Vector2f position){
	setPosition(position);
}

CompoundSprite::CompoundSprite(const CompoundSprite& other) : CompoundSprite()
{
	this->setPosition(other.getPosition());
	this->setRotation(other.getRotation());
	this->setScale(other.getScale());
	this->setOrigin(other.getOrigin());

	for (auto& priorityComponent : other.m_prioritizedComponents)
	{
		this->m_prioritizedComponents.emplace(
			priorityComponent.first, 
			priorityComponent.second->cloneAsUnique()
		);
	}
}

CompoundSprite& CompoundSprite::operator=(const CompoundSprite& other)
{
	CompoundSprite tempOther{ other };
	*this = std::move(tempOther);
	return *this;
}

CompoundSprite::CompoundSprite(CompoundSprite&& other) noexcept
	: Transformable(other), m_prioritizedComponents(std::move(other.m_prioritizedComponents))
{}

CompoundSprite& CompoundSprite::operator=(CompoundSprite&& other) noexcept
{
	// Move the CompoundSprite members from the other
	this->m_prioritizedComponents = std::move(other.m_prioritizedComponents);

	// Copy the Transformable members from the other, since it cannot be moved.
	this->Transformable::setPosition(other.getPosition());
	this->Transformable::setRotation(other.getRotation());
	this->Transformable::setScale(other.getScale());
	this->Transformable::setOrigin(other.getOrigin());

	return *this;
}

std::size_t CompoundSprite::getComponentCount() const {
	return m_prioritizedComponents.size();
}

std::size_t CompoundSprite::getComponentCount(int priority) const {
	return m_prioritizedComponents.count(priority);
}

std::vector<CompoundSprite::ComponentWrapper*> CompoundSprite::getComponentsWithPriorty(int priority) {
	std::vector<ComponentWrapper*> components;
	for (iterator iter = m_prioritizedComponents.begin(); iter != m_prioritizedComponents.end(); ++iter)
	{
		if (iter->first == priority)
		{
			components.push_back(iter->second.get());
		}
	}
	return components;
}

std::vector<int> CompoundSprite::getComponentPriorties()
{
	std::vector<int> priorities;
	for (iterator iter = m_prioritizedComponents.begin(); iter != m_prioritizedComponents.end(); ++iter)
	{
		priorities.push_back(iter->first);
	}
	return priorities;
}

bool CompoundSprite::isEmpty() const {
	return m_prioritizedComponents.empty();
}

void CompoundSprite::clearComponents() {
	m_prioritizedComponents.clear();
}


void CompoundSprite::setPosition(float x, float y) {
	const sf::Vector2f& oldPosition = sf::Transformable::getPosition();
	move(x - oldPosition.x, y - oldPosition.y);
}


void CompoundSprite::setPosition(const sf::Vector2f& position) {
	setPosition(position.x, position.y);
}

void CompoundSprite::setRotation(float angle) {
	// Lambda for rotating components
	auto setRotationFunction = [angle](auto& componentPair) {
		componentPair.second->setRotation(angle);
	};

	// Apply the rotateFunction to all components
	std::for_each(std::begin(m_prioritizedComponents), std::end(m_prioritizedComponents), setRotationFunction);

	// Update the position of the CompoundSprite as a whole
	sf::Transformable::setRotation(angle);
}

void CompoundSprite::setScale(float factorX, float factorY) {
	// Lambda function for scaling components
	auto setScaleFunction = [factorX, factorY](auto& componentPair) {
		componentPair.second->setScale(factorX, factorY);
	};

	// Apply the setScaleFunction to all components
	std::for_each(std::begin(m_prioritizedComponents), std::end(m_prioritizedComponents), setScaleFunction);

	// Update the position of the CompoundSprite as a whole
	sf::Transformable::setScale(factorX, factorY);
}

void CompoundSprite::setScale(const sf::Vector2f& factors) {
	setScale(factors.x, factors.y);
}

void CompoundSprite::setOrigin(float x, float y) {
	// function to update the origin of a component
	auto setOriginFunction = [x, y, this](auto& componentPair) {

		/*
		 * Move the origin of the component relative to how the origin of the full CompoundSprite is moving.
		 * This preserves the positioning established when components were first added to the CompoundSprite
		 */
		componentPair.second->setOrigin(componentPair.second->getOrigin().x + (x - getOrigin().x), componentPair.second->getOrigin().y + (y - getOrigin().y));
	};

	// update the origin of all components
	std::for_each(std::begin(m_prioritizedComponents), std::end(m_prioritizedComponents), setOriginFunction);

	// Update the origin of the CompoundSprite as a whole
	sf::Transformable::setOrigin(x, y);
}

void CompoundSprite::setOrigin(const sf::Vector2f& origin) {
	setOrigin(origin.x, origin.y);
}

void CompoundSprite::move(float offsetX, float offsetY) {
	// function for moving a component
	auto moveFunction = [offsetX, offsetY](auto& componentPair) {
		componentPair.second->move(offsetX, offsetY);
	};

	// apply the rotateFunction to all components
	std::for_each(std::begin(m_prioritizedComponents), std::end(m_prioritizedComponents), moveFunction);

	// update the position of the CompoundSprite as a whole
	sf::Transformable::move(offsetX, offsetY);
}

void CompoundSprite::move(const sf::Vector2f& offset) {
	move(offset.x, offset.y);
}

void CompoundSprite::rotate(float angle) {
	// Lambda for rotating components
	auto rotateFunction = [angle](auto& componentPair) {
		componentPair.second->rotate(angle);
	};

	// Apply the rotateFunction to all components
	std::for_each(std::begin(m_prioritizedComponents), std::end(m_prioritizedComponents), rotateFunction);

	// Update the position of the CompoundSprite as a whole
	sf::Transformable::rotate(angle);
}

void CompoundSprite::scale(float factorX, float factorY) {
	// Lambda function for scaling components
	auto scaleFunction = [factorX, factorY](auto& componentPair) {
		componentPair.second->scale(factorX, factorY);
	};

	// Apply the scaleFunction to all components
	std::for_each(std::begin(m_prioritizedComponents), std::end(m_prioritizedComponents), scaleFunction);

	// Update the position of the CompoundSprite as a whole
	sf::Transformable::scale(factorX, factorY);
}

void CompoundSprite::scale(const sf::Vector2f& factor) {
	scale(factor.x, factor.y);
}

void CompoundSprite::update(sf::Int64 elapsedTime) {
	// Forward the update to each component
	for (auto& componentPair : m_prioritizedComponents) {
		componentPair.second->update(elapsedTime);
	}
}

void CompoundSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// lambda function to draw a component
	auto drawFunction = [&target, &states](auto& componentPair) {
		target.draw(componentPair.second->getDataAsDrawable(), states);
	};

	// apply drawFunction to all components
	std::for_each(std::begin(m_prioritizedComponents), std::end(m_prioritizedComponents), drawFunction);
}

