# User Guide

## Dependencies:
### SFML:
GameBackbone uses SFML as a general drawing library. We primarily use SFML's sprites, window management, and keyboard/mouse callbacks. sf::Sprite and sf::Shape inherit from sf::Drawable and sf::Transformable. We generally store these as sf::Drawable.
SFML also has an audio library that we may wrap in the future as an audio manager. It is a good place to start for clients looking into using audio.

### Box2d: (Optional/For Demo Only)
GameBackbone uses Box2d in our Platform Demo as a general physics engine. We only use it as an example for clients of how to integrate a physics engine and implement live graphic updates. If only our dll is needed, Box2d does not need to be built or linked.

### Boost: (Optional/For Tests Only)
GameBackbone uses Boost only for their unit test library. This is exclusively utilized by our dev team to ensure stability of our codebase. If you do not want to run our tests boost does not need to be built or linked.

### GUI Library
GameBackbone makes no assumptions about use of GUI libraries. However the GameBackbone Demo uses TGUI. TGUI's basic class is tgui::Widget. All of the GUI's components are made out of widgets. TGUI is built atop SFML, which allows for easy setting of sprites upon these widgets.

## Core Concepts:
### Updatable:
Our base class for anything in GameBackbone that is regularly updated. Currently this includes AnimatedSprite, CompoundSprite, and GameRegion. Updatable is very simplistic in that it only have one member function `update` on it. The `update` function, takes in the time elapsed from the last `update` call.

### AnimatedSprite:
An sf::Sprite that has an AnimationSet. The intention of AnimatedSprite is to only show a small portion of it's texture at a time. This portion would contain a single still frame of the Sprite. The portion of the texture can then be moved to show a different still frame. This allows the AnimatedSprite to be a single Sprite but appear to be changing textures. AnimatedSprite inherits from Updatable, and implements `update`, which is what moves the sprites animation. AnimatedSprite inherits from sf::Sprite, and acts the same as sf:Sprite when drawing.

### CompoundSprite:
A collection of Drawable, Transformable, and (optionally) Updatable objects that behave as a single entity. They move, rotate, and update as though they were a single Sprite. CompoundSprite inherits from Updatable, and implements `update`, which calls `update` on all of the Updatables that it owns. CompoundSprite inherits from sf::Drawable, and implements the `draw`, which calls `draw` on all of the Drawables that it owns.

### GameRegion:
An abstract class representing anything in a game that contains game logic (levels, menus, loading screens, etc...). GameRegion inherits from Updatable, and implements `update` which is how they run through their logic. GameRegion inherits from sf::Drawable, and implements `draw`, which calls `draw` on all of the Drawables that it references. GameRegion does not own any of its Drawables. Users must take care to ensure that GameRegion is not drawn while holding dangling pointers to any Drawables.

### CoreEventController:
An abstract class representing GameBackbone's main loop. It creates and owns a window and requires that children handle the events from this window by implementing the `handleEvent` pure virtual member function. The CoreEventController also references a single “active” BasicGameRegion. 

The main loop provided by `CoreEventController::runLoop` first handles updates, draws the “active” region, updates the “active” region, then checks to see if a different BasicGameRegion should be made the “active” region for the next iteration of the loop. 

Each of these steps, with the exception of handling window events, has a default implementation. Each of these default implementations can be safely overridden by a child class if customization is required.
