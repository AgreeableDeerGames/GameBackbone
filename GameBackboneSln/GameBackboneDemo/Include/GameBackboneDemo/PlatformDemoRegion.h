#pragma once

#include <GameBackboneDemo/DemoRegion.h>

#include <GameBackbone/Util/Point.h>

#include <SFML/Graphics.hpp>

#include <Box2D/Box2D.h>

namespace EXE {
	/// <summary>
	/// GameRegion with logic for demonstrating basic platforming using Box2d for physics and SFML to represent it.
	/// </summary>
	/// <seealso cref="GameRegion" />
	class PlatformDemoRegion : public DemoRegion {
	public:
		// Constructors
		PlatformDemoRegion(sf::RenderWindow & window);
		virtual ~PlatformDemoRegion();

		PlatformDemoRegion() = delete;
		PlatformDemoRegion(const PlatformDemoRegion& other) = delete;
		PlatformDemoRegion(PlatformDemoRegion&& other) = delete;
		PlatformDemoRegion& operator= (const PlatformDemoRegion& other) = delete;
		PlatformDemoRegion& operator= (PlatformDemoRegion&& other) = delete;

		// Behavior
		virtual void behave(sf::Time currentTime) override;

		// Handle sf::Events
		virtual void handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button) override;
		virtual void handleKeyPress(sf::Event::KeyEvent key) override;
		virtual void handleKeyRelease(sf::Event::KeyEvent key) override;


	protected:
		// Initialization and Cleanup
		void init();
		void initGUI();
		void destroy();
		virtual void reset() override;

		// Helper functions
		b2Vec2 convertToWorld(sf::Vector2f sfCoords);
		sf::Vector2f convertToSprite(b2Vec2 worldCoords);
		sf::Vector2f convertToSprite(double worldCoordX, double worldCoordY);

		// Update logic storage
		sf::Time lastUpdateTime;

		// Sprite textures
		sf::Texture* blockTexture;

		// Box2d world which will be used to perform physical operations
		b2World* platformWorld;
		// Visual Representation of Box2d Bodies
		std::vector<sf::Sprite*> objectSprites;
		// Box2d Bodies for access or delete
		std::vector<b2Body*> objectBodies;

		// Stored player body. 
		// Note: ALSO STORED IN objectBodies!! DO NOT DELETE!
		b2Body* playerBody;
	};
}
