#pragma once

namespace UE
{
	class Configuration
	{
	public:
		UEResult<> ReadFromFile(const std::string& filename);

		UEResult<> GetByName(const std::string& name);

	private:
	};
}