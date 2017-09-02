#include <iostream>

#define _USE_MATH_DEFINES

#include <SwirlyDemoRegion.h>
#include <Backbone/RelativeRotationSprite.h>
#include <Navigation/NavigationTools.h>

#include <TGUI/TGUI.hpp>

#include <SFML/Graphics.hpp>

#include <string>
#include <math.h>

using namespace GB;

/// <summary>
/// Initializes a new instance of the <see cref="SwirlyDemoRegion"/> class.
/// </summary>
SwirlyDemoRegion::SwirlyDemoRegion() {
	init();
}

/// <summary>
/// Initializes a new instance of the <see cref="SwirlyDemoRegion"/> class.
/// </summary>
/// <param name="window">The window that will be attached to this instances GUI.</param>
SwirlyDemoRegion::SwirlyDemoRegion(sf::RenderWindow & window) : GameRegion(window) {
	init();
}

/// <summary>
/// Finalizes an instance of the <see cref="SwirlyDemoRegion"/> class.
/// </summary>
SwirlyDemoRegion::~SwirlyDemoRegion() {
	//delete textures
	delete navigatorTexture;
	navigatorTexture = nullptr;

	delete compComponent1;
	compComponent1 = nullptr;
	delete compComponent2;
	compComponent2 = nullptr;
	delete compSprite;
	compSprite = nullptr;
}

/// <summary>
/// Executes a single cycle of the main logic loop for this region.
/// </summary>
void SwirlyDemoRegion::behave(sf::Time currentTime) {

	sf::Int64 msPassed = currentTime.asMilliseconds() - lastUpdateTime.asMicroseconds();

	lastUpdateTime = currentTime;
}

/// <summary>
/// Handles mouse click logic.
/// </summary>
/// <param name="newPosition">The position of the click.</param>
/// <param name="button">The mouse button clicked button.</param>
void SwirlyDemoRegion::handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button) {
	if (button == sf::Mouse::Left) {
		compSprite->setPosition(newPosition);
	}
}


/// <summary>
/// Handles mouse wheel scroll logic.
/// </summary>
/// <param name="scrollDelta">The change in the wheel.</param>
void SwirlyDemoRegion::handleWheelScroll(int scrollDelta) {
	compSprite->scale({powf(1.25, (float)scrollDelta) , powf(1.25, (float)scrollDelta)});
}


/// <summary>
/// Handles the mouse drag.
/// Rotates the compound sprite to face the mouse position
/// </summary>
/// <param name="mousePosition">The mouse position.</param>
void SwirlyDemoRegion::handleMouseMove(sf::Vector2f mousePosition) {
	float angle = atan2f(mousePosition.y - compSprite->getPosition().y, mousePosition.x - compSprite->getPosition().x) * 180 / (float)M_PI;
	compSprite->setRotation(angle);
}

/// <summary>
/// Initializes this instance.
/// </summary>
void GB::SwirlyDemoRegion::init() {

	//init textures
	std::string arrowPath("..\\..\\Textures\\SmallArrow.png");
	navigatorTexture = new sf::Texture();
	navigatorTexture->loadFromFile(arrowPath);
	
	//compound sprite
	const float COMPOUND_SPRITE_TEST_X = 400;
	const float COMPOUND_SPRITE_TEST_y = 400;
	compComponent1 = new sf::Sprite(*navigatorTexture);
	compComponent2 = new sf::Sprite(*navigatorTexture);
	compComponent3 = new sf::Sprite(*navigatorTexture);

	std::vector<sf::Sprite*> spriteVector = {compComponent1 , compComponent2, compComponent3 };


	// This is the working version of addComponent using the ContructorLand
	compComponent1->setPosition(COMPOUND_SPRITE_TEST_X + 92, COMPOUND_SPRITE_TEST_y + 12);
	compComponent2->setPosition(COMPOUND_SPRITE_TEST_X + 12, COMPOUND_SPRITE_TEST_y + 92);
	compComponent3->setPosition(COMPOUND_SPRITE_TEST_X + 12, COMPOUND_SPRITE_TEST_y + 12);
	compSprite = new RelativeRotationSprite(spriteVector, { COMPOUND_SPRITE_TEST_X, COMPOUND_SPRITE_TEST_y });

	/*
	// This is the working version of addComponent using the relative offset
	compSprite = new RelativeRotationSprite({ COMPOUND_SPRITE_TEST_X, COMPOUND_SPRITE_TEST_y });
	compComponent1->setPosition(COMPOUND_SPRITE_TEST_X, COMPOUND_SPRITE_TEST_y);
	compComponent2->setPosition(COMPOUND_SPRITE_TEST_X, COMPOUND_SPRITE_TEST_y);
	compComponent3->setPosition(COMPOUND_SPRITE_TEST_X, COMPOUND_SPRITE_TEST_y);
	static_cast<RelativeRotationSprite*>(compSprite)->addComponent(compComponent1, { 80, 0 });
	static_cast<RelativeRotationSprite*>(compSprite)->addComponent(compComponent2, { 0, 80 });
	static_cast<RelativeRotationSprite*>(compSprite)->addComponent(compComponent3, { 0, 0 });*/

	/*
	// This is the working version of addComponent using the relative position 
	compSprite = new RelativeRotationSprite({ COMPOUND_SPRITE_TEST_X, COMPOUND_SPRITE_TEST_y });
	compComponent1->setPosition(COMPOUND_SPRITE_TEST_X + 80, COMPOUND_SPRITE_TEST_y);
	compComponent2->setPosition(COMPOUND_SPRITE_TEST_X, COMPOUND_SPRITE_TEST_y + 80);
	compComponent3->setPosition(COMPOUND_SPRITE_TEST_X, COMPOUND_SPRITE_TEST_y);
	static_cast<RelativeRotationSprite*>(compSprite)->addComponent(compComponent1);
	static_cast<RelativeRotationSprite*>(compSprite)->addComponent(compComponent2);
	static_cast<RelativeRotationSprite*>(compSprite)->addComponent(compComponent3);*/



	compComponent1->setColor(sf::Color::Magenta);
	compComponent2->setColor(sf::Color::White);
	compComponent3->setColor(sf::Color::Green);

	setDrawAndUpdateable(true, compSprite);


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
/// Initializes the GUI.
/// </summary>
void SwirlyDemoRegion::initGUI() {
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
}
