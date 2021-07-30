#pragma once

namespace UE
{
	UEResult LoadWavFileHeader(
		std::ifstream& file,
		std::uint8_t& channels,
		std::uint32_t& sampleRate,
		std::uint8_t& bitsPerSample,
		std::uint32_t& size);

	UEResult LoadWav(
		std::vector<char>& target,
		const std::string& filename,
		std::uint8_t& channels,
		std::uint32_t& sampleRate,
		std::uint8_t& bitsPerSample,
		std::uint32_t& size);
}