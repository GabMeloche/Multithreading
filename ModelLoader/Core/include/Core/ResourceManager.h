#pragma once
#include "stdafx.h"

#include <fstream>
#include <sstream>
#include <thread>
#include <future>

#include <Rendering/Resources/Model.h>

namespace Core
{
	///flyweight model: models loaded here and sent to GameObject as pointers
	class ResourceManager
	{
	public:
		ResourceManager() = default;
		~ResourceManager();

		void AddModelMultiThreaded(const char* p_path, const std::string& p_name);

		///AddModelThread() is multithreaded; must use WaitLoad() once every model has been loaded
		void AddModel(const char* p_path, size_t p_promiseIndex, const std::string& p_name, bool p_multiThread);
		void WaitLoad();

		//Alternative to AddModelThread() and WaitLoad()
		void AddModelMonoThreaded(const char* p_path, const std::string& p_name);

		Rendering::Resources::Model* GetModel(const std::string& p_name);
		inline std::unordered_map <std::string, Rendering::Resources::Model*>& GetModels() { return m_models; }

	private:
		std::unordered_map<std::string, Rendering::Resources::Model*> m_models;
		std::vector<std::promise<Rendering::Resources::Model*>> m_promises;
		std::vector<std::future<Rendering::Resources::Model*>> m_futures;

	};
}
