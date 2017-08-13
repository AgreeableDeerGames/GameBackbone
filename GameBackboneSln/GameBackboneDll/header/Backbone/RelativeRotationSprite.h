#pragma once
#include <Backbone\CompoundSprite.h>


namespace GB {

	/// <summary> Controls several sprites and animated sprites as one logical unit. </summary>
	class libGameBackbone RelativeRotationSprite : public virtual CompoundSprite {
	public:

		//ctr / dtr
		//shallow copy and move are fine for this class
		RelativeRotationSprite();
		RelativeRotationSprite(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites);
		RelativeRotationSprite(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites, Point2D<float> position);
		RelativeRotationSprite(const Point2D<float> initialPosition);
		RelativeRotationSprite(const RelativeRotationSprite& other) = default;
		RelativeRotationSprite(RelativeRotationSprite&& other) = default;
		RelativeRotationSprite& operator= (const RelativeRotationSprite& other) = default;
		RelativeRotationSprite& operator= (RelativeRotationSprite&& other) = default;
		virtual ~RelativeRotationSprite();

		//getters
		Point2D<float> getUnscaledOrigin() const;

		//setters
		void setUnscaledOrigin(Point2D<float> val);
		void setUnscaledOrigin(float x, float y);

		//add / remove
		virtual void addSprite(sf::Sprite* component) override;
		virtual void addAnimatedSprite(AnimatedSprite* component) override;

		//operations
		virtual void scale(float factorX, float factorY) override;
		virtual void scale(Point2D<float> newScale) override;
		virtual void setScale(float factorX, float factorY);
		virtual void setScale(Point2D<float> newScale);

		virtual void rotate(float degreeOffset) override;
		virtual void setRotation(float newRotation) override;

		virtual void rotateAnimatedSprites(std::set<size_t> indiciesToRotate, float degreeOffset) override;
		virtual void setRotationAnimatedSprites(std::set<size_t> indicesToRotate, float newRotation) override;

		virtual void rotateSfSprites(std::set<size_t> indicesToRotate, float degreeOffset) override;
		virtual void setRotationSfSprites(std::set<size_t> indicesToRotate, float newRotation) override;

	protected:
		Point2D<float> unscaledOrigin;
	};

}
