import sys
from sys import platform
import os
from subprocess import Popen, PIPE, STDOUT
import argparse
import requests
import zipfile
import shutil


def download_vcpkg():
	print("Downloading vcpkg from github")
	zip_url = "https://github.com/Microsoft/vcpkg/archive/master.zip"
	s = requests.session()
	retry_count = 3
	while retry_count > 0:
		r = s.get(zip_url)
		if r.status_code == 200:
			break
		print("Unable to download, retrying")
		retry_count -= 1
	if retry_count == 0:
		print("Unable to retrieve vcpkg, exiting now")
		exit(1)
	zip_file_path = os.path.join(os.path.abspath(os.getcwd()), "vcpkg_zip.zip")

	with open(zip_file_path, "wb") as f:
		f.write(r.content)
	zip_folder_path = os.path.join(os.path.dirname(zip_file_path), "vcpkg_zip")
	zip_ref = zipfile.ZipFile(zip_file_path, "r")
	zip_ref.extractall(zip_folder_path)
	zip_ref.close()
	folder_path = os.path.join(os.path.dirname(zip_folder_path), "vcpkg")
	shutil.move(os.path.join(zip_folder_path, "vcpkg-master"), folder_path)
	shutil.rmtree(zip_folder_path)
	os.remove(zip_file_path)
	return folder_path


def linux_bootstrap(path):
	bootstrap_script_path = os.path.join(path, "bootstrap-vcpkg.sh")
	os.chmod(bootstrap_script_path, 0o755)
	os.system(bootstrap_script_path)
	bin_path = os.path.join(path, "vcpkg")
	if not os.path.exists(bin_path):
		print("Binary not built correctly, exiting now")
		exit(1)
	return bin_path


# Clone vcpkg from git
def main(path, download):

	if download is True:
		vcpkgPath = download_vcpkg()
	else:
		vcpkgPath = path

	# Run .bat file
	# windows
	if platform == "win32":
		print("Operating system found to be windows")

		exePath = vcpkgPath + r"\vcpkg.exe"
		print(exePath)
		if os.path.isfile(exePath) :
			print("Found vcpkg.exe.")
		else:
			print("Could not find vcpkg.exe. Running bootstrap-vcpkg.bat")
			batPath = vcpkgPath + r"\bootstrap-vcpkg.bat"
			print(batPath)
			p = Popen(batPath)
			stdout, stderr = p.communicate()

	# linux
	elif platform == "linux":
		print("linux")
		bin_path = linux_bootstrap(vcpkgPath)
		packages = ["boost", "sfml", "tgui", "box2d"]
		for package in packages:
			os.system("{:s} install {:s}".format(bin_path, package))
			
	# mac
	elif platform == "darwin":
		print("mac")

	# install commands
	# windows
	if platform == "win32":
		command = exePath + " install boost:x64-windows"
		print("Running" + command)
		p = Popen(command, shell=True)
		stdout, stderr = p.communicate()

		command = exePath + " install sfml:x64-windows"
		print("Running" + command)
		p = Popen(command, shell=True)
		stdout, stderr = p.communicate()

		command = exePath + " install tgui:x64-windows"
		print("Running" + command)
		p = Popen(command, shell=True)
		stdout, stderr = p.communicate()

		command = exePath + " install box2d:x64-windows"
		print("Running" + command)
		p = Popen(command, shell=True)
		stdout, stderr = p.communicate()


if __name__ == "__main__":
	parser = argparse.ArgumentParser(description="This script runs vcpkg setup for multiple platforms")
	group = parser.add_mutually_exclusive_group(required=True)
	group.add_argument("-p", "--vcpkg_path", help="Path to vcpkg", type=str, default="")
	group.add_argument("-d", "--download", help="Flag to choose to download vcpkg", action='store_true')
	args = parser.parse_args()
	main(args.vcpkg_path, args.download)
