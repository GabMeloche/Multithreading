#pragma once
#include <Rendering/Export.h>
#include <Rendering/Resources/Model.h>
#include <cstdarg>
#include <future>

//flyweight model
class ResourceManager
{
public:
	ResourceManager() = default;
	~ResourceManager();

	void AddModel(const char* p_path);
	void AddModelThread(const char* p_path, int p_promiseIndex);
	inline std::vector<Rendering::Resources::Model*>& GetModels() { return m_models; }
	void WaitLoad();
	/*template<typename T, typename... Ts>
	void AddModels(T* arg, Ts*... args)
	{
		AddModel(arg);
		AddModels(args...);
	}*/
	
public:
	std::vector<Rendering::Resources::Model*> m_models;
	std::vector<std::promise<Rendering::Resources::Model*>> m_promises;
	std::vector<std::future<Rendering::Resources::Model*>> m_futures;
	
};
