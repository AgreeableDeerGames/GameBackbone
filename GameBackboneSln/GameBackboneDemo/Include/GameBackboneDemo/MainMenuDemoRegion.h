#pragma once

#include <GameBackboneDemo/DemoRegion.h>

#include <TGUI/TGUI.hpp>

namespace EXE {

	/// <summary>
	/// Menu for selecting what demo region to display
	/// </summary>
	class MainMenuDemoRegion: public DemoRegion
	{
	public:
		// Constructors
		MainMenuDemoRegion(sf::RenderWindow & window);
		~MainMenuDemoRegion();

		MainMenuDemoRegion() = delete;
		MainMenuDemoRegion(const MainMenuDemoRegion& other) = delete;
		MainMenuDemoRegion(MainMenuDemoRegion&& other) = delete;
		MainMenuDemoRegion& operator= (const MainMenuDemoRegion& other) = delete;
		MainMenuDemoRegion& operator= (MainMenuDemoRegion&& other) = delete;

		// Behavior
		void registerSetActiveRegionCB(std::function<void(GameRegion*)> newSetActiveRegionCB) override;
	
	protected:
		/// <summary>
		/// The available demo types to choose from
		/// </summary>
		enum DEMO_OPTIONS_TYPE
		{
			NAVIGATION_DEMO,
			PLATFORM_DEMO,
			SCALE_ROTATION_DEMO,
			REGION_CHANGE_DEMO
		};

		// Initialization
		void initGUI();

		// Handle TGUI Callbacks
		void navigationRegionCB();
		void platformRegionCB();
		void scaleAndRotationDemoCB();
		void regionChangeDemoCB();

		// Storage
		std::vector<GB::GameRegion*> selectableRegions;
		tgui::Theme defaultTheme;

	};

}

