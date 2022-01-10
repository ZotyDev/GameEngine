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

		Last
	};
}