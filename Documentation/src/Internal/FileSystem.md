# File System

## Methods
- [`FileSelectorDialog()`](#FileSelectorDialog)
- [`DoesFileExists()`](#DoesFileExists)
- [`ReadToBuffer()`](#ReadToBuffer)
- [`MakeSureFolder`](#MakeSureFolder)
- [`MakeSureFile`](#MakeSureFile)
- [`GetUserDataFolder`](#GetUserDataFolder)

---
## <a name="FileSelectorDialog"></a> `FileSelectorDialog(receivedPath, filters, folderOnly)`

Shows a window containing files and folders that can be selected, the function then returns the location of the selected file/folder. Filters can also be applied.

**Return:** [`UEResult`](./Types.md#UEResult) <br>
**Arguments:** <br>
&nbsp; **receivedPath:** [`UEPath`](./Types.md#UEPath)`&` <br>
&nbsp; &nbsp; The location of the selected file/folder. <br>
&nbsp; **filters:** `const std::vector<std::pair<`[`UEString`](./Types.md#UEString)`,`[`UEString`](./Types.md#UEString)`>>&` <br>
&nbsp; &nbsp; The filters to select allowed files. Only works if `folderOnly` is `false`. To treat this as a empty value use `{}`. <br>
&nbsp; **folderOnly:** [`UEBool`](./Types.md#UEBool) `default : false` <br>
&nbsp; &nbsp; If `true` the dialog will only accept the selection of folders, if `false` only files can be selected. <br>

**Example:**
```cpp
UEPath ReturnedPathLocation;
UEResult Result = FileSelectorDialog(
    ReturnedPathLocation, 
    {{"Cpp Files", "*.cpp, *.h, *.hpp"}, {"Lua Scripts", "*.lua"}},
    false);
if (Result == UEResult::Error)
{
    UE_CORE_ERROR("Something went wrong: failed to select file");
}
```

---
## <a name="DoesFileExists"></a> `DoesFileExists()`

Checks if a file/folder exists.

**Return:** [`UEBool`](./Types.md#UEBool) <br>
**Arguments:** <br>
&nbsp; **path:** `const` [`UEPath`](./Types.md#UEPath)`&` <br>
&nbsp; &nbsp; Location of the file/folder being checked.

---
## <a name="ReadToBuffer"></a> `ReadToBuffer()`

Reads the data of a file and stores it into a buffer.

**Return:** [`UEResult`](./Types.md#UEResult) <br>
**Arguments:** <br>
&nbsp; **path:** `const` [`UEPath`](./Types.md#UEPath)`&` <br>
&nbsp; &nbsp; Location of the file being read. <br>
&nbsp; **buffer:** [`UEString`](./Types.md#UEStrin)`&` <br>
&nbsp; &nbsp; Reference to the buffer that will be filled with the read data.

---
## <a name="MakeSureFolder"></a> `MakeSureFolder()`

Check if a folder exists, if not it gets created.

**Return:** [`UEResult`](./Types.md#UEResult) <br>
&nbsp; **Warn:** folder got created. <br>
**Arguments:** <br>
&nbsp; **path:** `const` [`UEPath`](./Types.md#UEPath)`&` <br>
&nbsp; &nbsp; Location of the folder being checked.

---
## <a name="MakeSureFile"></a> `MakeSureFile()`

Check if a file exists, if not it gets created.

**Return:** [`UEResult`](./Types.md#UEResult) <br>
&nbsp; **Warn:** file got created. <br>
&nbsp; **Success:** file already exists. <br>
**Arguments:** <br>
&nbsp; **path:** `const` [`UEPath`](./Types.md#UEPath)`&` <br>
&nbsp; &nbsp; Location of the file being checked.

---
## <a name="GetUserDataFolder"></a> `GetUserDataFolder()`

Returns the location of the user data folder of the system.

**Return:** [`UEResult`](./Types.md#UEResult) <br>
&nbsp; **Error:** could not get user data folder location. <br>
**Arguments:** <br>
&nbsp; **path:** [`UEPath`](./Types.md#UEPath)`&` <br>
&nbsp; &nbsp; The location of the user data folder.