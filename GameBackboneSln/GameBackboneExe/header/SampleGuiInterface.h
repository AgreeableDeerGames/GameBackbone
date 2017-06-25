#pragma once
#include <Util\stdafx.h>

#include <TGUI/TGUI.hpp>

#include <SFML/Graphics.hpp>

class SampleGuiInterface
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="SampleGuiInterface"/> class.
	/// Attaches the created GUI to the passed window
	/// </summary>
	/// <param name="attachedWindow">The attached window.</param>
	explicit SampleGuiInterface(sf::RenderWindow& attachedWindow);
	virtual ~SampleGuiInterface();

protected:
	tgui::Gui* gui;

};

