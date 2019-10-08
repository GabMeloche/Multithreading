#include "stdafx.h"
#include <Core/ResourceManager.h>

Core::ResourceManager::~ResourceManager()
{
	for (auto& model: m_models)
			delete model.second;

	m_models.clear();
}

/// Remember to call "WaitLoad()" before rendering objects for first time
void Core::ResourceManager::AddModelMultiThreaded(const char* p_path, const std::string& p_name)
{
	if (m_models.find(p_name) != m_models.end() && !m_models.empty())
	{
		std::cout << "Model " << p_name << " already loaded\n";
		return;
	}

	m_models.try_emplace(p_name, nullptr);
	
	std::promise<Rendering::Resources::Model*> newPromise;
	std::future<Rendering::Resources::Model*> newFuture = newPromise.get_future();
	
	m_promises.push_back(std::move(newPromise));
	m_futures.push_back(std::move(newFuture));
	size_t index = m_futures.size() - 1;
	
	std::thread t{ &ResourceManager::AddModel, this, p_path, index, p_name, true };
	t.detach();
}

void Core::ResourceManager::AddModelMonoThreaded(const char* p_path, const std::string& p_name)
{
	AddModel(p_path, 0, p_name, false);
	m_models.find(p_name)->second->GetMesh()->CreateBuffers();
	m_models.find(p_name)->second->LoadShader();
}

void Core::ResourceManager::AddModel(const char* p_path, size_t p_promiseIndex, const std::string& p_name, bool p_multiThread)
{	
	std::vector<Rendering::Geometry::Vertex> vertices;
	std::vector<GLuint> faceIndex, textureIndex, normalIndex;
	std::vector<glm::vec3> tmpVertex;
	std::vector<glm::vec2> tmpUv;
	std::vector<glm::vec3> tmpNormal;

	std::ifstream in(p_path);

	if (!in)
	{
		std::cerr << "Cannot open " << p_path << std::endl;
		exit(1);

	}
	
	std::string line;
	while (std::getline(in, line))
	{
		//check v for vertices
		if (line.substr(0, 2) == "v ")
		{
			std::istringstream v(line.substr(2));
			glm::vec3 vert;
			GLfloat x, y, z;
			v >> x; v >> y; v >> z;
			vert = glm::vec3(x, y, z);
			tmpVertex.push_back(vert);
		}
		//check for texture co-ordinate
		else if (line.substr(0, 2) == "vt")
		{

			std::istringstream v(line.substr(3));
			glm::vec2 tex;
			GLfloat U, V;
			v >> U; v >> V;
			tex = glm::vec2(U, V);
			tmpUv.push_back(tex);
		}
		else if (line.substr(0, 2) == "vn")
		{

			std::istringstream v(line.substr(3));
			glm::vec3 norm;
			GLfloat x, y, z;
			v >> x; v >> y; v >> z;
			norm = glm::vec3(x, y, z);
			tmpNormal.push_back(norm);
		}

		//check for faces
		else if (line.substr(0, 2) == "f ")
		{
			GLuint x, y, z, a; //to store mesh index
			GLuint u, v, w, i; //to store texture index
			GLuint X, Y, Z, A; //to store normal index
			
			const char* chh = line.c_str();
			int count = sscanf_s(chh, "f %i/%i/%i %i/%i/%i %i/%i/%i %i/%i/%i", &x, &u, &X, &y, &v, &Y, &z, &w, &Z, &a, &i, &A);
			
			faceIndex.push_back(x - 1); textureIndex.push_back(u - 1); normalIndex.push_back(X - 1);
			faceIndex.push_back(y - 1); textureIndex.push_back(v - 1); normalIndex.push_back(Y - 1);
			faceIndex.push_back(z - 1); textureIndex.push_back(w - 1); normalIndex.push_back(Z - 1);

			if (count == 12)
			{
				faceIndex.push_back(z - 1); textureIndex.push_back(w - 1); normalIndex.push_back(Z - 1);
				faceIndex.push_back(a - 1); textureIndex.push_back(i - 1); normalIndex.push_back(A - 1);
				faceIndex.push_back(x - 1); textureIndex.push_back(u - 1); normalIndex.push_back(X - 1);
			}
		}

	}
	for (unsigned int i = 0; i < faceIndex.size(); ++i)
	{
		Rendering::Geometry::Vertex vertex{ tmpVertex[i % tmpVertex.size()], tmpUv[textureIndex[i]], tmpNormal[normalIndex[i]] };
		vertices.push_back(vertex);
	}
	
	auto model = m_models.find(p_name)->second = new Rendering::Resources::Model(new Rendering::Resources::Mesh(vertices, faceIndex));

	if (p_multiThread)
		m_promises[p_promiseIndex].set_value(model);
}

void Core::ResourceManager::WaitLoad()
{
	for (auto& future : m_futures)
	{
		Rendering::Resources::Model* model = future.get();
		model->GetMesh()->CreateBuffers();
		model->LoadShader();
	}
}

Rendering::Resources::Model* Core::ResourceManager::GetModel(const std::string& p_name)
{
	if (m_models.find(p_name) == m_models.end())
	{
		std::cout << "Could not find model: " + p_name + " in ResourceManager\n";
		return nullptr;
	}
	
	return m_models.find(p_name)->second;
}