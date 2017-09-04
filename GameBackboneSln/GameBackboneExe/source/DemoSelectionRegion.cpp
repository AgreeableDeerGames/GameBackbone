#include <DemoSelectionRegion.h>
#include <NavigationDemoRegion.h>
#include <SwirlyDemoRegion.h>

using namespace EXE;

// Ctr / Dtr


/// <summary>
/// Initializes a new instance of the <see cref="DemoSelectionRegion"/> class.
/// Creates all required child regions.
/// </summary>
/// <param name="window">The window.</param>
DemoSelectionRegion::DemoSelectionRegion(sf::RenderWindow & window) : DemoRegion(window) {
	initGUI();

	// create and link child regions
	addChildRegion(new NavigationDemoRegion(window));
	addChildRegion(new SwirlyDemoRegion(window));
}


/// <summary>
/// Finalizes an instance of the <see cref="DemoSelectionRegion"/> class.
/// Frees memory for every child region of this instance.
/// </summary>
DemoSelectionRegion::~DemoSelectionRegion() {
	
	// free all children
	auto it = childRegions.begin();
	while (it != childRegions.end()) {
		auto tempIt = it;
		++it;
		delete *tempIt;
	}
}

// internal behavior modification

/// <summary>
/// Registers the callback function for changing the active region and propagates this callback to all of its children.
/// </summary>
/// <param name="newSetActiveRegionCB">The new callback for changing the active region..</param>
void DemoSelectionRegion::registerSetActiveRegionCB(std::function<void(GameRegion*)> newSetActiveRegionCB) {
	GameRegion::registerSetActiveRegionCB(newSetActiveRegionCB);
	for (GameRegion* childRegion : childRegions) {
		childRegion->registerSetActiveRegionCB(newSetActiveRegionCB);
	}
}

// initialization

#define BUTTON_WIDTH(windowWidth) windowWidth / 4.0f
#define BUTTON_HEIGHT(windowHeight) windowHeight / 4.0f

/// <summary>
/// Initializes the GUI.
/// </summary>
void EXE::DemoSelectionRegion::initGUI() {
	// Load the black theme
	tgui::Theme::Ptr theme = tgui::Theme::create("TGUI_Widgets/Black.txt");

	// Get a bound version of the window size
	// Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
	tgui::Layout windowWidth = tgui::bindWidth(*regionGUI);
	tgui::Layout windowHeight = tgui::bindHeight(*regionGUI);

	// Create the background image (picture is of type tgui::Picture::Ptr or std::shared_widget<Picture>)
	tgui::Picture::Ptr background = tgui::Picture::create(R"(../../Textures/Backbone2.png)");
	background->setSize(windowWidth, windowHeight);
	background->setPosition(0,0);
	regionGUI->add(background);

	// create buttons for regions

		// create Navigation region button
	tgui::Button::Ptr navigationRegionButton = theme->load("Button");
	navigationRegionButton->setSize(BUTTON_WIDTH(windowWidth), BUTTON_HEIGHT(windowHeight));
	navigationRegionButton->setPosition(windowWidth / 2.0f, 2.0f *windowHeight / 4.0f);
	navigationRegionButton->setText("Navigation Demo");
	navigationRegionButton->connect("pressed", &DemoSelectionRegion::navigationRegionCB, this);
	regionGUI->add(navigationRegionButton);

		// create Swirly Sprite Demo button
	tgui::Button::Ptr swirlyDemoButton = theme->load("Button");
	swirlyDemoButton->setSize(BUTTON_WIDTH(windowWidth), BUTTON_HEIGHT(windowHeight));
	swirlyDemoButton->setPosition(windowWidth / 2.0f, 3.0f * windowHeight / 4.0f);
	swirlyDemoButton->setText("Swirly Sprite Demo");
	swirlyDemoButton->connect("pressed", &DemoSelectionRegion::swirlyDemoCB, this);
	regionGUI->add(swirlyDemoButton);

}

// gui callbacks

/// <summary>
/// Callback that is fired when the navigationRegionButton is clicked.
/// Sets the active region to the first child of this region (which should always be a NavigationDemoRegion)
/// </summary>
void DemoSelectionRegion::navigationRegionCB() {
	setActiveRegionCB(childRegions.front());
}

/// <summary>
/// Callback that is fired when the swirlyDemoButton is clicked.
/// Sets the active region to the second child of this region (which should always be a NavigationDemoRegion)
/// </summary>
void DemoSelectionRegion::swirlyDemoCB() {
	setActiveRegionCB(*(++childRegions.begin()));
}
