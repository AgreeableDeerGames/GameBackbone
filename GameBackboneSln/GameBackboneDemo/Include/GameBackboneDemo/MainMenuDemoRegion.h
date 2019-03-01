#pragma once

#include <GameBackboneDemo/DemoRegion.h>

namespace EXE {

	/// <summary>
	/// Menu for selecting what demo region to display
	/// </summary>
	class MainMenuDemoRegion: public DemoRegion
	{
	public:
		// Ctrs / Dtr
		MainMenuDemoRegion(sf::RenderWindow & window);

		MainMenuDemoRegion() = delete;
		MainMenuDemoRegion(const MainMenuDemoRegion& other) = delete;
		MainMenuDemoRegion(MainMenuDemoRegion&& other) = delete;
		MainMenuDemoRegion& operator= (const MainMenuDemoRegion& other) = delete;
		MainMenuDemoRegion& operator= (MainMenuDemoRegion&& other) = delete;

		~MainMenuDemoRegion();

		// internal behavior alteration
		virtual void registerSetActiveRegionCB(std::function<void(GameRegion*)> newSetActiveRegionCB) override;
	
	private:

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

		// initialization
		void initGUI();

		// gui callbacks
		void navigationRegionCB();
		void platformRegionCB();
		void scaleAndRotationDemoCB();
		void regionChangeDemoCB();


		// storage
		std::vector<GB::GameRegion*> selectableRegions;

	};

}

