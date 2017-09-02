# GameBackbone
//TODO: describe backbone

## Getting Started (Windows)
### Environment
1. Download all three folders from [here](https://drive.google.com/drive/folders/0B8DpBZPTQCGia21wUVl2MnFHRk0?usp=sharing)
2. Create environment variables that point to the include and lib folders of each 3rd party library used.
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
