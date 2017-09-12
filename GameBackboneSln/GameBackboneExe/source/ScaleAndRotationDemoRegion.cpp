#include <iostream>

#define _USE_MATH_DEFINES

#include <ScaleAndRotationDemoRegion.h>
#include <Backbone/RelativeRotationSprite.h>
#include <Navigation/NavigationTools.h>

#include <TGUI/TGUI.hpp>

#include <SFML/Graphics.hpp>

#include <string>
#include <math.h>

using namespace EXE;

/// <summary>
/// Initializes a new instance of the <see cref="ScaleAndRotationDemoRegion"/> class.
/// </summary>
ScaleAndRotationDemoRegion::ScaleAndRotationDemoRegion() {
	selectedInitMethod = ROTATION_INIT_TYPE::RELATIVE_POSITION_CONSTRUCTOR;
	init();
	//initialize GUI
	try {
		// Load the widgets
		initGUI();
	}
	catch (const tgui::Exception& e) {
		std::cerr << "Failed to load GUI: " << e.what() << std::endl;
	}
}

/// <summary>
/// Initializes a new instance of the <see cref="ScaleAndRotationDemoRegion"/> class.
/// </summary>
/// <param name="window">The window that will be attached to this instances GUI.</param>
ScaleAndRotationDemoRegion::ScaleAndRotationDemoRegion(sf::RenderWindow & window) : DemoRegion(window) {
	init();
	//initialize GUI
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
	destroy();
}

/// <summary>
/// Executes a single cycle of the main logic loop for this region.
/// </summary>
void ScaleAndRotationDemoRegion::behave(sf::Time currentTime) {

	sf::Int64 msPassed = currentTime.asMilliseconds() - lastUpdateTime.asMicroseconds();

	lastUpdateTime = currentTime;
}

/// <summary>
/// Handles mouse click logic.
/// </summary>
/// <param name="newPosition">The position of the click.</param>
/// <param name="button">The mouse button clicked button.</param>
void ScaleAndRotationDemoRegion::handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button) {
	if (button == sf::Mouse::Left) {
		compSprite->setPosition(newPosition);
	}
}


/// <summary>
/// Handles mouse wheel scroll logic.
/// </summary>
/// <param name="scrollDelta">The change in the wheel.</param>
void ScaleAndRotationDemoRegion::handleWheelScroll(float scrollDelta) {
	compSprite->scale({powf(1.25, scrollDelta) , powf(1.25, scrollDelta)});
}


/// <summary>
/// Handles the mouse drag.
/// Rotates the compound sprite to face the mouse position
/// </summary>
/// <param name="mousePosition">The mouse position.</param>
void ScaleAndRotationDemoRegion::handleMouseMove(sf::Vector2f mousePosition) {
	float angle = atan2f(mousePosition.y - compSprite->getPosition().y, mousePosition.x - compSprite->getPosition().x) * 180 / (float)M_PI;
	compSprite->setRotation(angle);
}

/// <summary>
/// Initializes this instance.
/// </summary>
void ScaleAndRotationDemoRegion::init() {

	//init textures
	std::string arrowPath("..\\..\\Textures\\SmallArrow.png");
	std::string rotationArrowCenterPath("..//..//Textures/RotationArrowCenter.png");
	std::string rotationArrowLowPath("..//..//Textures/RotationArrowLow.png");
	std::string rotationArrowLeftPath("..//..//Textures/RotationArrowLeft.png");
	navigatorTexture = new sf::Texture();
	navigatorTexture->loadFromFile(arrowPath);
	rotationArrowCenterTexture = new sf::Texture();
	
	// component sprites
	const float COMPOUND_SPRITE_TEST_X = 400;
	const float COMPOUND_SPRITE_TEST_y = 400;
	compComponent1 = new sf::Sprite(*navigatorTexture);
	compComponent2 = new sf::Sprite(*navigatorTexture);
	compComponent3 = new sf::Sprite(*navigatorTexture);

	std::vector<sf::Sprite*> spriteVector = {compComponent1 , compComponent2, compComponent3 };

		

	switch (selectedInitMethod) {
	case ROTATION_INIT_TYPE::RELATIVE_POSITION_CONSTRUCTOR:
	{
		// set the positions of the components
		compComponent1->setPosition(COMPOUND_SPRITE_TEST_X + 92, COMPOUND_SPRITE_TEST_y + 12);
		compComponent2->setPosition(COMPOUND_SPRITE_TEST_X + 12, COMPOUND_SPRITE_TEST_y + 92);
		compComponent3->setPosition(COMPOUND_SPRITE_TEST_X + 12, COMPOUND_SPRITE_TEST_y + 12);

		// Create the compound sprite by adding the components to the constructor
		compSprite = new GB::RelativeRotationSprite(spriteVector, { COMPOUND_SPRITE_TEST_X, COMPOUND_SPRITE_TEST_y });
		break;
	}
	case ROTATION_INIT_TYPE::RELATIVE_OFFSET:
	{
		// set the positions of the components
		compComponent1->setPosition(COMPOUND_SPRITE_TEST_X, COMPOUND_SPRITE_TEST_y);
		compComponent2->setPosition(COMPOUND_SPRITE_TEST_X, COMPOUND_SPRITE_TEST_y);
		compComponent3->setPosition(COMPOUND_SPRITE_TEST_X, COMPOUND_SPRITE_TEST_y);

		// Create the compound sprite then add all of the components with a relative offset
		compSprite = new GB::RelativeRotationSprite({ COMPOUND_SPRITE_TEST_X, COMPOUND_SPRITE_TEST_y });
		static_cast<GB::RelativeRotationSprite*>(compSprite)->addComponent(compComponent1, { 80, 0 });
		static_cast<GB::RelativeRotationSprite*>(compSprite)->addComponent(compComponent2, { 0, 80 });
		static_cast<GB::RelativeRotationSprite*>(compSprite)->addComponent(compComponent3, { 0, 0 });
		break;
	}
	case ROTATION_INIT_TYPE::RELATIVE_POSITION:
	{
		// set the positions of the components
		compComponent1->setPosition(COMPOUND_SPRITE_TEST_X + 92, COMPOUND_SPRITE_TEST_y + 12);
		compComponent2->setPosition(COMPOUND_SPRITE_TEST_X + 12, COMPOUND_SPRITE_TEST_y + 92);
		compComponent3->setPosition(COMPOUND_SPRITE_TEST_X + 12, COMPOUND_SPRITE_TEST_y + 12);

		// create the compound sprite then add all of the components. The components will maintain their
		// positions relative to the compound sprite
		compSprite = new GB::RelativeRotationSprite({ COMPOUND_SPRITE_TEST_X, COMPOUND_SPRITE_TEST_y });
		compSprite->addComponent(compComponent1);
		compSprite->addComponent(compComponent2);
		compSprite->addComponent(compComponent3);
		break;
	}
	case ROTATION_INIT_TYPE::TEXTURE_BASED_OFFSET:

	}

	// assign colors and draw
	compComponent1->setColor(sf::Color::Magenta);
	compComponent2->setColor(sf::Color::White);
	compComponent3->setColor(sf::Color::Green);
	setDrawAndUpdateable(true, compSprite);
}


/// <summary>
/// Resets this instance.
/// frees and / or reinitializes all members of this instance that impact the demo.
/// </summary>
void ScaleAndRotationDemoRegion::reset() {
	// free all dynamic memory
	destroy();

	// reset non-dynamic members
	lastUpdateTime = sf::Time::Zero;
	clearDrawable();
	clearUpdatable();

	// reinitialize
	init();
}

/// <summary>
/// Initializes the GUI.
/// </summary>
void ScaleAndRotationDemoRegion::initGUI() {
	// Load the black theme
	tgui::Theme::Ptr theme = tgui::Theme::create("TGUI_Widgets/Black.txt");

	// Get a bound version of the window size
	// Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
	tgui::Layout windowWidth = tgui::bindWidth(*regionGUI);
	tgui::Layout windowHeight = tgui::bindHeight(*regionGUI);

	// Create the background image (picture is of type tgui::Picture::Ptr or std::shared_widget<Picture>)
	tgui::Picture::Ptr picture = tgui::Picture::create("..\\..\\Textures\\Backbone2.png");
	picture->setSize(tgui::bindMax(800, windowWidth), tgui::bindMax(200, windowHeight / 10.0f));
	picture->setPosition(0, 9 * windowHeight / 10.0f);
	regionGUI->add(picture);

	// create initMethod1 button
	tgui::Button::Ptr navigator1Button = theme->load("Button");
	navigator1Button->setSize(windowWidth / 10.0f, windowHeight / 20.0f);
	navigator1Button->setPosition(4 * windowWidth / 10.0f, windowHeight * 9 / 10.0f);
	navigator1Button->setText("Relative Position\n    Constructor");
	navigator1Button->connect("pressed", &ScaleAndRotationDemoRegion::initMethod1CB, this);
	regionGUI->add(navigator1Button);

	// create initMethod2 button
	tgui::Button::Ptr navigator2Button = theme->load("Button");
	navigator2Button->setSize(windowWidth / 10.0f, windowHeight / 20.0f);
	navigator2Button->setPosition(5 * windowWidth / 10.0f, windowHeight * 9 / 10.0f);
	navigator2Button->setText("Relative Offset");
	navigator2Button->connect("pressed", &ScaleAndRotationDemoRegion::initMethod2CB, this);
	regionGUI->add(navigator2Button);

	// create initMethod3 button
	tgui::Button::Ptr allNavigatorsButton = theme->load("Button");
	allNavigatorsButton->setSize(windowWidth / 10.0f, windowHeight / 20.0f);
	allNavigatorsButton->setPosition(6 * windowWidth / 10.0f, windowHeight * 9 / 10.0f);
	allNavigatorsButton->setText("Relative Position");
	allNavigatorsButton->connect("pressed", &ScaleAndRotationDemoRegion::initMethod3CB, this);
	regionGUI->add(allNavigatorsButton);
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

// private dtr

/// <summary>
/// Frees all dynamically allocated memory in this instance
/// </summary>
void ScaleAndRotationDemoRegion::destroy() {
	//delete textures
	delete navigatorTexture;
	navigatorTexture = nullptr;
	delete rotationArrowCenterTexture;
	rotationArrowCenterTexture = nullptr;

	delete compComponent1;
	compComponent1 = nullptr;
	delete compComponent2;
	compComponent2 = nullptr;
	delete compSprite;
	compSprite = nullptr;
}
