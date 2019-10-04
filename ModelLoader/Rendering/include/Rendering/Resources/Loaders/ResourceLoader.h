#pragma once
#include <thread>
#include <Rendering/Resources/Model.h>
#include <mutex>

class ResourceLoader
{
public:
	ResourceLoader() = delete;
	~ResourceLoader() = delete;

	/*template<typename T, typename... args>
	static std::vector<Rendering::Resources::Model> LoadModels(T first, args... args)
	{
		std::vector<Rendering::Resources::Model> models;
		//std::thread t{ &ThreadLoadModel,  models, first};
		LoadModels(args...);
		//t.join();
		return models;
	}*/
	
	static void ThreadLoadModel(std::vector<Rendering::Resources::Model>& p_models, const char* p_path)
	{
		p_models.push_back(Rendering::Resources::Model::StaticLoadModel(p_path));
	}
};
