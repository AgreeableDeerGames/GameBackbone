# User Guide

## Dependencies:
### SFML:
GameBackbone uses SFML as a general drawing library. We primarily use SFML's sprites, window management, and keyboard/mouse callbacks. sf::Sprite and sf::Shape inherit from sf::Drawable and sf::Transformable. We generally store these as sf::Drawable.
SFML also has an audio library that we may wrap in the future as an audio manager. It is a good place to start for clients looking into using audio.

### TGUI:
GameBackbone uses TGUI as a general GUI library. TGUI's basic class is tgui::Widget. All of the GUI's components are made out of widgets. TGUI is built atop SFML, which allows for easy setting of sprites upon these widgets.

### Box2d: (Optional/For Demo Only)
GameBackbone uses Box2d in our Platform Demo as a general physics engine. We only use it as an example for clients of how to integrate a physics engine and implement live graphic updates. If only our dll is needed, Box2d does not need to be built or linked.

### Boost: (Optional/For Tests Only)
GameBackbone uses Boost only for their unit test library. This is exclusively utilized by our dev team to ensure stability of our codebase. If you are not on our internal dev team, boost does not need to be built or linked.


## Core Concepts:
### Updatable:
Our base class for anything in GameBackbone that is regularly updated. Currently this includes AnimatedSprite, CompoundSprite, and GameRegion. Updatable is very simplistic in that it only have one method "update" on it. The "update" method, takes in the time elapsed from the last "update" call.

### AnimatedSprite:
An sf::Sprite that has an AnimationSet on it. The intention of AnimatedSprite is to only show a small portion of it's texture at a time. This portion would contain a single still frame of the Sprite. The portion of the texture can then be moved to show a different still frame. This allows the AnimatedSprite to be a single Sprite but appear to be changing textures. AnimatedSprite inherits from Updatable, and implements the method "update", which is what move the sprites animated. AnimatedSprite inherits from sf::Sprite, and acts the same as sf:Sprite when drawing.

### CompoundSprite:
A collection of Sprites and AnimatedSprites that behave as a single entity. They move, rotate, and update as though they were a single Sprite. CompoundSprite inherits from Updatable, and implements the method "update", which calls "update" on all of the Updatables that it owns. CompoundSprite inherits from sf::Drawable, and implement the method "draw", which calls draw on all of the Drawables that it owns.

### GameRegion:
An abstract class representing anything in a game that contains game logic. GameRegions have neighbors, children, and a parent. GameRegion inherits from Updatable, and implements the method "update" which is how they run through their logic. They also call "update" on all of the Updatables that it references. GameRegion inherits from sf::Drawable, and implement the method "draw", which calls draw on all of the Drawables that it references. They have a tgui::Gui that they control and can handle callbacks for it. GameRegion is intended to be inherited from, and thus does not own any of its data.

### CoreEventController:
GameBackbone's main loop. It handles a single active GameRegion, activeRegion and sends all events to this GameRegion. It directs events to their correct handler, updates the activeRegion and then draws the activeRegion. Each of these 3 steps, is split into 3 substeps: premethod, method, postmethod.