#include "stdafx.h"

#include <Core/ResourceManager.h>
#include <fstream>
#include <sstream>
#include <thread>

#pragma warning (disable: 4996)

ResourceManager::~ResourceManager()
{
	for (auto& model: m_models)
			delete model;

	m_models.clear();
}

void ResourceManager::AddModel(const char* p_path)
{
	std::promise<Rendering::Resources::Model*> newPromise;
	std::future<Rendering::Resources::Model*> newFuture = newPromise.get_future();
	
	m_promises.push_back(std::move(newPromise));
	m_futures.push_back(std::move(newFuture));
	int index = m_futures.size() - 1;
	std::thread t{ &ResourceManager::AddModelThread, this, p_path, index };
	t.detach();
}

void ResourceManager::WaitLoad()
{
	for (auto& future : m_futures)
	{
		Rendering::Resources::Model* model = future.get();
		model->GetMesh()->CreateBuffers();
		model->LoadShader();
	}
}

void ResourceManager::AddModelThread(const char* p_path, int p_promiseIndex)
{
	bool isQuad = false;
	std::vector<Rendering::Geometry::Vertex> vertices;
	std::vector<GLuint> faceIndex, textureIndex, normalIndex;
	std::vector<glm::vec3> tmp_vertex;
	std::vector<glm::vec2> tmp_uv;
	std::vector<glm::vec3> tmp_normal;

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
			tmp_vertex.push_back(vert);
		}
		//check for texture co-ordinate
		else if (line.substr(0, 2) == "vt")
		{

			std::istringstream v(line.substr(3));
			glm::vec2 tex;
			GLfloat U, V;
			v >> U; v >> V;
			tex = glm::vec2(U, V);
			tmp_uv.push_back(tex);

		}
		else if (line.substr(0, 2) == "vn")
		{

			std::istringstream v(line.substr(3));
			glm::vec3 norm;
			GLfloat x, y, z;
			v >> x; v >> y; v >> z;
			norm = glm::vec3(x, y, z);
			tmp_normal.push_back(norm);

		}

		//check for faces
		else if (line.substr(0, 2) == "f ")
		{
			GLuint x, y, z, a; //to store mesh index
			GLuint u, v, w, i; //to store texture index
			GLuint X, Y, Z, A; //to store normal index
			//std::istringstream v;
		  //v.str(line.substr(2));
			const char* chh = line.c_str();
			int count = sscanf(chh, "f %i/%i/%i %i/%i/%i %i/%i/%i %i/%i/%i", &x, &u, &X, &y, &v, &Y, &z, &w, &Z, &a, &i, &A); //here it read the line start with f and store the corresponding values in the variables

			faceIndex.push_back(x - 1); textureIndex.push_back(u - 1); normalIndex.push_back(X - 1);
			faceIndex.push_back(y - 1); textureIndex.push_back(v - 1); normalIndex.push_back(Y - 1);
			faceIndex.push_back(z - 1); textureIndex.push_back(w - 1); normalIndex.push_back(Z - 1);
			if (count == 12)
			{
				//faceIndex.push_back(a - 1); textureIndex.push_back(i - 1); normalIndex.push_back(A - 1);
				isQuad = true;
			}
			else
				isQuad = false;
		}

	}

	for (unsigned int i = 0; i < faceIndex.size(); ++i)
	{
		Rendering::Geometry::Vertex vertex{ tmp_vertex[i % tmp_vertex.size()], tmp_uv[textureIndex[i]], tmp_normal[normalIndex[i]] };
		vertices.push_back(vertex);
	}


	m_models.emplace_back(new Rendering::Resources::Model(new Rendering::Resources::Mesh(vertices, faceIndex)));
	m_promises[p_promiseIndex].set_value(m_models.back());
}