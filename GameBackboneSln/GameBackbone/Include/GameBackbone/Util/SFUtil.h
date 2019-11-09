#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace GB {

	/// <summary>
	/// Used to compare which of two sf::Vector2 is less
	/// Designed to facilitate map and set use of sf::Vector2
	/// </summary>
	template <typename T>
	class IsVector2Less {
	public:
		constexpr bool operator()(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs) const {
			return lhs.x < rhs.x || (!(rhs.x < lhs.x) && lhs.y < rhs.y);
		}
	};

	/// <summary>
	/// Used to create new Drawable* vectors using Drawable child pointer vectors
	/// Designed to improve compatibility between vectors of Drawable and Drawable children
	/// </summary>
	//template <class T>
	//std::vector<sf::Drawable*> toDrawableVector(const std::vector<T>& DrawableChild)
	//{
	//	/*std::vector<sf::Drawable*> DrawableVector(DrawableChild.size());
	//	for (auto di = 0; di < DrawableChild.size(); di++)
	//	{
	//		DrawableVector.at(di) = DrawableChild.at(di);
	//	}
	//	return DrawableVector;*/
	//	
	//	std::vector<sf::Drawable*> drawableVector(DrawableChild.begin(), DrawableChild.end());
	//	return drawableVector;
	//}

	/// <summary>
	/// Used to create new Drawable* vectors using Drawable child vectors
	/// Designed to improve compatibility between vectors of Drawable and Drawable children
	/// </summary>
	template <class T>
	std::vector<sf::Drawable*> toDrawableVector(const std::vector<T>& drawableChildren)
	{
		std::vector<sf::Drawable*> drawableVector(drawableChildren.size());
		auto getPointer = [](const T& drawableChild){ return const_cast<sf::Sprite*>(&drawableChild);  };
		std::transform(drawableChildren.begin(), drawableChildren.end(), drawableVector.begin(), getPointer);
		/*for (auto di = 0; di < DrawableChild.size(); di++)
		{
			DrawableVector.at(di) = const_cast<sf::Drawable*>(&DrawableChild.at(di));
		}*/
		return drawableVector;
	}
}
