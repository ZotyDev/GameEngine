<style>
    table {
        margin-left: 0px;
    }
</style>

# Types

UnnamedEngine never uses raw primitive because of planned platform compatibility, instead it uses its own primitive types, wich are in essence just typedefs.

---

### Primitive
  - [`UEBool`](#UEBool)
  - [`UEChar`](#UEChar)
  - [`UEInt8`](#UEInt8)
  - [`UEInt16`](#UEInt16)
  - [`UEInt32`](#UEInt32)
  - [`UEInt64`](#UEInt64)
  - [`UEUint8`](#UEUint8)
  - [`UEUint16`](#UEUint16)
  - [`UEUint32`](#UEUint32)
  - [`UEUint64`](#UEUint64)

### String
- [`UECString`](#UECString)
- [`UEString`](#UEString)

### Path
- [`UEPath`](#UEPath)

### Return
- [`UEResult`](#UEResult)

<br><br>

---
# Primitives

## <a name="UEBool"></a> `UEBool`
| Platform | Type   | Bits |
| -------- | ------ | ---- |
| Windows  | `bool` | `8`  |

## <a name="UEChar"></a> `UEChar`
| Platform | Type   | Bits |
| -------- | ------ | ---- |
| Windows  | `char` | `8`  |

## <a name="UEInt8"></a> `UEInt8`
| Platform | Type          | Bits |
| -------- | ------------- | ---- |
| Windows  | `signed char` | `8`  |

## <a name="UEInt16"></a> `UEInt16`
| Platform | Type        | Bits |
| -------- | ----------- | ---- |
| Windows  | `short int` | `16` |

## <a name="UEInt32"></a> `UEInt32`
| Platform | Type  | Bits |
| -------- | ----- | ---- |
| Windows  | `int` | `32` |

## <a name="UEInt64"></a> `UEInt64`
| Platform | Type            | Bits |
| -------- | --------------- | ---- |
| Windows  | `long long int` | `64` |

## <a name="UEUint8"></a> `UEUint8`
| Platform | Type            | Bits |
| -------- | --------------- | ---- |
| Windows  | `unsigned char` | `8`  |

## <a name="UEUint16"></a> `UEUint16`
| Platform | Type                 | Bits |
| -------- | -------------------- | ---- |
| Windows  | `unsigned short int` | `16` |

## <a name="UEUint32"></a> `UEUint32`
| Platform | Type           | Bits |
| -------- | -------------- | ---- |
| Windows  | `unsigned int` | `32` |

## <a name="UEUint64"></a> `UEUint64`
| Platform | Type                     | Bits |
| -------- | ------------------------ | ---- |
| Windows  | `unsigned long long int` | `64` |

## <a name="UEFloat"></a> `UEFloat`
| Platform | Type    | Bits |
| -------- | ------- | ---- |
| Windows  | `float` | `32` |

## <a name="UEDouble"></a> `UEDouble`
| Platform | Type     | Bits |
| -------- | -------- | ---- |
| Windows  | `double` | `64` |

<br><br>

---
# String

## <a name="UECString"></a> `UECString`
| Platform | Type    |
| -------- | ------- |
| Windows  | `char*` |

## <a name="UEString"></a> `UEString`
| Platform | Type          |
| -------- | ------------- |
| Windows  | `std::string` |

<br><br>

---
# Path

## <a name="UEPath"></a> `UEPath`
| Platform | Type                    |
| -------- | ----------------------- |
| Windows  | `std::filesystem::path` |

<br><br>

---
# Return

## <a name="UEResult"></a> `UEResult`
The default return for functions that can return errors, when these functions are used there should be ways to handle the possible errors. This type is a `enum class` containig the following return codes:

| Code       | Value | Description |
| ---------- | ----- | --- |
| `Error`    | `-1`  | Operation could not be completed, data was not changed and the returned values are all `NULL` or `nullptr` |
| `Successs` | `0`   | Everything went ok without errors |
| `Warn`     | `1`   |Operation went almost ok, everything should work, but not completely |