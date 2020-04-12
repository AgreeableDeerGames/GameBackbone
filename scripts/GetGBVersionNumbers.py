import re

def get_gb_version(backbone_top_cmake_path):
    """
    Find the game backbone version number by searching the top level CMake file
    """
    with open(backbone_top_cmake_path, 'r') as file:
        cmake_text = file.read()
        regex_result = re.search(r"\"GameBackboneProject\" VERSION ([0-9]+\.[0-9]+\.[0-9]+)", cmake_text)
        return regex_result.group(1)

def get_doxygen_version(doxyfile_path):
    """
    Find the game backbone version number in a Doxyfile
    """
    with open(doxyfile_path, 'r') as file:
        doxyfile_text = file.read()
        regex_result = re.search(r"PROJECT_NUMBER\s+=\s+([0-9]+\.[0-9]+\.[0-9]+)", doxyfile_text)
        return regex_result.group(1)

def get_install_consumer_gb_version(install_consumer_cmake_path):
    pass