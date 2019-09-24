#pragma once
#include <glm/glm.hpp>
#include <vector>

class Mesh
{
public:
	Mesh() = default;
	Mesh(const char* p_path);
	~Mesh() = default;

	bool LoadOBJ(const char* p_path);

	std::vector<glm::vec3>& GetVertices() { return m_vertices; }
	std::vector<glm::vec2>& GetUVs() { return m_uvs; }
	std::vector<glm::vec3>& GetNormals() { return m_normals; }
	
private:
	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec2> m_uvs;
	std::vector<glm::vec3> m_normals;
};
