
#include <stdafx.h>
#include <fstream>
#include <sstream>
#include <Rendering/Resources/Model.h>
#include <Rendering/Geometry/Vertex.h>
#include <Rendering/Resources/Mesh.h>
#include <Rendering/Resources/Loaders/ShaderLoader.h>
#include <thread>
#include <mutex>

#pragma warning(disable: 4996)

Rendering::Resources::Model::Model(const char* p_path) noexcept
{
	LoadModel(p_path);
	m_shader = nullptr;
	//LoadShader();
}

Rendering::Resources::Model::Model(const char* p_modelPath,
	const std::string& p_vertexFilepath,
	const std::string& p_fragmentFilepath) noexcept
{
	m_shader = nullptr;
	LoadModel(p_modelPath);
	//LoadShader(p_vertexFilepath.c_str(), p_fragmentFilepath);
}

Rendering::Resources::Model::Model(Mesh* p_mesh)
{
	m_shader = nullptr;
	m_mesh = p_mesh;
}

Rendering::Resources::Model::Model(const Model& p_other) noexcept
{
	m_directory = p_other.m_directory;
	m_mesh = p_other.m_mesh;
	m_shader = p_other.m_shader;
}

void Rendering::Resources::Model::AddTexture(const std::string& p_texturePath) const
{
	if (this == nullptr)
		return;
	
	m_mesh->AddTexture(p_texturePath);
}

void Rendering::Resources::Model::LoadModel(const char* p_path) noexcept
{
	std::vector<Rendering::Geometry::Vertex> vertices;
	std::vector<GLuint> faceIndex, textureIndex, normalIndex;
	std::vector<glm::vec3> tmpVertex;
	std::vector<glm::vec2> tmpUv;
	std::vector<glm::vec3> tmpNormal;

	auto start = std::chrono::high_resolution_clock::now();
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
			int count = sscanf(chh, "f %i/%i/%i %i/%i/%i %i/%i/%i %i/%i/%i", &x, &u, &X, &y, &v, &Y, &z, &w, &Z, &a, &i, &A);

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
	
	m_mesh = new Mesh(vertices, faceIndex);
}

Rendering::Resources::Model Rendering::Resources::Model::StaticLoadModel(const char* path)
{
	Model m(path);
	return m;
}

void Rendering::Resources::Model::LoadShader(const std::string& p_vertexFilepath,
	const std::string& p_fragmentFilepath) noexcept
{
	m_shader = Loaders::ShaderLoader::Load(p_vertexFilepath, p_fragmentFilepath);
}

void Rendering::Resources::Model::Bind() const noexcept
{
	m_mesh->Bind();
	m_shader->Bind();
}

void Rendering::Resources::Model::Unbind() const noexcept
{
	m_mesh->Unbind();
	m_shader->Unbind();
}
