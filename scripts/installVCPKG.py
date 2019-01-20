import sys
from sys import platform
import os.path
import os
import subprocess
from subprocess import Popen
from subprocess import Popen, PIPE, STDOUT



# Clone vcpkg from git



vcpkgPath = sys.argv[1]

# Run .bat file
# windows
if platform == "win32":
	print("Operating system found to be windows")
	
	exePath = vcpkgPath + r"\vcpkg.exe"
	print(exePath)
	if os.path.isfile(exePath) :
		print ("Found vcpkg.exe.")
	else:
		print ("Could not find vcpkg.exe. Running bootstrap-vcpkg.bat")
		batPath = vcpkgPath + r"\bootstrap-vcpkg.bat"
		print(batPath)
		p = Popen(batPath)
		stdout, stderr = p.communicate()
		
# linux
elif platform == "linux":
	print("linux")
# mac
elif platform == "darwin":
	print("mac")


# install commands
# windows
if platform == "win32":
	command = exePath + " install boost:x64-windows"
	print ("Running" + command)
	p = Popen(command, shell=True)
	stdout, stderr = p.communicate()
	
	command = exePath + " install sfml:x64-windows"
	print ("Running" + command)
	p = Popen(command, shell=True)
	stdout, stderr = p.communicate()
	
	command = exePath + " install tgui:x64-windows"
	print ("Running" + command)
	p = Popen(command, shell=True)
	stdout, stderr = p.communicate()
	
	command = exePath + " install box2d:x64-windows"
	print ("Running" + command)
	p = Popen(command, shell=True)
	stdout, stderr = p.communicate()

