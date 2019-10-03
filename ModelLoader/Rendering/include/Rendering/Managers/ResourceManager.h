#pragma once
#include <Rendering/Export.h>
#include <Rendering/Resources/Model.h>

class ResourceManager
{
public:
	ResourceManager() = default;
	~ResourceManager() = default;

	void AddMesh(const char* p_path);
	
public:
	std::vector<Rendering::Resources::Mesh> m_models;
};
