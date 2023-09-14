import os

import Utils

Utils.SYSTEM_ROOT = os.environ["ProgramFiles"]
Utils.PATH_LLVM_WINDOWS = os.path.abspath(Utils.SYSTEM_ROOT + "\\LLVM")
Utils.PATH_LLVM_WINDOWS_TEMP = os.path.abspath(Utils.PATH_LLVM_WINDOWS_TEMP)

Utils.DownloadFile(Utils.URL_LLVM, Utils.PATH_LLVM_WINDOWS_TEMP)
print(f"Installing LLVM at {Utils.PATH_LLVM_WINDOWS}..")
Utils.MakeSureFilepath(Utils.PATH_LLVM_WINDOWS)
os.system(Utils.PATH_LLVM_WINDOWS_TEMP + ' /S /D=' + Utils.PATH_LLVM_WINDOWS)
