

Dependencies:
SFML:
GameBackbone uses SFML as a general drawing library. We primarily use SFML's sprites, window management, and keyboard/mouse callbacks. sf::Sprite and sf::Shape inherit from sf::Drawable and sf::Transformable. We generally store these as sf::Drawable.
SFML also has an audio library that we may wrap in the future as an audio manager. It is a good place to start for clients looking into using audio.

TGUI:
GameBackbone uses TGUI as a general GUI library. TGUI's basic class is tgui::Widget. All of the GUI's components are made out of widgets. TGUI is built atop SFML, which allows for easy setting of sprites upon these widgets.

Box2d: (Optional/For Demo Only)
GameBackbone uses Box2d in our Platform Demo as a general physics engine. We only use it as an example for clients of how to integrate a physics engine and implement live graphic updates. If only our dll is needed, Box2d does not need to be built or linked.

Boost: (Optional/For Tests Only)
GameBackbone uses Boost only for their unit test library. This is exclusively utilized by our dev team 


Core Concepts:
Animated Sprite


Compound Sprite
A collection of sprites that behave as a single entity. They move, rotate, and animate as though they were

Game Region

Core Event Controller