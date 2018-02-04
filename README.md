# Pytheas-project
This project is a simple basic game framework written in c++ that I want to improve over time and add features to.
At the moment it's mostly bare bones but covers some basic boiler plate stuff but covers simple stuff like:
* Creating an OpenGL3 window
* Keyboard support
* Basic 2D collision
* Sprites

I started the project a little while ago working on it on and off originally it was using SFML as the underlying 
framework but it's been rewrtitten to remove the reliance on SFML and now the current project uses SDL though it's
been written to allow game code to be agnostic to whatever framework runs underneath.


## Current development dependencies
The following list is the current list of dependencies used by the project with the version currently used in brackets
* GLEW (2.0.0)
* GLM (0.9.8.4)
* SDL2_image (2.0.1)
* SDL2 (2.0.5)

## Feature roadmap (not ordered)
* Improve physics (possibly intergrate 3rd party library)
* Add networking support
* Add sound support
* Add support for authoring AI
* Create some tools for creating content