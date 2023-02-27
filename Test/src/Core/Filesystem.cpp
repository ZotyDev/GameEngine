#include <Core/Filesystem.hpp>
#include <gtest/gtest.h>

namespace UE
{
    const UEString AssetsTestDirectoryNameCorrect     = "AssetsTestDirectory";
    const UEString AssetsTestDirectoryNameWrongName   = "NotAssetsTestDirectory";

    const UEString AssetsTestFileNameCorrect     = AssetsTestDirectoryNameCorrect + "/AssetsTestFile.txt";
    const UEString AssetsTestFileNameWrongName   = AssetsTestDirectoryNameWrongName + "/NotAssetsTestFile.txt";

    const UEString TestFileContent = "the first line\nthe second line\n";

    //////////////////////////////////////////////////
    // Exist Directories
    TEST(Filesystem, Exists_Assets_Test_Directory_Correct_Any)
    {
        UEResult<UEBool> Result = Filesystem::Exists(AssetsTestDirectoryNameCorrect, Filesystem::Path::Assets);
        EXPECT_TRUE(Result);
        EXPECT_TRUE(Result.Value);
    }

    TEST(Filesystem, Exists_Assets_Test_Directory_Correct)
    {
        UEResult<UEBool> Result = Filesystem::Exists(AssetsTestDirectoryNameCorrect, Filesystem::Path::Assets, Filesystem::Target::Directory);
        EXPECT_TRUE(Result);
        EXPECT_TRUE(Result.Value);
    }

    TEST(Filesystem, Exists_Assets_Test_Directory_Wrong_Target)
    {
        UEResult<UEBool> Result = Filesystem::Exists(AssetsTestDirectoryNameCorrect, Filesystem::Path::Assets, Filesystem::Target::File);
        EXPECT_FALSE(Result);
    }

    TEST(Filesystem, Exists_Assets_Test_Directory_Wrong_Name)
    {
        UEResult<UEBool> Result = Filesystem::Exists(AssetsTestDirectoryNameWrongName, Filesystem::Path::Assets, Filesystem::Target::Directory);
        EXPECT_FALSE(Result);
    }

    ////////// ////////////////////////////////////////
    // Exist Files
    TEST(Filesystem, Exists_Assets_Test_File_Correct_Any)
    {
        UEResult<UEBool> Result = Filesystem::Exists(AssetsTestFileNameCorrect, Filesystem::Path::Assets);
        EXPECT_TRUE(Result);
        EXPECT_TRUE(Result.Value);
    }

    TEST(Filesystem, Exists_Assets_Test_File_Correct)
    {
        UEResult<UEBool> Result = Filesystem::Exists(AssetsTestFileNameCorrect, Filesystem::Path::Assets, Filesystem::Target::File);
        EXPECT_TRUE(Result);
        EXPECT_TRUE(Result.Value);
    }

    TEST(Filesystem, Exists_Assets_Test_File_Wrong_Target)
    {
        UEResult<UEBool> Result = Filesystem::Exists(AssetsTestFileNameCorrect, Filesystem::Path::Assets, Filesystem::Target::Directory);
        EXPECT_FALSE(Result);
        EXPECT_FALSE(Result.Value);
    }

    TEST(Filesystem, Exists_Assets_Test_File_Wrong_Name)
    {
        UEResult<UEBool> Result = Filesystem::Exists(AssetsTestFileNameWrongName, Filesystem::Path::Assets, Filesystem::Target::File);
        EXPECT_FALSE(Result);
        EXPECT_FALSE(Result.Value);
    }

    //////////////////////////////////////////////////
    // MakeSure
    TEST(Filesystem, MakeSure_Assets_Test_Directory_Correct)
    {
        UEResult<UEBool> Result = Filesystem::MakeSure(AssetsTestDirectoryNameCorrect, Filesystem::Path::Assets, Filesystem::Target::Directory);
        EXPECT_TRUE(Result);
        EXPECT_TRUE(Result.Value);
    }

    TEST(Filesystem, MakeSure_Assets_Test_Directory_Wrong_Target)
    {
        UEResult<UEBool> Result = Filesystem::MakeSure(AssetsTestDirectoryNameCorrect, Filesystem::Path::Internal, Filesystem::Target::File);
        EXPECT_FALSE(Result);
        EXPECT_FALSE(Result.Value);
    }

    TEST(Filesystem, MakeSure_Assets_Test_Directory_Wrong_Name)
    {
        UEResult<UEBool> Result = Filesystem::MakeSure(AssetsTestDirectoryNameWrongName, Filesystem::Path::Assets, Filesystem::Target::Directory);
        EXPECT_FALSE(Result);
        EXPECT_FALSE(Result.Value);
    }

    TEST(Filesystem, MakeSure_Assets_Test_File_Correct)
    {
        UEResult<UEBool> Result = Filesystem::MakeSure(AssetsTestFileNameCorrect, Filesystem::Path::Assets, Filesystem::Target::File);
        EXPECT_TRUE(Result);
        EXPECT_TRUE(Result.Value);
    }

    TEST(Filesystem, MakeSure_Assets_Test_File_Wrong_Target)
    {
        UEResult<UEBool> Result = Filesystem::MakeSure(AssetsTestFileNameCorrect, Filesystem::Path::Internal, Filesystem::Target::Directory);
        EXPECT_FALSE(Result);
        EXPECT_FALSE(Result.Value);
    }

    TEST(Filesystem, MakeSure_Assets_Test_File_Wrong_Name)
    {
        UEResult<UEBool> Result = Filesystem::MakeSure(AssetsTestFileNameWrongName, Filesystem::Path::Assets, Filesystem::Target::File);
        EXPECT_FALSE(Result);
        EXPECT_FALSE(Result.Value);
    }

    //////////////////////////////////////////////////
    // Write
    TEST(Filesystem, Write_Assets_Test_File_Overwrite)
    {
        UEResult<UEBool> Result = Filesystem::Write(AssetsTestFileNameCorrect, TestFileContent, Filesystem::WriteMode::Overwrite, Filesystem::Path::Assets);
        EXPECT_TRUE(Result);
        EXPECT_TRUE(Result.Value);
    }

    TEST(Filesystem, Write_Assets_Test_File_Append)
    {
        UEResult<UEBool> Result = Filesystem::Write(AssetsTestFileNameCorrect, TestFileContent, Filesystem::WriteMode::Append, Filesystem::Path::Assets);
        EXPECT_TRUE(Result);
        EXPECT_TRUE(Result.Value);
    }

    //////////////////////////////////////////////////
    // Read
    TEST(Filesystem, Read_Assets_Test_File)
    {
        UEResult<UEString> Result = Filesystem::Read(AssetsTestFileNameCorrect, Filesystem::Path::Assets);
        EXPECT_TRUE(Result);
        EXPECT_EQ(Result.Value, TestFileContent + TestFileContent);
    }

    //////////////////////////////////////////////////
    // Delete
    TEST(Filesystem, Delete_Assets_Test_Directory_Wrong_Name)
    {
        UEResult<UEBool> Result = Filesystem::Delete(AssetsTestDirectoryNameWrongName, Filesystem::Path::Assets, Filesystem::Target::Directory, true);
        EXPECT_TRUE(Result);
        EXPECT_TRUE(Result.Value);
    }

    TEST(Filesystem, Delete_Assets_Test_Directory_Wrong_Name_Not_Exist)
    {
        UEResult<UEBool> Result = Filesystem::Delete(AssetsTestDirectoryNameWrongName, Filesystem::Path::Assets, Filesystem::Target::Directory, true);
        EXPECT_FALSE(Result);
        EXPECT_FALSE(Result.Value);
    }
}