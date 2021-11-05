#pragma once

#include <string>

namespace UE
{
	typedef bool					UEBool;

	typedef char					UEChar;

	typedef signed char				UEInt8;
	typedef short int				UEInt16;
	typedef int						UEInt32;
	typedef long long int			UEInt64;

	typedef unsigned char			UEUint8;
	typedef unsigned short int		UEUint16;
	typedef unsigned int			UEUint32;
	typedef unsigned long long int	UEUint64;

	typedef float					UEFloat;
	typedef double					UEDouble;

	// Todo: Verify if this is the best approach
	typedef char*					UECString;
	typedef std::string				UEString;

	enum class UEType
	{
		Bool,

		Char,

		Int8,
		Int16,
		Int32,
		Int64,

		Uint8,
		Uint16,
		Uint32,
		Uint64,

		Float,
		Double,

		String,

		Int = Int32
	};

	struct UEVDescriptor
	{
		UEType Type;
		UECString Name;
		UEUint64 Range;
	};

	struct UEVValue
	{
		UEVValue() = default;
		UEVValue(UEBool value)		:Bool(value)	{}
		UEVValue(UEChar value)		:Char(value)	{}
		UEVValue(UEInt8 value)		:Uint8(value)	{}
		UEVValue(UEInt16 value)		:Uint16(value)	{}
		UEVValue(UEInt32 value)		:Uint32(value)	{}
		UEVValue(UEInt64 value)		:Uint64(value)	{}
		UEVValue(UEUint8 value)		:Uint8(value)	{}
		UEVValue(UEUint16 value)	:Uint16(value)	{}
		UEVValue(UEUint32 value)	:Uint32(value)	{}
		UEVValue(UEUint64 value)	:Uint64(value)	{}
		UEVValue(UEFloat value)		:Float(value)	{}
		UEVValue(UEDouble value)	:Double(value)	{}

		union
		{
			UEBool Bool;

			UEChar Char;

			UEInt8 Int8;
			UEInt16 Int16;
			UEInt32 Int32;
			UEInt64 Int64;

			UEUint8 Uint8;
			UEUint16 Uint16;
			UEUint32 Uint32;
			UEUint64 Uint64;

			UEFloat Float;
			UEDouble Double;

			UECString String;
		};
	};

	struct UEVVValue
	{
		UEVDescriptor Descriptor;
		UEVValue Value;
	};
}