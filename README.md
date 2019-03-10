# GameBackbone
GameBackbone (GB) is a small, low-level, library meant to accelerate the
production of 2D video games. GB provides little to no gameplay logic and is
simply meant to help remove long overhead times when starting a new 2D game.
This narrow scope allows GB to maintain high performance and allows users of
GB to maintain total control over their codebase.
<br>
<br>
A good understanding of C++ is required to make use of GB. Game developers
who want to quickly make a game without a background in software development
should look into other solutions.

***


# GB User Guide

## Getting Started
* [Download](https://cmake.org/download/) CMake 3.8 or newer
* Supported c++ compiler
  * MSVC 14.1
  * Clang 7
  * GCC 7.3


## Versioning
We follow [Semantic Versioning](http://semver.org/spec/v2.0.0.html)
Major.Minor.Patch
* Major
  - Increments in Major version indicate backwards incompatible API changes
* Minor
  - indicates one or more backwards compatible functionality additions to the API
* Patch
  - Indicates one or more backwards compatible bug fixes

All versions before 1.0.0 are unstable and have no guarantee for backwards compatibility

***


See the license [here](https://github.com/lavinrp/GameBackbone/blob/master/LICENSE.txt)

***

##How To Contribute

### Submitting Issues
1. Create an issue [here](https://github.com/lavinrp/GameBackbone/issues)
2. Assign Ryan Lavin
3. Give a brief description of what is wrong and the steps to reproduce the error
4. Assign one or more tags to the issue that you think best summarizes it
5. Do not assign a project or milestone

### Submitting Code/Fixes
1. Make sure your code is compliant with our [style guide](https://github.com/lavinrp/GameBackbone/blob/master/StyleGuide.txt)
2. Make sure your code compiles with no warnings (this includes [CppCheck](http://cppcheck.sourceforge.net/) warnings)
3. Make sure your code passes all unit tests
4. Make sure no memory leaks are detected in any of the unit tests
5. Create Pull Request
6. Assign Ryan Lavin as reviewer

### Coding Guidelines

see [style guide](https://github.com/lavinrp/GameBackbone/blob/master/StyleGuide.txt)

***
# GB Developer Guide

## IDE Setup
### Visual Studio
* [Download](https://visualstudio.microsoft.com/downloads/) Visual Studio 2017

#### Download C++
Download the MSVC 14.0 toolset through the visual studio installer

#### Download Extensions 
It is recommended that you download the following additions to visual studio
* [Download](https://marketplace.visualstudio.com/items?itemName=sergeb.GhostDoc) GhostDoc
* [Download](https://marketplace.visualstudio.com/items?itemName=VisualCPPTeam.TestAdapterforBoostTest) Test Adapter for Boost.Test
* [Download](https://marketplace.visualstudio.com/items?itemName=OpenCppCoverage.OpenCppCoveragePlugin) OpenCppCoverage

### Visual Studio Code
* [Download](https://code.visualstudio.com/) Visual Studio Code

#### Download Extensions
Download the following extensions
* [cpp tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) from microsoft
* [CMake Tools](https://marketplace.visualstudio.com/items?itemName=vector-of-bool.cmake-tools) from vector-of-bool
* [CMake Tools Helper](https://marketplace.visualstudio.com/items?itemName=maddouri.cmake-tools-helper) from Yassine MADDOURI

#### Set Working Directory

Create a debug profile for the GameBackbone demo and/or unit tests by pointing the "Program" variable in launch.json to the respective executable file.
Set the current working directory of this profile to the folder where the executable files were generated.

#### Set Environment (Linux Only)

If you are on **linux** you must set your environment to load the correct .so files at runtime. 

Do this by setting the environment variable in your debug configuration to:

    "environment": 
    [
	    {
	        "name": "LD_LIBRARY_PATH",
	        "value": "path/to/SFML/lib:path/to/TGUI/lib"
	    }
    ],

***
## Productivity Assistants
It is recommended that you download the following 3rd party apps
* [CppCheck](http://cppcheck.sourceforge.net/)
  - Standalone app that does a better job than the visual studio plugin of the same name
  - Required to use the visual studio plugin of the same name
* [Doxygen](http://www.stack.nl/~dimitri/doxygen/index.html)
  - Used to build documentation that is output [here](https://lavinrp.github.io/GameBackbone/)

***
## Running Tests
Tests should be run before every push to the develop branch. No branch will be merged into develop if any new tests are failing.

### Visual Studio
* Download the boost test adapter and run the tests from there
* Run the tests by launching the test project
* Open a developer command prompt in the bin folder for the solution and launch the test executable from the command prompt
* Run tests through CTest
### Visual Studio Code
* Run CTest or run tests through the terminal
***
