from GetGBVersionNumbers import get_gb_version
from GetGBVersionNumbers import get_doxygen_version
from GetGBVersionNumbers import get_install_consumer_gb_version
import argparse
import os
import sys

def validate_version(gb_root):
    gb_cmake_path = os.path.join(gb_root, "CMakeLists.txt")
    doxyfile_path = os.path.join(gb_root, "Doxyfile")
    install_consumer_cmake_path = os.path.join(gb_root, "Tests", "InstallConsumer", "CMakeLists.txt")

    gb_version = get_gb_version(gb_cmake_path)
    doxy_gb_version = get_doxygen_version(doxyfile_path)
    install_consumer_cmake_gb_version = get_install_consumer_gb_version(install_consumer_cmake_path)

    return gb_version == doxy_gb_version == install_consumer_cmake_gb_version

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Checks that all instances of the GB version number match")
    parser.add_argument("--GB_ROOT", type=str, help="Root directory of GameBackbone", dest="gb_root", default=".")
    args = parser.parse_args()

    if validate_version(args.gb_root):
        sys.exit()

    sys.exit("versions do not match")