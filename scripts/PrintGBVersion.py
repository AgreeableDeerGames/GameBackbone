from GBVersionNumbers import get_gb_version
from GBVersionNumbers import get_doxygen_version
from GBVersionNumbers import get_install_consumer_gb_version
import argparse
import os
import sys

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Returns the version number of GameBackbone")
    parser.add_argument("--GB_ROOT", type=str, help="Root directory of GameBackbone", dest="gb_root", default="..")
    args = parser.parse_args()
    gb_cmake_path = os.path.join(args.gb_root, "CMakeLists.txt")
    print(get_gb_version(gb_cmake_path), end="")