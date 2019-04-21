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

	// Create and link child regions

	// Create a new NavigationDemoRegion
	NavigationDemoRegion* navigationDemoRegion = new NavigationDemoRegion(window);
	// Make navigationDemoRegion a child of this MainMenuDemoRegion
	addChildRegion(navigationDemoRegion);
	// Store NavigationDemoRegion as a selectableRegion
	selectableRegions.push_back(navigationDemoRegion);

	// Don't create PlatformDemo if the user doesn't want it
	#ifdef GAMEBACKBONE_BUILD_PLATFORM_DEMO
		// Create and link a PlatformDemoRegion to this MainMenuDemoRegion
		PlatformDemoRegion* platformDemoRegion = new PlatformDemoRegion(window);
		addChildRegion(platformDemoRegion);
		selectableRegions.push_back(platformDemoRegion);
	#endif // GAMEBACKBONE_BUILD_PLATFORM_DEMO

	// Create and link a ScaleAndRotationDemoRegion to this MainMenuDemoRegion
	ScaleAndRotationDemoRegion* scaleAndRotationDemoRegion = new ScaleAndRotationDemoRegion(window);
	addChildRegion(scaleAndRotationDemoRegion);
	selectableRegions.push_back(scaleAndRotationDemoRegion);

	// Create and link two RegionChangeDemoRegions to this MainMenuDemoRegion
	RegionChangeDemoRegion* regionChangeRegion1 = new RegionChangeDemoRegion(window, sf::Color::Red, { 300, 300 });
	RegionChangeDemoRegion* regionChangeRegion2 = new RegionChangeDemoRegion(window, sf::Color::Green, { 200, 200 });
	// Make the two RegionChangeDemoRegions neighbors. This allows them to access each other
	// even though there is no parent child relation between them.
	regionChangeRegion1->addNeighborRegion(regionChangeRegion2);
	addChildRegion(regionChangeRegion1);
	addChildRegion(regionChangeRegion2);
	// Only make one of the RegionChangeDemoRegions a selectableRegion
	// The other one will be accessable through this one
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

/// <summary>
/// Registers the callback function for changing the active region and propagates this callback to all of its children.
/// </summary>
/// <param name="newSetActiveRegionCB">The new callback for changing the active region.</param>
void MainMenuDemoRegion::registerSetActiveRegionCB(std::function<void(GameRegion*)> newSetActiveRegionCB) {
	// Register the passed in function on this GameRegion
	GameRegion::registerSetActiveRegionCB(newSetActiveRegionCB);
	// Go through every childRegion and register the function with their GameRegion
	for (GameRegion* childRegion : childRegions) {
		childRegion->registerSetActiveRegionCB(newSetActiveRegionCB);
	}
}

/// <summary>
/// Initializes the GUI.
/// </summary>
void EXE::MainMenuDemoRegion::initGUI() {
	// Load the black theme
	defaultTheme.load("TGUI_Widgets/Black.txt");

	// By setting this as the default theme all widgets created
	// after this point will be created with this theme.
	// After defaultTheme deconstructs all widgets that are using the default
	// theme will be reset to white theme.
	// This is ok for this use case because defaultTheme
	// wont be destructed until the end of the program.
	tgui::Theme::setDefault(&defaultTheme);
	// hide parent classes button
	returnToMenuButton->setVisible(false);
	resetButton->setVisible(false);

	// Get a bound version of the window size
	// Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
	tgui::Layout windowWidth = tgui::bindWidth(*regionGUI);
	tgui::Layout windowHeight = tgui::bindHeight(*regionGUI);

	// Create the background image (picture is of type tgui::Picture::Ptr)
	tgui::Picture::Ptr background = tgui::Picture::create(R"(Textures/Backbone2.png)");
	background->setSize(windowWidth, windowHeight);
	background->setPosition(0,0);
	regionGUI->add(background);

	// Add buttons for each demo region
	std::vector<tgui::Button::Ptr> demoRegionButtons;

	// Areate navigation region button
	// Create a new button
	tgui::Button::Ptr navigationRegionButton = tgui::Button::create();
	// Give the button its text
	navigationRegionButton->setText("Navigation Demo");
	// Connect the button to its callback
	navigationRegionButton->connect("pressed", &MainMenuDemoRegion::navigationRegionCB, this);
	// Add the button to the vector of buttons for changing to demo regions
	demoRegionButtons.push_back(navigationRegionButton);

	// Create Scale and Rotation Demo button
	tgui::Button::Ptr scaleAndRotationDemoButton = tgui::Button::create();
	scaleAndRotationDemoButton->setText("Scale and Rotation Demo");
	scaleAndRotationDemoButton->connect("pressed", &MainMenuDemoRegion::scaleAndRotationDemoCB, this);
	demoRegionButtons.push_back(scaleAndRotationDemoButton);

	// Create region change demo button
	tgui::Button::Ptr regionChangeButton = tgui::Button::create();
	regionChangeButton->setText("Region Change Demo");
	regionChangeButton->connect("pressed", &MainMenuDemoRegion::regionChangeDemoCB, this);
	demoRegionButtons.push_back(regionChangeButton);

	// Don't create a button for PlatformDemo if the user doesn't want it
	#ifdef GAMEBACKBONE_BUILD_PLATFORM_DEMO
		// Create Platform region button
		tgui::Button::Ptr platformRegionButton = tgui::Button::create();
		platformRegionButton->setText("Platform Demo");
		platformRegionButton->connect("pressed", &MainMenuDemoRegion::platformRegionCB, this);
		demoRegionButtons.push_back(platformRegionButton);
	#endif // GAMEBACKBONE_BUILD_PLATFORM_DEMO

	// Size and place buttons
	// The number of buttons will be needed a few times. Calculate it once.
	const std::size_t demoRegionButtonCount = demoRegionButtons.size();
	// The buttons should be 1/4 the width of the screen
	tgui::Layout buttonWidth = windowWidth / 4.0f;
	// Adjust the height of the buttons so that they can all fit on screen
	tgui::Layout buttonHeight = windowHeight / ((float)demoRegionButtonCount * 2 + 1);
	for (std::size_t i = 0; i < demoRegionButtonCount; ++i)
	{
		// Save some repetitive typing
		auto& currentButton = demoRegionButtons.at(i);
		// Set the size of the button
		currentButton->setSize(buttonWidth, buttonHeight);
		// Place the button in the middle of the screen
		tgui::Layout horizontalPosition = windowWidth / 2.0f - buttonWidth / 2.0f;
		// Space the buttons apart
		tgui::Layout verticalPosition = (2 * i + 1) * buttonHeight;
		currentButton->setPosition(horizontalPosition, verticalPosition);
		// Add the buttons to the gui
		regionGUI->add(currentButton);
	}
}

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
