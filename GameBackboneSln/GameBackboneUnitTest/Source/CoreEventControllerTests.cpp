#include "stdafx.h"

#include <GameBackbone/Core/CoreEventController.h>
#include <GameBackbone/Util/DebugIncludes.h>

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
class TestCoreEventController : public CoreEventController
{

public:
	// ctr / dtr
	TestCoreEventController() {
		hasFinishedCoreDraw = false;
		hasFinishedCoreUpdate = false;
		hasFinishedHandleCoreEvent = false;
		hasFinishedHandleGuiEvent = false;
		hasFinishedPostDraw = false;
		hasFinishedPostHandleEvent = false;
		hasFinishedPostUpdate = false;
		hasFinishedPreDraw = false;
		hasFinishedPreHandleEvent = false;
		hasFinishedPreUpdate = false;
	}
	~TestCoreEventController() {}

	// test event functions

	/// pretend to handle the gui event if its a LostFocus event
	bool handleGuiEvent(sf::Event& event) override {
		//ensure that preHandleEvent has been called and the postHandleEvent has not
		BOOST_CHECK(hasFinishedPreHandleEvent);
		BOOST_CHECK(!hasFinishedPostHandleEvent);
		if (event.type == sf::Event::LostFocus) {
			hasFinishedHandleGuiEvent = true;
			return true;
		}
		return false;
	}

	/// always handle core events
	bool handleCoreEvent(sf::Event& /*event*/) override {
		//ensure that preHandleEvent has been called and the postHandleEvent has not
		BOOST_CHECK(hasFinishedPreHandleEvent);
		BOOST_CHECK(!hasFinishedPostHandleEvent);

		//handleCoreEvent only fires when the GUI does not handle the event
		BOOST_CHECK(!hasFinishedHandleGuiEvent);
		hasFinishedHandleCoreEvent = true;
		return true;
	}
	void preHandleEvent(sf::Event& /*event*/) override {
		hasFinishedPreHandleEvent = true;

		//ensure that preHandleEvent first before handleGuiEvent, handleCoreEvent and postHandleEvent
		BOOST_CHECK(!hasFinishedHandleCoreEvent && !hasFinishedHandleGuiEvent);
		BOOST_CHECK(!hasFinishedPostHandleEvent);
	}

	void postHandleEvent(sf::Event& /*event*/) override {
		hasFinishedPostHandleEvent = true;

		//ensure that postHandleEvent happens after preHandleEvent and either handleGuiEvent or handleCoreEvent
		BOOST_CHECK(hasFinishedPreHandleEvent);
		BOOST_CHECK(hasFinishedHandleCoreEvent || hasFinishedHandleGuiEvent);

		//Reset these flags to prevent multiple GUI events from trampling one another's results
		hasFinishedHandleCoreEvent = false;
		hasFinishedHandleGuiEvent = false;
		hasFinishedPostHandleEvent = false;
		hasFinishedPreHandleEvent = false;

	}

	//draw
	void preDraw() override {
		hasFinishedPreDraw = true;

		//ensure preDraw happens before coreDraw and postDraw
		BOOST_CHECK(!hasFinishedCoreDraw);
		BOOST_CHECK(!hasFinishedPostDraw);
	}
	void coreDraw() override {
		hasFinishedCoreDraw = true;

		//ensure that coreDraw happens after preDraw and before postDraw
		BOOST_CHECK(hasFinishedPreDraw);
		BOOST_CHECK(!hasFinishedPostDraw);
	}
	void postDraw() override {
		hasFinishedPostDraw = true;

		//ensure that post draw happens after both preDraw and coreDraw
		BOOST_CHECK(hasFinishedCoreDraw);
		BOOST_CHECK(hasFinishedPreDraw);
	}

	//update
	void preUpdate() override {
		hasFinishedPreUpdate = true;

		//ensure that preUpdate happens before coreUpdate and postUpdate
		BOOST_CHECK(!hasFinishedCoreUpdate);
		BOOST_CHECK(!hasFinishedPostUpdate);
	}
	void coreUpdate() override {
		hasFinishedCoreUpdate = true;

		//ensure that coreUpdate happens after preUpdate and before postUpdate
		BOOST_CHECK(!hasFinishedPostUpdate);
		BOOST_CHECK(hasFinishedPreUpdate);
	}

	void postUpdate() override {
		hasFinishedPostUpdate = true;

		//ensure that postUpdate happens after both preUpdate and coreUpdate
		BOOST_CHECK(hasFinishedPreUpdate);
		BOOST_CHECK(hasFinishedCoreUpdate);

		//close the window after the last logic for runLoop finishes to avoid an infinite loop
		m_window->close();
	}


	// handle event trackers
	bool hasFinishedHandleGuiEvent;
	bool hasFinishedHandleCoreEvent;
	bool hasFinishedPreHandleEvent;
	bool hasFinishedPostHandleEvent;

	// draw trackers
	bool hasFinishedPreDraw;
	bool hasFinishedCoreDraw;
	bool hasFinishedPostDraw;

	// update trackers
	bool hasFinishedPreUpdate;
	bool hasFinishedCoreUpdate;
	bool hasFinishedPostUpdate;

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
			giveActivation(*parent);
		} else if (children.front()) {
			giveActivation(*children.front().get());
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

 // Tests the behavior of RunLoop when the sf window has no events
BOOST_AUTO_TEST_CASE(CoreEventController_RunLoop_No_Window_Event) {
	TestCoreEventController testController;
	GameRegion gameRegion;
	testController.registerActiveRegion(gameRegion);

	testController.runLoop();

	// ensure that the draw functions have been called
	BOOST_CHECK(testController.hasFinishedPreDraw);
	BOOST_CHECK(testController.hasFinishedCoreDraw);
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
	BOOST_CHECK(testController.hasFinishedCoreUpdate);
	BOOST_CHECK(testController.hasFinishedPostUpdate);
}

// ensure that calling setActiveRegion changes to the correct active region
BOOST_AUTO_TEST_CASE(CoreEventController_setActiveRegion) {
	TestCoreEventController testController;

	GameRegion region1;
	testController.registerActiveRegion(region1);
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
	testController.registerActiveRegion(testRegion);

	//change to child region
	testController.getActiveRegion()->update(0);
	BOOST_CHECK(testController.getActiveRegion() == testRegion.children.front().get());

	//change back to parent region
	testController.getActiveRegion()->update(0);
	BOOST_CHECK(testController.getActiveRegion() == &testRegion);

}

BOOST_AUTO_TEST_SUITE_END() // end CoreEventController_Events

BOOST_AUTO_TEST_SUITE_END() // end CoreEventController Tests