#pragma once

// Don't define PlatformDemo if the user doesn't want it
#ifdef GAMEBACKBONE_BUILD_PLATFORM_DEMO

#include <GameBackboneDemo/DemoRegion.h>

#include <GameBackbone/Util/Point.h>

#include <SFML/Graphics.hpp>

#include <Box2D/Box2D.h>

#include <memory>

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
		void behave(sf::Time currentTime) override;

		// Handle sf::Events
		void handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button) override;
		void handleKeyPress(sf::Event::KeyEvent key) override;
		void handleKeyRelease(sf::Event::KeyEvent key) override;


	protected:
		// Initialization and Cleanup
		void init();
		void initGUI();
		void destroy();
		void reset() override;

		// Helper functions
		b2Vec2 convertToBox(sf::Vector2f sfCoords);
		sf::Vector2f convertToSprite(b2Vec2 boxCoord);
		sf::Vector2f convertToSprite(double boxCoordX, double boxCoordY);
		void addGameBody(sf::Vector2f spritePosition, sf::Vector2f scale, sf::Texture& texture, bool dynamicBody, bool allowSleep = true);

		// Update logic storage
		sf::Time lastUpdateTime;

		// Sprite textures
		std::unique_ptr<sf::Texture> blockTexture;

		// Box2d world which will be used to perform physical operations
		std::unique_ptr<b2World> platformWorld;
		// Visual Representation of Box2d Bodies
		std::vector<std::unique_ptr<sf::Sprite>> objectSprites;

		// Box2D Bodies for access
		// Box2D owns this memory
		std::vector<b2Body*> objectBodies;

		// Stored player body for access
		b2Body* playerBody;
	};
}

#endif // GAMEBACKBONE_BUILD_PLATFORM_DEMO