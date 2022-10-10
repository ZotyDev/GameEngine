#pragma once

namespace UE
{
	enum class ShaderDataType
	{
		Bool = 0,
		Int = 1,
		Uint = 2,
		Float = 3,
		Double = 4,

		BVec2 = 5,
		BVec3 = 6,
		BVec4 = 7,

		IVec2 = 8,
		IVec3 = 9,
		IVec4 = 10,

		UVec2 = 11,
		UVec3 = 12,
		UVec4 = 13,

		Vec2 = 14,
		Vec3 = 15,
		Vec4 = 16,

		DVec2 = 17,
		DVec3 = 18,
		DVec4 = 19,

		Mat2 = 20,
		Mat3 = 21,
		Mat4 = 22,

		Mat2x2 = 23,
		Mat2x3 = 24,
		Mat2x4 = 25,

		Mat3x2 = 26,
		Mat3x3 = 27,
		Mat3x4 = 28,

		Mat4x2 = 29,
		Mat4x3 = 30,
		Mat4x4 = 31,

		Sampler1D					= 32,
		Sampler2D					= 33,
		Sampler3D					= 34,
		SamplerCube					= 35,
		Sampler2DRect				= 36,
		Sampler3DRect				= 37,
		Sampler1DArray				= 38,
		Sampler2DArray				= 39,
		SamplerCubeArray			= 40,
		SamplerBuffer				= 41,
		Sampler2DMS					= 42,
		Sampler2DMSArray			= 43,

		ISampler1D					= 44,
		ISampler2D					= 45,
		ISampler3D					= 46,
		ISamplerCube				= 47,
		ISampler2DRect				= 48,
		ISampler3DRect				= 49,
		ISampler1DArray				= 50,
		ISampler2DArray				= 51,
		ISamplerCubeArray			= 52,
		ISamplerBuffer				= 53,
		ISampler2DMS				= 54,
		ISampler2DMSArray			= 55,

		USampler1D					= 56,
		USampler2D					= 57,
		USampler3D					= 58,
		USamplerCube				= 59,
		USampler2DRect				= 60,
		USampler3DRect				= 61,
		USampler1DArray				= 62,
		USampler2DArray				= 63,
		USamplerCubeArray			= 64,
		USamplerBuffer				= 65,
		USampler2DMS				= 66,
		USampler2DMSArray			= 67,

		Sampler1DShadow				= 68,
		Sampler2DShadow				= 69,
		SamplerCubeShadow			= 70,
		Sampler2DRectShadow			= 71,
		Sampler1DArrayShadow		= 72,
		Sampler2DArrayShadow		= 73,
		SamplerCubeArrayShadow		= 74,

		Invalid
	};
}