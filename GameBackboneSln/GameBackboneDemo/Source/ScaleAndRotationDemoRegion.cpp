#define _USE_MATH_DEFINES

#include <GameBackboneDemo/ScaleAndRotationDemoRegion.h>

#include <GameBackbone/Core/RelativeRotationSprite.h>
#include <GameBackbone/Navigation/NavigationTools.h>

#include <TGUI/TGUI.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <string>


using namespace EXE;

/// <summary>
/// Initializes a new instance of the <see cref="ScaleAndRotationDemoRegion"/> class.
/// </summary>
/// <param name="window">The window that will be attached to this instances GUI.</param>
ScaleAndRotationDemoRegion::ScaleAndRotationDemoRegion(sf::RenderWindow & window) : DemoRegion(window) {
	init();

	// Try to initialize the GUI, catch and display any errors.
	try {
		// Load the widgets
		initGUI();
	}
	catch (const tgui::Exception& e) {
		std::cerr << "Failed to load GUI: " << e.what() << std::endl;
	}
}

/// <summary>
/// Finalizes an instance of the <see cref="ScaleAndRotationDemoRegion"/> class.
/// </summary>
ScaleAndRotationDemoRegion::~ScaleAndRotationDemoRegion() {
	// Free all memory stored on the ScaleAndRotationDemoRegion
	destroy();
}

/// <summary>
/// Handles mouse click logic.
/// </summary>
/// <param name="newPosition">The position of the click.</param>
/// <param name="button">The mouse button that was clicked.</param>
void ScaleAndRotationDemoRegion::handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button) {
	// Only handle Left Clicks
	if (button == sf::Mouse::Left) {
		// Set the position of the displaySprite
		displaySprite->setPosition(newPosition);
	}
}

/// <summary>
/// Handles mouse wheel scroll logic.
/// </summary>
/// <param name="scrollDelta">The change in the wheel.</param>
void ScaleAndRotationDemoRegion::handleWheelScroll(float scrollDelta) {
	// Scale the displaySprite by 1.25^scrollDelta in both axes
	displaySprite->scale({powf(1.25, scrollDelta) , powf(1.25, scrollDelta)});
}

/// <summary>
/// Handles the mouse move.
/// Rotates the compound sprite to face the mouse position.
/// </summary>
/// <param name="mousePosition">The mouse position.</param>
void ScaleAndRotationDemoRegion::handleMouseMove(sf::Vector2f mousePosition) {
	// Calculate the angle between the sprite and the mouse
	const float radianAngle = atan2f(mousePosition.y - displaySprite->getPosition().y, mousePosition.x - displaySprite->getPosition().x);
	// Convert the angle into degrees because SFML uses degrees
	const float degreeAngle = radianAngle * 180 / (float)M_PI;
	// Rotate the sprite to point at the calculated angle (at the mouse)
	displaySprite->setRotation(degreeAngle);
}

/// <summary>
/// Initializes this instance.
/// </summary>
void ScaleAndRotationDemoRegion::init() {

	// Initialize the arrow textures for the component sprites
	std::string arrowPath("Textures/SmallArrow.png");
	arrowTexture = std::make_unique<sf::Texture>();
	arrowTexture->loadFromFile(arrowPath);

	// Load the textures for the component sprites of the compound sprite with overlapping sprites
	std::string rotationArrowCenterPath("Textures/RotationArrowCenter.png");
	std::string rotationArrowLowPath("Textures/RotationArrowLow.png");
	std::string rotationArrowLeftPath("Textures/RotationArrowLeft.png");
	rotationArrowCenterTexture = std::make_unique<sf::Texture>();
	rotationArrowCenterTexture->loadFromFile(rotationArrowCenterPath);
	rotationArrowLeftTexture = std::make_unique<sf::Texture>();
	rotationArrowLeftTexture->loadFromFile(rotationArrowLeftPath);
	rotationArrowLowTexture = std::make_unique<sf::Texture>();
	rotationArrowLowTexture->loadFromFile(rotationArrowLowPath);

	
	// Component sprites

	// Relative rotation sprites

	// The X and Y positions for all the compound sprites
	// Note: This is different than the X and Y positions of all of the component sprites
	// that make up each compound sprite
	const float compoundSpriteXPosition = 400;
	const float compoundSpriteYPosition = 400;

	// Create component sprites for the relative rotation sprite
	spriteComponent1 = std::make_unique<sf::Sprite>(*arrowTexture);
	spriteComponent2 = std::make_unique<sf::Sprite>(*arrowTexture);
	spriteComponent3 = std::make_unique<sf::Sprite>(*arrowTexture);
	std::vector<sf::Sprite*> spriteVector = { spriteComponent1.get() , spriteComponent2.get(), spriteComponent3.get() };

	// Create the component sprites for the compound sprite with overlapping sprites
	sf::Sprite* rotationArrowCenterSprite = new sf::Sprite(*rotationArrowCenterTexture);
	sf::Sprite* rotationArrowLeftSprite = new sf::Sprite(*rotationArrowLeftTexture);
	sf::Sprite* rotationArrowLowSprite = new sf::Sprite(*rotationArrowLowTexture);
	rotationArrowCenterSprite->setColor(sf::Color::Magenta);
	rotationArrowLeftSprite->setColor(sf::Color::White);
	rotationArrowLowSprite->setColor(sf::Color::Green);
	textureOffsetSprites = {rotationArrowCenterSprite, rotationArrowLeftSprite, rotationArrowLowSprite};

	switch (selectedInitMethod) {
		case ROTATION_INIT_TYPE::RELATIVE_POSITION_CONSTRUCTOR: {
			// Set the positions of the components
			spriteComponent1->setPosition(compoundSpriteXPosition + 92, compoundSpriteYPosition + 12);
			spriteComponent2->setPosition(compoundSpriteXPosition + 12, compoundSpriteYPosition + 92);
			spriteComponent3->setPosition(compoundSpriteXPosition + 12, compoundSpriteYPosition + 12);

			// Create the compound sprite by adding the components to the constructor
			// The component sprites maintain their position
			displaySprite = std::make_unique<GB::RelativeRotationSprite>(spriteVector, sf::Vector2f(compoundSpriteXPosition, compoundSpriteYPosition));
			break;
		}
		case ROTATION_INIT_TYPE::RELATIVE_OFFSET: {
			// Set the positions of the components
			spriteComponent1->setPosition(compoundSpriteXPosition, compoundSpriteYPosition);
			spriteComponent2->setPosition(compoundSpriteXPosition, compoundSpriteYPosition);
			spriteComponent3->setPosition(compoundSpriteXPosition, compoundSpriteYPosition);

			// Create the compound sprite then add all of the components with a relative offset
			displaySprite = std::make_unique<GB::RelativeRotationSprite>(sf::Vector2f(compoundSpriteXPosition, compoundSpriteYPosition));
			static_cast<GB::RelativeRotationSprite*>(displaySprite.get())->addComponent(spriteComponent1.get(), { 80, 0 });
			static_cast<GB::RelativeRotationSprite*>(displaySprite.get())->addComponent(spriteComponent2.get(), { 0, 80 });
			static_cast<GB::RelativeRotationSprite*>(displaySprite.get())->addComponent(spriteComponent3.get(), { 0, 0 });
			break;
		}
		case ROTATION_INIT_TYPE::RELATIVE_POSITION: {
			// Set the positions of the components
			spriteComponent1->setPosition(compoundSpriteXPosition + 92, compoundSpriteYPosition + 12);
			spriteComponent2->setPosition(compoundSpriteXPosition + 12, compoundSpriteYPosition + 92);
			spriteComponent3->setPosition(compoundSpriteXPosition + 12, compoundSpriteYPosition + 12);

			// Create the compound sprite then add all of the components. 
			// The components will maintain their positions relative to the compound sprite
			displaySprite = std::make_unique<GB::RelativeRotationSprite>(sf::Vector2f(compoundSpriteXPosition, compoundSpriteYPosition));
			displaySprite->addComponent(spriteComponent1.get());
			displaySprite->addComponent(spriteComponent2.get());
			displaySprite->addComponent(spriteComponent3.get());
			break;
		}
		case ROTATION_INIT_TYPE::TEXTURE_BASED_OFFSET: {
			displaySprite = std::make_unique<GB::CompoundSprite>(textureOffsetSprites);
			displaySprite->setPosition(compoundSpriteXPosition, compoundSpriteYPosition);
			break;
		}
		default: {
			throw new std::out_of_range("Invalid ROTATION_INIT_TYPE");
		}
	}

	// Assign colors and draw
	spriteComponent1->setColor(sf::Color::Magenta);
	spriteComponent2->setColor(sf::Color::White);
	spriteComponent3->setColor(sf::Color::Green);
	setDrawAndUpdateable(true, displaySprite.get());
}

/// <summary>
/// Initializes the GUI.
/// </summary>
void ScaleAndRotationDemoRegion::initGUI() {
	// Get a bound version of the window size
	// Passing this to setPosition or setSize will make the widget automatically update when the view of the GUI changes
	tgui::Layout windowWidth = tgui::bindWidth(*regionGUI);
	tgui::Layout windowHeight = tgui::bindHeight(*regionGUI);

	// Create the background image (picture is of type tgui::Picture::Ptr)
	tgui::Picture::Ptr picture = tgui::Picture::create("Textures/Backbone2.png");

	// Make the image 1/10th of the screen and start it 9/10ths of the way down
	picture->setSize(windowWidth, "&.height / 10");
	picture->setPosition(0, 9 * windowHeight / 10.0f);
	regionGUI->add(picture);

	// Vector to temporarily hold all of the initialization options
	std::vector<tgui::Button::Ptr> initOptionButtons;

	// Create initMethod1 button
	tgui::Button::Ptr relativePositionCtrButton = tgui::Button::create();
	// Give the Button Its Text
	relativePositionCtrButton->setText("Relative\nPosition\nConstructor");
	// Connect the button to its callback function
	relativePositionCtrButton->connect("pressed", &ScaleAndRotationDemoRegion::initMethod1CB, this);
	// Add the button to the vector for future use
	initOptionButtons.push_back(relativePositionCtrButton);

	// Create initMethod2 button
	tgui::Button::Ptr relativeOffsetButton = tgui::Button::create();
	relativeOffsetButton->setText("Relative\nOffset");
	relativeOffsetButton->connect("pressed", &ScaleAndRotationDemoRegion::initMethod2CB, this);
	initOptionButtons.push_back(relativeOffsetButton);

	// Create initMethod3 button
	tgui::Button::Ptr relativePositionButton = tgui::Button::create();
	relativePositionButton->setText("Relative\nPosition");
	relativePositionButton->connect("pressed", &ScaleAndRotationDemoRegion::initMethod3CB, this);
	initOptionButtons.push_back(relativePositionButton);

	// Create initMethod4 button
	tgui::Button::Ptr textureBasedOffsetButton = tgui::Button::create();
	textureBasedOffsetButton->setText("Texture\nOffset");
	textureBasedOffsetButton->connect("pressed", &ScaleAndRotationDemoRegion::initMethod4CB, this);
	initOptionButtons.push_back(textureBasedOffsetButton);

	// The number of buttons in this menu
	const std::size_t numButtons = initOptionButtons.size();
	// Size the width and height of the buttons to give them space on all sides
	tgui::Layout buttonWidth = windowWidth / ((numButtons + 1) * 1.5);
	tgui::Layout buttonHeight = windowHeight / 15.0f;
	for (std::size_t i = 0; i < numButtons; ++i)
	{
		// Save some repetitive typing
		auto& currentButton = initOptionButtons[i];
		// Set the size of the button
		currentButton->setSize(buttonWidth, buttonHeight);
		// Place the buttons in a row along the bottom of the window
		// They will be evenly spaced out and be in the bottom 1/10th of the window
		currentButton->setPosition(((windowWidth / numButtons) * i) + buttonWidth / 2, windowHeight * 9.15 / 10.0f);
		// Add the button to the GUI
		regionGUI->add(currentButton);
	}
}

/// <summary>
/// Frees all dynamically allocated memory in this instance
/// </summary>
void ScaleAndRotationDemoRegion::destroy() {
	// Delete sprites stored on the ScaleAndRotationDemoRegion and set them to nullptr
	for (sf::Sprite* sprite : textureOffsetSprites) {
		delete sprite;
		sprite = nullptr;
	}
}

/// <summary>
/// Resets this instance.
/// frees and / or reinitializes all members of this instance that impact the demo.
/// </summary>
void ScaleAndRotationDemoRegion::reset() {
	// Free all dynamic memory
	destroy();

	// Reset all non-dynamic members
	clearDrawable();
	clearUpdatable();

	// Reinitialize for the user to use again
	init();
}

/// <summary>
/// Handles the button initMethod1.
/// </summary>
void ScaleAndRotationDemoRegion::initMethod1CB()
{
	selectedInitMethod = ROTATION_INIT_TYPE::RELATIVE_POSITION_CONSTRUCTOR;
	debugPrint("Relative Position Constructor");
	reset();
}

/// <summary>
/// Handles the button initMethod2.
/// </summary>
void ScaleAndRotationDemoRegion::initMethod2CB()
{
	selectedInitMethod = ROTATION_INIT_TYPE::RELATIVE_OFFSET;
	debugPrint("Relative Offset");
	reset();
}

/// <summary>
/// Handles the button initMethod3.
/// </summary>
void ScaleAndRotationDemoRegion::initMethod3CB()
{
	selectedInitMethod = ROTATION_INIT_TYPE::RELATIVE_POSITION;
	debugPrint("Relative Position");
	reset();
}

/// <summary>
///  Handles the button initMethod4.
/// </summary>
void ScaleAndRotationDemoRegion::initMethod4CB() {
	selectedInitMethod = ROTATION_INIT_TYPE::TEXTURE_BASED_OFFSET;
	debugPrint("Texture Based Offset");
	reset();
}