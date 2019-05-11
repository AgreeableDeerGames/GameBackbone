import os
import shutil
import subprocess
import time


#setup the current folder and destination folder for copying
currentDir = os.path.dirname(__file__)
desinationDir = os.path.join(currentDir, '')

#copy the exe to the current folder from the debug folder
originExe = os.path.join(currentDir, '../x64/Debug/GameBackboneBoostUnitTest1.exe')
destExe = os.path.join(desinationDir, 'GameBackboneBoostUnitTest1.exe')
shutil.copyfile(originExe, destExe)

#copy the dll to the current folder from the debug folder
originGBDll = os.path.join(currentDir, '../x64/Debug/GameBackboneDll.dll')
destGBDll = os.path.join(desinationDir, 'GameBackboneDll.dll')
shutil.copyfile(originGBDll, destGBDll)

for index in range(1,5):
	#run the tests
	process = subprocess.Popen([destExe], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	out, err = process.communicate()
	print(out.decode("utf-8"))
	print(err.decode("utf-8"))
	
	if err != b'\r\n*** No errors detected\r\n':
		#print(out)	
		f = open('MassTest.log', 'w')
		f.write(out.decode("utf-8"))

#with open('output.txt', 'wb') as f:
#    subprocess.check_call(destExe, stdout=f)
#with open('output.txt') as f:
#    for line in f:
#        print (line,)


#delete the files that were moved at the beginning to the current folder
os.remove(destExe)
os.remove(destGBDll)