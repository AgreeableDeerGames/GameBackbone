#pragma once

#include <DemoRegion.h>

namespace EXE {

	/// <summary>
	/// Menu for selecting what demo region to display
	/// </summary>
	class DemoSelectionRegion : public DemoRegion
	{
	public:
		// Ctrs / Dtr
		DemoSelectionRegion(sf::RenderWindow & window);

		DemoSelectionRegion() = delete;
		DemoSelectionRegion(const DemoSelectionRegion& other) = delete;
		DemoSelectionRegion(DemoSelectionRegion&& other) = delete;
		DemoSelectionRegion& operator= (const DemoSelectionRegion& other) = delete;
		DemoSelectionRegion& operator= (DemoSelectionRegion&& other) = delete;

		~DemoSelectionRegion();

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
			SWIRLY_DEMO,
			REGION_CHANGE_DEMO
		};

		// initialization
		void initGUI();

		// gui callbacks
		void navigationRegionCB();
		void swirlyDemoCB();
		void regionChangeDemoCB();

	};

}

