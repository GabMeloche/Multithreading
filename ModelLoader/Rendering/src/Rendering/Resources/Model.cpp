
#include <stdafx.h>
#include <fstream>
#include <sstream>
#include <Rendering/Resources/Model.h>
#include <Rendering/Geometry/Vertex.h>
#include <Rendering/Resources/Mesh.h>
#include <Rendering/Resources/Loaders/ShaderLoader.h>

#pragma warning(disable: 4996)

Rendering::Resources::Model::Model(const char* p_path) noexcept
{
	LoadModel(p_path);
	LoadShader();
}

Rendering::Resources::Model::Model(const char* p_modelPath,
	const std::string& p_vertexFilepath,
	const std::string& p_fragmentFilepath) noexcept
{
	LoadModel(p_modelPath);
	LoadShader(p_vertexFilepath.c_str(), p_fragmentFilepath);
}

Rendering::Resources::Model::Model(const Model& p_other) noexcept
{
	m_directory = p_other.m_directory;
	m_mesh = p_other.m_mesh;
	m_shader = p_other.m_shader;
}

void Rendering::Resources::Model::AddTexture(const std::string& p_texturePath) const
{
	m_mesh->AddTexture(p_texturePath);
}

void Rendering::Resources::Model::LoadModel(const char* filename) noexcept
{
	std::vector<Geometry::Vertex> vertices;
	std::vector<GLuint> faceIndex, textureIndex, normalIndex;
	std::vector<glm::vec3> tmp_vertex;
	std::vector<glm::vec2> tmp_uv;
	std::vector<glm::vec3> tmp_normal;
	
	std::ifstream in(filename);
	if (!in)
	{
		std::cerr << "Cannot open " << filename << std::endl;
		exit(1);

	}
	std::string line;
	while (std::getline(in, line))
	{
		//check v for vertices
		if (line.substr(0, 2) == "v ") {
			std::istringstream v(line.substr(2));
			glm::vec3 vert;
			GLfloat x, y, z;
			v >> x; v >> y; v >> z;
			vert = glm::vec3(x, y, z);
			tmp_vertex.push_back(vert);
		}
		//check for texture co-ordinate
		else if (line.substr(0, 2) == "vt") {

			std::istringstream v(line.substr(3));
			glm::vec2 tex;
			GLfloat U, V;
			v >> U; v >> V;
			tex = glm::vec2(U, V);
			tmp_uv.push_back(tex);

		}
		else if (line.substr(0, 2) == "vn") {

			std::istringstream v(line.substr(3));
			glm::vec3 norm;
			GLfloat x, y, z;
			v >> x; v >> y; v >> z;
			norm = glm::vec3(x, y, z);
			tmp_normal.push_back(norm);

		}
		
		//check for faces
		else if (line.substr(0, 2) == "f ") {
			GLuint x, y, z; //to store mesh index
			GLuint u, v, w; //to store texture index
			GLuint X, Y, Z; //to store normal index
			//std::istringstream v;
		  //v.str(line.substr(2));
			const char* chh = line.c_str();
			sscanf(chh, "f %i/%i/%i %i/%i/%i %i/%i/%i", &x, &u, &X, &y, &v, &Y, &z, &w, &Z); //here it read the line start with f and store the corresponding values in the variables
			
			faceIndex.push_back(x - 1); textureIndex.push_back(u - 1); normalIndex.push_back(X - 1);
			faceIndex.push_back(y - 1); textureIndex.push_back(v - 1); normalIndex.push_back(Y - 1);
			faceIndex.push_back(z - 1); textureIndex.push_back(w - 1); normalIndex.push_back(Z - 1);
		}

	}
	//the mesh data is finally calculated here
	
	for (unsigned int i = 0; i < faceIndex.size(); i++)
	{
		glm::vec3 a{ tmp_vertex[faceIndex[i]].x, tmp_vertex[faceIndex[i]].y, tmp_vertex[faceIndex[i]].z };
		glm::vec2 b{ tmp_uv[textureIndex[i]].x, tmp_uv[textureIndex[i]].y };
		glm::vec3 c{ tmp_normal[normalIndex[i]].x, tmp_normal[normalIndex[i]].y, tmp_normal[normalIndex[i]].z };
		
		Geometry::Vertex vertex{ a, b, c };
		
		vertices.emplace_back(vertex);

	}

	m_mesh = std::make_shared<Mesh>(vertices, faceIndex);

}

void Rendering::Resources::Model::LoadShader(const std::string& p_vertexFilepath,
	const std::string& p_fragmentFilepath) noexcept
{
	m_shader = std::make_shared<Shader>(*Loaders::ShaderLoader::
		Load(p_vertexFilepath, p_fragmentFilepath));
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
