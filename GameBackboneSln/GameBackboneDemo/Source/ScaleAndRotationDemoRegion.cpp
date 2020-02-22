#define _USE_MATH_DEFINES

#include <GameBackboneDemo/ScaleAndRotationDemoRegion.h>

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
/// Handles mouse click logic.
/// </summary>
/// <param name="newPosition">The position of the click.</param>
/// <param name="button">The mouse button that was clicked.</param>
void ScaleAndRotationDemoRegion::handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button) {
	// Left clicks set the position of the sprite
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
/// Handles key press logic.
/// </summary>
/// <param name="scrollDelta">The change in the wheel.</param>
void ScaleAndRotationDemoRegion::handleKeyPress(sf::Event::KeyEvent key) {
	// Pressing 1 will set the scale the sprite to half of its original scale
	if (key.code == sf::Keyboard::Key::Num1 || key.code == sf::Keyboard::Key::Numpad1) {
	displaySprite->setScale(0.5f, 0.5f);
	}
	// Pressing 2 will set the scale the sprite its original scale
	else if (key.code == sf::Keyboard::Key::Num2 || key.code == sf::Keyboard::Key::Numpad2)
	{
	displaySprite->setScale(1.0f, 1.0f);
	}
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

	// The X and Y positions for all the compound sprites
	// Note: This is different than the X and Y positions of all of the component sprites
	// that make up each compound sprite
	const float compoundSpriteXPosition = 400;
	const float compoundSpriteYPosition = 400;

	// Create component sprites for the compound sprite
	// Create three sprites with an arrow texture
	std::vector<sf::Sprite> compoundSpriteComponents = {
		sf::Sprite(*arrowTexture),
		sf::Sprite(*arrowTexture),
		sf::Sprite(*arrowTexture)
	};
	// Give them different colors
	compoundSpriteComponents[0].setColor(sf::Color::Magenta);
	compoundSpriteComponents[1].setColor(sf::Color::White);
	compoundSpriteComponents[2].setColor(sf::Color::Green);

	// Create the component sprites for the compound sprite with overlapping sprites
	std::vector<sf::Sprite> textureOffsetSprites = {
		sf::Sprite(*rotationArrowCenterTexture),
		sf::Sprite(*rotationArrowLeftTexture),
		sf::Sprite(*rotationArrowLowTexture)
	};
	// Give them different colors
	textureOffsetSprites[0].setColor(sf::Color::Magenta);
	textureOffsetSprites[1].setColor(sf::Color::White);
	textureOffsetSprites[2].setColor(sf::Color::Green);

	switch (selectedInitMethod) {
		case ROTATION_INIT_TYPE::RELATIVE_POSITION_CONSTRUCTOR: {
			// Set the positions of the components
			compoundSpriteComponents[0].setPosition(compoundSpriteXPosition + 50, compoundSpriteYPosition + 0);
			compoundSpriteComponents[1].setPosition(compoundSpriteXPosition + 0, compoundSpriteYPosition + 0);
			compoundSpriteComponents[2].setPosition(compoundSpriteXPosition + 50, compoundSpriteYPosition + 50);

			// Create the compound sprite by adding the components to the constructor
			// The component sprites maintain their position
			displaySprite = std::make_unique<GB::CompoundSprite>(
				sf::Vector2f(compoundSpriteXPosition, compoundSpriteYPosition),
				0, 
				std::move(compoundSpriteComponents[0]),
				std::move(compoundSpriteComponents[1]),
				std::move(compoundSpriteComponents[2]));
			break;
		}
		case ROTATION_INIT_TYPE::RELATIVE_POSITION: {
			// Set the positions of the components
			compoundSpriteComponents[0].setPosition(compoundSpriteXPosition + 50, compoundSpriteYPosition + 0);
			compoundSpriteComponents[1].setPosition(compoundSpriteXPosition + 0, compoundSpriteYPosition + 0);
			compoundSpriteComponents[2].setPosition(compoundSpriteXPosition + 50, compoundSpriteYPosition + 50);

			// Create the compound sprite then add all of the components. 
			// The components will maintain their positions relative to the compound sprite
			displaySprite = std::make_unique<GB::CompoundSprite>(sf::Vector2f(compoundSpriteXPosition, compoundSpriteYPosition));
			displaySprite->addComponent(0, std::move(compoundSpriteComponents[0]));
			displaySprite->addComponent(0, std::move(compoundSpriteComponents[1]));
			displaySprite->addComponent(0, std::move(compoundSpriteComponents[2]));
			break;
		}
		case ROTATION_INIT_TYPE::TEXTURE_BASED_OFFSET: {
			// Create a CompoundSprite That overlays its component sprite on top of each other.
			// This allows them to rotate in sync.
			// The differences in the textures creates the appearance that the components are in different places.
			displaySprite = std::make_unique<GB::CompoundSprite>(
				0,
				std::move(textureOffsetSprites[0]),
				std::move(textureOffsetSprites[1]),
				std::move(textureOffsetSprites[2]));
			displaySprite->setPosition(compoundSpriteXPosition, compoundSpriteYPosition);
			break;
		}
		default: {
			throw new std::out_of_range("Invalid ROTATION_INIT_TYPE");
		}
	}

	// Set displaySprite to be drawn
	addDrawable(0, displaySprite.get());
}

/// <summary>
/// Initializes the GUI.
/// </summary>
void ScaleAndRotationDemoRegion::initGUI() {
	// Get a bound version of the window size
	// Passing this to setPosition or setSize will make the widget automatically update when the view of the GUI changes
	tgui::Layout windowWidth = tgui::bindWidth(this->getGUI());
	tgui::Layout windowHeight = tgui::bindHeight(this->getGUI());

	// Create the background image (picture is of type tgui::Picture::Ptr)
	tgui::Picture::Ptr picture = tgui::Picture::create("Textures/Backbone2.png");

	// Make the image 1/10th of the screen and start it 9/10ths of the way down
	picture->setSize(windowWidth, "&.height / 10");
	picture->setPosition(0, 9 * windowHeight / 10.0f);
	this->getGUI().add(picture);

	// Vector to temporarily hold all of the initialization options
	std::vector<tgui::Button::Ptr> initOptionButtons;

	// Create initMethod1 button
	tgui::Button::Ptr relativePositionCtrButton = tgui::Button::create();
	// Give the Button Its Text
	relativePositionCtrButton->setText("Relative\nPosition\nConstructor");
	// Connect the button to its callback function
	relativePositionCtrButton->connect("pressed", &ScaleAndRotationDemoRegion::selectRelativePositionConstructorCB, this);
	// Add the button to the vector for future use
	initOptionButtons.push_back(relativePositionCtrButton);

	// Create initMethod3 button
	tgui::Button::Ptr relativePositionButton = tgui::Button::create();
	relativePositionButton->setText("Relative\nPosition");
	relativePositionButton->connect("pressed", &ScaleAndRotationDemoRegion::selectRelativePositionAssignmentCB, this);
	initOptionButtons.push_back(relativePositionButton);

	// Create initMethod4 button
	tgui::Button::Ptr textureBasedOffsetButton = tgui::Button::create();
	textureBasedOffsetButton->setText("Texture\nOffset");
	textureBasedOffsetButton->connect("pressed", &ScaleAndRotationDemoRegion::selectTextureOffsetCB, this);
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
		this->getGUI().add(currentButton);
	}
}

/// <summary>
/// Resets this instance.
/// frees and / or reinitializes all members of this instance that impact the demo.
/// </summary>
void ScaleAndRotationDemoRegion::reset() {
	// Clear all of GameRegion's references to drawables
	clearDrawables();

	// Reinitialize for the user to use again
	init();
}

/// <summary>
/// Callback invoked when the user selects the button to display a
/// CompoundSprite constructed from components.
/// </summary>
void ScaleAndRotationDemoRegion::selectRelativePositionConstructorCB()
{
	selectedInitMethod = ROTATION_INIT_TYPE::RELATIVE_POSITION_CONSTRUCTOR;
	reset();
}

/// <summary>
/// Callback invoked when the user selects the button to display a
/// CompoundSprite with components added after construction.
/// </summary>
void ScaleAndRotationDemoRegion::selectRelativePositionAssignmentCB()
{
	selectedInitMethod = ROTATION_INIT_TYPE::RELATIVE_POSITION;
	reset();
}

/// <summary>
/// Callback invoked when the user selects the button to display a
/// CompoundSprite whose components textures are overlaid on each other.
/// Each components position is the same position of the compound sprite.
/// </summary>
void ScaleAndRotationDemoRegion::selectTextureOffsetCB() {
	selectedInitMethod = ROTATION_INIT_TYPE::TEXTURE_BASED_OFFSET;
	reset();
}