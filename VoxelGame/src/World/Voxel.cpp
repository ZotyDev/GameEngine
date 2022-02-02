#include "uepch.h"
#include "World/Voxel.h"

namespace UE
{
	VoxelDefinition::VoxelDefinition(const VoxelDefinition::Props& props)
		: m_Props(props)
	{}

	VoxelDefinition::VoxelDefinition()
		: m_Props(AIR_VOXEL)
	{}

	VoxelManager::VoxelManager()
	{
		for (UEUint32 i = 0; i < 1024; i++)
		{
			m_VoxelToVoxelDefinitionIndex[i] = VoxelDefinition();
		}
	}

	Voxel VoxelManager::RegisterVoxel(const UEString& name, const VoxelDefinition::Props& props)
	{
		auto it = m_NameToVoxelIndex.find(name);
		auto end = m_NameToVoxelIndex.end();
		if (it != end)
		{
			UE_ERROR("Failed to register Voxel: \"{0}\" is already registered", name);
			return 0;
		}

		m_VoxelToVoxelDefinitionIndex[m_VoxelCount] = props;
		m_NameToVoxelIndex.insert({ name, m_VoxelCount });

		return m_VoxelCount++;
	}

	Voxel VoxelManager::GetVoxel(const UEString& name)
	{
		auto it = m_NameToVoxelIndex.find(name);
		auto end = m_NameToVoxelIndex.end();
		if (it == end)
		{
			UE_ERROR("Failed to get Voxel: \"{0}\" not found", name);
			return 0;
		}

		return it->second;
	}

	VoxelDefinition VoxelManager::GetVoxelDefinition(const UEString& name)
	{
		auto it = m_NameToVoxelIndex.find(name);
		auto end = m_NameToVoxelIndex.end();
		if (it == end)
		{
			UE_ERROR("Failed to get Voxel Definition: \"{0}\" not found", name);
			return VoxelDefinition();
		}

		return m_VoxelToVoxelDefinitionIndex[it->second];
	}
}