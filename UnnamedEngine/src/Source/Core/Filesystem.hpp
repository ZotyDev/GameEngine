#pragma once

#include "Core/Base.hpp"

namespace UE
{
    // Todo: Zoty
    // Create a struct to hold the filters of file selector dialog
    class Filesystem
    {
    public:
        enum class Path: UEUint8
        {
            Internal       = 0,
            Assets         = 1,
            UserDataFolder = 2
        };

        enum class Target : UEUint8
        {
            Any       = 0,
            Directory = 1,
            File      = 2
        };

        enum class WriteMode : UEUint8
        {
            Overwrite = 0,
            Append    = 1
        };

        static inline constexpr UEString PathToString(Filesystem::Path path)
        {
            switch(path)
            {
                case Filesystem::Path::Assets        : return "Assets"        ; break;
                case Filesystem::Path::Internal      : return "Internal"      ; break;
                case Filesystem::Path::UserDataFolder: return "UserDataFolder"; break;
                default: return "UE_INVALID_PATH"; break;
            }
        }

        static inline constexpr UEString TargetToString(Filesystem::Target target)
        {
            switch(target)
            {
                case Filesystem::Target::Any      : return "Any"       ; break;
                case Filesystem::Target::File     : return "File"      ; break;
                case Filesystem::Target::Directory: return "Directory" ; break;
                default: return "UE_INVALID_TARGET"; break;
            }
        }

    public:
        //static UEResult<UEPath> SelectorDialog(const std::vector<std::pair<UEString, UEString>>& filters, Filesystem::Path enginePath = Filesystem::Path::Assets, Filesystem::Target target = Filesystem::Target::Any);
        static UEResult<UEBool> Exists(const UEPath& path, Filesystem::Path enginePath = Filesystem::Path::Assets, Filesystem::Target target = Filesystem::Target::Any)
        {
            std::error_code Error;

            // Prepend the data location
            UEPath FinalPath = _PrependLocation(path, enginePath);

            // Check if the file exists
            UEResult<UEBool> Result(std::filesystem::exists(FinalPath, Error));
            // Check for errors related to the check
            if (Error)
            {
                UE_LOG_CORE_ERROR("Filesystem::Exists: Failed to check if '{}' exists - {}", FinalPath.string(), Error.message());
                return UEResult<UEBool>(false, UEResult<>::Error);
            }

            // File exist
            if (Result)
            {
                // Check target
                UEBool IsSame = _SameAsTarget(FinalPath, target);
                if (!IsSame)
                {
                    UE_LOG_CORE_ERROR("Filesystem::Exists: '{}' does exist but has different target - expected: '{}'", FinalPath.string(), Filesystem::TargetToString(target));
                    Result.Value = false;
                    return Result;
                }
                else
                {
                    return Result;
                }
            }
            else
            {
                UE_LOG_CORE_WARN("Filesystem::Exists: '{}' does not exist", FinalPath.string());
                return Result;
            }
        }

        static UEResult<UEBool> MakeSure(const UEPath& path, Filesystem::Path enginePath = Filesystem::Path::Assets, Filesystem::Target target = Filesystem::Target::Any)
        {
            // Check if the file should be created
            if (!Exists(path, enginePath, target))
            {
                std::error_code Error;
                UEPath FinalPath = _PrependLocation(path, enginePath);
                // If the target is any, we should detect what to create
                if (target == Filesystem::Target::Any)
                {
                    // Check if target is a file
                    if (FinalPath.filename().string().find('.') != std::string::npos)
                    {
                        std::ofstream output;
                        output.open(FinalPath);
                        if (output.is_open())
                        {
                            output.close();
                            UE_LOG_CORE_WARN("Filesystem::MakeSure: Created '{}'", FinalPath.string());
                            return UEResult<UEBool>(false);
                        }
                        else
                        {
                            UE_LOG_CORE_ERROR("Filesystem::MakeSure: Failed to create '{}'", FinalPath.string());
                            return UEResult<UEBool>(false, UEResult<>::Error); 
                        }
                    }
                    else
                    {
                        std::filesystem::create_directory(FinalPath, Error);
                        if (Error)
                        {
                            UE_LOG_CORE_ERROR("Filesystem::MakeSure: Failed to create '{}' - {}", FinalPath.string(), Error.message());
                            return UEResult<UEBool>(false, UEResult<>::Error);
                        }
                        UE_LOG_CORE_WARN("Filesystem::MakeSure: Created '{}'", FinalPath.string());
                        return UEResult<UEBool>(false);
                    }
                }
                // Make sure file
                else if (target == Filesystem::Target::File)
                {
                    std::ofstream output;
                    output.open(FinalPath);
                    if (output.is_open())
                    {
                        output.close();
                        UE_LOG_CORE_WARN("Filesystem::MakeSure: Created '{}'", FinalPath.string());
                        return UEResult<UEBool>(false);
                    }
                    else
                    {
                        UE_LOG_CORE_ERROR("Filesystem::MakeSure: Failed to create '{}'", FinalPath.string());
                        return UEResult<UEBool>(false, UEResult<>::Error); 
                    }
                }
                // Make sure directory
                else if (target == Filesystem::Target::Directory)
                {
                    // Check if the target path is a filename with extension
                    if (FinalPath.filename().string().find('.') != std::string::npos)
                    {
                        UE_LOG_CORE_ERROR("Filesystem::MakeSure: Failed to create '{}' - '.' is not allowed inside directory names", FinalPath.string());
                        return UEResult<UEBool>(false);
                    }

                    std::filesystem::create_directory(FinalPath, Error);
                    if (Error)
                    {
                        UE_LOG_CORE_ERROR("Filesystem::MakeSure: Failed to create '{}' - {}", FinalPath.string(), Error.message().c_str());
                        return UEResult<UEBool>(false, UEResult<>::Error);
                    }
                    UE_LOG_CORE_WARN("Filesystem::MakeSure: Created '{}'", FinalPath);
                    return UEResult<UEBool>(false);
                }
            }

            return UEResult<UEBool>(true);
        }

        static UEResult<UEBool> Write(const UEPath& path, const UEString& data, Filesystem::WriteMode writeMode = Filesystem::WriteMode::Overwrite, Filesystem::Path enginePath = Filesystem::Path::Assets)
        {
            // Make sure the file exists
            MakeSure(path, enginePath, Filesystem::Target::File);

            // Open file
            UEPath FinalPath = _PrependLocation(path, enginePath);
            std::ofstream Output;
            switch (writeMode)
            {
                case Filesystem::WriteMode::Overwrite: Output.open(FinalPath, std::ofstream::out | std::ofstream::trunc); break;
                case Filesystem::WriteMode::Append: Output.open(FinalPath, std::ofstream::out | std::ofstream::app); break;
            }

            // Something went wrong
            if (!Output.is_open())
            {
                UE_LOG_CORE_ERROR("Filesystem::Write: Failed to write \n'{}'\nCould not open '{}'", data, FinalPath.string());
                return UEResult<UEBool>(false, UEResult<>::Error);
            }

            // Write data to file
            Output << data;

            Output.close();

            return UEResult<UEBool>(true);
        }

        static UEResult<UEString> Read(const UEPath& path, Filesystem::Path enginePath = Filesystem::Path::Assets)
        {
            // Check if file exists
            if (!Exists(path, enginePath, Filesystem::Target::File))
            {
                UE_LOG_CORE_ERROR("Filesystem::Read: '{}' does not exist");
                return UEResult<UEString>("UE_STRING_PLACEHOLDER", UEResult<>::Error);
            }

            // Open file
            UEPath FinalPath = _PrependLocation(path, enginePath);
            std::ifstream Input;
            Input.open(FinalPath);

            // Something went wrong
            if (!Input.is_open())
            {
                UE_LOG_CORE_ERROR("Filesystem::Read: Could not open '{}'", FinalPath.string());
                return UEResult<UEString>("UE_STRING_PLACEHOLDER", UEResult<>::Error);
            }

            // Read data from file
            UEResult<UEString> Result(UEResult<>::Success);
            std::stringstream Buffer;
            Buffer << Input.rdbuf();
            Result.Value = Buffer.str();

            return Result;
        }

        static UEResult<UEBool> Delete(const UEPath& path, Filesystem::Path enginePath = Filesystem::Path::Assets, Filesystem::Target target = Filesystem::Target::Any, UEBool recursive = false)
        {
            UEPath FinalPath = _PrependLocation(path, enginePath);

            // Check if path exists
            if (!Exists(path, enginePath, target))
            {
                UE_LOG_CORE_ERROR("Filesystem::Delete: '{}' does not exist", FinalPath.string());
                return UEResult<UEBool>(false, UEResult<>::Error);
            }

            std::error_code Error;

            // Should we remove all?
            if (target == Filesystem::Target::Directory && recursive)
            {
                std::filesystem::remove_all(FinalPath, Error);
                if (Error)
                {
                    UE_LOG_CORE_ERROR("Filesystem::MakeSure: Failed to delete '{}' - {}", FinalPath.string(), Error.message());
                    return UEResult<UEBool>(false, UEResult<>::Error);
                }
            }
            else
            {
                std::filesystem::remove(FinalPath, Error);
                if (Error)
                {
                    UE_LOG_CORE_ERROR("Filesystem::MakeSure: Failed to delete '{}' - {}", FinalPath.string(), Error.message());
                    return UEResult<UEBool>(false, UEResult<>::Error);
                }
            }

            return UEResult<UEBool>(true);
        }

    private:
        static UEBool _SameAsTarget(const UEPath& path, Filesystem::Target target)
        {
            if (target == Filesystem::Target::Any)
            {
                return true;
            }
            else if (target == Filesystem::Target::Directory)
            {
                return std::filesystem::is_directory(path);
            }
            else if (target == Filesystem::Target::File)
            {
                return !std::filesystem::is_directory(path);
            }

            return false;
        }

        static UEString _PrependLocation(const UEPath& path, Filesystem::Path enginePath)
        {
            switch (enginePath)
            {
            default:
                case Filesystem::Path::Assets:
                {
                    return (m_AssetsPath / path).string();
                    break;
                }
                case Filesystem::Path::Internal:
                {
                    return (m_InternalPath / path).string();
                    break;
                }
                case Filesystem::Path::UserDataFolder:
                {
                    return (m_UserDataFolderPath / path).string();
                    break;
                }
            }
        }

    private:
        static UEPath m_InternalPath;
        static UEPath m_AssetsPath;
        static UEPath m_UserDataFolderPath;
    };
}