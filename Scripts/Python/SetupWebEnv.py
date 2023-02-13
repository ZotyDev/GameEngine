import os

import Utils

Utils.SYSTEM_ROOT = "C:"
Utils.PATH_EMSDK_WINDOWS = os.path.abspath(Utils.SYSTEM_ROOT + "/emsdk")

print(f"Installing EMSDK at {Utils.PATH_EMSDK_WINDOWS}..")
#Utils.GitCloneFrom("https://github.com/emscripten-core/emsdk.git", Utils.PATH_EMSDK_WINDOWS)
os.system("cd " + Utils.PATH_EMSDK_WINDOWS + " && git pull && emsdk install latest && emsdk activate latest --permanent")
