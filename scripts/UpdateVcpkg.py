from GBVersionNumbers import get_gb_version

import getopt
import re
import os
import argparse
import subprocess

def set_agvcpkg_portfile_version_number(portfile_text, new_version_string):
    """
    Update the version number of the portfile
    """
    return re.sub(pattern=r"REF ([0-9]+\.[0-9]+\.[0-9]+)", repl="REF " + new_version_string, string=portfile_text)


def set_agvcpkg_control_version_number(control_text, new_version_string):
    """
    Update the version number of the control file
    """
    return re.sub(pattern=r"Version: ([0-9]+\.[0-9]+\.[0-9]+)", repl="Version: " + new_version_string, string=control_text)

def set_agvcpkg_sha(portfile_text, new_sha):
    """
    Update the sha of the port file
    """
    return re.sub(pattern=r"SHA512 .+", repl="SHA512 " + new_sha, string=portfile_text)

def update_vcpkg_port(agvcpkg_path, new_sha, new_version_string):
    """
    update the sha and version number of the vcpkg portfile
    """
    portfile_path = os.path.join( agvcpkg_path, "portfile.cmake")
    with open(portfile_path, 'r+') as file:
        portfile_text = file.read()

        portfile_text = set_agvcpkg_sha(portfile_text, new_sha)
        portfile_text = set_agvcpkg_portfile_version_number(portfile_text, new_version_string)

        file.seek(0)
        file.truncate()
        file.write(portfile_text)

def update_vcpkg_control(agvcpkg_path, new_version_string):
    """
    update the sha and version number of the vcpkg control file
    """

    control_path = os.path.join( agvcpkg_path, "CONTROL")
    with open(control_path, 'r+') as file:
        control_text = file.read()

        control_text = set_agvcpkg_control_version_number(control_text, new_version_string)

        file.seek(0)
        file.truncate()
        file.write(control_text)

def update_vcpkg(gb_dir, vcpkg_gb_port_dir, sha):
    """
    Updates the VCPKG port for GB
    """
    cmake_file = "CMakeLists.txt"
    combined_path = os.path.join( gb_dir, cmake_file)
    version_string = get_gb_version(combined_path)
    update_vcpkg_control(vcpkg_gb_port_dir, version_string)
    update_vcpkg_port(vcpkg_gb_port_dir, sha, version_string)

def extract_sha_from_vcpkg_output(vcpkg_output: str):
    sha_match = re.search(pattern=r"(Actual hash: \[ )([a-zA-Z0-9]+)( \])", string=vcpkg_output)
    return sha_match.group(2)

def run_vcpkg_with_wrong_sha(vcpkg_folder_path: str):
    """
    Run VCPKG with wrong SHA to get it to give us the correct SHA
    """
    result = subprocess.run([os.path.join(vcpkg_folder_path, "vcpkg.exe"), "install", "gamebackbone:x64-windows"], stdout=subprocess.PIPE)
    sha = extract_sha_from_vcpkg_output(result.stdout.decode('utf-8'))
    return sha



if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Updates GB VCPKG port to new version")
    parser.add_argument("--gb_path", type=str, help="path to the top level folder of the GB repo", dest="gb_path")
    parser.add_argument("--gb_port_path", type=str, help="path to the GB port in VCPKG", dest="gb_port_path")
    parser.add_argument("--vcpkg_folder_path", type=str, help="VCPKG folder", dest="vcpkg_folder_path")
    args = parser.parse_args()

    gb_port_path = os.path.join(args.vcpkg_folder_path, "ports/gamebackbone")
    update_vcpkg(args.gb_path, gb_port_path, "1")
    sha = run_vcpkg_with_wrong_sha(args.vcpkg_folder_path)
    update_vcpkg(args.gb_path, gb_port_path, sha)
