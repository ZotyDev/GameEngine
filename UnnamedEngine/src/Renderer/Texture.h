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
		virtual ~Texture() = default;

		virtual void Bind(UEUint32 slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		virtual UEResult<> LoadFromSource(const UEPath& path, TextureFlags flags = TextureFlags::NONE) = 0;
		virtual UEResult<> LoadFromSourceScaledMax(const UEPath& path, UEUint32 maxSize, TextureFlags = TextureFlags::NONE) = 0;

		virtual UEUint32 GetWidth() const = 0;
		virtual UEUint32 GetHeight() const = 0;
		virtual UEFloat GetRatio() const = 0;
		virtual UEUint32 GetID() const = 0;

		static Ref<Texture2D> Create();
	protected:
		UEUint32 m_Width;
		UEUint32 m_Height;
		UEFloat m_Ratio;
	};
}