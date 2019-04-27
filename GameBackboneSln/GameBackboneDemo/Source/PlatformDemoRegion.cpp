// Dont declare PlatformDemo functions if the user doesn't want it
#ifdef GAMEBACKBONE_BUILD_PLATFORM_DEMO

#define _USE_MATH_DEFINES

#include <GameBackboneDemo/PlatformDemoRegion.h>

#include <GameBackbone/Util/Point.h>
#include <GameBackbone/Util/UtilMath.h>

#include <TGUI/TGUI.hpp>

#include <SFML/Graphics.hpp>

#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>

#include <string>
#include <math.h>

using namespace EXE;

// Prepare for simulation. Typically we use a time step of 1/60 of a
// second (60Hz) and 10 iterations. This provides a high quality simulation
// in most game scenarios.
const float32 timeStep = 1.0f / 60.0f;
const int32 velocityIterations = 6;
const int32 positionIterations = 2;
// Define the gravity vector.
const b2Vec2 gravity(0.0f, 0.10f);

const double pixelsPerMeter = 32;

/// <summary>
/// Initializes a new instance of the <see cref="PlatformDemoRegion"/> class.
/// </summary>
/// <param name="window">The window that will be attached to this instances GUI.</param>
PlatformDemoRegion::PlatformDemoRegion(sf::RenderWindow & window) : DemoRegion(window) {
	init();

	// Initialize GUI
	try {
		// Load the widgets
		initGUI();
	}
	catch (const tgui::Exception& e) {
		std::cerr << "Failed to load GUI: " << e.what() << std::endl;
	}
}

/// <summary>
/// Finalizes an instance of the <see cref="PlatformDemoRegion"/> class.
/// </summary>
PlatformDemoRegion::~PlatformDemoRegion() {
	destroy();
}

/// <summary>
/// Executes a single cycle of the main logic loop for this region.
/// </summary>
void PlatformDemoRegion::behave(sf::Time currentTime) {
	// Calculate how much time has passed since the previous behave call.
	sf::Uint64 msPassed = currentTime.asMilliseconds() - lastUpdateTime.asMilliseconds();


	// Instruct the world to perform a single step of simulation.
	// It is generally best to keep the time step and iterations fixed.
	platformWorld->Step(msPassed/50.0f, velocityIterations, positionIterations);

	for (int ii = 0; ii < objectBodies.size(); ii++)
	{
		// Create a temporary body for accessing
		b2Body* objectBody = objectBodies[ii];

		// Set the new position of the object onto the corresponding sprite.
		b2Vec2 pos = objectBody->GetPosition();
		objectSprites[ii]->setPosition(convertToSprite(pos));

		// I know this can't be seen at this scale, but lets set the angle just as a demo.
		// I'm not sure if this needs converted. You may want to check that before copying this code.
		float32 angle = objectBody->GetAngle();
		objectSprites[ii]->setRotation(angle * (180.0 / M_PI));
	}

	lastUpdateTime = currentTime;
}

/// <summary>
/// Handles mouse click logic.
/// </summary>
/// <param name="newPosition">The position of the click.</param>
/// <param name="button">The mouse button clicked button.</param>
void PlatformDemoRegion::handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button) {
	b2Vec2 vel = playerBody->GetLinearVelocity();
	vel.y = -0.9;
	playerBody->SetLinearVelocity(vel);

}

/// <summary>
/// Handles the key press.
/// Moves the sprite right or left or jumps
/// </summary>
/// <param name="mousePosition">The key pressed.</param>
void PlatformDemoRegion::handleKeyPress(sf::Event::KeyEvent key){
	if (key.code == sf::Keyboard::A){
		b2Vec2 vel = playerBody->GetLinearVelocity();
		vel.x = -0.4;
		playerBody->SetLinearVelocity(vel);
	}
	else if(key.code == sf::Keyboard::D){
		b2Vec2 vel = playerBody->GetLinearVelocity();
		vel.x = 0.4;
		playerBody->SetLinearVelocity(vel);
	}
	else if (key.code == sf::Keyboard::Space) {
		b2Vec2 vel = playerBody->GetLinearVelocity();
		vel.y = -0.9;
		playerBody->SetLinearVelocity(vel);
	}
}

/// <summary>
/// Handles the key release.
/// Immediately stops the sprite moving right or left or jumping
/// </summary>
/// <param name="mousePosition">The key released.</param>
void PlatformDemoRegion::handleKeyRelease(sf::Event::KeyEvent key){
	if (key.code == sf::Keyboard::A) {
		b2Vec2 vel = playerBody->GetLinearVelocity();
		// Make sure that the sprite is moving left, otherwise we could randomly stop moving right
		if (vel.x < 0)
		{
			vel.x = 0;
			playerBody->SetLinearVelocity(vel);
		}
	}
	else if (key.code == sf::Keyboard::D) {
		b2Vec2 vel = playerBody->GetLinearVelocity();
		if (vel.x > 0)
		{
			// Make sure that the sprite is moving right, otherwise we could randomly stop moving left
			vel.x = 0;
			playerBody->SetLinearVelocity(vel);
		}
	}
	else if (key.code == sf::Keyboard::Space) {
		b2Vec2 vel = playerBody->GetLinearVelocity();
		vel.y = 0;
		playerBody->SetLinearVelocity(vel);
	}
}

b2Vec2 PlatformDemoRegion::convertToWorld(sf::Vector2f sfCoords) {
	return b2Vec2(sfCoords.x / pixelsPerMeter, sfCoords.y / pixelsPerMeter);
}

sf::Vector2f PlatformDemoRegion::convertToSprite(b2Vec2 worldCoords) {
	return sf::Vector2f(worldCoords.x * pixelsPerMeter, worldCoords.y * pixelsPerMeter);
}

sf::Vector2f PlatformDemoRegion::convertToSprite(double worldCoordX, double worldCoordY) {
	return sf::Vector2f(worldCoordX * pixelsPerMeter, worldCoordY * pixelsPerMeter);
}

/// <summary>
/// Initializes this instance.
/// </summary>
void PlatformDemoRegion::init() {
	// Init textures
	std::string blockString(R"(Textures/testSprite.png)");
	blockTexture = std::make_unique<sf::Texture>();
	blockTexture->loadFromFile(blockString);

	// Construct a world object, which will hold and simulate the rigid bodies.
	platformWorld = std::make_unique<b2World>(gravity);


	// Create a ground body for our player to spawn on
	//-----------------------------------------------------------
	// Define the ground body.
	b2BodyDef groundBodyDef;
	b2Vec2 groundPos(1.5f, 15.0f);
	groundBodyDef.position.Set(groundPos.x, groundPos.y);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = platformWorld->CreateBody(&groundBodyDef);
	objectBodies.emplace_back(groundBody);
	// Define the ground box shape.
	b2PolygonShape groundBox;
	// The extents are the half-widths of the box.
	b2Vec2 groundHalves(1.0f, 0.25f);
	groundBox.SetAsBox(groundHalves.x, groundHalves.y);
	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Create a sprite to represent the player
	sf::Sprite* sfGroundBox = new sf::Sprite(*blockTexture);
	objectSprites.emplace_back(std::unique_ptr<sf::Sprite>(sfGroundBox));
	setDrawable(true, sfGroundBox);

	// size * scale = desired
	// Set the origin, size, and position of our sprite to match that of the Box2d body
	const sf::IntRect* const textureRect = &sfGroundBox->getTextureRect();
	sf::Vector2f newOrigin(textureRect->width / 2.0f, textureRect->height / 2.0f);
	sfGroundBox->setOrigin(newOrigin);
	sf::Vector2f newScale = convertToSprite((groundHalves.x * 2 / textureRect->width), (groundHalves.y * 2 / textureRect->width));
	sfGroundBox->setScale(newScale);
	sfGroundBox->setPosition(convertToSprite(groundPos));

	// Create a ground body for our player to jump to
	//-----------------------------------------------------------
	// Define the ground body.
	b2BodyDef ground2BodyDef;
	b2Vec2 ground2Pos(6.25f, 15.0f);
	ground2BodyDef.position.Set(ground2Pos.x, ground2Pos.y);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* ground2Body = platformWorld->CreateBody(&ground2BodyDef);
	objectBodies.push_back(ground2Body);
	// Define the ground box shape.
	b2PolygonShape ground2Box;
	// The extents are the half-widths of the box.
	b2Vec2 ground2Halves(1.0f, 0.25f);
	ground2Box.SetAsBox(ground2Halves.x, ground2Halves.y);
	// Add the ground fixture to the ground body.
	ground2Body->CreateFixture(&ground2Box, 0.0f);

	// Create a sprite to represent the body
	sf::Sprite* sfGround2Box = new sf::Sprite(*blockTexture);
	setDrawable(true, sfGround2Box);
	objectSprites.push_back(std::unique_ptr<sf::Sprite>(sfGround2Box));

	// size * scale = desired
	// Set the origin, size, and position of our sprite to match that of the Box2d body
	const sf::IntRect* const texture2Rect = &sfGround2Box->getTextureRect();
	sf::Vector2f new2Origin(texture2Rect->width / 2.0f, texture2Rect->height / 2.0f);
	sfGround2Box->setOrigin(new2Origin);
	sf::Vector2f new2Scale = convertToSprite((ground2Halves.x * 2 / texture2Rect->width), (ground2Halves.y * 2 / texture2Rect->width));
	sfGround2Box->setScale(new2Scale);
	sfGround2Box->setPosition(convertToSprite(ground2Pos));

	// Create the player to be controlled.
	//-----------------------------------------------------------
	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	b2Vec2 bodyPos(1.0f, 1.0f);
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(bodyPos.x, bodyPos.y);
	b2Body* body = platformWorld->CreateBody(&bodyDef);
	playerBody = body;
	objectBodies.push_back(body);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	b2Vec2 bodyHalves(0.25, 0.25);
	dynamicBox.SetAsBox(bodyHalves.x, bodyHalves.y);
	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;
	// Override the default friction.
	fixtureDef.friction = 0.3f;
	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	// Create a sprite to represent the player
	sf::Sprite* sfbodyBox = new sf::Sprite(*blockTexture);
	setDrawable(true, sfbodyBox);
	objectSprites.push_back(std::unique_ptr<sf::Sprite>(sfbodyBox));

	// size * scale = desired
	// Set the origin, size, and position of our sprite to match that of the Box2d body
	const sf::IntRect* const otherTextureRect = &sfbodyBox->getTextureRect();
	sf::Vector2f newNewOrigin(textureRect->width / 2.0f, textureRect->height / 2.0f);
	sfbodyBox->setOrigin(newOrigin);
	sf::Vector2f newNewScale = convertToSprite((bodyHalves.x * 2 / otherTextureRect->width), (bodyHalves.y * 2 / otherTextureRect->width));
	sfbodyBox->setScale(newNewScale);
	sfbodyBox->setPosition(convertToSprite(bodyPos));
}

/// <summary>
/// Initializes the GUI.
/// </summary>
void PlatformDemoRegion::initGUI() {
	// Load the black theme
	tgui::Theme theme("TGUI_Widgets/Black.txt");

	// Get a bound version of the window size
	// Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
	tgui::Layout windowWidth = tgui::bindWidth(*regionGUI);
	tgui::Layout windowHeight = tgui::bindHeight(*regionGUI);

	// Create the background image (picture is of type tgui::Picture::Ptr or std::shared_widget<Picture>)
	tgui::Picture::Ptr picture = tgui::Picture::create(R"(Textures/Backbone2.png)");

	picture->setSize(windowWidth, "&.height / 10");
	picture->setPosition(0, 9 * windowHeight / 10.0f);
	regionGUI->add(picture);
}

/// <summary>
/// Frees all dynamic memory allocated for this instance.
/// Resets the state of every member of this instance.
/// </summary>
void PlatformDemoRegion::destroy() {
	// Delete sprites
	for (auto& objectSprite : objectSprites) {
		objectSprite.reset();
	}
	objectSprites.clear();
	clearDrawable();
	clearUpdatable();

	// Upon looking, I believe this also frees all of the object memory.
	// That means that our above step is "unneeded". I think that it is ok though to explicitly do it.
	platformWorld.reset();

	objectBodies.clear();
	// playBody is also in objectBodies, so DON'T DOUBLE DELETE IT.
	playerBody = nullptr;

	// Delete textures
	blockTexture.reset();

	// Reset time
	lastUpdateTime = sf::Time::Zero;
}

/// <summary>
/// Resets this instance.
/// Box2d objects and their sprites are deleted and regenerated.
/// Everything else in this instance is also reset or reconstructed.
/// </summary>
void PlatformDemoRegion::reset() {
	destroy();
	init();
}
#endif // GAMEBACKBONE_BUILD_PLATFORM_DEMO