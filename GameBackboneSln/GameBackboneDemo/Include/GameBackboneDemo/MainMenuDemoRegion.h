#pragma once

#include <GameBackboneDemo/DemoRegion.h>

#include <TGUI/TGUI.hpp>

#include <memory>

namespace EXE {

	/// <summary>
	/// Menu for selecting what demo region to display
	/// </summary>
	class MainMenuDemoRegion: public DemoRegion
	{
	public:
		/// <summary>shared_ptr to MainMenuDemoRegion</summary>
		using Ptr = std::shared_ptr<MainMenuDemoRegion>;

		// Constructors
		MainMenuDemoRegion(sf::RenderWindow & window);
		MainMenuDemoRegion() = delete;
		MainMenuDemoRegion(const MainMenuDemoRegion& other) = delete;
		MainMenuDemoRegion(MainMenuDemoRegion&& other) noexcept = delete;
		MainMenuDemoRegion& operator= (const MainMenuDemoRegion& other) = delete;
		MainMenuDemoRegion& operator= (MainMenuDemoRegion&& other) noexcept = delete;
		~MainMenuDemoRegion() = default;
	
	protected:
		/// <summary>
		/// The available demo types to choose from
		/// </summary>
		enum DEMO_OPTIONS_TYPE
		{
			#ifdef GAMEBACKBONE_BUILD_PLATFORM_DEMO
				PLATFORM_DEMO,
			#endif // GAMEBACKBONE_BUILD_PLATFORM_DEMO
			SCALE_ROTATION_DEMO,
			REGION_CHANGE_DEMO,
			ANIMATION_DEMO
		};

		// Initialization
		void init(sf::RenderWindow & window);
		void initGUI();

		// Handle TGUI Callbacks
		void platformRegionCB();
		void scaleAndRotationDemoCB();
		void regionChangeDemoCB();
		void animationDemoCB();

		// Storage
		std::vector<GB::GameRegion::Ptr> selectableRegions;
		tgui::Theme defaultTheme;
	};

}

