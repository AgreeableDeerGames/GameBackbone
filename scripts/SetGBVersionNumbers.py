from GetGBVersionNumbers import set_gb_version
from GetGBVersionNumbers import set_doxygen_version
from GetGBVersionNumbers import set_install_consumer_gb_version

import argparse
import getopt
import os

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Updates GB VCPKG port to new version")
    parser.add_argument("--version", type=str, help="New GB version", dest="version")
    parser.add_argument("--gb_path", type=str, help="path to the top level folder of the GB repo", dest="gb_path")

    args = parser.parse_args()
    set_gb_version(os.path.join(args.gb_path, "CMakeLists.txt"), args.version)
    set_doxygen_version(os.pardir.join(args.gb_path, "Doxyfile"), args.version)
    set_install_consumer_gb_version(os.pardir.join(args.gb_path, "Tests", "InstallConsumer", "CMakeLists.txt"), args.version)