#include "stdafx.h"

#include <Backbone\CoreEventController.h>
#include <Util\DebugIncludes.h>

#include <SFML\Graphics.hpp>

#include <thread>
#include <chrono>

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

		activeRegion = new GameRegion(*window);
	}
	~TestCoreEventController() {
		delete activeRegion;
	}

	// test event functions

	/// pretend to handle the gui event if its a LostFocus event
	virtual bool handleGuiEvent(sf::Event& event) override {
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
	virtual bool handleCoreEvent(sf::Event& event) override {
		//ensure that preHandleEvent has been called and the postHandleEvent has not
		BOOST_CHECK(hasFinishedPreHandleEvent);
		BOOST_CHECK(!hasFinishedPostHandleEvent);

		//handleCoreEvent only fires when the GUI does not handle the event
		BOOST_CHECK(!hasFinishedHandleGuiEvent);
		hasFinishedHandleCoreEvent = true;
		return true;
	}
	virtual void preHandleEvent(sf::Event& event) override {
		hasFinishedPreHandleEvent = true;

		//ensure that preHandleEvent first before handleGuiEvent, handleCoreEvent and postHandleEvent
		BOOST_CHECK(!hasFinishedHandleCoreEvent && !hasFinishedHandleGuiEvent);
		BOOST_CHECK(!hasFinishedPostHandleEvent);
	}

	virtual void postHandleEvent(sf::Event& event) override {
		hasFinishedPostHandleEvent = true;

		//ensure that postHandleEvent happens after preHandleEvent and either handleGuiEvent or handleCoreEvent
		BOOST_CHECK(hasFinishedPreHandleEvent);
		BOOST_CHECK(hasFinishedHandleCoreEvent || hasFinishedHandleGuiEvent);
	}

	//draw
	virtual void preDraw() override {
		hasFinishedPreDraw = true;

		//ensure preDraw happens before coreDraw and postDraw
		BOOST_CHECK(!hasFinishedCoreDraw);
		BOOST_CHECK(!hasFinishedPostDraw);
	}
	virtual void coreDraw() override {
		hasFinishedCoreDraw = true;

		//ensure that coreDraw happens after preDraw and before postDraw
		BOOST_CHECK(hasFinishedPreDraw);
		BOOST_CHECK(!hasFinishedPostDraw);
	}
	virtual void postDraw() override {
		hasFinishedPostDraw = true;

		//ensure that post draw happens after both preDraw and coreDraw
		BOOST_CHECK(hasFinishedCoreDraw);
		BOOST_CHECK(hasFinishedPreDraw);
	}

	//update
	virtual void preUpdate() override {
		hasFinishedPreUpdate = true;

		//ensure that preUpdate happens before coreUpdate and postUpdate
		BOOST_CHECK(!hasFinishedCoreUpdate);
		BOOST_CHECK(!hasFinishedPostUpdate);
	}
	virtual void coreUpdate() override {
		hasFinishedCoreUpdate = true;

		//ensure that coreUpdate happens after preUpdate and before postUpdate
		BOOST_CHECK(!hasFinishedPostUpdate);
		BOOST_CHECK(hasFinishedPreUpdate);
	}

	virtual void postUpdate() override {
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

};

BOOST_AUTO_TEST_SUITE(CoreEventController_ctrs)

// Test the constructor and destructor for memory leaks and correctness.
BOOST_AUTO_TEST_CASE(CoreEventController_default_ctr) {
	TestCoreEventController testController;
}

BOOST_AUTO_TEST_SUITE_END() // end CoreEventController_ctrs

BOOST_AUTO_TEST_SUITE(CoreEventController_Events)

 //Tests the behavior of RunLoop when the sf window has no events
BOOST_AUTO_TEST_CASE(CoreEventController_RunLoop_No_Window_Event) {
	TestCoreEventController testController;

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

BOOST_AUTO_TEST_SUITE_END() // end CoreEventController_Events

BOOST_AUTO_TEST_SUITE_END() // end CoreEventController Tests