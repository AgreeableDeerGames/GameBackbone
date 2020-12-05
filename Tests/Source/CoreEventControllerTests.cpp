#include "stdafx.h"

#include <GameBackbone/Core/CoreEventController.h>
#include <GameBackbone/Core/GameRegion.h>

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
class TestCoreEventController final : public CoreEventController
{
public:
	// ctr / dtr
	TestCoreEventController() {
		hasFinishedDraw = false;
		hasFinishedUpdate = false;
		hasFinishedHandleCoreEvent = false;
		hasFinishedHandleGuiEvent = false;
		hasFinishedSwap = false;
	}
	virtual ~TestCoreEventController() {}

	// test event functions
protected:
	void handleEvents(sf::Int64 /*elapsedTime*/) override
	{
		BOOST_CHECK(!hasFinishedHandleCoreEvent);
		BOOST_CHECK(!hasFinishedHandleGuiEvent);

		BOOST_CHECK(hasFinishedHandleCoreEvent);
		BOOST_CHECK(hasFinishedHandleGuiEvent);

		//Reset these flags to prevent multiple GUI events from trampling one another's results
		hasFinishedHandleCoreEvent = false;
		hasFinishedHandleGuiEvent = false;
	}

public:

	///// pretend to handle the gui event if its a LostFocus event
	//bool handleGuiEvent(sf::Event& event) override {
	//	if (event.type == sf::Event::LostFocus) {
	//		hasFinishedHandleGuiEvent = true;
	//		return true;
	//	}
	//	return false;
	//}

	///// always handle core events
	//bool handleCoreEvent(sf::Event& /*event*/) override {
	//	// handleCoreEvent only fires when the GUI does not handle the event
	//	BOOST_CHECK(!hasFinishedHandleGuiEvent);
	//	hasFinishedHandleCoreEvent = true;
	//	return true;
	//}

	void draw() override {
		hasFinishedDraw = true;
	}

	void update(sf::Int64 /*elapsedTime*/) override {
		hasFinishedUpdate = true;
	}

	void swapRegion() override {
		hasFinishedSwap = true;
		// Close the window after the last logic for runLoop finishes to avoid an infinite loop
		getWindow().close();
	}


	// handle event trackers
	bool hasFinishedHandleGuiEvent;
	bool hasFinishedHandleCoreEvent;
	bool hasFinishedDraw;
	bool hasFinishedUpdate;
	bool hasFinishedSwap;
};

/// <summary>
/// GameRegion that creates a child region.
/// Changes active region to child/parent region on update call.
/// </summary>
class TestGameRegion : public GB::GameRegion
{
public:

	/// <summary>shared_ptr of TestGameRegion</summary>
	using Ptr = std::shared_ptr<TestGameRegion>;

	TestGameRegion(bool shouldCreateChild = false) {
		if (shouldCreateChild) {
			TestGameRegion::Ptr child = std::make_shared<TestGameRegion>();
			addChild(child);
		}
	}
	~TestGameRegion() = default;

	/// <summary>
	/// change mark different region as active
	/// </summary>
	/// <param name="elapsedTime">The elapsed time.</param>
	void update(sf::Int64 /*elapsedTime*/) {
		if (parent) {
			setNextRegion(*parent);
		} else if (children.front()) {
			setNextRegion(*children.front().get());
		}
	}

	/// <summary>
	/// Adds a child to the TestGameRegion
	/// </summary>
	/// <param name="child"> </param>
	void addChild(TestGameRegion::Ptr child) {
		child->parent = this;
		children.emplace_back(std::move(child));
	}

	std::vector<TestGameRegion::Ptr> children;

private:
	GB::GameRegion* parent = nullptr;
};


BOOST_AUTO_TEST_SUITE(CoreEventController_CTRs)

// Test the constructor and destructor for memory leaks and correctness.
BOOST_AUTO_TEST_CASE(CoreEventController_default_CTR) {
	TestCoreEventController testController;
}

BOOST_AUTO_TEST_SUITE_END() // end CoreEventController_CTRs


BOOST_AUTO_TEST_SUITE(CoreEventController_Events)
/*
 // Tests the behavior of RunLoop when the sf window has no events
BOOST_AUTO_TEST_CASE(CoreEventController_RunLoop_No_Window_Event) {
	TestCoreEventController testController;
	GameRegion gameRegion;
	testController.setActiveRegion(&gameRegion);

	testController.runLoop();

	// ensure that the draw functions have been called
	BOOST_CHECK(testController.hasFinishedPreDraw);
	BOOST_CHECK(testController.hasFinishedDraw);
	BOOST_CHECK(testController.hasFinishedPostDraw);

	// ensure that neither or only one of handleGuiEvent and handleCoreEvent has fired
	BOOST_CHECK((!testController.hasFinishedHandleGuiEvent && !testController.hasFinishedHandleCoreEvent)||
				((testController.hasFinishedHandleGuiEvent || testController.hasFinishedHandleCoreEvent) &&
				!(testController.hasFinishedHandleGuiEvent && testController.hasFinishedHandleCoreEvent)));

	// if there has been a window event ensure that the pre and post event functions are called
	if (testController.hasFinishedHandleCoreEvent || testController.hasFinishedHandleGuiEvent) {
		BOOST_CHECK(testController.hasFinishedPreHandleEvent);
		BOOST_CHECK(testController.hasFinishedPostHandleEvent);
	}

	//ensure that the update functions have been called
	BOOST_CHECK(testController.hasFinishedPreUpdate);
	BOOST_CHECK(testController.hasFinishedUpdate);
	BOOST_CHECK(testController.hasFinishedPostUpdate);
}*/

// TODO: Write a swap tests

/*
// ensure that calling setActiveRegion changes to the correct active region
BOOST_AUTO_TEST_CASE(CoreEventController_setActiveRegion) {
	TestCoreEventController testController;

	GameRegion region1;
	testController.setActiveRegion(&region1);
	BasicGameRegion* returnedRegion = testController.getActiveRegion();

	//ensure that the region stored by testController is the one set by setActiveRegion
	BOOST_CHECK(returnedRegion == &region1);
}

// ensure that regions within the CoreEventController can correctly change the active region.
BOOST_AUTO_TEST_CASE(CoreEventController_setActiveRegion_From_Region) {
	TestCoreEventController testController;

	//create a region with a child
	TestGameRegion testRegion(true);

	//setup the first active region
	testController.setActiveRegion(&testRegion);

	//change to child region
	testController.getActiveRegion()->update(0);
	BOOST_CHECK(testController.getActiveRegion() == testRegion.children.front().get());

	//change back to parent region
	testController.getActiveRegion()->update(0);
	BOOST_CHECK(testController.getActiveRegion() == &testRegion);
}*/

BOOST_AUTO_TEST_SUITE_END() // end CoreEventController_Events

BOOST_AUTO_TEST_SUITE_END() // end CoreEventController Tests