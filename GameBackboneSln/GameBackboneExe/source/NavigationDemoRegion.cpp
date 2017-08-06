#include <iostream>

#define _USE_MATH_DEFINES

#include <NavigationDemoRegion.h>
#include <Navigation\NavigationTools.h>

#include <TGUI\TGUI.hpp>

#include <SFML\Graphics.hpp>

#include <string>
#include <math.h>

using namespace GB;

/// <summary>
/// Initializes a new instance of the <see cref="NavigationDemoRegion"/> class.
/// </summary>
NavigationDemoRegion::NavigationDemoRegion() {
	init();
}

/// <summary>
/// Initializes a new instance of the <see cref="NavigationDemoRegion"/> class.
/// </summary>
/// <param name="window">The window that will be attached to this instances GUI.</param>
GB::NavigationDemoRegion::NavigationDemoRegion(sf::RenderWindow & window) : GameRegion(window) {
	init();
}

/// <summary>
/// Finalizes an instance of the <see cref="NavigationDemoRegion"/> class.
/// </summary>
NavigationDemoRegion::~NavigationDemoRegion() {

	//delete navigation data
	freeAllNavigationGridData(*navGrid);
	delete navGrid;
	navGrid = nullptr;

	//delete navigators
	for each (auto navigator in navigators) {
		delete navigator;
		navigator = nullptr;
	}

	//delete textures
	delete navigatorTexture;
	navigatorTexture = nullptr;
	delete gridTexture;
	gridTexture = nullptr;
}

/// <summary>
/// Executes a single cycle of the main logic loop for this region.
/// </summary>
void NavigationDemoRegion::behave(sf::Time currentTime) {



	//move navigators
	sf::Uint64 msPassed = currentTime.asMilliseconds() - lastUpdateTime.asMilliseconds();

	switch (selectedNavigatorOption)
	{
	case GB::NAVIGATOR_1: 
	{
		moveSpriteAlongPath(*navigators[0], paths[0], msPassed, 1);
		break;
	}
	case GB::NAVIGATOR_2:
	{
		moveSpriteAlongPath(*navigators[1], paths[1], msPassed, 1);
	}
		break;
	case GB::ALL_NAVIGATORS: 
	{
		std::vector<float> speeds(navigators.size(), 1.0f);
		bulkMoveSpriteAlongPath(navigators, paths, msPassed, speeds);
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
		std::vector<PathRequest> pathRequests(navigators.size());

		//create each path request
		for (size_t i = 0; i < navigators.size(); i++) {
			sf::Sprite* currentNavigator = navigators[i];
			Point2D<int> startingPos = coordinateConverter.convertCoordToNavGrid(currentNavigator->getPosition());
			Point2D<int> endingPos = coordinateConverter.convertCoordToNavGrid(newPosition);
			pathRequests[i] = PathRequest{ startingPos, endingPos, 1, 0 };
		}

		//path-find
		std::vector<NavGridCoordinatePath> pathsReturn;
		pathsReturn.resize(pathRequests.size());
		regionPathfinder.pathFind(pathRequests, &pathsReturn);

		//convert paths to window coordinates
		paths.clear();
		paths.resize(pathsReturn.size());
		for (unsigned int i = 0; i < navigators.size(); i++) {
			paths[i] = std::make_shared<std::list<sf::Vector2f>>(coordinateConverter.convertPathToWindow(pathsReturn[i]));
		}
	}
}

/// <summary>
/// Initializes this instance.
/// </summary>
void GB::NavigationDemoRegion::init() {
	//init storage
	navGrid = new NavigationGrid(NAV_GRID_DIM);
	initAllNavigationGridValues(*navGrid, NavigationDemoData());
	regionPathfinder.setNavigationGrid(navGrid);


	//init textures
	std::string arrowPath(R"(..\..\Textures\SmallArrow.png)");
	navigatorTexture = new sf::Texture();
	navigatorTexture->loadFromFile(arrowPath);
	std::string navigationGridPath(R"(..\..\Textures\NavigationGrid.png)");
	gridTexture = new sf::Texture();
	gridTexture->loadFromFile(navigationGridPath);

	//internal function logic
	std::vector<Point2D<int>> nonBlockableGridSquares;


	//init navigators

	//create navigators and add to respective arrays
	sf::Sprite* navigator1 = new sf::Sprite(*navigatorTexture);
	sf::Sprite* navigator2 = new sf::Sprite(*navigatorTexture);
	navigators.push_back(navigator1);
	navigators.push_back(navigator2);
	navigator2->setColor(sf::Color::Green);
	navigator1->setColor(sf::Color::Blue);

	//set rotation point and scale of navigators
	for each (sf::Sprite* navigator in navigators) {
		const sf::IntRect * const  textureRect = &navigator->getTextureRect();
		sf::Vector2f newOrigin(textureRect->width / 2.0f, textureRect->height / 2.0f);
		navigator->setOrigin(newOrigin);
		navigator->setScale(0.5, 0.5);
	}

	//create maze
	Point2D<int> navigator1StartingGrid{ 0, 0 };
	Point2D<int> navigator2StartingGrid{15, 15};
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
	PathRequest pathRequest{ navigator1StartingGrid, Point2D<int>{15,15}, 3, 0 };
	std::vector<PathRequest> pathRequests;
	pathRequests.push_back(pathRequest);

	//second request
	PathRequest pathRequest2{ navigator2StartingGrid, Point2D<int>{0,0}, 1, 0 };
	pathRequests.push_back(pathRequest2);

	//find the path
	std::vector<std::list<Point2D<int>>> pathsReturn;
	pathsReturn.resize(pathRequests.size());
	regionPathfinder.pathFind(pathRequests, &pathsReturn);

	//convert paths to window coordinates
	paths.resize(pathsReturn.size());
	for (unsigned int i = 0; i < navigators.size(); i++) {
		paths[i] = std::make_shared<std::list<sf::Vector2f>>(coordinateConverter.convertPathToWindow(pathsReturn[i]));
	}

	//initialize GUI
	try {
		// Load the widgets
		initGUI();
	}
	catch (const tgui::Exception& e) {
		std::cerr << "Failed to load GUI: " << e.what() << std::endl;
	}
	selectedNavigatorOption = SELECTED_NAVIGATOR_BUTTON_TYPE::ALL_NAVIGATORS;
}

/// <summary>
/// Initializes the GUI.
/// </summary>
void GB::NavigationDemoRegion::initGUI() {
	// Load the black theme
	tgui::Theme::Ptr theme = tgui::Theme::create("TGUI_Widgets/Black.txt");

	// Get a bound version of the window size
	// Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
	tgui::Layout windowWidth = tgui::bindWidth(*regionGUI);
	tgui::Layout windowHeight = tgui::bindHeight(*regionGUI);

	// Create the background image (picture is of type tgui::Picture::Ptr or std::shared_widget<Picture>)
	tgui::Picture::Ptr picture = tgui::Picture::create(R"(..\..\Textures\Backbone2.png)");
	picture->setSize(tgui::bindMax(800, windowWidth), tgui::bindMax(200, windowHeight / 10.0f));
	picture->setPosition(0, 9 * windowHeight / 10.0f);
	regionGUI->add(picture);

	// create navigator 1 button
	tgui::Button::Ptr navigator1Button = theme->load("Button");
	navigator1Button->setSize(windowWidth / 10.0f, windowHeight / 20.0f);
	navigator1Button->setPosition(4 * windowWidth / 10.0f, windowHeight * 9 / 10.0f);
	navigator1Button->setText("Navigator1");
	navigator1Button->connect("pressed", &NavigationDemoRegion::Navigator1CB, this);
	regionGUI->add(navigator1Button);

	// create navigator 2 button
	tgui::Button::Ptr navigator2Button = theme->load("Button");
	navigator2Button->setSize(windowWidth / 10.0f, windowHeight / 20.0f);
	navigator2Button->setPosition(5 * windowWidth / 10.0f, windowHeight * 9 / 10.0f);
	navigator2Button->setText("Navigator2");
	navigator2Button->connect("pressed", &NavigationDemoRegion::Navigator2CB, this);
	regionGUI->add(navigator2Button);

	// create all navigators button
	tgui::Button::Ptr allNavigatorsButton = theme->load("Button");
	allNavigatorsButton->setSize(windowWidth / 10.0f, windowHeight / 20.0f);
	allNavigatorsButton->setPosition(6 * windowWidth / 10.0f, windowHeight * 9 / 10.0f);
	allNavigatorsButton->setText("All Navigators");
	allNavigatorsButton->connect("pressed", &NavigationDemoRegion::AllNavigatorsCB, this);
	regionGUI->add(allNavigatorsButton);
}

/// <summary>
/// Initializes the maze that the navigators will use.
/// </summary>
void NavigationDemoRegion::initMaze(std::vector<Point2D<int>> nonBlockablePositions) {
	//block grids for maze
	srand((unsigned int)time(NULL));
	for (unsigned int i = 0; i < navGrid->getArraySizeX(); i++) {
		for (unsigned int j = 0; j < navGrid->getArraySizeY(); j++) {
			if (! (rand() % 5)) {//1 in 5 are blocked
				bool blockable = true;
				//determine if the square is non-blockable
				for each (Point2D<int> nonBlockable in nonBlockablePositions) {
					if (nonBlockable.x == i && nonBlockable.y == j) {
						blockable = false;
					}
				}
				//only block blockable grids	
				if (blockable) {
					(*navGrid)[i][j]->weight = BLOCKED_GRID_WEIGHT;
				}
			}
		}
	}

	//fill visual grid
	for (unsigned int i = 0; i < navGrid->getArraySizeX(); i++) {
		for (unsigned int j = 0; j < navGrid->getArraySizeY(); j++) {
			//create sprite in correct position
			sf::Sprite* gridSquare = new sf::Sprite(*gridTexture);
			const float gridOriginOffsetX = gridSquare->getLocalBounds().width / 2;
			const float gridOriginOffsetY = gridSquare->getLocalBounds().height / 2;
			gridSquare->setOrigin(gridOriginOffsetX, gridOriginOffsetY); //set origin to center of grid
			gridSquare->setScale(VISUAL_GRID_SCALE, VISUAL_GRID_SCALE);
			gridSquare->move(i * gridSquare->getLocalBounds().width + gridOriginOffsetX, j * gridSquare->getLocalBounds().height + gridOriginOffsetY);

			//shade blocked grids
			bool blocked = (*navGrid)[i][j]->weight == BLOCKED_GRID_WEIGHT;
			if (blocked) {
				gridSquare->setColor(sf::Color::Red);
			}

			//add grids to storage
			//sf::Sprite* gridSprite = (static_cast<NavigationDemoData*>(navGrid->at(i, j))->demoSprite);
			static_cast<NavigationDemoData*>(navGrid->at(i, j))->demoSprite = gridSquare;

			//ensure grids are drawn
			setDrawable(true, gridSquare);
		}
	}
}

/// <summary>
/// Handles the button navigator1.
/// </summary>
void GB::NavigationDemoRegion::Navigator1CB()
{
	selectedNavigatorOption = SELECTED_NAVIGATOR_BUTTON_TYPE::NAVIGATOR_1;
	debugPrint("navigator1");
}

/// <summary>
/// Handles the button navigator2.
/// </summary>
void GB::NavigationDemoRegion::Navigator2CB()
{
	selectedNavigatorOption = SELECTED_NAVIGATOR_BUTTON_TYPE::NAVIGATOR_2;
	debugPrint("navigator2");
}

/// <summary>
/// Handles the button all navigators.
/// </summary>
void GB::NavigationDemoRegion::AllNavigatorsCB()
{
	selectedNavigatorOption = SELECTED_NAVIGATOR_BUTTON_TYPE::ALL_NAVIGATORS;
	debugPrint("all navigators");
}