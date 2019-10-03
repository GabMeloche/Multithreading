#pragma once
#include <Rendering/Export.h>
#include <Rendering/Resources/Model.h>
#include <cstdarg>

class ResourceManager
{
public:
	ResourceManager() = default;
	~ResourceManager();

	void AddModel(const char* p_path);
	inline std::vector<Rendering::Resources::Model*>& GetModels() { return m_models; }

	/*void AddModels(const char* arg, const char* args...)
	{
		AddModel(arg);
		AddModels(args...);
	}*/
	
public:
	std::vector<Rendering::Resources::Model*> m_models;
};
