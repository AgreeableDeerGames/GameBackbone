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

		// Update the angle of the sprite to match the angle of the Box2D body.
		// Converting from radians to degrees because Box2D uses radians and SFML uses degrees. 
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

/// Everything created by this function will be a box. You may want to use different shapes in your own code.
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
	// This will allow the sprite to rotate around its center instead of around its top left corner
	float spriteHalfHeight = gameBodySprite->getGlobalBounds().height / 2.0;
	float spriteHalfWidth = gameBodySprite->getGlobalBounds().width / 2.0;
	gameBodySprite->setOrigin(spriteHalfHeight, spriteHalfWidth);

	// Mark the sprite to be displayed
	setDrawable(true, gameBodySprite.get());

	// Create the Box2D representation for physics

	// This defines the properties of body that the Box2D will operate on
	b2BodyDef bodyDef;

	// Move the Box2D body to a place in the Box2D coordinate system that corresponds to the sprite's position in the SFML coordinate system
	b2Vec2 worldPosition = convertToWorld(spritePosition);
	bodyDef.position.Set(worldPosition.x, worldPosition.y);

	// Allow the body to move
	if (dynamicBody)
	{
		bodyDef.type = b2_dynamicBody;
	}

	// TODO: tell people that the sleep thing is our fault
	// This will prevent the body from ever falling asleep
	// This slows things down, but prevents strange bugs where objects suddenly stop moving
	bodyDef.allowSleep = allowSleep;

	// Create a Box2D body from the provided properties and add it to the world
	b2Body* body = platformWorld->CreateBody(&bodyDef);

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
		// TODO: WHY DO WE NEED FIXTURES
		body->CreateFixture(&fixtureDef);
	}
	else
	{
		// Non-dynamic bodies just need a shape.
		// Setting the Density of 0 makes it static
		body->CreateFixture(&shape, 0.0f);
	}

	// Add the sprite and the Box2D body to corresponding indices in their vectors
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

	// Create the player
	addGameBody({125, 200}, {0.09f, 0.09f}, *blockTexture, true, false);
	playerBody = objectBodies[0];

	// Create the ground for the player
	addGameBody({100, 400}, {0.3f, 0.2f}, *blockTexture, false);
	addGameBody({400, 400}, {0.3f, 0.2f}, *blockTexture, false);
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

	// Destroy the world and all of its memory
	platformWorld.reset();

	objectBodies.clear();
	// PlayBody is also in objectBodies, so DON'T DOUBLE DELETE IT.
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