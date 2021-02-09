#include "image.h"

namespace UE
{
	Image::Image() : Initialized(false), Data(nullptr), W(0), H(0), NrChannels(0) {};

	Image::~Image() 
	{
		stbi_image_free(Data);
	};

	int Image::Initialize(const char* path, int desiredChannels)
	{
		// Check if the image is already initialized
		if (Initialized)
		{
			//UE_LOG_ERROR("Image is already initialized!");
			return -1;
		}

		// Check if the image exist
		if (!FileExists(path))
		{
			//UE_LOG_ERROR("Failed to load image: ", path, " does not exist!");
			return -1;
		}

		// Load image and check if the image is corrupt or not
		Data = stbi_load(path, &W, &H, &NrChannels, 0);
		if (!Data)
		{
			//UE_LOG_ERROR("Failed to load image: ", path, " is corrupt!");
			return -1;
		}

		Initialized = true;
		return 0;
	}
}