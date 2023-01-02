#pragma once

#define AIR_VOXEL		{0, 0, 0, 0, VoxelDefinition::Material::Air}

namespace UE
{
	class VoxelDefinition
	{
	public:
		enum class Material
		{
			Air,
			Grass,
			Dir,
			Stone,
			Foliage,
			Metal,
		};

		struct Props
		{
			UEUint8 R;
			UEUint8 G;
			UEUint8 B;
			UEUint8 A = 255;
			VoxelDefinition::Material Material;
		};

	public:
		VoxelDefinition(const VoxelDefinition::Props& props);
		VoxelDefinition();

	public:
		VoxelDefinition::Props m_Props;
	};

	typedef UEUint32 Voxel;

	class VoxelManager
	{
	public:
		VoxelManager();

		Voxel RegisterVoxel(const UEString& name, const VoxelDefinition::Props& props);
		Voxel GetVoxel(const UEString& name);
		VoxelDefinition GetVoxelDefinition(const UEString& name);

	private:
		VoxelDefinition m_VoxelToVoxelDefinitionIndex[1024];
		std::unordered_map<UEString, Voxel> m_NameToVoxelIndex;

		UEUint32 m_VoxelCount = 1;
	};
}