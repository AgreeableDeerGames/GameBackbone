# GameBackbone
//TODO: describe backbone

***

## Getting Started (Windows)
### Environment
1. Download Visual Studio 2017 or above
2. Download all three folders from [here](https://drive.google.com/drive/folders/0B8DpBZPTQCGia21wUVl2MnFHRk0?usp=sharing)
  - You must unzip the files within the sub folders
3. Create environment variables that point to the include and lib folders of each 3rd party library used
  - The variables __must__ have the following names and __must__ correspond to the correct subfolder
  - Be sure to restart visual studio after setting the vars
  - A tutorial on how to set the vars can be found [here](https://www.techjunkie.com/environment-variables-windows-10/)


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
* ~~Boost unit test adapter~~ (currently does not work)
* OpenCppCoverage

### Productivity Assistants
It is recommended that you download the following 3rd party apps
* [CppCheck](http://cppcheck.sourceforge.net/)
  - Standalone app that does a better job than the visual studio plugin of the same name
  - Required to use the visual studio plugin of the same name
* [Doxygen](http://www.stack.nl/~dimitri/doxygen/index.html)
  - Used to build documentation that is output [here](https://lavinrp.github.io/GameBackbone/)

***

### Getting Started (Linux)
### Boost:
Preferably install boost with your package manager. There will be no need to include or link boost libraries outside of what is in the makefile if doing this.

Otherwise, grab boost and compile from source. Installing should place the libraries in a location where the system can find them - http://www.boost.org/doc/libs/1_61_0/more/getting_started/unix-variants.html

### SFML:
Preferably install SFML with your system's package manager. Make sure it is version 2.4.2 or above.

Otherwise, compile from source, v2.4.2 or greater. This may require editing the makefile to include paths.
https://www.sfml-dev.org/tutorials/2.0/start-linux.php

### TGUI:
TGUI needs to be installed after SFML is installed as TGUI uses SFML libraries.
Grab TGUI v0.7.4 from https://tgui.eu/download/
Install instructions https://tgui.eu/tutorials/v0.7/linux/
This will install toy our system

### Troubleshooting:
You may run into an error about not finding libtgui.so.0.7.4 while compiling. To solve this edit /etc/ld.so.conf and place the location TGUI installed to , /usr/local/lib , on a new line. Then run ldconfig as root.

### Building:
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

### Versioning
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
