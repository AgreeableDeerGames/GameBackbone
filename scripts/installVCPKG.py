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
        print("Binary build failed, exiting now")
        exit(1)


def windows_bootstrap(path):
    bin_path = os.path.join(path, r"\vcpkg.exe")
    print(bin_path)
    print("Could not find vcpkg.exe. Running bootstrap-vcpkg.bat")
    script_path = os.path.join(path, r"\bootstrap-vcpkg.bat")
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
        vcpkgPath = download_vcpkg()

    if not os.path.exists(vcpkgPath):
        print("vcpkg path is not valid")
        exit(1)

    packages = ["boost", "sfml", "tgui", "box2d"]
    # Run .bat file
    # windows
    if platform == "win32":
        print("Operating system found to be windows")
        if no_bootstrap is False:
            windows_bootstrap(vcpkgPath)
        bin_path = os.path.join(vcpkgPath, r"\vcpkg.exe")

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
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("-p", "--vcpkg-path", help="Path to vcpkg", type=str, default="")
    group.add_argument("-d", "--download", help="Flag to choose to download vcpkg", default=False, action='store_true')
    parser.add_argument("-nb", "--no-bootstrap", help="Flag to specify that bootstrap script should not be run"
                        "This option can only be used if vcpkg_path is specified", default=False, action='store_true')
    args = parser.parse_args()
    if args.vcpkg_path == '' and args.no_bootstrap is True:
        print("Bootstrap scripts cannot be turned off if vcpkg_path is not specified")
        print(parser.usage())
        exit(0)
    main(args.vcpkg_path, args.download, args.no_bootstrap)
