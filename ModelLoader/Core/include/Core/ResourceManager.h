#pragma once
#include <Rendering/Export.h>
#include <Rendering/Resources/Model.h>
#include <cstdarg>
#include <future>

///flyweight model: models loaded here and sent as reference to GameObjects
class ResourceManager
{
public:
	ResourceManager() = default;
	~ResourceManager();

	void AddModel(const char* p_path, const std::string& p_name);
	void AddModelThread(const char* p_path, unsigned int p_promiseIndex, const std::string& p_name);
	void WaitLoad();
	
	Rendering::Resources::Model* GetModel(const std::string& p_name);
	inline std::unordered_map < std::string, Rendering::Resources::Model* > & GetModels() { return m_models; }
	
private:
	std::unordered_map<std::string, Rendering::Resources::Model*> m_models;
	std::vector<std::promise<Rendering::Resources::Model*>> m_promises;
	std::vector<std::future<Rendering::Resources::Model*>> m_futures;
	
};
