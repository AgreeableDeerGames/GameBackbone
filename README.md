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

<!-- TOC depthFrom:1 depthTo:6 withLinks:1 updateOnSave:1 orderedList:0 -->

- [GameBackbone](#gamebackbone)
	- [Getting Started](#getting-started)
		- [Windows](#windows)
		- [Linux](#linux)
	- [Environment](#environment)
		- [GB_BuildVars.txt (preferred)](#gb_buildvarstxt-preferred)
		- [Environment Variables](#environment-variables)
	- [IDE Setup](#ide-setup)
		- [Visual Studio](#visual-studio)
			- [Download C++](#download-c)
			- [Download Extensions](#download-extensions)
		- [Visual Studio Code](#visual-studio-code)
			- [Download Extensions](#download-extensions-1)
			- [Misc Setup](#misc-setup)
				- [Set Working Directory](#set-working-directory)
				- [Set Environment (Linux Only)](#set-environment-linux-only)
		- [Productivity Assistants](#productivity-assistants)
	- [Running Tests](#running-tests)
		- [Visual Studio](#visual-studio-1)
		- [Visual Studio Code](#visual-studio-code-1)
	- [Coding Guidelines](#coding-guidelines)
	- [How To Contribute](#how-to-contribute)
		- [Submitting Issues](#submitting-issues)
		- [Submitting Code/Fixes](#submitting-codefixes)
	- [Versioning](#versioning)
	- [Authors](#authors)
	- [License](#license)

<!-- /TOC -->

***

## Getting Started

### Windows
* [Download](https://visualstudio.microsoft.com/downloads/) Visual Studio 2017 or Visual Studio Code
  * If ensure that you have the correct version of the msvc compiler (14.0)
* [Download](http://releases.llvm.org/download.html) LLVM/clang
* [Download](https://drive.google.com/drive/folders/0B8DpBZPTQCGia21wUVl2MnFHRk0?usp=sharing) pre-built dependencies
  * You must unzip the files within the sub folders

### Linux
* [Download](https://code.visualstudio.com/) Visual Studio Code
* [Download](http://releases.llvm.org/download.html) LLVM/clang
* [Download](https://cmake.org/download/) CMake 3.8 or above
* [Download](https://drive.google.com/drive/folders/0B8DpBZPTQCGia21wUVl2MnFHRk0?usp=sharing) pre-built dependencies or build them on your own
  * You must unzip the files within the sub folders

**Warning:** Many (if not all) of the packages used in GB are not compatible with the versions in most package managers. It is likely that you will need to download / install the libraries and tools on your own.

***

## Environment

You can either set **environment variables** or use **GB_BuildVars.txt**

### GB_BuildVars.txt (preferred)
GB_BuildVars.txt.example is included in the git repository. This file provides an example of how to format GB_BuildVars.txt. It is recommended that you just copy GB_BuildVars.txt.example to GB_BuildVars.txt.

Inside GB_BuildVars.txt replace the lines with <LIB_ROOT_PATH> with the path to the root folder of that lib.

Example: **<SFML_ROOT_PATH>** should be replaced with **/path/to/SFML**
The end of the path should be one level above the **/include** and **/lib** folders of each library.

### Environment Variables

* Create environment variables that point to the include and lib folders of each 3rd party library used
  * The variables __must__ have the following names and __must__ correspond to the correct subfolder
  * Be sure to restart visual studio / CMake after setting the vars
  * A tutorial on how to set the vars can be found [here](https://www.techjunkie.com/environment-variables-windows-10/) (windows) or [here](https://askubuntu.com/a/849954) (linux)


 Variable Name | Variable Path
---------------|----------------------------------
 BOOST_ROOT    | your/path/to/BOOST
 SFML_ROOT     | your/path/to/SFML
 TGUI_ROOT     | your/path/to/TGUI


***

## IDE Setup
### Visual Studio

#### Download C++
Download the MSVC 14.0 toolset 

#### Download Extensions 
It is recommended that you download the following additions to visual studio
* [Download](https://marketplace.visualstudio.com/items?itemName=sergeb.GhostDoc) GhostDoc
* [Download](https://marketplace.visualstudio.com/items?itemName=VisualCPPTeam.TestAdapterforBoostTest) Test Adapter for Boost.Test
* [Download](https://marketplace.visualstudio.com/items?itemName=OpenCppCoverage.OpenCppCoveragePlugin) OpenCppCoverage

### Visual Studio Code

#### Download Extensions
Download the following extensions
* [cpp tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) from microsoft
* [CMake Tools](https://marketplace.visualstudio.com/items?itemName=vector-of-bool.cmake-tools) from vector-of-bool
* [CMake Tools Helper](https://marketplace.visualstudio.com/items?itemName=maddouri.cmake-tools-helper) from Yassine MADDOURI

#### Misc Setup

##### Set Working Directory

Create a debug profile for the GameBackbone demo and/or unit tests by pointing the "Program" variable in launch.json to the respective executable file.
Set the current working directory of this profile to the folder where the executable files were generated.

##### Set Environment (Linux Only)

If you are on **linux** you must set your environment to load the correct .so files at runtime. 

Do this by setting the environment variable in your debug configuration to:

    "environment": 
    [
	    {
	        "name": "LD_LIBRARY_PATH",
	        "value": "path/to/SFML/lib:path/to/TGUI/lib"
	    }
    ],


### Productivity Assistants
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
### Visual Studio Code
* Create a new debug profile to launch the test executable in the launch.json file

***

## Coding Guidelines

see [style guide](https://github.com/lavinrp/GameBackbone/blob/master/StyleGuide.txt)

***

## How To Contribute

### Submitting Issues
1. Create an issue [here](https://github.com/lavinrp/GameBackbone/issues)
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

## Authors
* Ryan Lavin
* Michael Gyurgyak
* Brian Bauer
* Matthew McClellan
* Chris Ochs
* Kyle Peasley

***

## License
See the license [here](https://github.com/lavinrp/GameBackbone/blob/master/LICENSE.txt)

