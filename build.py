import os, sys, glob, subprocess

PROJ_NAME = "SpinningCube"
OPT_LEVEL = 0
DEBUG = True

ROOT_PATH = os.path.dirname(__file__)
LIB_PATH  = "/home/logan/Programming/Libraries"

"""
Filesystem Setup
"""

os.system(rf"cp -r {ROOT_PATH}/src/assets {ROOT_PATH}/bin")

"""
Building Main
"""

globbed_src_c_files = glob.glob(rf"{ROOT_PATH}/src/*.c")

build_cmd = ' '.join([
    "gcc",
    ' '.join(globbed_src_c_files),
    rf"{LIB_PATH}/glad/src/glad.c",
    rf"-o {ROOT_PATH}/bin/{PROJ_NAME}",
    rf"-I{ROOT_PATH}/include",
    rf"-I{LIB_PATH}/glad/include",
    rf"-I{LIB_PATH}/stb",
    rf"-I{LIB_PATH}/glfw-3.4/include",
    rf"-L{LIB_PATH}/glfw-3.4/bin/src",
    "-lglfw -lm",
    f"-O{OPT_LEVEL} {'-DDEBUG' if DEBUG else ''}",
    "-Wall"
])

if not os.system(build_cmd):
    exe_ext = ""
    if sys.platform == "win32":
        exe_ext = ".exe"

    errlvl = subprocess.run([rf"{ROOT_PATH}/bin/{PROJ_NAME}{exe_ext}"], cwd=rf"{ROOT_PATH}/bin").returncode
    
    print(f"\nProgram finished with exit code: {hex(errlvl & 0xffffffff)} ({errlvl & 0xffffffff})")
