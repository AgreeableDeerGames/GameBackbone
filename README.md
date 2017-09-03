# GameBackbone
Open-source framework for developing 2D video games.

***

<!-- TOC depthFrom:1 depthTo:6 withLinks:1 updateOnSave:1 orderedList:0 -->

- [GameBackbone](#gamebackbone)
	- [Getting Started (Windows)](#getting-started-windows)
		- [Environment](#environment)
		- [Visual Studio](#visual-studio)
		- [Productivity Assistants](#productivity-assistants)
	- [Getting Started (Linux)](#getting-started-linux)
		- [Boost](#boost)
		- [SFML](#sfml)
		- [TGUI](#tgui)
		- [Troubleshooting](#troubleshooting)
		- [Building](#building)
	- [Running Tests](#running-tests)
		- [Windows](#windows)
		- [~~Linux~~](#linux)
	- [Coding Guidelines](#coding-guidelines)
	- [How To Contribute](#how-to-contribute)
		- [Submitting Issues](#submitting-issues)
		- [Submitting Code/Fixes](#submitting-codefixes)
	- [Versioning](#versioning)
	- [Authors](#authors)
	- [License](#license)

<!-- /TOC -->

***

## Getting Started (Windows)
### Environment
* Download Visual Studio 2017 or above
* Download all three folders from [here](https://drive.google.com/drive/folders/0B8DpBZPTQCGia21wUVl2MnFHRk0?usp=sharing)
  * You must unzip the files within the sub folders
* Create environment variables that point to the include and lib folders of each 3rd party library used
  * The variables __must__ have the following names and __must__ correspond to the correct subfolder
  * Be sure to restart visual studio after setting the vars
  * A tutorial on how to set the vars can be found [here](https://www.techjunkie.com/environment-variables-windows-10/)


 Variable Name | Variable Path                    
----------------|----------------------------------
 BOOST_INCLUDE  | yourBoostFolder__\include\boost-1_63__
 BOOST_LIB      | yourBoostFolder__\lib__
 SFML_INCLUDE   | yourSfmlFolder__\include__
 SFML_LIB       | yourSfmlFolder__\lib__
 TGUI_INCLUDE   | yourTguiFolder__\include__
 TGUI_LIB       | yourTguiFolder__\lib__


### Visual Studio
It is recommended that you download the following additions to visual studio
* GhostDoc
* Test Adapter for Boost.Test https://marketplace.visualstudio.com/items?itemName=VisualCPPTeam.TestAdapterforBoostTest
* OpenCppCoverage

### Productivity Assistants
It is recommended that you download the following 3rd party apps
* [CppCheck](http://cppcheck.sourceforge.net/)
  - Standalone app that does a better job than the visual studio plugin of the same name
  - Required to use the visual studio plugin of the same name
* [Doxygen](http://www.stack.nl/~dimitri/doxygen/index.html)
  - Used to build documentation that is output [here](https://lavinrp.github.io/GameBackbone/)

***

## Getting Started (Linux)
### Boost
Preferably install boost with your package manager. There will be no need to include or link boost libraries outside of what is in the makefile if doing this.

Otherwise, grab boost and compile from source. Installing should place the libraries in a location where the system can find them - http://www.boost.org/doc/libs/1_61_0/more/getting_started/unix-variants.html

### SFML
Preferably install SFML with your system's package manager. Make sure it is version 2.4.2 or above.

Otherwise, compile from source, v2.4.2 or greater. This may require editing the makefile to include paths.
https://www.sfml-dev.org/tutorials/2.0/start-linux.php

### TGUI
TGUI needs to be installed after SFML is installed as TGUI uses SFML libraries.
Grab TGUI v0.7.4 from https://tgui.eu/download/
Install instructions https://tgui.eu/tutorials/v0.7/linux/
This will install toy our system

### Troubleshooting
You may run into an error about not finding libtgui.so.0.7.4 while compiling. To solve this edit /etc/ld.so.conf and place the location TGUI installed to , /usr/local/lib , on a new line. Then run ldconfig as root.

### Building
To build the libraries and the demo, type ‘make’ at the project root. That will create the bld/ folder and an executable demo called demo. To run this, type ‘./demo’

‘Make clean’ will remove the bld folder

***

## Running Tests
### Windows
1. build the solution
2. right click the __GameBackboneBoostUnitTests1__ project
3. select "Set as startup project"
4. Run without debugging (ctrl + f5)

### ~~Linux~~
1. Not currently supported

***

## Coding Guidelines

see [style guide](https://github.com/lavinrp/GameBackbone/blob/master/StyleGuide.txt)

***

## How To Contribute

### Submitting Issues
1. Create an issue (here)[https://github.com/lavinrp/GameBackbone/issues]
2. Assign Ryan Lavin
3. Give a brief description of what is wrong and, if applicable, the steps to reproduce the error
4. Assign one or more tags to the issue that you think best summarizes it
5. Do not assign a project or milestone

### Submitting Code/Fixes
1. Make sure your code is compliant with our [style guide](https://github.com/lavinrp/GameBackbone/blob/master/StyleGuide.txt)
2. Make sure your code compiles with no warnings (this includes [CppCheck](http://cppcheck.sourceforge.net/) warnings)
3. Make sure your code passes all unit tests
4. Make sure no memory leaks are detected in any of the unit tests
5. Create Pull Request
6. Assign Ryan Lavin as reviewer

***

## Versioning
Major.Minor.Sprint
* Major
  - indicates full releases with significant feature additions / changes
* Minor
  - indicates a stable build
* Sprint
  - indicates a psudo-stable build at the end of each sprint

***

## Authors
* Ryan Lavin
* Michael Gyurgyak
* Brian Bauer
* Matthew McClellan
* Chris Ochs
* Kyle Peasley

***

## License
This project is licensed under the MIT license
