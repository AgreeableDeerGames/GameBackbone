#include <DemoSelectionRegion.h>

using namespace EXE;

// Ctr / Dtr

DemoSelectionRegion::DemoSelectionRegion(sf::RenderWindow & window) : DemoRegion(window) {
	initGUI();
}

EXE::DemoSelectionRegion::~DemoSelectionRegion() {
}

// initialization

#define BUTTON_WIDTH(windowWidth) windowWidth / 4.0f
#define BUTTON_HEIGHT(windowHeight) windowHeight / 4.0f

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
	//navigationRegionButton->connect("pressed", &NavigationDemoRegion::Navigator1CB, this);
	regionGUI->add(navigationRegionButton);

		// create Swirly Sprite Demo button
	tgui::Button::Ptr RotatingCompoundSpriteDemoButton = theme->load("Button");
	RotatingCompoundSpriteDemoButton->setSize(BUTTON_WIDTH(windowWidth), BUTTON_HEIGHT(windowHeight));
	RotatingCompoundSpriteDemoButton->setPosition(windowWidth / 2.0f, 3.0f * windowHeight / 4.0f);
	RotatingCompoundSpriteDemoButton->setText("Rotating Compound\n Sprite Demo");
	//RotatingCompoundSpriteDemoButton->connect("pressed", &NavigationDemoRegion::Navigator1CB, this);
	regionGUI->add(RotatingCompoundSpriteDemoButton);

}
