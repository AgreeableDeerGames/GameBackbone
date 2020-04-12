from GetGBVersionNumbers import get_gb_version
from GetGBVersionNumbers import get_doxygen_version
from GetGBVersionNumbers import get_install_consumer_gb_version
import argparse
import os
import sys

def is_new_version_greater(new_version, old_version):
    new_version_elements = new_version.split('.')
    old_version_elements = old_version.split('.')
    new_major = int(new_version_elements[0])
    new_minor = int(new_version_elements[1])
    new_patch = int(new_version_elements[2])
    old_major = int(old_version_elements[0])
    old_minor = int(old_version_elements[1])
    old_patch = int(old_version_elements[2])
    if (new_major > old_major):
        return True
    if (new_major == old_major and new_minor > old_minor):
        return True
    if (new_major == old_major and new_minor == old_minor and new_patch > old_patch):
        return True
    return False

def validate_version(gb_root, last_version):
    gb_cmake_path = os.path.join(gb_root, "CMakeLists.txt")
    doxyfile_path = os.path.join(gb_root, "Doxyfile")
    install_consumer_cmake_path = os.path.join(gb_root, "Tests", "InstallConsumer", "CMakeLists.txt")

    gb_version = get_gb_version(gb_cmake_path)
    doxy_gb_version = get_doxygen_version(doxyfile_path)
    install_consumer_cmake_gb_version = get_install_consumer_gb_version(install_consumer_cmake_path)

    # versions always go up
    if (last_version is not None):
        if not is_new_version_greater(gb_version, last_version):
            return False
    # versions must be consistent
    return gb_version == doxy_gb_version == install_consumer_cmake_gb_version


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Checks that all instances of the GB version number match")
    parser.add_argument("--GB_ROOT", type=str, help="Root directory of GameBackbone", dest="gb_root", default="..")
    parser.add_argument("--LAST_VERSION", type=str, help="Version number of the previous release of GameBackbone", dest="last_version", default=None)
    args = parser.parse_args()

    if validate_version(args.gb_root, args.last_version):
        sys.exit()

    sys.exit("version is invalid")