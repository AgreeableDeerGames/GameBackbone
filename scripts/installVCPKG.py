import sys
from sys import platform
import os
from subprocess import Popen, PIPE, STDOUT
import argparse
import zipfile
import shutil


def download_vcpkg(path):
    print("Downloading vcpkg from github")
    os.system("git clone https://github.com/lavinrp/ag_vcpkg.git {:s}".format(path))

def update_vcpkg(path, no_bootstrap):
    print("Updating vcpkg")
    orig_working_dir = os.getcwd()
    os.chdir(path)

    # calc vcpkg path
    # windows
    if platform == "win32":
        bin_path = os.path.join(path, "vcpkg.exe")
    # linux
    elif platform == "linux":
        bin_path = os.path.join(path, "vcpkg")
    elif platform == "darwin":
        pass # we might support mac later

    # Run update and upgrade
    os.system("git pull origin master")
    os.system("{:s} upgrade --no-dry-run".format(bin_path))

    # return original working dir
    os.chdir(orig_working_dir)



def linux_bootstrap(path):
    bootstrap_script_path = os.path.join(path, "bootstrap-vcpkg.sh")
    os.chmod(bootstrap_script_path, 0o755)
    os.system(bootstrap_script_path)
    bin_path = os.path.join(path, "vcpkg")
    if not os.path.exists(bin_path):
        print("Binary build failed, exiting now")
        exit(1)


def windows_bootstrap(path):
    bin_path = os.path.join(path, "vcpkg.exe")
    print(bin_path)
    print("Could not find vcpkg.exe. Running bootstrap-vcpkg.bat")
    script_path = os.path.join(path, "bootstrap-vcpkg.bat")
    print(script_path)
    p = Popen(script_path)
    stdout, stderr = p.communicate()
    if not os.path.isfile(bin_path):
        print("Binary build failed, exiting now")
        exit(1)


# Clone vcpkg from git
def main(path, download, no_bootstrap):
    vcpkgPath = path
    bin_path = ""
    if download is True:
        download_vcpkg(path)
    else:
        update_vcpkg(path, no_bootstrap)

    if not os.path.exists(os.path.normpath(vcpkgPath)):
        print("vcpkg path is not valid")
        exit(1)

    packages = ["boost", "sfml", "tgui", "box2d"]

    # Run .bat file
    # windows
    if platform == "win32":
        print("Operating system found to be windows")
        if no_bootstrap is False:
            windows_bootstrap(vcpkgPath)
        bin_path = os.path.join(vcpkgPath, "vcpkg.exe")
        os.environ["VCPKG_DEFAULT_TRIPLET"] = "x64-windows"

    # linux
    elif platform == "linux":
        print("OS: linux")
        if no_bootstrap is False:
            linux_bootstrap(vcpkgPath)
        bin_path = os.path.join(vcpkgPath, "vcpkg")

    # mac
    elif platform == "darwin":
        print("OS: mac")

    # install commands
    for package in packages:
        os.system("{:s} install {:s}".format(bin_path, package))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="This script runs vcpkg setup for multiple platforms")
    group = parser.add_mutually_exclusive_group(required=False)
    parser.add_argument("-p", "--vcpkg-path", help="Path to vcpkg", type=str, default="")
    group.add_argument("-d", "--download", help="Flag to choose to download vcpkg", default=False, action='store_true')
    group.add_argument("-nb", "--no-bootstrap", help="Flag to specify that bootstrap script should not be run"
                        "This option can only be used if vcpkg_path is specified", default=False, action='store_true')
    args = parser.parse_args()
    if args.vcpkg_path == '':
        print("A vcpkg path must be provided.")
        print(parser.usage())
        exit(1)
    main(args.vcpkg_path, args.download, args.no_bootstrap)
