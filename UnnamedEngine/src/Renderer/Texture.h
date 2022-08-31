#pragma once

namespace UE 
{
	class Texture
	{
	public:
		enum TextureFlags
		{
			NONE = 0,
			FILTERING_NEAREST = BIT(0),
			FILTERING_LINEAR = 0,
			CLAMP_TO_EDGE = BIT(1),
			REPEAT = 0,
		};

	public:
		virtual UEResult<> LoadFromSource(const UEPath& path, TextureFlags flags = TextureFlags::NONE) = 0;

		virtual ~Texture() = default;

		virtual UEUint32 GetWidth() const = 0;
		virtual UEUint32 GetHeight() const = 0;
		virtual UEUint32 GetID() const = 0;

		virtual void Bind(UEUint32 slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create();
	};
}