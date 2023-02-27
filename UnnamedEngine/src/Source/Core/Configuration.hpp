#pragma once

namespace UE
{
    struct Configuration
    {
        struct Window
        {
            static UEUint32 Width;
            static UEUint32 Height;
            static UEString Title;
        };

        struct Renderer
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

        struct Camera
        {
            static UEFloat ZoomInSensibility;
            static UEFloat ZoomOutSensibility;
        }
    };
}