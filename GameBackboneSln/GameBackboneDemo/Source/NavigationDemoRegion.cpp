#define _USE_MATH_DEFINES

#include <GameBackboneDemo/NavigationDemoRegion.h>

#include <GameBackbone/Navigation/NavigationGridData.h>
#include <GameBackbone/Navigation/NavigationTools.h>
#include <GameBackbone/Util/RandGen.h>
#include <GameBackbone/Util/UtilMath.h>

#include <TGUI/TGUI.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <memory>
#include <string>

using namespace EXE;

/// <summary>
/// Initializes a new instance of the <see cref="NavigationDemoRegion"/> class.
/// </summary>
/// <param name="window">The window that will be attached to this instances GUI.</param>
NavigationDemoRegion::NavigationDemoRegion(sf::RenderWindow & window) : DemoRegion(window) {
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
/// Finalizes an instance of the <see cref="NavigationDemoRegion"/> class.
/// </summary>
NavigationDemoRegion::~NavigationDemoRegion() {
	destroy();
}

/// <summary>
/// Executes a single cycle of the main logic loop for this region.
/// </summary>
void NavigationDemoRegion::update(sf::Int64 elapsedTime) {
	// Depending on which state the Region is in, move only the appropriate navigator(s)
	switch (selectedNavigatorOption)
	{
	case EXE::NAVIGATOR_1:
	{
		// Move the first navigator
		GB::moveSpriteAlongPath(*navigators[0], paths[0], elapsedTime, 0.0005f);
		break;
	}
	case EXE::NAVIGATOR_2:
	{
		// Move the second navigator
		GB::moveSpriteAlongPath(*navigators[1], paths[1], elapsedTime, 0.0005f);
		break;
	}
	case EXE::ALL_NAVIGATORS:
	{
		// Loop through and move all navigators
		for (size_t i = 0; i < navigators.size(); i++) {
			GB::moveSpriteAlongPath(*navigators[i], paths[i], elapsedTime, 0.0005f);
		}
		break;
	}
	default:
		break;
	}
}

/// <summary>
/// Handles mouse click logic.
/// </summary>
/// <param name="clickPosition">The position of the click.</param>
/// <param name="button">The mouse button clicked button.</param>
void NavigationDemoRegion::handleMouseClick(sf::Vector2f clickPosition, sf::Mouse::Button button) {
	// Check if the user left clicked
	if (button == sf::Mouse::Left) {
		// Create a vector to store the PathRequests that is the size of the number of navigators
		std::vector<GB::PathRequest> pathRequests(navigators.size());

		// Create each PathRequest
		for (size_t i = 0; i < navigators.size(); i++) {
			// Get the current sf position of the navigator's sprite
			sf::Vector2f sfPos = navigators[i]->getPosition();
			// Convert the sfPos to NavGrid coordinates to use as the starting position
			sf::Vector2i startingPos = coordinateConverter.convertCoordToNavGrid(sfPos);
			// Convert the clicked position from sf to NavGrid coordinates to use as the end position
			sf::Vector2i endingPos = coordinateConverter.convertCoordToNavGrid(clickPosition);
			// Create and assign the PathRequest for the given start and end position
			pathRequests[i] = GB::PathRequest{ startingPos, endingPos };
		}

		// Prepare a vector to be used as an output parameter
		std::vector<GB::NavGridCoordinatePath> pathsReturn(pathRequests.size());
		// Call pathFind to get the paths the navigators will use 
		regionPathfinder.pathFind(pathRequests, &pathsReturn);

		// Clear and resize the member variable to store the active paths
		paths.clear();
		paths.resize(pathsReturn.size());
		for (unsigned int i = 0; i < navigators.size(); i++) {
			// Convert the path to sf coordinates
			GB::WindowCoordinatePath sfCoordPath = coordinateConverter.convertPathToWindow(pathsReturn[i]);
			// Use std::move to avoid a copy when assigning the converted path to the member variable
			paths[i] = std::make_shared<GB::WindowCoordinatePath>(std::move(sfCoordPath));
		}
	}
}

/// <summary>
/// Initializes this instance.
/// </summary>
void NavigationDemoRegion::init() {
	// Initialize the navigation grid and set it on Pathfinder
	navGrid = std::make_unique<GB::NavigationGrid>(NAV_GRID_DIM);
	GB::initAllNavigationGridValues(*navGrid, NavigationDemoData());
	regionPathfinder.setNavigationGrid(navGrid.get());


	// Initialize the arrow textures for the navigators
	std::string arrowPath(R"(Textures/SmallArrow.png)");
	navigatorTexture = std::make_unique<sf::Texture>();
	navigatorTexture->loadFromFile(arrowPath);

	// Initialize the box textures on the NavigationGrid
	std::string navigationGridPath(R"(Textures/NavigationGrid.png)");
	gridTexture = std::make_unique<sf::Texture>();
	gridTexture->loadFromFile(navigationGridPath);


	// Initialize navigators
	// Create navigators and add to respective arrays
	sf::Sprite* navigator1 = navigators.emplace_back(std::make_unique<sf::Sprite>(*navigatorTexture)).get();
	sf::Sprite* navigator2 = navigators.emplace_back(std::make_unique<sf::Sprite>(*navigatorTexture)).get();

	// Set the color of each navigator to tell them apart
	navigator1->setColor(sf::Color::Blue);
	navigator2->setColor(sf::Color::Green);

	// Set rotation point and scale of navigators
	for (std::unique_ptr<sf::Sprite>& navigator : navigators) {
		// Get the texture's rectangle from SFML
		const sf::IntRect* const  textureRect = &navigator->getTextureRect();
		// Create a new origin in the center of the texture
		sf::Vector2f newOrigin(textureRect->width / 2.0f, textureRect->height / 2.0f);
		navigator->setOrigin(newOrigin);
		navigator->setScale(0.5, 0.5);
	}

	initMaze();

	// Ensure that window / grid coordinates are converted with the correct ratio
	sf::Sprite* gridSprite = static_cast<NavigationDemoData*>(navGrid->at(0, 0))->demoSprite;
	float gridSquareWidth = gridSprite->getLocalBounds().width;
	coordinateConverter.setGridSquareWidth(gridSquareWidth);

	// Position navigators
	sf::Vector2i navigator1StartingGrid{ 0, 0 };
	sf::Vector2i navigator2StartingGrid{ 15, 15 };
	const sf::Vector2f navigator1StartingPos = coordinateConverter.convertCoordToWindow(navigator1StartingGrid);
	const sf::Vector2f navigator2StartingPos = coordinateConverter.convertCoordToWindow(navigator2StartingGrid);
	navigator1->setPosition(navigator1StartingPos);
	navigator2->setPosition(navigator2StartingPos);

	// Draw navigators on top of maze
	addDrawable(1, navigator1);
	addDrawable(1, navigator2);

	// Path-find from starting positions to end positions
	// Create request

	// Find a path from navigator 1's starting position to navigator2's starting position
	GB::PathRequest pathRequest{ navigator1StartingGrid, navigator2StartingGrid };
	std::vector<GB::PathRequest> pathRequests;
	pathRequests.push_back(pathRequest);

	// Second request

	// Find a path from navigator 2's starting position to navigator1's starting position
	GB::PathRequest pathRequest2{ navigator2StartingGrid, navigator1StartingGrid };
	pathRequests.push_back(pathRequest2);

	// Find the path
	std::vector<std::deque<sf::Vector2i>> pathsReturn;
	pathsReturn.resize(pathRequests.size());
	regionPathfinder.pathFind(pathRequests, &pathsReturn);

	// Convert paths to window coordinates
	paths.resize(pathsReturn.size());
	for (unsigned int i = 0; i < navigators.size(); i++) {
		paths[i] = std::make_shared<std::deque<sf::Vector2f>>(coordinateConverter.convertPathToWindow(pathsReturn[i]));
	}

	// All navigators will move to a mouse click by default
	selectedNavigatorOption = SELECTED_NAVIGATOR_BUTTON_TYPE::ALL_NAVIGATORS;
}

/// <summary>
/// Initializes the GUI.
/// </summary>
void NavigationDemoRegion::initGUI() {
	// Get a bound version of the window size
	// Passing this to setPosition or setSize will make the widget automatically update when the view of the GUI changes
	tgui::Layout windowWidth = tgui::bindWidth(this->getGUI());
	tgui::Layout windowHeight = tgui::bindHeight(this->getGUI());

	// Create the background image (picture is of type tgui::Picture::Ptr)
	tgui::Picture::Ptr picture = tgui::Picture::create(R"(Textures/Backbone2.png)");

	// Make the image 1/10th of the screen and start it 9/10ths of the way down
	picture->setSize(windowWidth, "&.height / 10");
	picture->setPosition(0, 9 * windowHeight / 10.0f);
	this->getGUI().add(picture);

	// Temporarily track all of the buttons for controlling navigation
	std::vector<tgui::Button::Ptr> navigationButtons;

	// Navigator 1 button
	tgui::Button::Ptr navigator1Button = tgui::Button::create();
	// The text that the button will display
	navigator1Button->setText("Navigator1");
	// The action that will happen when the button is pressed
	// Note that the "this" pointer must be passed. This is because the 
	// function being connected to the button is a member function
	navigator1Button->connect("pressed", &NavigationDemoRegion::Navigator1CB, this);
	// Add the button to the vector of buttons for the navigation bar
	navigationButtons.push_back(navigator1Button);

	// Navigator 2 button
	// Everything for navigator 2 is the same as for navigator 1
	tgui::Button::Ptr navigator2Button = tgui::Button::create();
	navigator2Button->setText("Navigator2");
	navigator2Button->connect("pressed", &NavigationDemoRegion::Navigator2CB, this);
	navigationButtons.push_back(navigator2Button);

	// All Navigators button
	// Everything for All Navigators is the same as for navigator 1 and 2
	tgui::Button::Ptr allNavigatorsButton = tgui::Button::create();
	allNavigatorsButton->setText("All Navigators");
	allNavigatorsButton->connect("pressed", &NavigationDemoRegion::AllNavigatorsCB, this);
	navigationButtons.push_back(allNavigatorsButton);

	// Size and place the buttons
	const std::size_t numButtons = navigationButtons.size();
	// This will be the width of all the buttons. It gives them all room on either side.
	tgui::Layout buttonWidth = windowWidth / (numButtons * 2 + 1);
	// This will be the height of all of the buttons
	tgui::Layout buttonHeight = windowHeight / 20.0f;
	for (std::size_t i = 0; i < navigationButtons.size(); ++i)
	{
		// Save some repetitive typing
		auto& currentButton = navigationButtons[i];
		// Set the size of the button
		currentButton->setSize(buttonWidth, buttonHeight);
		// Place the buttons in a row along the bottom of the window
		// They will be evenly spaced out and be in the bottom 1/10th of the window
		currentButton->setPosition((2 * i + 1) * buttonWidth, windowHeight * 9.25 / 10.0f);
		// Add the button to the GUI
		this->getGUI().add(currentButton);
	}
}

/// <summary>
/// Initializes the maze that the navigators will use.
/// </summary>
void NavigationDemoRegion::initMaze() {
	// This vector stores the generation options for a cluster.
	// Every element in the vector will produce a cluster with the associated weight.
	// The weights of all the clusters should not reach 1.0.
	// After the 1.0 - the accumulated weights of all of the clusters will be the % of empty squares.
	// Comment these out to make random clusters
	std::vector<double> genOptions;
	genOptions.push_back(0.05);
	genOptions.push_back(0.10);
	genOptions.push_back(0.05);
	genOptions.push_back(0.30);
	genOptions.push_back(0.4);

	// Create a ClusterGreenhouse that will create clusters spanning the entire navigation grid.
	GB::ClusterGreenhouse graphGenerator(sf::Vector2i{(int)NAV_GRID_DIM, (int)NAV_GRID_DIM});

	// Generate all of the clusters.
	// Each std::set of Point2D is a cluster.
	std::vector<std::set<sf::Vector2i, GB::IsVector2Less<int>>> clusterVector = graphGenerator.generateClusteredGraph(genOptions);

	// Create a vector of navigation weights. This is the cost associated with moving through a tile.
	// Each value in the vector corresponds to the cluster in clusterVector of the same index.
	std::vector<int> clusterNavigationWeights;
	GB::RandGen randGen;
	for (int i = 0; i < clusterVector.size(); ++i) {
		// randomly assign a weight for each cluster
		int weight = (int)randGen.uniDist(0, GB::BLOCKED_GRID_WEIGHT);
		clusterNavigationWeights.push_back(weight);
	}

	// Create a color for each cluster
	// The color gets more red the harder it is to move through the cluster
	std::vector<sf::Color> clusterColors;
	for (int i = 0; i < clusterVector.size(); ++i) {
		// More red the higher the value of clusterNavigationWeights
		sf::Uint8 red = (sf::Uint8)(255 * ((double)clusterNavigationWeights[i] / GB::BLOCKED_GRID_WEIGHT));
		sf::Uint8 green = 0;
		// Less blue the higher the value of clusterNavigationWeights
		sf::Uint8 blue = 255 - (sf::Uint8)(255 * ((double)clusterNavigationWeights[i] / GB::BLOCKED_GRID_WEIGHT));

		// Create an SFML color withe the calculated values
		sf::Color clusterColor(red, green, blue);

		// Store the color in the clusterColors vector
		// The index of the color in this vector matches the index of
		// cluster that it corresponds to
		clusterColors.emplace_back(std::move(clusterColor));
	}

	std::vector<sf::Drawable*> navGridSprites;
	// Fill visual grid
	for (unsigned int i = 0; i < NAV_GRID_DIM; i++) {
		for (unsigned int j = 0; j < NAV_GRID_DIM; j++) {
			// Create sprite to represent grid square
			sf::Sprite* gridSquare = new sf::Sprite(*gridTexture);
			const float gridOriginOffsetX = gridSquare->getLocalBounds().width / 2;
			const float gridOriginOffsetY = gridSquare->getLocalBounds().height / 2;

			// Scale the grid square sprite to be the correct size
			gridSquare->setScale(VISUAL_GRID_SCALE, VISUAL_GRID_SCALE);

			// Set the origin of the grid square to be the center of the square instead of the top left corner.
			// This just makes it easier to place the squares in the correct place
			gridSquare->setOrigin(gridOriginOffsetX, gridOriginOffsetY); //set origin to center of square

			// Put the square in its correct place
			gridSquare->move(i * gridSquare->getLocalBounds().width + gridOriginOffsetX, j * gridSquare->getLocalBounds().height + gridOriginOffsetY);

			// Unblocked squares will be yellow
			gridSquare->setColor(sf::Color::Yellow);

			// Make the initial weight of the square 0 (unblocked)
			navGrid->at(i, j)->weight = 0;

			// Add grids to storage
			static_cast<NavigationDemoData*>(navGrid->at(i, j))->demoSprite = gridSquare;

			// Tell GameRegion to draw square
			navGridSprites.push_back(gridSquare);
			addDrawable(0, gridSquare);
		}
	}

	// Give each cluster the correct color and navigation weight
	for (std::size_t i = 0; i < clusterVector.size(); ++i)
	{
		// Give each point the correct color and weight
		for (auto& point : clusterVector[i])
		{
			// Set the weight of the point
			navGrid->at(point.x, point.y)->weight = clusterNavigationWeights[i];

			// The navGrid is really of type NavigationDemoData. Cast it to this so that we can
			// access the sprite member of the grid data.
			NavigationDemoData* gridData = static_cast<NavigationDemoData*>(navGrid->at(point.x, point.y));

			// Set the color of the sprite representing the grid
			gridData->demoSprite->setColor(clusterColors[i]);
		}
	}
}

/// <summary>
/// Frees all dynamic memory allocated for this instance.
/// Resets the state of every member of this instance.
/// </summary>
void NavigationDemoRegion::destroy() {
	// Delete navigation data
	GB::freeAllNavigationGridData(*navGrid);

	// Free the navigation grid memory and prepare it for a future call to init
	navGrid.reset();

	// Reset pathfinder
	regionPathfinder.setNavigationGrid(nullptr);

	// Clear paths
	paths.clear();

	// Delete navigators
	// The navigators are managed by the vector
	// Clearing the vector is sufficient to free the memory for the navigators
	navigators.clear();

	// Clear all of GameRegion's references to drawables
	clearDrawables();

	//Delete textures and prepare them for future calls to init
	navigatorTexture.reset();
	gridTexture.reset();

	// Reset coordinate converter
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
/// Handles the button navigator1.
/// </summary>
void NavigationDemoRegion::Navigator1CB()
{
	// Changes the state of the region to only move the first navigator
	selectedNavigatorOption = SELECTED_NAVIGATOR_BUTTON_TYPE::NAVIGATOR_1;
	debugPrint("navigator1");
}

/// <summary>
/// Handles the button navigator2.
/// </summary>
void NavigationDemoRegion::Navigator2CB()
{
	// Changes the state of the region to only move the second navigator
	selectedNavigatorOption = SELECTED_NAVIGATOR_BUTTON_TYPE::NAVIGATOR_2;
	debugPrint("navigator2");
}

/// <summary>
/// Handles the button all navigators.
/// </summary>
void NavigationDemoRegion::AllNavigatorsCB()
{
	// Changes the state of the region to move both navigators
	selectedNavigatorOption = SELECTED_NAVIGATOR_BUTTON_TYPE::ALL_NAVIGATORS;
	debugPrint("all navigators");
}