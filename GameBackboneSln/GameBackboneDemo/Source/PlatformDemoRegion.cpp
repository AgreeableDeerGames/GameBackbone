// Don't declare PlatformDemo functions if the user doesn't want it
#ifdef GAMEBACKBONE_BUILD_PLATFORM_DEMO

#define _USE_MATH_DEFINES

#include <GameBackboneDemo/PlatformDemoRegion.h>

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
const float pixelsPerMeter = 32;

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
void PlatformDemoRegion::update(sf::Int64 elapsedTime) {
	// Instruct the world to perform a single step of simulation.
	float stepTime = elapsedTime /50000.0f;
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
		objectSprites[ii]->setRotation(static_cast<float>(angle * (180.0f / M_PI)));
	}
}

/// <summary>
/// Handles mouse click logic.
/// </summary>
/// <param name="newPosition">The position of the click.</param>
/// <param name="button">The mouse button clicked button.</param>
void PlatformDemoRegion::handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button) {

	// 'Jump' the player by providing upward linear velocity when the mouse button is pressed
	b2Vec2 vel = playerBody->GetLinearVelocity();
	vel.y = -0.9f;
	playerBody->SetLinearVelocity(vel);

}

/// <summary>
/// Handles the key press.
/// Moves the sprite right or left or jumps
/// </summary>
/// <param name="mousePosition">The key pressed.</param>
void PlatformDemoRegion::handleKeyPress(sf::Event::KeyEvent key){

	// Move the player left by applying a linear velocity when the user presses
	if (key.code == sf::Keyboard::A){
		b2Vec2 vel = playerBody->GetLinearVelocity();
		vel.x = -0.4f;
		playerBody->SetLinearVelocity(vel);
	}

	// Move the player right by applying a linear velocity when the user presses
	else if(key.code == sf::Keyboard::D){
		b2Vec2 vel = playerBody->GetLinearVelocity();
		vel.x = 0.4f;
		playerBody->SetLinearVelocity(vel);
	}

	// 'Jump' the player by providing upward linear velocity
	else if (key.code == sf::Keyboard::Space) {
		b2Vec2 vel = playerBody->GetLinearVelocity();
		vel.y = -0.9f;
		playerBody->SetLinearVelocity(vel);
	}
}

/// <summary>
/// Handles the key release.
/// Immediately stops the sprite moving right or left or jumping
/// </summary>
/// <param name="mousePosition">The key released.</param>
void PlatformDemoRegion::handleKeyRelease(sf::Event::KeyEvent key){

	// Stop moving left by setting the linear velocity to 0
	if (key.code == sf::Keyboard::A) {
		b2Vec2 vel = playerBody->GetLinearVelocity();
		// Make sure that the sprite is moving left, otherwise we could randomly stop moving right
		if (vel.x < 0)
		{
			vel.x = 0;
			playerBody->SetLinearVelocity(vel);
		}
	}

	// Stop moving right by setting the linear velocity to 0
	else if (key.code == sf::Keyboard::D) {
		b2Vec2 vel = playerBody->GetLinearVelocity();
		if (vel.x > 0)
		{
			// Make sure that the sprite is moving right, otherwise we could randomly stop moving left
			vel.x = 0;
			playerBody->SetLinearVelocity(vel);
		}
	}

	// Stop jumping by setting the linear velocity to 0
	// This allows the user to control the size of the jump
	else if (key.code == sf::Keyboard::Space) {
		b2Vec2 vel = playerBody->GetLinearVelocity();
		vel.y = 0;
		playerBody->SetLinearVelocity(vel);
	}
}

/// <summary>
/// Convert a coordinate from the SFML coordinate system to the Box2D coordinate system.
/// </summary>
/// <param name="sfCoords"> </param>
/// <return> b2Vec2 </return>
b2Vec2 PlatformDemoRegion::convertToBox(sf::Vector2f sfCoords) {
	return b2Vec2(sfCoords.x / pixelsPerMeter, sfCoords.y / pixelsPerMeter);
}

/// <summary>
/// Convert a coordinate from the Box2D coordinate system to the SFML coordinate system.
/// </summary>
/// <param name="boxCoord"> The coordinate in the Box2D coordinate system </param>
/// <return> The coordinate in the SFML coordinate system. </return>
sf::Vector2f PlatformDemoRegion::convertToSprite(b2Vec2 boxCoord) {
	return sf::Vector2f(boxCoord.x * pixelsPerMeter, boxCoord.y * pixelsPerMeter);
}

/// <summary>
/// Convert a coordinate from the Box2D coordinate system to the SFML coordinate system.
/// </summary>
/// <param name="boxCoordX"> The X position in the Box2D coordinate space. </param>
/// <param name="boxCoordY"> The Y position in the Box2D coordinate space. </param>
/// <return> The coordinate in the SFML coordinate system. </return>
sf::Vector2f PlatformDemoRegion::convertToSprite(float boxCoordX, float boxCoordY) {
	return sf::Vector2f(boxCoordX * pixelsPerMeter, boxCoordY * pixelsPerMeter);
}

/// <summary>
/// Creates a new sprite and a corresponding Box2D body to handle its collision and physics interaction.
/// Everything created by this function will be a box. You may want to use different shapes in your own code.
/// </summary>
/// <param name="spritePosition"> The position of the sprite to create (In sprite coordinates) </param>
/// <param name="scale"> The scaling factor applied to the sprite that will be created. </param>
/// <param name="texture"> The texture of the sprite that will be created. </param>
/// <param name="dynamicBody"> True if the created object should be allowed to move. False otherwise. </param>
/// <param name="allowSleep"> (Optional: Default True) True if the created object should be allowed to sleep (optimizes collision). False to disable this optimization. </param>
void PlatformDemoRegion::addGameBody(sf::Vector2f spritePosition, sf::Vector2f scale, sf::Texture& texture, bool dynamicBody, bool allowSleep)
{
	// Create sprite
	std::unique_ptr<sf::Sprite> gameBodySprite = std::make_unique<sf::Sprite>(texture);

	// Move origin of the sprite to its center
	// This will allow the sprite to rotate around its center instead of around its top left corner
	// The function getLocalBounds is used instead of getGlobalBounds as the origin is always calculated before
	// other transformations (though it won't matter in this case since we apply this operation before any transformations)
	float spriteLocalHalfHeight = gameBodySprite->getLocalBounds().height / 2.0f;
	float spriteLocalHalfWidth = gameBodySprite->getLocalBounds().width / 2.0f;
	gameBodySprite->setOrigin(spriteLocalHalfWidth, spriteLocalHalfHeight);

	// Scale the sprite to the desired dimensions
	gameBodySprite->setScale(scale);

	// Move the sprite to its Intended position
	gameBodySprite->setPosition(spritePosition);

	// Mark the sprite to be displayed
	setDrawable(true, gameBodySprite.get());

	// Create the Box2D representation for physics

	// This defines the properties of body that the Box2D will operate on
	b2BodyDef bodyDef;

	// Move the Box2D body to a place in the Box2D coordinate system that corresponds to the sprite's position in the SFML coordinate system
	b2Vec2 worldPosition = convertToBox(spritePosition);
	bodyDef.position.Set(worldPosition.x, worldPosition.y);

	// Allow the body to move
	if (dynamicBody)
	{
		bodyDef.type = b2_dynamicBody;
	}

	// This will prevent the body from ever falling asleep
	// This slows things down, but prevents strange bugs (possibly in this demo only) where objects suddenly stop moving
	bodyDef.allowSleep = allowSleep;

	// Create a Box2D body from the provided properties and add it to the world
	b2Body* body = platformWorld->CreateBody(&bodyDef);

	// Define the shape of the Box2D body.
	b2PolygonShape shape;

	// Give the shape the dimensions of the sprite (converted to the Box2D coordinate system)
	float bodyWidth = gameBodySprite->getGlobalBounds().width / pixelsPerMeter;
	float bodyHeight = gameBodySprite->getGlobalBounds().height / pixelsPerMeter;

	// You must pass the half width and half height to Box2D to create a box shape
	shape.SetAsBox(bodyWidth / 2.0f, bodyHeight / 2.0f);

	if (dynamicBody)
	{
		// Properties for the dynamic body
		b2FixtureDef fixtureDef;

		// The Shape
		fixtureDef.shape = &shape;

		// These change the way that the object behaves in the world
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;

		// Add a fixture to the body with the calculated paramaters
		// (these are the individual shapes that make up the body and actually do the collision)
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
	// Init textures
	std::string blockString(R"(Textures/testSprite.png)");
	blockTexture = std::make_unique<sf::Texture>();
	blockTexture->loadFromFile(blockString);

	// Construct a world object, which will hold and simulate the rigid bodies.
	platformWorld = std::make_unique<b2World>(gravity);

	// Create the player
	// The player will need to move (dynamic body) and should always be simulated (disallow sleep)
	const sf::Vector2f playerPosition(125, 200);
	const sf::Vector2f playerScale(0.09f, 0.09f);
	const bool dynamicPlayerBody = true;
	const bool allowPlayerSimulationToSleep = false;
	addGameBody(playerPosition, playerScale, *blockTexture, dynamicPlayerBody, allowPlayerSimulationToSleep);

	// The player will always be the first body added
	playerBody = objectBodies[0];

	// Create some ground for the player to platform on
	const unsigned int numSteps = 5;
	for (unsigned int i = 1; i <= numSteps; ++i)
	{
		// Arbitrary spacing and sizing logic for the ground
		const sf::Vector2f groundPosition(75.0f * i, 1000.0f / i);
		const sf::Vector2f groundScale(0.3f, 0.2f);

		// The ground should not be allowed to move
		const bool dynamicGroundBody = false;

		// Create a body to serve as the ground
		addGameBody(groundPosition, groundScale, *blockTexture, dynamicGroundBody);
	}
}

/// <summary>
/// Initializes the GUI.
/// </summary>
void PlatformDemoRegion::initGUI() {
	// Load the black theme
	tgui::Theme theme("TGUI_Widgets/Black.txt");

	// Get a bound version of the window size
	// Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
	tgui::Layout windowWidth = tgui::bindWidth(regionGUI);
	tgui::Layout windowHeight = tgui::bindHeight(regionGUI);

	// Create the background image
	tgui::Picture::Ptr picture = tgui::Picture::create(R"(Textures/Backbone2.png)");

	// Place the image at the bottom 1/10th of the screen
	picture->setSize(windowWidth, "&.height / 10");
	picture->setPosition(0, 9 * windowHeight / 10.0f);
	regionGUI.add(picture);
}

/// <summary>
/// Frees all dynamic memory allocated for this instance.
/// Resets the state of every member of this instance.
/// </summary>
void PlatformDemoRegion::destroy() {
	// Delete sprites
	// Because these are unique_ptr clearing the vector also frees the memory
	objectSprites.clear();

	// Clear all of GameRegion's references to drawables or updatables
	clearDrawable();

	// Destroy the world and all of its memory
	platformWorld.reset();

	// These were deleted when platformWorld was deleted
	// Just remove the pointers from the vector here
	objectBodies.clear();

	// PlayerBody is a non-owning pointer so no need to delete
	playerBody = nullptr;

	// Delete textures
	blockTexture.reset();
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