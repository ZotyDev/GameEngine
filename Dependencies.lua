VULKAN_SDK = os.getenv("VULKAN_SDK")

-- Include Directories
IncludeDir = {}
	IncludeDir["GLFW"] = "%{wks.location}/UnnamedEngine/vendor/GLFW/include"
	IncludeDir["GLAD"] = "%{wks.location}/UnnamedEngine/vendor/GLAD/include"
	IncludeDir["GLM"] = "%{wks.location}/UnnamedEngine/vendor/GLM"
	IncludeDir["STB"] = "%{wks.location}/UnnamedEngine/vendor/STB"
	IncludeDir["LUA"] = "%{wks.location}/UnnamedEngine/vendor/LUA"
	IncludeDir["FreeType"] = "%{wks.location}/UnnamedEngine/vendor/FreeType/include"
	IncludeDir["ImGui"] = "%{wks.location}/UnnamedEngine/vendor/ImGui"
	IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"
	IncludeDir["OpenAL"] = "%{wks.location}/UnnamedEngine/vendor/OpenAL-Soft/include"
	IncludeDir["Emscripten"] = "C:/emsdk/upstream/emscripten/system/include"
	IncludeDir["fmt"] = "%{wks.location}/UnnamedEngine/vendor/fmt/include"
    IncludeDir["shaderc"] = "{%wks.location}/UnnamedEngine/vendor/shaderc/libshaderc/include"
    IncludeDir["SPIRV_Cross"] = "%{wks.location}/UnnamedEngine/vendor/SPIRV-Cross"
    IncludeDir["toml"] = "%{wks.location}/UnnamedEngine/vendor/toml"
    IncludeDir["yaml_cpp"] = "%{wks.location}/UnnamedEngine/vendor/yaml-cpp/include"
	
	IncludeDir["ImPlot"] = "%{wks.location}/UnnamedEngine/vendor/ImPlot"
	IncludeDir["ImGuizmo"] = "%{wks.location}/UnnamedEngine/vendor/ImGuizmo"
    IncludeDir["ImGuiNodeEditor"] = "%{wks.location}/UnnamedEngine/vendor/imgui-node-editor"

-- Library Directories
LibraryDir = {}

    LibraryDir["OpenAL"] = "%{wks.location}/UnnamedEngine/vendor/OpenAL-Soft/libs/Win64"
    LibraryDir["Emscripten"] = "C:/emsdk/upstream/emscripten/system/lib"

    LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

-- Libraries
Library = {}
    Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
    Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VKLayer_utils.lib"

    Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK}/shaderc_sharedd.lib"
    Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-cored.lib"
    Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsld.lib"
    Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK}/SPIRV-Toolsd.lib"

    Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
    Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
    Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"