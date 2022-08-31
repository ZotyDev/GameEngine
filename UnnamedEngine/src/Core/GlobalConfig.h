#pragma once

namespace UE
{
	struct GlobalConfig
	{
		static UEResult<> LoadConfigs();

		struct Application
		{
			static UEUint32 Width;
			static UEUint32 Height;
		};

		struct Rendering
		{
			static UEFloat PixelSize;
			static UEUint32 ScreenWidth;
			static UEUint32 ScreenHeight;
			static UEUint32 DesiredWidth;
			static UEUint32 DesiredHeight;
		};

		struct Mouse
		{
			static UEFloat MovementSensibilityX;
			static UEFloat MovementSensibilityY;
			static UEFloat ScrollSensibilityX;
			static UEFloat ScrollSensibilityY;
		};

		struct Zoom
		{
			static UEFloat SensibilityIn;
			static UEFloat SensibilityOut;
		};
	};
}