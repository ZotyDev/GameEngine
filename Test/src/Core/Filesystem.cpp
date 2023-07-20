#include <Core/PlatformIndependenceLayer/Filesystem.hpp>
#include <gtest/gtest.h>

namespace UE
{
    const UEString AssetsTestDirectoryNameCorrect     = "AssetsTestDirectory";
    const UEString AssetsTestDirectoryNameWrongName   = "NotAssetsTestDirectory";

    const UEString AssetsTestFileNameCorrect     = AssetsTestDirectoryNameCorrect + "/AssetsTestFile.txt";
    const UEString AssetsTestFileNameWrongName   = AssetsTestDirectoryNameCorrect + "/NotAssetsTestFile.txt";

    const UEString TestFileContent = "the first line\nthe second line\n";
}