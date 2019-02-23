#include <iostream>

#define _USE_MATH_DEFINES

#include <GameBackboneDemo/NavigationDemoRegion.h>

#include <GameBackbone/Navigation/NavigationTools.h>
#include <GameBackbone/Util/Point.h>
#include <GameBackbone/Util/UtilMath.h>

#include <TGUI/TGUI.hpp>

#include <SFML/Graphics.hpp>

#include <string>
#include <math.h>

using namespace EXE;

/// <summary>
/// Initializes a new instance of the <see cref="NavigationDemoRegion"/> class.
/// </summary>
NavigationDemoRegion::NavigationDemoRegion() {
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
/// Initializes a new instance of the <see cref="NavigationDemoRegion"/> class.
/// </summary>
/// <param name="window">The window that will be attached to this instances GUI.</param>
NavigationDemoRegion::NavigationDemoRegion(sf::RenderWindow & window) : DemoRegion(window) {
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
/// Finalizes an instance of the <see cref="NavigationDemoRegion"/> class.
/// </summary>
NavigationDemoRegion::~NavigationDemoRegion() {
	destroy();
}

/// <summary>
/// Executes a single cycle of the main logic loop for this region.
/// </summary>
void NavigationDemoRegion::behave(sf::Time currentTime) {



	//move navigators
	sf::Uint64 msPassed = currentTime.asMilliseconds() - lastUpdateTime.asMilliseconds();

	switch (selectedNavigatorOption)
	{
	case EXE::NAVIGATOR_1:
	{
		GB::moveSpriteAlongPath(*navigators[0], paths[0], msPassed, 1);
		break;
	}
	case EXE::NAVIGATOR_2:
	{
		GB::moveSpriteAlongPath(*navigators[1], paths[1], msPassed, 1);
		break;
	}
	case EXE::ALL_NAVIGATORS:
	{
		std::vector<float> speeds(navigators.size(), 1.0f);
		for (size_t i = 0; i < navigators.size(); i++) {
			GB::moveSpriteAlongPath(*navigators[i], paths[i], msPassed, speeds[i]);
		}
		break;
	}
	default:
		break;
	}

	lastUpdateTime = currentTime;
}

/// <summary>
/// Handles mouse click logic.
/// </summary>
/// <param name="newPosition">The position of the click.</param>
/// <param name="button">The mouse button clicked button.</param>
void NavigationDemoRegion::handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button) {
	if (button == sf::Mouse::Left) {
		std::vector<GB::PathRequest> pathRequests(navigators.size());

		//create each path request
		for (size_t i = 0; i < navigators.size(); i++) {
			sf::Sprite* currentNavigator = navigators[i];
			GB::Point2D<int> startingPos = coordinateConverter.convertCoordToNavGrid(currentNavigator->getPosition());
			GB::Point2D<int> endingPos = coordinateConverter.convertCoordToNavGrid(newPosition);
			pathRequests[i] = GB::PathRequest{ startingPos, endingPos, 1, 0 };
		}

		//path-find
		std::vector<GB::NavGridCoordinatePath> pathsReturn;
		pathsReturn.resize(pathRequests.size());
		regionPathfinder.pathFind(pathRequests, &pathsReturn);

		//convert paths to window coordinates
		paths.clear();
		paths.resize(pathsReturn.size());
		for (unsigned int i = 0; i < navigators.size(); i++) {
			paths[i] = std::make_shared<std::deque<sf::Vector2f>>(coordinateConverter.convertPathToWindow(pathsReturn[i]));
		}
	}
}


/// <summary>
/// Handles the mouse drag.
/// Rotates the compound sprite to face the mouse position
/// </summary>
/// <param name="mousePosition">The mouse position.</param>
void NavigationDemoRegion::handleMouseMove(sf::Vector2f mousePosition) {

}

/// <summary>
/// Initializes this instance.
/// </summary>
void NavigationDemoRegion::init() {
	//init storage
	navGrid = new GB::NavigationGrid(NAV_GRID_DIM);
	GB::initAllNavigationGridValues(*navGrid, NavigationDemoData());
	regionPathfinder.setNavigationGrid(navGrid);


	//init textures
	std::string arrowPath(R"(Textures/SmallArrow.png)");
	navigatorTexture = new sf::Texture();
	navigatorTexture->loadFromFile(arrowPath);
	std::string navigationGridPath(R"(Textures/NavigationGrid.png)");
	gridTexture = new sf::Texture();
	gridTexture->loadFromFile(navigationGridPath);

	//internal function logic
	std::vector<GB::Point2D<int>> nonBlockableGridSquares;


	//init navigators

	//create navigators and add to respective arrays
	sf::Sprite* navigator1 = new sf::Sprite(*navigatorTexture);
	sf::Sprite* navigator2 = new sf::Sprite(*navigatorTexture);
	navigators.push_back(navigator1);
	navigators.push_back(navigator2);
	navigator2->setColor(sf::Color::Green);
	navigator1->setColor(sf::Color::Blue);

	//set rotation point and scale of navigators
	for (sf::Sprite* navigator : navigators) {
		const sf::IntRect* const  textureRect = &navigator->getTextureRect();
		sf::Vector2f newOrigin(textureRect->width / 2.0f, textureRect->height / 2.0f);
		navigator->setOrigin(newOrigin);
		navigator->setScale(0.5, 0.5);
	}

	//create maze
	GB::Point2D<int> navigator1StartingGrid{ 0, 0 };
	GB::Point2D<int> navigator2StartingGrid{15, 15};
	nonBlockableGridSquares.push_back(navigator1StartingGrid);
	nonBlockableGridSquares.push_back(navigator2StartingGrid);
	initMaze(nonBlockableGridSquares);

	//ensure that window / grid coordinates are converted with the correct ratio
	sf::Sprite* gridSprite = static_cast<NavigationDemoData*>(navGrid->at(0, 0))->demoSprite;
	float gridSquareWidth = gridSprite->getLocalBounds().width;
	coordinateConverter.setGridSquareWidth(gridSquareWidth);

	//position navigators
	const sf::Vector2f navigator1StartingPos = coordinateConverter.convertCoordToWindow(navigator1StartingGrid);
	const sf::Vector2f navigator2StartingPos = coordinateConverter.convertCoordToWindow(navigator2StartingGrid);
	navigator1->setPosition(navigator1StartingPos);
	navigator2->setPosition(navigator2StartingPos);

	//draw navigators on top of maze
	setDrawable(true, navigator1);
	setDrawable(true, navigator2);

	//Path-find from starting positions to end positions
	//create request
	GB::PathRequest pathRequest{ navigator1StartingGrid, GB::Point2D<int>{15,15}, 3, 0 };
	std::vector<GB::PathRequest> pathRequests;
	pathRequests.push_back(pathRequest);

	//second request
	GB::PathRequest pathRequest2{ navigator2StartingGrid, GB::Point2D<int>{0,0}, 1, 0 };
	pathRequests.push_back(pathRequest2);

	//find the path
	std::vector<std::deque<GB::Point2D<int>>> pathsReturn;
	pathsReturn.resize(pathRequests.size());
	regionPathfinder.pathFind(pathRequests, &pathsReturn);

	//convert paths to window coordinates
	paths.resize(pathsReturn.size());
	for (unsigned int i = 0; i < navigators.size(); i++) {
		paths[i] = std::make_shared<std::deque<sf::Vector2f>>(coordinateConverter.convertPathToWindow(pathsReturn[i]));
	}

	selectedNavigatorOption = SELECTED_NAVIGATOR_BUTTON_TYPE::ALL_NAVIGATORS;
}

/// <summary>
/// Frees all dynamic memory allocated for this instance.
/// Resets the state of every member of this instance.
/// </summary>
void NavigationDemoRegion::destroy() {


	//delete navigation data
	GB::freeAllNavigationGridData(*navGrid);
	delete navGrid;
	navGrid = nullptr;

	// reset pathfinder
	regionPathfinder.setNavigationGrid(nullptr);

	// clear paths
	paths.clear();

	//delete navigators
	for (auto navigator : navigators) {
		delete navigator;
		navigator = nullptr;
	}
	navigators.clear();
	clearDrawable();
	clearUpdatable();

	//delete textures
	delete navigatorTexture;
	navigatorTexture = nullptr;
	delete gridTexture;
	gridTexture = nullptr;

	// reset time
	lastUpdateTime = sf::Time::Zero;

	// reset coordinate converter
	GB::CoordinateConverter newConverter;
	coordinateConverter = newConverter;
}

/// <summary>
/// Resets this instance.
/// The random clusters are regenerated and the navigators are reset.
/// Everything else in this instance is also reset or reconstructed.
/// </summary>
void NavigationDemoRegion::reset() {
	destroy();
	init();
}

/// <summary>
/// Initializes the GUI.
/// </summary>
void NavigationDemoRegion::initGUI() {
	// Load the black theme
	tgui::Theme theme("TGUI_Widgets/Black.txt");

	// Get a bound version of the window size
	// Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
	tgui::Layout windowWidth = tgui::bindWidth(*regionGUI);
	tgui::Layout windowHeight = tgui::bindHeight(*regionGUI);

	// Create the background image (picture is of type tgui::Picture::Ptr or std::shared_widget<Picture>)
	tgui::Picture::Ptr picture = tgui::Picture::create(R"(Textures/Backbone2.png)");

	picture->setSize(windowWidth, "&.height / 10");
	picture->setPosition(0, 9 * windowHeight / 10.0f);
	regionGUI->add(picture);

	const int NUM_BUTTONS = 3;
	tgui::Layout buttonWidth = windowWidth / (NUM_BUTTONS + NUM_BUTTONS + 1);
	tgui::Layout buttonHeight = windowHeight / 20.0f;
	int buttonIndex = 0;

	// create navigator 1 button
	tgui::Button::Ptr navigator1Button = tgui::Button::create();
	navigator1Button->setRenderer(theme.getRenderer("Button"));
	navigator1Button->setSize(buttonWidth, buttonHeight);
	navigator1Button->setPosition((2 * buttonIndex + 1) * buttonWidth, windowHeight * 9 / 10.0f);
	navigator1Button->setText("Navigator1");
	navigator1Button->connect("pressed", &NavigationDemoRegion::Navigator1CB, this);
	regionGUI->add(navigator1Button);
	buttonIndex++;

	// create navigator 2 button
	tgui::Button::Ptr navigator2Button = tgui::Button::create();
	navigator2Button->setRenderer(theme.getRenderer("Button"));
	navigator2Button->setSize(buttonWidth, buttonHeight);
	navigator2Button->setPosition((2 * buttonIndex + 1) * buttonWidth, windowHeight * 9 / 10.0f);
	navigator2Button->setText("Navigator2");
	navigator2Button->connect("pressed", &NavigationDemoRegion::Navigator2CB, this);
	regionGUI->add(navigator2Button);
	buttonIndex++;

	// create all navigators button
	tgui::Button::Ptr allNavigatorsButton = tgui::Button::create();
	allNavigatorsButton->setRenderer(theme.getRenderer("Button"));
	allNavigatorsButton->setSize(buttonWidth, buttonHeight);
	allNavigatorsButton->setPosition((2 * buttonIndex + 1) * buttonWidth, windowHeight * 9 / 10.0f);
	allNavigatorsButton->setText("All Navigators");
	allNavigatorsButton->connect("pressed", &NavigationDemoRegion::AllNavigatorsCB, this);
	regionGUI->add(allNavigatorsButton);
	buttonIndex++;
}

/// <summary>
/// Initializes the maze that the navigators will use.
/// </summary>
void NavigationDemoRegion::initMaze(std::vector<GB::Point2D<int>> nonBlockablePositions) {
    std::vector<double> genOptions;
    // comment these out to make random clusters
    genOptions.push_back(.05);
    genOptions.push_back(.10);
    genOptions.push_back(.05);

	GB::ClusterGreenhouse* graphGenerator = new GB::ClusterGreenhouse(GB::Point2D<int>{(int)NAV_GRID_DIM, (int)NAV_GRID_DIM});

    std::vector<std::set<GB::Point2D<int>>> ClusterPointSetVector = graphGenerator->generateClusteredGraph(genOptions);
    std::vector<std::set<GB::Point2D<int>>> ClusterPointSetVector2 = graphGenerator->generateClusteredGraph(genOptions);
    //merge output vectors
    ClusterPointSetVector.insert(ClusterPointSetVector.end(), ClusterPointSetVector2.begin(), ClusterPointSetVector2.end());

	std::vector<sf::Color> clusterColors;
	for (int i = 0; i < ClusterPointSetVector.size(); i++) {
		clusterColors.push_back(sf::Color(rand() % 250, rand() % 250, rand() % 250));
	}

	//fill visual grid
	for (unsigned int i = 0; i < NAV_GRID_DIM; i++) {
		for (unsigned int j = 0; j < NAV_GRID_DIM; j++) {
			//create sprite in correct position
			sf::Sprite* gridSquare = new sf::Sprite(*gridTexture);
			const float gridOriginOffsetX = gridSquare->getLocalBounds().width / 2;
			const float gridOriginOffsetY = gridSquare->getLocalBounds().height / 2;
			gridSquare->setOrigin(gridOriginOffsetX, gridOriginOffsetY); //set origin to center of grid
			gridSquare->setScale(VISUAL_GRID_SCALE, VISUAL_GRID_SCALE);
			gridSquare->move(i * gridSquare->getLocalBounds().width + gridOriginOffsetX, j * gridSquare->getLocalBounds().height + gridOriginOffsetY);
			gridSquare->setColor(sf::Color::Yellow);

            // color the graph
			GB::Point2D<int> clusterKey{(int)i, (int)j};
			for (int k = 0; k < ClusterPointSetVector.size(); k++) {
				if (ClusterPointSetVector[k].find(clusterKey) != ClusterPointSetVector[k].end()) {
					gridSquare->setColor(clusterColors[k]);
					(*navGrid)[i][j]->weight = BLOCKED_GRID_WEIGHT;
					break;
				}
			}

			//add grids to storage
			static_cast<NavigationDemoData*>(navGrid->at(i, j))->demoSprite = gridSquare;

			//ensure grids are drawn
			setDrawable(true, gridSquare);
		}
	}
	delete graphGenerator;
}

/// <summary>
/// Handles the button navigator1.
/// </summary>
void NavigationDemoRegion::Navigator1CB()
{
	selectedNavigatorOption = SELECTED_NAVIGATOR_BUTTON_TYPE::NAVIGATOR_1;
	debugPrint("navigator1");
}

/// <summary>
/// Handles the button navigator2.
/// </summary>
void NavigationDemoRegion::Navigator2CB()
{
	selectedNavigatorOption = SELECTED_NAVIGATOR_BUTTON_TYPE::NAVIGATOR_2;
	debugPrint("navigator2");
}

/// <summary>
/// Handles the button all navigators.
/// </summary>
void NavigationDemoRegion::AllNavigatorsCB()
{
	selectedNavigatorOption = SELECTED_NAVIGATOR_BUTTON_TYPE::ALL_NAVIGATORS;
	debugPrint("all navigators");
}