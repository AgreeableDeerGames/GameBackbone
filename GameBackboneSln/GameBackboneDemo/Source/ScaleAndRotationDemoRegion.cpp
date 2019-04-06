#include <iostream>

#define _USE_MATH_DEFINES

#include <GameBackboneDemo/ScaleAndRotationDemoRegion.h>
#include <GameBackbone/Core/RelativeRotationSprite.h>
#include <GameBackbone/Navigation/NavigationTools.h>

#include <TGUI/TGUI.hpp>

#include <SFML/Graphics.hpp>

#include <string>
#include <math.h>

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

	//TODO: We should break this up and explain exactly what each step is doing. This is super complicated for one line.
	// Calculates the angle that should be pointed at
	float angle = atan2f(mousePosition.y - displaySprite->getPosition().y, mousePosition.x - displaySprite->getPosition().x) * 180 / (float)M_PI;
	displaySprite->setRotation(angle);
}

/// <summary>
/// Initializes this instance.
/// </summary>
void ScaleAndRotationDemoRegion::init() {

	// Initialize the arrow textures for the component sprites
	std::string arrowPath("Textures/SmallArrow.png");
	arrowTexture = std::make_unique<sf::Texture>();
	arrowTexture->loadFromFile(arrowPath);

	// compound sprite with overlapping sprites
	std::string rotationArrowCenterPath("Textures/RotationArrowCenter.png");
	std::string rotationArrowLowPath("Textures/RotationArrowLow.png");
	std::string rotationArrowLeftPath("Textures/RotationArrowLeft.png");
	rotationArrowCenterTexture = std::make_unique<sf::Texture>();
	rotationArrowCenterTexture->loadFromFile(rotationArrowCenterPath);
	rotationArrowLeftTexture = std::make_unique<sf::Texture>();
	rotationArrowLeftTexture->loadFromFile(rotationArrowLeftPath);
	rotationArrowLowTexture = std::make_unique<sf::Texture>();
	rotationArrowLowTexture->loadFromFile(rotationArrowLowPath);

	
	// component sprites

	// relative rotation sprites
	const float COMPOUND_SPRITE_TEST_X = 400;
	const float COMPOUND_SPRITE_TEST_y = 400;
	spriteComponent1 = std::make_unique<sf::Sprite>(*arrowTexture);
	spriteComponent2 = std::make_unique<sf::Sprite>(*arrowTexture);
	spriteComponent3 = std::make_unique<sf::Sprite>(*arrowTexture);
	std::vector<sf::Sprite*> spriteVector = { spriteComponent1.get() , spriteComponent2.get(), spriteComponent3.get() };

	// compound sprite with overlapping sprites
	sf::Sprite* rotationArrowCenterSprite = new sf::Sprite(*rotationArrowCenterTexture);
	sf::Sprite* rotationArrowLeftSprite = new sf::Sprite(*rotationArrowLeftTexture);
	sf::Sprite* rotationArrowLowSprite = new sf::Sprite(*rotationArrowLowTexture);
	rotationArrowCenterSprite->setColor(sf::Color::Magenta);
	rotationArrowLeftSprite->setColor(sf::Color::White);
	rotationArrowLowSprite->setColor(sf::Color::Green);
	textureOffsetSprites = {rotationArrowCenterSprite, rotationArrowLeftSprite, rotationArrowLowSprite};

	switch (selectedInitMethod) {
		case ROTATION_INIT_TYPE::RELATIVE_POSITION_CONSTRUCTOR: {
			// set the positions of the components
			spriteComponent1->setPosition(COMPOUND_SPRITE_TEST_X + 92, COMPOUND_SPRITE_TEST_y + 12);
			spriteComponent2->setPosition(COMPOUND_SPRITE_TEST_X + 12, COMPOUND_SPRITE_TEST_y + 92);
			spriteComponent3->setPosition(COMPOUND_SPRITE_TEST_X + 12, COMPOUND_SPRITE_TEST_y + 12);

			// Create the compound sprite by adding the components to the constructor
			displaySprite = std::make_unique<GB::RelativeRotationSprite>(spriteVector, sf::Vector2f(COMPOUND_SPRITE_TEST_X, COMPOUND_SPRITE_TEST_y));
			break;
		}
		case ROTATION_INIT_TYPE::RELATIVE_OFFSET: {
			// set the positions of the components
			spriteComponent1->setPosition(COMPOUND_SPRITE_TEST_X, COMPOUND_SPRITE_TEST_y);
			spriteComponent2->setPosition(COMPOUND_SPRITE_TEST_X, COMPOUND_SPRITE_TEST_y);
			spriteComponent3->setPosition(COMPOUND_SPRITE_TEST_X, COMPOUND_SPRITE_TEST_y);

			// Create the compound sprite then add all of the components with a relative offset
			displaySprite = std::make_unique<GB::RelativeRotationSprite>(sf::Vector2f(COMPOUND_SPRITE_TEST_X, COMPOUND_SPRITE_TEST_y));
			static_cast<GB::RelativeRotationSprite*>(displaySprite.get())->addComponent(spriteComponent1.get(), { 80, 0 });
			static_cast<GB::RelativeRotationSprite*>(displaySprite.get())->addComponent(spriteComponent2.get(), { 0, 80 });
			static_cast<GB::RelativeRotationSprite*>(displaySprite.get())->addComponent(spriteComponent3.get(), { 0, 0 });
			break;
		}
		case ROTATION_INIT_TYPE::RELATIVE_POSITION: {
			// set the positions of the components
			spriteComponent1->setPosition(COMPOUND_SPRITE_TEST_X + 92, COMPOUND_SPRITE_TEST_y + 12);
			spriteComponent2->setPosition(COMPOUND_SPRITE_TEST_X + 12, COMPOUND_SPRITE_TEST_y + 92);
			spriteComponent3->setPosition(COMPOUND_SPRITE_TEST_X + 12, COMPOUND_SPRITE_TEST_y + 12);

			// create the compound sprite then add all of the components. The components will maintain their
			// positions relative to the compound sprite
			displaySprite = std::make_unique<GB::RelativeRotationSprite>(sf::Vector2f(COMPOUND_SPRITE_TEST_X, COMPOUND_SPRITE_TEST_y));
			displaySprite->addComponent(spriteComponent1.get());
			displaySprite->addComponent(spriteComponent2.get());
			displaySprite->addComponent(spriteComponent3.get());
			break;
		}
		case ROTATION_INIT_TYPE::TEXTURE_BASED_OFFSET: {
			displaySprite = std::make_unique<GB::CompoundSprite>(textureOffsetSprites);
			displaySprite->setPosition(COMPOUND_SPRITE_TEST_X, COMPOUND_SPRITE_TEST_y);
			break;
		}
		default: {
			throw new std::out_of_range("Invalid ROTATION_INIT_TYPE");
		}
	}

	// assign colors and draw
	spriteComponent1->setColor(sf::Color::Magenta);
	spriteComponent2->setColor(sf::Color::White);
	spriteComponent3->setColor(sf::Color::Green);
	setDrawAndUpdateable(true, displaySprite.get());
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
/// Initializes the GUI.
/// </summary>
void ScaleAndRotationDemoRegion::initGUI() {
	// Load the black theme
	tgui::Theme theme("TGUI_Widgets/Black.txt");

	// Get a bound version of the window size
	// Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
	tgui::Layout windowWidth = tgui::bindWidth(*regionGUI);
	tgui::Layout windowHeight = tgui::bindHeight(*regionGUI);

	// Create the background image (picture is of type tgui::Picture::Ptr or std::shared_widget<Picture>)
	tgui::Picture::Ptr picture = tgui::Picture::create("Textures/Backbone2.png");
	picture->setSize(windowWidth, "&.height / 10");
	picture->setPosition(0, 9 * windowHeight / 10.0f);
	regionGUI->add(picture);

	const int NUM_BUTTONS = 4;
	tgui::Layout buttonWidth = windowWidth / (NUM_BUTTONS + NUM_BUTTONS + 1);
	tgui::Layout buttonHeight = windowHeight / 20.0f;
	int buttonIndex = 0;

	// create initMethod1 button
	tgui::Button::Ptr relativePositionCtrButton = tgui::Button::create();
	relativePositionCtrButton->setRenderer(theme.getRenderer("Button"));
	relativePositionCtrButton->setSize(buttonWidth, buttonHeight);
	relativePositionCtrButton->setPosition((2 * buttonIndex + 1) * buttonWidth, windowHeight * 9 / 10.0f);
	relativePositionCtrButton->setText("Relative Position\n    Constructor");
	relativePositionCtrButton->connect("pressed", &ScaleAndRotationDemoRegion::initMethod1CB, this);
	regionGUI->add(relativePositionCtrButton);
	buttonIndex++;

	// create initMethod2 button
	tgui::Button::Ptr relativeOffsetButton = tgui::Button::create();
	relativeOffsetButton->setRenderer(theme.getRenderer("Button"));
	relativeOffsetButton->setSize(buttonWidth, buttonHeight);
	relativeOffsetButton->setPosition((2 * buttonIndex + 1) * buttonWidth, windowHeight * 9 / 10.0f);
	relativeOffsetButton->setText("Relative Offset");
	relativeOffsetButton->connect("pressed", &ScaleAndRotationDemoRegion::initMethod2CB, this);
	regionGUI->add(relativeOffsetButton);
	buttonIndex++;

	// create initMethod3 button
	tgui::Button::Ptr relativePositionButton = tgui::Button::create();
	relativePositionButton->setRenderer(theme.getRenderer("Button"));
	relativePositionButton->setSize(buttonWidth, buttonHeight);
	relativePositionButton->setPosition((2 * buttonIndex + 1) * buttonWidth, windowHeight * 9 / 10.0f);
	relativePositionButton->setText("Relative Position");
	relativePositionButton->connect("pressed", &ScaleAndRotationDemoRegion::initMethod3CB, this);
	regionGUI->add(relativePositionButton);
	buttonIndex++;

	// create initMethod4 button
	tgui::Button::Ptr textureBasedOffsetButton = tgui::Button::create();
	textureBasedOffsetButton->setRenderer(theme.getRenderer("Button"));
	textureBasedOffsetButton->setSize(buttonWidth, buttonHeight);
	textureBasedOffsetButton->setPosition((2 * buttonIndex + 1) * buttonWidth, windowHeight * 9 / 10.0f);
	textureBasedOffsetButton->setText("Texture Offset");
	textureBasedOffsetButton->connect("pressed", &ScaleAndRotationDemoRegion::initMethod4CB, this);
	regionGUI->add(textureBasedOffsetButton);
	buttonIndex++;

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

// private dtr

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
