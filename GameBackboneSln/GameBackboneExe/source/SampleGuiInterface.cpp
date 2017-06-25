#include <SampleGuiInterface.h>


SampleGuiInterface::SampleGuiInterface(sf::RenderWindow & attachedWindow) {
	
	auto theme = tgui::Theme::create("TGUI_Widgets/Black.txt");
	gui = new tgui::Gui(attachedWindow);

	//get window width and height
	auto windowWidth = tgui::bindWidth(*gui);
	auto windowHeight = tgui::bindHeight(*gui);

	tgui::EditBox::Ptr editBoxSearch = theme->load("EditBox");
	editBoxSearch->setSize(windowWidth * 2 / 3.0f, windowHeight / 10.0f);
	editBoxSearch->setDefaultText("test text");
	editBoxSearch->setPosition(0, windowHeight);
	gui->add(editBoxSearch);
}

SampleGuiInterface::~SampleGuiInterface() {
	delete gui;
}
