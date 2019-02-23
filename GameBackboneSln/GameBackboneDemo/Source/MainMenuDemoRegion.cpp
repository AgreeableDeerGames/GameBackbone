#include <GameBackboneDemo/MainMenuDemoRegion.h>
#include <GameBackboneDemo/NavigationDemoRegion.h>
#include <GameBackboneDemo/PlatformDemoRegion.h>
#include <GameBackboneDemo/RegionChangeDemoRegion.h>
#include <GameBackboneDemo/ScaleAndRotationDemoRegion.h>

using namespace EXE;

// Ctr / Dtr


/// <summary>
/// Initializes a new instance of the <see cref="MainMenuDemoRegion"/> class.
/// Creates all required child regions.
/// </summary>
/// <param name="window">The window.</param>
MainMenuDemoRegion::MainMenuDemoRegion(sf::RenderWindow & window) : DemoRegion(window) {
	initGUI();

	// create and link child regions
	NavigationDemoRegion* navigationDemoRegion = new NavigationDemoRegion(window);
	addChildRegion(navigationDemoRegion);
	selectableRegions.push_back(navigationDemoRegion);

	PlatformDemoRegion* platformDemoRegion = new PlatformDemoRegion(window);
	addChildRegion(platformDemoRegion);
	selectableRegions.push_back(platformDemoRegion);

	ScaleAndRotationDemoRegion* scaleAndRotationDemoRegion = new ScaleAndRotationDemoRegion(window);
	addChildRegion(scaleAndRotationDemoRegion);
	selectableRegions.push_back(scaleAndRotationDemoRegion);

	RegionChangeDemoRegion* regionChangeRegion1 = new RegionChangeDemoRegion(window, sf::Color::Red);
	RegionChangeDemoRegion* regionChangeRegion2 = new RegionChangeDemoRegion(window, sf::Color::Green);
	regionChangeRegion1->addNeighborRegion(regionChangeRegion2);
	addChildRegion(regionChangeRegion1);
	addChildRegion(regionChangeRegion2);
	selectableRegions.push_back(regionChangeRegion1);

}


/// <summary>
/// Finalizes an instance of the <see cref="MainMenuDemoRegion"/> class.
/// Frees memory for every child region of this instance.
/// </summary>
MainMenuDemoRegion::~MainMenuDemoRegion() {
	// free all children
	for (int ii = childRegions.size() - 1; ii >= 0; ii--) {
		delete childRegions[ii];
	}
}

// internal behavior modification

/// <summary>
/// Registers the callback function for changing the active region and propagates this callback to all of its children.
/// </summary>
/// <param name="newSetActiveRegionCB">The new callback for changing the active region.</param>
void MainMenuDemoRegion::registerSetActiveRegionCB(std::function<void(GameRegion*)> newSetActiveRegionCB) {
	GameRegion::registerSetActiveRegionCB(newSetActiveRegionCB);
	for (GameRegion* childRegion : childRegions) {
		childRegion->registerSetActiveRegionCB(newSetActiveRegionCB);
	}
}

// initialization

/// <summary>
/// Initializes the GUI.
/// </summary>
void EXE::MainMenuDemoRegion::initGUI() {
	// Load the black theme
	tgui::Theme theme("TGUI_Widgets/Black.txt");

	// hide parent classes button
	returnToMenuButton->setVisible(false);
	resetButton->setVisible(false);

	// Get a bound version of the window size
	// Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
	tgui::Layout windowWidth = tgui::bindWidth(*regionGUI);
	tgui::Layout windowHeight = tgui::bindHeight(*regionGUI);

	// Create the background image (picture is of type tgui::Picture::Ptr or std::shared_widget<Picture>)
	tgui::Picture::Ptr background = tgui::Picture::create(R"(Textures/Backbone2.png)");
	background->setSize(windowWidth, windowHeight);
	background->setPosition(0,0);
	regionGUI->add(background);

	// create buttons for regions
	tgui::Layout buttonWidth = windowWidth / 4.0f;
	tgui::Layout buttonHeight = windowHeight / 9.0f;

	// create Navigation region button
	tgui::Button::Ptr navigationRegionButton = tgui::Button::create();
	navigationRegionButton->setRenderer(theme.getRenderer("Button"));
	navigationRegionButton->setSize(buttonWidth, buttonHeight);
	navigationRegionButton->setPosition(windowWidth / 2.0f - buttonWidth / 2.0f, 1.0f *windowHeight / 9.0f);
	navigationRegionButton->setText("Navigation Demo");
	navigationRegionButton->connect("pressed", &MainMenuDemoRegion::navigationRegionCB, this);
	regionGUI->add(navigationRegionButton);

	// create Platform region button
	tgui::Button::Ptr platformRegionButton = tgui::Button::create();
	platformRegionButton->setRenderer(theme.getRenderer("Button"));
	platformRegionButton->setSize(buttonWidth, buttonHeight);
	platformRegionButton->setPosition(windowWidth / 2.0f - buttonWidth / 2.0f, 3.0f *windowHeight / 9.0f);
	platformRegionButton->setText("Platform Demo");
	platformRegionButton->connect("pressed", &MainMenuDemoRegion::platformRegionCB, this);
	regionGUI->add(platformRegionButton);

	// create Scale and Rotation Demo button
	tgui::Button::Ptr scaleAndRotationDemoButton = tgui::Button::create();
	scaleAndRotationDemoButton->setRenderer(theme.getRenderer("Button"));
	scaleAndRotationDemoButton->setSize(buttonWidth, buttonHeight);
	scaleAndRotationDemoButton->setPosition(windowWidth / 2.0f - buttonWidth / 2.0f, 5.0f * windowHeight / 9.0f);
	scaleAndRotationDemoButton->setText("Scale and Rotation Demo");
	scaleAndRotationDemoButton->connect("pressed", &MainMenuDemoRegion::scaleAndRotationDemoCB, this);
	regionGUI->add(scaleAndRotationDemoButton);

	// create region change demo button
	tgui::Button::Ptr regionChangeButton = tgui::Button::create();
	regionChangeButton->setRenderer(theme.getRenderer("Button"));
	regionChangeButton->setSize(buttonWidth, buttonHeight);
	regionChangeButton->setPosition(windowWidth / 2.0f - buttonWidth / 2.0f, 7.0f * windowHeight / 9.0f);
	regionChangeButton->setText("Region Change Demo");
	regionChangeButton->connect("pressed", &MainMenuDemoRegion::regionChangeDemoCB, this);
	regionGUI->add(regionChangeButton);
}

// gui callbacks

/// <summary>
/// Callback that is fired when the navigationRegionButton is clicked.
/// Sets the active region to the first child of this region (which should always be a NavigationDemoRegion)
/// </summary>
void MainMenuDemoRegion::navigationRegionCB() {
	setActiveRegionCB(childRegions[DEMO_OPTIONS_TYPE::NAVIGATION_DEMO]);
}

/// <summary>
/// Callback that is fired when the platformRegionButton is clicked.
/// Sets the active region to the first child of this region (which should always be a PlatformDemoRegion)
/// </summary>
void MainMenuDemoRegion::platformRegionCB() {
	setActiveRegionCB(childRegions[DEMO_OPTIONS_TYPE::PLATFORM_DEMO]);
}

/// <summary>
/// Callback that is fired when the swirlyDemoButton is clicked.
/// Sets the active region to the second child of this region (which should always be a ScaleAndRotationDemoRegion)
/// </summary>
void MainMenuDemoRegion::scaleAndRotationDemoCB() {
	setActiveRegionCB(childRegions[DEMO_OPTIONS_TYPE::SCALE_ROTATION_DEMO]);
}

/// <summary>
/// Callback that is fired when the regionChangeButton is clicked.
/// Sets the active region to the third child of this region (which should always be a RegionChangeDemoRegion)
/// </summary>
void MainMenuDemoRegion::regionChangeDemoCB() {
	setActiveRegionCB(selectableRegions[DEMO_OPTIONS_TYPE::REGION_CHANGE_DEMO]);
}
