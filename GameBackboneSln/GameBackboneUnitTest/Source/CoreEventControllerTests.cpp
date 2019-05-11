#include "stdafx.h"

#include <GameBackbone/Core/CoreEventController.h>
#include <GameBackbone/Util/DebugIncludes.h>

#include <SFML/Graphics.hpp>

#include <thread>
#include <chrono>

using namespace GB;

// Contains all of the tests for CoreEventController
BOOST_AUTO_TEST_SUITE(CoreEventControllerTests)

/// <summary>
/// Fake CoreEventRontroller for testing functionality
/// </summary>
/// <seealso cref="CoreEventController" />
class TestCoreEventController : public CoreEventController<TestCoreEventController>
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
	virtual bool handleGuiEvent(sf::Event& event) {
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
	virtual bool handleCoreEvent(sf::Event& event) {
		//ensure that preHandleEvent has been called and the postHandleEvent has not
		BOOST_CHECK(hasFinishedPreHandleEvent);
		BOOST_CHECK(!hasFinishedPostHandleEvent);

		//handleCoreEvent only fires when the GUI does not handle the event
		BOOST_CHECK(!hasFinishedHandleGuiEvent);
		hasFinishedHandleCoreEvent = true;
		return true;
	}
	virtual void preHandleEvent(sf::Event& event) {
		hasFinishedPreHandleEvent = true;

		//ensure that preHandleEvent first before handleGuiEvent, handleCoreEvent and postHandleEvent
		BOOST_CHECK(!hasFinishedHandleCoreEvent && !hasFinishedHandleGuiEvent);
		BOOST_CHECK(!hasFinishedPostHandleEvent);
	}

	virtual void postHandleEvent(sf::Event& event) {
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
	virtual void preDraw() {
		hasFinishedPreDraw = true;

		//ensure preDraw happens before coreDraw and postDraw
		BOOST_CHECK(!hasFinishedCoreDraw);
		BOOST_CHECK(!hasFinishedPostDraw);
	}
	virtual void coreDraw() {
		hasFinishedCoreDraw = true;

		//ensure that coreDraw happens after preDraw and before postDraw
		BOOST_CHECK(hasFinishedPreDraw);
		BOOST_CHECK(!hasFinishedPostDraw);
	}
	virtual void postDraw() {
		hasFinishedPostDraw = true;

		//ensure that post draw happens after both preDraw and coreDraw
		BOOST_CHECK(hasFinishedCoreDraw);
		BOOST_CHECK(hasFinishedPreDraw);
	}

	//update
	virtual void preUpdate() {
		hasFinishedPreUpdate = true;

		//ensure that preUpdate happens before coreUpdate and postUpdate
		BOOST_CHECK(!hasFinishedCoreUpdate);
		BOOST_CHECK(!hasFinishedPostUpdate);
	}
	virtual void coreUpdate() {
		hasFinishedCoreUpdate = true;

		//ensure that coreUpdate happens after preUpdate and before postUpdate
		BOOST_CHECK(!hasFinishedPostUpdate);
		BOOST_CHECK(hasFinishedPreUpdate);
	}

	virtual void postUpdate() {
		hasFinishedPostUpdate = true;

		//ensure that postUpdate happens after both preUpdate and coreUpdate
		BOOST_CHECK(hasFinishedPreUpdate);
		BOOST_CHECK(hasFinishedCoreUpdate);

		//close the window after the last logic for runLoop finishes to avoid an infinite loop
		window->close();
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

	//region tracker
	GameRegion* getActiveGameRegion() {
		return activeRegion;
	}

};

/// <summary>
/// GameRegion that creates a child region.
/// Changes active region to child/parent region on behave call.
/// </summary>
class TestGameRegion : public GB::GameRegion
{
public:
	TestGameRegion(bool shouldCreateChild = false) {
		if (shouldCreateChild) {
			TestGameRegion* child = new TestGameRegion();
			addChildRegion(child);
		}
	}
	~TestGameRegion(){
		//free memory created for each child region.

		if (!childRegions.empty()) {
			delete childRegions.front();
		}
	}

	/// <summary>
	/// change mark different region as active
	/// </summary>
	/// <param name="currentTime">The current time.</param>
	virtual void behave(sf::Time currentTime) override {
		if (parentRegion) {
			setActiveRegionCB(parentRegion);
		} else if (childRegions.front()){
			setActiveRegionCB(childRegions.front());
		}
	}

private:

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
	testController.setActiveRegion(&gameRegion);

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

	//region constructed by TestCoreEventController is not required for this test
	GameRegion* defaultRegion = testController.getActiveGameRegion();
	delete defaultRegion;
	testController.setActiveRegion(nullptr);

	GameRegion region1;
	testController.setActiveRegion(&region1);
	GameRegion* returnedRegion = testController.getActiveGameRegion();

	//ensure that the region stored by testController is the one set by setActiveRegion
	BOOST_CHECK(returnedRegion == &region1);
}

// ensure that regions within the CoreEventController can correctly change the active region.
BOOST_AUTO_TEST_CASE(CoreEventController_setActiveRegion_From_Region) {
	TestCoreEventController testController;

	//region constructed by TestCoreEventController is not required for this test
	GameRegion* defaultRegion = testController.getActiveGameRegion();
	delete defaultRegion;
	testController.setActiveRegion(nullptr);

	//create a region with a child
	TestGameRegion testRegion(true);

	//register testRegion's callback to testController
	//this would normally be done from within testController with the "&testController" being replaced with "this"
	testRegion.registerSetActiveRegionCB(std::bind(&TestCoreEventController::setActiveRegion, &testController, std::placeholders::_1));

	for (auto child : *testRegion.getChildRegions())
	{
		child->registerSetActiveRegionCB(std::bind(&TestCoreEventController::setActiveRegion, &testController, std::placeholders::_1));
	}

	//setup the first active region
	testController.setActiveRegion(&testRegion);

	//change to child region
	testController.getActiveGameRegion()->behave(sf::Time());
	BOOST_CHECK(testController.getActiveGameRegion() == testRegion.getChildRegions()->front());

	//change back to parent region
	testController.getActiveGameRegion()->behave(sf::Time());
	BOOST_CHECK(testController.getActiveGameRegion() == &testRegion);

}

BOOST_AUTO_TEST_SUITE_END() // end CoreEventController_Events

BOOST_AUTO_TEST_SUITE_END() // end CoreEventController Tests