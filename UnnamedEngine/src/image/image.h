#pragma once

#include "core.h"
#include "misc/utilities.h"
#include <stb_image.h>

namespace UE
{
	class Image
	{
	public:
		Image();
		~Image();

		int Initialize(const char* path, int desiredChannels = 0);

		byte* GetData() { return Data; };

		int GetW() { return W; };
		int GetH() { return H; };
		int GetNrChannels() { return NrChannels; };

	private:
		bool Initialized;
		byte* Data;
		int W;
		int H;
		int NrChannels;
	};
}