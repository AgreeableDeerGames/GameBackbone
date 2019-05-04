// Don't declare PlatformDemo functions if the user doesn't want it
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

const int32 velocityIterations = 6;
const int32 positionIterations = 2;
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
	float stepTime = msPassed/50.0f;
 	platformWorld->Step(stepTime, velocityIterations, positionIterations);
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
/// </summary>
/// 
/// <param name="spritePosition"> </param>
/// <param name="scale"> </param>
/// <param name="texture"> </param>
/// <param name="dynamicBody"> </param>
/// <param name="allowSleep"> </param>
void PlatformDemoRegion::addGameBody(sf::Vector2f spritePosition, sf::Vector2f scale, sf::Texture& texture, bool dynamicBody, bool allowSleep)
{
	// Create sprite
	std::unique_ptr<sf::Sprite> gameBodySprite = std::make_unique<sf::Sprite>(texture);
	// Scale the sprite to the desired dimensions
	gameBodySprite->setScale(scale);
	// Move the sprite to its Intended position
	gameBodySprite->setPosition(spritePosition);
	// Move origin of the sprite to its center
	// This will allow the sprite to rotate around its center
	// instead of around its top left corner
	float spriteHalfHeight = gameBodySprite->getGlobalBounds().height / 2.0;
	float spriteHalfWidth = gameBodySprite->getGlobalBounds().width / 2.0;
	gameBodySprite->setOrigin(spriteHalfHeight, spriteHalfWidth);

	// Mark the sprite to be displayed
	setDrawable(true, gameBodySprite.get());

	// Create the Box2D representation for physics

	// This defines the properties of body that the Box2D will operate on
	b2BodyDef bodyDef;

	// Move the Box2D body to a place in the Box2D coordinate system that coresponds to the
	// sprite's position in the SFML coordinate system
	b2Vec2 worldPosition = convertToWorld(spritePosition);
	bodyDef.position.Set(worldPosition.x, worldPosition.y);

	// This will prevent the body from ever falling asleep
	// This slows things down, but prevents strange bugs where 
	// objects suddenly stop moving
	bodyDef.allowSleep = allowSleep;

	// Create a Box2D body from the provided properties and add it to the world
	b2Body* body = platformWorld->CreateBody(&bodyDef);

	// Add to body to internal vector of bodies
	objectBodies.push_back(body);

	// Define the shape of the Box2D body.
	b2PolygonShape shape;

	// You must pass the half width and half height to Box2D to create a box shape
	float box2dFullWidth = (gameBodySprite->getGlobalBounds().width / pixelsPerMeter);
	float box2dHalfWidth = box2dFullWidth / 2.0;
	float box2dFullHeight = (gameBodySprite->getGlobalBounds().height / pixelsPerMeter);
	float box2dHalfHeight = box2dFullHeight / 2.0;
	
	// Give the shape the dimensions of the sprite (converted to the Box2D coordinate system)
	shape.SetAsBox(box2dHalfWidth, box2dHalfHeight);

	if (dynamicBody)
	{
		// Properties for the dynamic body
		b2FixtureDef fixtureDef;
		// The Shape
		fixtureDef.shape = &shape;
		// These change the way that the object behaves in the world
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		// Tell the 
		body->CreateFixture(&fixtureDef);
	}
	else
	{
		// Non-dynamic bodies just need a shape.
		// Setting the Density of 0 makes it static
		body->CreateFixture(&shape, 0.0f);
	}

	// Add the sprite and the Box2D body to corresponding indicies in their vectors
	objectSprites.emplace_back(std::move(gameBodySprite));
	objectBodies.push_back(body);
}

/// <summary>
/// Initializes this instance.
/// </summary>
void PlatformDemoRegion::init() {
	lastUpdateTime = sf::Time::Zero;
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

	// // Call the body factory which allocates memory for the ground body
	// // from a pool and creates the ground box shape (also from a pool).
	// // The body is also added to the world.
	// b2Body* groundBody = platformWorld->CreateBody(&groundBodyDef);
	// objectBodies.emplace_back(groundBody);
	// // Define the ground box shape.
	// b2PolygonShape groundBox;
	// // The extents are the half-widths of the box.
	// b2Vec2 groundHalves(1.0f, 0.25f);
	// groundBox.SetAsBox(groundHalves.x, groundHalves.y);
	// // Add the ground fixture to the ground body.
	// groundBody->CreateFixture(&groundBox, 0.0f);

	// // Create a sprite to represent the player
	// sf::Sprite* sfGroundBox = new sf::Sprite(*blockTexture);
	// objectSprites.emplace_back(std::unique_ptr<sf::Sprite>(sfGroundBox));
	// setDrawable(true, sfGroundBox);

	// // size * scale = desired
	// // Set the origin, size, and position of our sprite to match that of the Box2d body
	// const sf::IntRect* const textureRect = &sfGroundBox->getTextureRect();
	// sf::Vector2f newOrigin(textureRect->width / 2.0f, textureRect->height / 2.0f);
	// sfGroundBox->setOrigin(newOrigin);
	// sf::Vector2f newScale = convertToSprite((groundHalves.x * 2 / textureRect->width), (groundHalves.y * 2 / textureRect->width));
	// sfGroundBox->setScale(newScale);
	// sfGroundBox->setPosition(convertToSprite(groundPos));

	// // Create a ground body for our player to jump to
	// //-----------------------------------------------------------
	// // Define the ground body.
	// b2BodyDef ground2BodyDef;
	// b2Vec2 ground2Pos(6.25f, 15.0f);
	// ground2BodyDef.position.Set(ground2Pos.x, ground2Pos.y);

	// // Call the body factory which allocates memory for the ground body
	// // from a pool and creates the ground box shape (also from a pool).
	// // The body is also added to the world.
	// b2Body* ground2Body = platformWorld->CreateBody(&ground2BodyDef);
	// objectBodies.push_back(ground2Body);
	// // Define the ground box shape.
	// b2PolygonShape ground2Box;
	// // The extents are the half-widths of the box.
	// b2Vec2 ground2Halves(1.0f, 0.25f);
	// ground2Box.SetAsBox(ground2Halves.x, ground2Halves.y);
	// // Add the ground fixture to the ground body.
	// ground2Body->CreateFixture(&ground2Box, 0.0f);

	// // Create a sprite to represent the body
	// sf::Sprite* sfGround2Box = new sf::Sprite(*blockTexture);
	// setDrawable(true, sfGround2Box);
	// objectSprites.push_back(std::unique_ptr<sf::Sprite>(sfGround2Box));

	// // size * scale = desired
	// // Set the origin, size, and position of our sprite to match that of the Box2d body
	// const sf::IntRect* const texture2Rect = &sfGround2Box->getTextureRect();
	// sf::Vector2f new2Origin(texture2Rect->width / 2.0f, texture2Rect->height / 2.0f);
	// sfGround2Box->setOrigin(new2Origin);
	// sf::Vector2f new2Scale = convertToSprite((ground2Halves.x * 2 / texture2Rect->width), (ground2Halves.y * 2 / texture2Rect->width));
	// sfGround2Box->setScale(new2Scale);
	// sfGround2Box->setPosition(convertToSprite(ground2Pos));

	// // Create the player to be controlled.
	// //-----------------------------------------------------------
	// // Define the dynamic body. We set its position and call the body factory.
	// b2BodyDef bodyDef;
	// // bodyDef.allowSleep = false;
	// b2Vec2 bodyPos(1.0f, 1.0f);
	// bodyDef.type = b2_dynamicBody;
	// bodyDef.position.Set(bodyPos.x, bodyPos.y);
	// b2Body* body = platformWorld->CreateBody(&bodyDef);
	// playerBody = body;
	// objectBodies.push_back(body);

	// // Define another box shape for our dynamic body.
	// b2PolygonShape dynamicBox;
	// b2Vec2 bodyHalves(0.25, 0.25);
	// dynamicBox.SetAsBox(bodyHalves.x, bodyHalves.y);
	// // Define the dynamic body fixture.
	// b2FixtureDef fixtureDef;
	// fixtureDef.shape = &dynamicBox;
	// // Set the box density to be non-zero, so it will be dynamic.
	// fixtureDef.density = 1.0f;
	// // Override the default friction.
	// fixtureDef.friction = 0.3f;
	// // Add the shape to the body.
	// body->CreateFixture(&fixtureDef);

	// // Create a sprite to represent the player
	// sf::Sprite* sfbodyBox = new sf::Sprite(*blockTexture);
	// setDrawable(true, sfbodyBox);
	// objectSprites.push_back(std::unique_ptr<sf::Sprite>(sfbodyBox));

	// // size * scale = desired
	// // Set the origin, size, and position of our sprite to match that of the Box2d body
	// const sf::IntRect* const otherTextureRect = &sfbodyBox->getTextureRect();
	// sf::Vector2f newNewOrigin(textureRect->width / 2.0f, textureRect->height / 2.0f);
	// sfbodyBox->setOrigin(newOrigin);
	// sf::Vector2f newNewScale = convertToSprite((bodyHalves.x * 2 / otherTextureRect->width), (bodyHalves.y * 2 / otherTextureRect->width));
	// sfbodyBox->setScale(newNewScale);
	// sfbodyBox->setPosition(convertToSprite(bodyPos));
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