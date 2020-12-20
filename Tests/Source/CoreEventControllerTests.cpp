#include "stdafx.h"

#include <GameBackbone/Core/CoreEventController.h>

#include <SFML/Graphics.hpp>

#include <chrono>
#include <memory>
#include <thread>
#include <vector>

using namespace GB;

// Contains all of the tests for CoreEventController
BOOST_AUTO_TEST_SUITE(CoreEventControllerTests)

/// <summary>
/// Fake CoreEventRontroller for testing functionality
/// </summary>
/// <seealso cref="CoreEventController" />
class OrderCECMock final : public CoreEventController
{
public:
	// ctr / dtr
	OrderCECMock() {
		hasFinishedHandleEvent = false;
		hasFinishedUpdate = false;
		hasFinishedDraw = false;
		hasFinishedSwap = false;
	}
	virtual ~OrderCECMock() {}

	// test event functions
protected:
	void handleEvents(sf::Int64 /*elapsedTime*/) override
	{
		BOOST_CHECK(!hasFinishedHandleEvent);
		BOOST_CHECK(!hasFinishedUpdate);
		BOOST_CHECK(!hasFinishedDraw);
		BOOST_CHECK(!hasFinishedSwap);

		hasFinishedHandleEvent = true;
	}

public:
	void update(sf::Int64 /*elapsedTime*/) override {
		BOOST_CHECK(hasFinishedHandleEvent);
		BOOST_CHECK(!hasFinishedUpdate);
		BOOST_CHECK(!hasFinishedDraw);
		BOOST_CHECK(!hasFinishedSwap);

		hasFinishedUpdate = true;
	}

	void draw() override {
		BOOST_CHECK(hasFinishedHandleEvent);
		BOOST_CHECK(hasFinishedUpdate);
		BOOST_CHECK(!hasFinishedDraw);
		BOOST_CHECK(!hasFinishedSwap);

		hasFinishedDraw = true;
	}

	void swapRegion() override {
		BOOST_CHECK(hasFinishedHandleEvent);
		BOOST_CHECK(hasFinishedUpdate);
		BOOST_CHECK(hasFinishedDraw);
		BOOST_CHECK(!hasFinishedSwap);

		hasFinishedSwap = true;
		// Close the window after the last logic for runLoop finishes to avoid an infinite loop
		getWindow().close();
	}

	// handle event trackers
	bool hasFinishedHandleEvent;
	bool hasFinishedUpdate;
	bool hasFinishedDraw;
	bool hasFinishedSwap;
};

// Test the constructor and destructor for memory leaks and correctness.
BOOST_AUTO_TEST_CASE(CoreEventController_default_CTR) {
	OrderCECMock testController;
}
// Tests the behavior of RunLoop when the sf window has no events
BOOST_AUTO_TEST_CASE(CoreEventController_RunLoop_No_Window_Event) {
	OrderCECMock testController;

	testController.runLoop();

	// Ensure that all functions have been called
	BOOST_CHECK(testController.hasFinishedHandleEvent);
	BOOST_CHECK(testController.hasFinishedUpdate);
	BOOST_CHECK(testController.hasFinishedDraw);
	BOOST_CHECK(testController.hasFinishedSwap);
}


class SwapCECMock final : public CoreEventController
{
public:
	SwapCECMock(BasicGameRegion* firstActiveRegion)
	{
		// Register the MainMenuDemoRegion as the active region
		setActiveRegion(firstActiveRegion);
	}

	void swapRegion() override
	{
		// Cache the previous GameRegion to test that it changed.
		BasicGameRegion* previousActiveRegion = getActiveRegion();
		// Call the actual function that is being tested.
		CoreEventController::swapRegion();
		BasicGameRegion* currentActiveRegion = getActiveRegion();

		// Check that the two GameRegions are different.
		BOOST_CHECK_NE(previousActiveRegion, currentActiveRegion);
	}
};

/// <summary>
/// GameRegion that creates a child region.
/// Changes active region to child/parent region on update call.
/// </summary>
class SwapGRMock : public GB::GameRegion
{
public:
	/// <summary>shared_ptr of TestGameRegion</summary>
	using Ptr = std::shared_ptr<SwapGRMock>;

	SwapGRMock(bool shouldCreateChild = false) : m_window(nullptr), m_parent(nullptr), m_updateCounter(0)
	{
		if (shouldCreateChild) {
			SwapGRMock::Ptr child = std::make_shared<SwapGRMock>();
			addChild(child);
		}
	}
	~SwapGRMock() = default;

	/// <summary>
	/// change mark different region as active
	/// </summary>
	/// <param name="elapsedTime">The elapsed time.</param>
	void update(sf::Int64 /*elapsedTime*/) {
		if (m_updateCounter > 3) {
			m_window->close();
		}

		if (m_parent) {
			setNextRegion(*m_parent);
		}
		else if (children.front()) {
			setNextRegion(*children.front().get());
		}
		m_updateCounter++;
	}

	/// <summary>
	/// Adds a child to the TestGameRegion
	/// </summary>
	/// <param name="child"> </param>
	void addChild(SwapGRMock::Ptr child) {
		child->m_parent = this;
		children.emplace_back(std::move(child));
	}
	
	// This must be called or we crash
	void setWindow(sf::RenderWindow* window) {
		m_window = window;
	}

	std::vector<SwapGRMock::Ptr> children;
	int m_updateCounter;

private:
	sf::RenderWindow* m_window;
	GB::GameRegion* m_parent;
};

// Tests the behavior of RunLoop when the sf window has no events
BOOST_AUTO_TEST_CASE(CoreEventController_SwapRegion) {
	SwapGRMock parentGameRegion(true);
	SwapCECMock testController{ &parentGameRegion };

	// Set the window on the GameRegion so it can call close on it. This must be called or we crash.
	parentGameRegion.setWindow(&testController.getWindow());

	// This runLoop call has the check for this test within swapRegion.
	testController.runLoop();

	// Ensure that the swapping actually happened and that the number of times updating was as expected.
	BOOST_CHECK_EQUAL(parentGameRegion.m_updateCounter, 5);
	BOOST_CHECK_EQUAL(parentGameRegion.children[0]->m_updateCounter, 4);
}

BOOST_AUTO_TEST_SUITE_END() // end CoreEventController Tests