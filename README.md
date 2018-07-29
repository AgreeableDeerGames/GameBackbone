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
- [1: GB User Guide](#1-gb-user-guide)
	- [1.1 Getting Started](#11-getting-started)
	- [1.2: Environment](#12-environment)
		- [1.2.1: GB_BuildVars.txt (preferred)](#121-gb_buildvarstxt-preferred)
		- [1.2.2: Environment Variables](#122-environment-variables)
	- [1.3: Versioning](#13-versioning)
	- [1.4 License](#14-license)
	- [1.5: How To Contribute](#15-how-to-contribute)
		- [1.5.1: Submitting Issues](#151-submitting-issues)
		- [1.5.2: Submitting Code/Fixes](#152-submitting-codefixes)
		- [1.5.3: Coding Guidelines](#153-coding-guidelines)
- [2: GB Developer Guide](#2-gb-developer-guide)
	- [2.1: IDE Setup](#21-ide-setup)
		- [2.1.1: Visual Studio](#211-visual-studio)
			- [2.1.1.1: Download C++](#2111-download-c)
			- [2.1.1.2: Download Extensions](#2112-download-extensions)
		- [2.1.2: Visual Studio Code](#212-visual-studio-code)
			- [2.1.2.1: Download Extensions](#2121-download-extensions)
			- [2.1.2.2: Set Working Directory](#2122-set-working-directory)
			- [2.1.2.3: Set Environment (Linux Only)](#2123-set-environment-linux-only)
	- [2.2: Productivity Assistants](#22-productivity-assistants)
	- [2.3: Running Tests](#23-running-tests)
		- [2.3.1: Visual Studio](#231-visual-studio)
		- [2.3.2: Visual Studio Code](#232-visual-studio-code)

<!-- /TOC -->

***

# 1: GB User Guide

## 1.1 Getting Started
* [Download](https://cmake.org/download/) CMake 3.8 or newer
* [Download](http://releases.llvm.org/download.html) the Clang Compiler 6.0.0 or newer
	* Other c++17 compliant compilers will probably work, but we only officially support Clang
* **Download** or **build** dependencies (ensure that the dependencies are compatible with your compiler)
  * SFML (2.5)
	  * [Download](https://drive.google.com/drive/folders/0B8DpBZPTQCGiay1HTUtZZk50VEk) Our Version
	  * [Their Website](https://www.sfml-dev.org/download.php)
  * TGUI (0.7.7)
	  * [Download](https://drive.google.com/drive/folders/0B8DpBZPTQCGiRWhtMDNZT0l3M0E) Our Version
	  * [Their Website](https://tgui.eu/download/)
  * BOOST (1.67)
	  * [Download](https://drive.google.com/drive/folders/0B8DpBZPTQCGiYW1fcEplLXhCRkU) Our Version
	  * [Their Website](https://www.boost.org/doc/libs/1_67_0/more/getting_started/index.html)

**Warning:** Many (if not all) of the packages used in GB are not compatible with the versions in most package managers. It is likely that you will need to download / install the libraries and tools on your own.

***

## 1.2: Environment

You can either use **GB_BuildVars.txt** or set **environment variables**

### 1.2.1: GB_BuildVars.txt (preferred)
GB_BuildVars.txt.example is included in the git repository. This file provides an example of how to format GB_BuildVars.txt. It is recommended that you just copy GB_BuildVars.txt.example to GB_BuildVars.txt.

Inside GB_BuildVars.txt replace the lines with <LIB_ROOT_PATH> with the path to the root folder of that lib.

Example: **<SFML_ROOT_PATH>** should be replaced with **/path/to/SFML**
The end of the path should be one level above the **/include** and **/lib** folders of each library.

### 1.2.2: Environment Variables

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


## 1.3: Versioning
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

## 1.4 License
See the license [here](https://github.com/lavinrp/GameBackbone/blob/master/LICENSE.txt)

***

## 1.5: How To Contribute

### 1.5.1: Submitting Issues
1. Create an issue [here](https://github.com/lavinrp/GameBackbone/issues)
2. Assign Ryan Lavin
3. Give a brief description of what is wrong and the steps to reproduce the error
4. Assign one or more tags to the issue that you think best summarizes it
5. Do not assign a project or milestone

### 1.5.2: Submitting Code/Fixes
1. Make sure your code is compliant with our [style guide](https://github.com/lavinrp/GameBackbone/blob/master/StyleGuide.txt)
2. Make sure your code compiles with no warnings (this includes [CppCheck](http://cppcheck.sourceforge.net/) warnings)
3. Make sure your code passes all unit tests
4. Make sure no memory leaks are detected in any of the unit tests
5. Create Pull Request
6. Assign Ryan Lavin as reviewer

### 1.5.3: Coding Guidelines

see [style guide](https://github.com/lavinrp/GameBackbone/blob/master/StyleGuide.txt)

***
# 2: GB Developer Guide

## 2.1: IDE Setup
### 2.1.1: Visual Studio
* [Download](https://visualstudio.microsoft.com/downloads/) Visual Studio 2017

#### 2.1.1.1: Download C++
Download the MSVC 14.0 toolset through the visual studio installer

#### 2.1.1.2: Download Extensions 
It is recommended that you download the following additions to visual studio
* [Download](https://marketplace.visualstudio.com/items?itemName=sergeb.GhostDoc) GhostDoc
* [Download](https://marketplace.visualstudio.com/items?itemName=VisualCPPTeam.TestAdapterforBoostTest) Test Adapter for Boost.Test
* [Download](https://marketplace.visualstudio.com/items?itemName=OpenCppCoverage.OpenCppCoveragePlugin) OpenCppCoverage

### 2.1.2: Visual Studio Code
* [Download](https://code.visualstudio.com/) Visual Studio Code

#### 2.1.2.1: Download Extensions
Download the following extensions
* [cpp tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) from microsoft
* [CMake Tools](https://marketplace.visualstudio.com/items?itemName=vector-of-bool.cmake-tools) from vector-of-bool
* [CMake Tools Helper](https://marketplace.visualstudio.com/items?itemName=maddouri.cmake-tools-helper) from Yassine MADDOURI

#### 2.1.2.2: Set Working Directory

Create a debug profile for the GameBackbone demo and/or unit tests by pointing the "Program" variable in launch.json to the respective executable file.
Set the current working directory of this profile to the folder where the executable files were generated.

#### 2.1.2.3: Set Environment (Linux Only)

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
## 2.2: Productivity Assistants
It is recommended that you download the following 3rd party apps
* [CppCheck](http://cppcheck.sourceforge.net/)
  - Standalone app that does a better job than the visual studio plugin of the same name
  - Required to use the visual studio plugin of the same name
* [Doxygen](http://www.stack.nl/~dimitri/doxygen/index.html)
  - Used to build documentation that is output [here](https://lavinrp.github.io/GameBackbone/)

***
## 2.3: Running Tests
Tests should be run before every push to the develop branch. No branch will be merged into develop if any new tests are failing.

### 2.3.1: Visual Studio
* Download the boost test adapter and run the tests from there
* Run the tests by launching the test project
* Open a developer command prompt in the bin folder for the solution and launch the test executable from the command prompt
* Run tests through CTest
### 2.3.2: Visual Studio Code
* Run CTest or run tests through the terminal
***
