#include <iostream>

#define _USE_MATH_DEFINES

#include <NavigationDemoRegion.h>
#include <Navigation\NavigationTools.h>
#include <Util\UtilMath.h>

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
	delete navGrid;
	navGrid = nullptr;

	//delete visual navigation grid data
	for (unsigned int i = 0; i < visualNavigationGrid->getArraySizeX(); i++) {
		for (unsigned int j = 0; j < visualNavigationGrid->getArraySizeY(); j++) {
			delete (*visualNavigationGrid)[i][j];
			(*visualNavigationGrid)[i][j] = nullptr;
		}
	}
	delete visualNavigationGrid;

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

	sf::Int64 msPassed = currentTime.asMilliseconds() - lastUpdateTime.asMicroseconds();
	switch (selectedNavigatorOption)
	{
	case GB::NAVIGATOR_1: 
	{
		moveSpriteAlongPath(navigators[0], &(pathsReturn[0]), msPassed, 1);
	}
		break;
	case GB::NAVIGATOR_2:
	{
		moveSpriteAlongPath(navigators[1], &(pathsReturn[1]), msPassed, 1);
	}
		break;
	case GB::ALL_NAVIGATORS: 
	{
		for (size_t i = 0; i < navigators.size(); i++) {
			moveSpriteAlongPath(navigators[i], &(pathsReturn[i]), msPassed, 1);
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
		std::vector<PathRequest> pathRequests(navigators.size());

		//create each path request
		for (size_t i = 0; i < navigators.size(); i++) {
			sf::Sprite* currentNavigator = navigators[i];
			Point2D<int> startingPos = worldCoordToGridCoord(currentNavigator->getPosition());
			Point2D<int> endingPos = worldCoordToGridCoord(newPosition);
			pathRequests[i] = PathRequest{ startingPos, endingPos, 1, 0 };
		}

		//path-find
		pathsReturn.resize(pathRequests.size());
		regionPathfinder.pathFind(pathRequests, &pathsReturn);
	}
}

/// <summary>
/// Initializes this instance.
/// </summary>
void GB::NavigationDemoRegion::init() {
	//init storage
	navGrid = new NavigationGrid(NAV_GRID_DIM);
	regionPathfinder.setNavigationGrid(navGrid);
	visualNavigationGrid = new Array2D<sf::Sprite*>(NAV_GRID_DIM);

	//init textures
	std::string arrowPath("..\\..\\Textures\\SmallArrow.png");
	navigatorTexture = new sf::Texture();
	navigatorTexture->loadFromFile(arrowPath);
	std::string navigationGridPath("..\\..\\Textures\\NavigationGrid.png");
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

	//set rotation point of navigators
	for each (sf::Sprite* navigator in navigators) {
		const sf::IntRect * const  textureRect = &navigator->getTextureRect();
		sf::Vector2f newOrigin(textureRect->width / 2.0f, textureRect->height / 2.0f);
		navigator->setOrigin(newOrigin);
	}

	//position navigators
	Point2D<int> navigator1StartingGrid{ 0, 0 };
	Point2D<int> navigator2StartingGrid{15, 15};
	nonBlockableGridSquares.push_back(navigator1StartingGrid);
	nonBlockableGridSquares.push_back(navigator2StartingGrid);
	const sf::Vector2f navigator1StartingPos = gridCoordToWorldCoord(navigator1StartingGrid);
	const sf::Vector2f navigator2StartingPos = gridCoordToWorldCoord(navigator2StartingGrid);
	navigator1->setPosition(navigator1StartingPos);
	navigator2->setPosition(navigator2StartingPos);

	//create maze
	initMaze(nonBlockableGridSquares);

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
	pathsReturn.resize(pathRequests.size());
	regionPathfinder.pathFind(pathRequests, &pathsReturn);

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
	tgui::Picture::Ptr picture = tgui::Picture::create("..\\..\\Textures\\Backbone2.png");
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
	initAllNavigationGridValues(*navGrid, NavigationGridData{ 1, 0 });

    Array2D<int> graph(NAV_GRID_DIM, NAV_GRID_DIM);
    std::vector<ClusterGenerationOptions> genOptions;
    // comment these out to make random clusters
    /*ClusterGenerationOptions ClusterGenerationOptions1{ sf::Color::Red, 10 }; genOptions.push_back(ClusterGenerationOptions1);
    ClusterGenerationOptions ClusterGenerationOptions2{ sf::Color::Blue, 40 }; genOptions.push_back(ClusterGenerationOptions2);
    ClusterGenerationOptions ClusterGenerationOptions3{ sf::Color::Magenta, 50 }; genOptions.push_back(ClusterGenerationOptions3);*/
    std::multimap<std::pair<int, int>, Cluster> pointToClusterMap = GenerateClusteredGraph(graph, &genOptions);

	//fill visual grid
	for (unsigned int i = 0; i < graph.getArraySizeX(); i++) {
		for (unsigned int j = 0; j < graph.getArraySizeY(); j++) {
			//create sprite in correct position
			sf::Sprite* gridSquare = new sf::Sprite(*gridTexture);
			const float gridOriginOffsetX = gridSquare->getLocalBounds().width / 2;
			const float gridOriginOffsetY = gridSquare->getLocalBounds().height / 2;
			gridSquare->setOrigin(gridOriginOffsetX, gridOriginOffsetY); //set origin to center of grid
			gridSquare->setScale(VISUAL_GRID_SCALE, VISUAL_GRID_SCALE);
			gridSquare->move(i * gridSquare->getLocalBounds().width + gridOriginOffsetX, j * gridSquare->getLocalBounds().height + gridOriginOffsetY);

            // color the graph
            std::pair<int, int> clusterKey(i, j);
            auto search = pointToClusterMap.find(clusterKey);
            if (search != pointToClusterMap.end()) {
                gridSquare->setColor(search->second.getClusterGenerationOptions()->colorOfCluster);
                (*navGrid)[i][j]->weight = BLOCKED_GRID_WEIGHT;
            }
            else {
                gridSquare->setColor(sf::Color::Yellow);
            }

			//add grids to storage
			(*visualNavigationGrid)[i][j] = gridSquare;

			//ensure grids are drawn
			setDrawable(true, gridSquare);
		}
	}
}

/// <summary>
/// Calculates the game world position of a grid coordinate.
/// </summary>
/// <param name="gridCoordinate">The grid coordinate.</param>
/// <returns>The 2D position of the grid coordinate's top left corner in the game world's coordinate system.</returns>
sf::Vector2f NavigationDemoRegion::gridCoordToWorldCoord(const Point2D<int> & gridCoordinate) {
	//for the demo we can assume that the grid starts at the origin
	sf::Vector2f gridOrigin(0, 0);

	int gridSquareWidth = gridTexture->getSize().x;
	int gridSquareHeight = gridTexture->getSize().y;
	sf::Vector2f offsetOrigin(0 + (gridSquareWidth / 2.0f), 0 + (gridSquareHeight / 2.0f));// bad hack

	// use size of grid squares and grid origin position to calculate world coordinate
	return sf::Vector2f(gridCoordinate.x * gridSquareWidth + offsetOrigin.x, 
						gridCoordinate.y * gridSquareHeight + offsetOrigin.y);
}

/// <summary>
/// Determine what grid square a game world coordinate lies in. 
/// </summary>
/// <param name="worldCoordinate">The world coordinate.</param>
/// <returns>The coordinate of the grid that the game world coordinate lies in.</returns>
Point2D<int> NavigationDemoRegion::worldCoordToGridCoord(const sf::Vector2f & worldCoordinate) {
	//for the demo we can assume that the grid starts at the origin
	sf::Vector2f gridOrigin(0, 0);

	//offset origin to produce coordinate in center of grid square
	unsigned int gridSquareWidth = gridTexture->getSize().x;
	unsigned int gridSquareHeight = gridTexture->getSize().y;
	sf::Vector2f offsetOrigin(0.0f + ((float)gridSquareWidth / 2.0f), 0.0f + ((float)gridSquareHeight / 2.0f));// bad hack

	// use size of grid squares and grid origin position to calculate grid coordinate
	return Point2D<int>{ (int)((worldCoordinate.x - offsetOrigin.x) / gridSquareWidth),
				   (int)((worldCoordinate.y - offsetOrigin.y) / gridSquareHeight) };
}

/// <summary>
/// Moves the sprite towards point.
/// </summary>
/// <param name="sprite">The sprite.</param>
/// <param name="destination">The destination.</param>
/// <param name="distance">The distance.</param>
void NavigationDemoRegion::moveSpriteTowardsPoint(sf::Sprite * sprite, sf::Vector2f destination, float distance) {
	
	distance = 0.1f; //TODO: figure out why this isn't ever big enough

	//angle between the sprite and the destination
	const float angleToDestination = atan2(destination.y - sprite->getPosition().y, destination.x - sprite->getPosition().x);
	const float angleToDestinationDeg = angleToDestination * (180.0f / (float)M_PI) + 90.0f;// This is offset by 90 degrees. This is because this value is only used to rotate the sprite. 
																				  //The sprite is currently rotated at -90 from the games coordinate system
	
	//angle sprite to point at destination 
	sprite->setRotation(angleToDestinationDeg);

	//move sprite by distance towards its destination
	const sf::Vector2f spriteMovement(cosf(angleToDestination) * distance, sinf(angleToDestination) * distance);
	sprite->move(spriteMovement);
	volatile auto sx = sprite->getPosition().x;
	volatile auto sy = sprite->getPosition().y;
}

/// <summary>
/// Moves a single sprite along a navigation path.
/// </summary>
/// <param name="sprite">The sprite.</param>
/// <param name="path">The path.</param>
/// <param name="msPassed">The time passed in ms since the last movement.</param>
/// <param name="speed">The speed of the sprite in pixels per ms.</param>
void NavigationDemoRegion::moveSpriteAlongPath(sf::Sprite * sprite, std::list<Point2D<int>>* path, sf::Int64 msPassed, float speed) {
	//determine if sprite has reached first point in path
	if (path->size() >= 1) {

		//move sprite a step towards the next point in the path
		float actualMovement = speed / msPassed;
		auto nextGrid = path->front();
		sf::Vector2f targetPosition = ((*visualNavigationGrid)[nextGrid.x][nextGrid.y])->getPosition();
		moveSpriteTowardsPoint(sprite, targetPosition, actualMovement);
		
		//check if the sprite is close enough to its destination
		auto spriteCurrentPosition = sprite->getPosition();
		auto destination = targetPosition;
		const float acceptableDistance = 0.2f;
		if(abs(destination.x - spriteCurrentPosition.x) < acceptableDistance && abs(destination.y - spriteCurrentPosition.y) < acceptableDistance) {// this is a bad way, but quick to code and run
			path->pop_front();
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