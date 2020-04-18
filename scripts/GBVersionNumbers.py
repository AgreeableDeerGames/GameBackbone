import re

gb_version_regex = r"\"GameBackboneProject\" VERSION ([0-9]+\.[0-9]+\.[0-9]+)"
doxyfile_gb_versioin_regex = r"PROJECT_NUMBER\s+=\s+([0-9]+\.[0-9]+\.[0-9]+)"
install_consumer_gb_version_regex = r"find_package\(GameBackbone ([0-9]+\.[0-9]+\.[0-9]+) REQUIRED\)"

def get_gb_version(backbone_top_cmake_path):
    """
    Find the game backbone version number by searching the top level CMake file
    """
    with open(backbone_top_cmake_path, 'r') as file:
        cmake_text = file.read()
        regex_result = re.search(gb_version_regex, cmake_text)
        return regex_result.group(1)

def get_doxygen_version(doxyfile_path):
    """
    Find the game backbone version number in a Doxyfile
    """
    with open(doxyfile_path, 'r') as file:
        doxyfile_text = file.read()
        regex_result = re.search(doxyfile_gb_versioin_regex, doxyfile_text)
        return regex_result.group(1)

def get_install_consumer_gb_version(install_consumer_cmake_path):
    """
    Find the game backbone version number in the game backbone install consumer
    """
    with open(install_consumer_cmake_path, 'r') as file: 
        cmake_text = file.read()
        regex_result = re.search(install_consumer_gb_version_regex, cmake_text)
        return regex_result.group(1)


def set_gb_version(backbone_top_cmake_path, new_version):
    """
    Set the game backbone version number by searching the top level CMake file
    """
    with open(backbone_top_cmake_path, 'r+') as file:
        cmake_text = file.read()
        regex_result = re.sub(gb_version_regex, repl=r"\"GameBackboneProject\" VERSION " + new_version, string=cmake_text)
        file.seek(0)
        file.truncate()
        file.write(regex_result)

def set_doxygen_version(doxyfile_path, new_version):
    """
    Set the game backbone version number in a Doxyfile
    """
    with open(doxyfile_path, 'r+') as file:
        doxyfile_text = file.read()
        regex_result = re.sub(doxyfile_gb_versioin_regex, repl=r"PROJECT_NUMBER         = " + new_version, string=doxyfile_text)
        file.seek(0)
        file.truncate()
        file.write(regex_result)

def set_install_consumer_gb_version(install_consumer_cmake_path, new_version):
    """
    Set the game backbone version number in the game backbone install consumer
    """
    with open(install_consumer_cmake_path, 'r+') as file:
        cmake_text = file.read()
        replacement_text = f"find_package(GameBackbone {new_version} REQUIRED)"
        regex_result = re.sub(doxyfile_gb_versioin_regex, repl=replacement_text, string=cmake_text)
        file.seek(0)
        file.truncate()
        file.write(regex_result)
