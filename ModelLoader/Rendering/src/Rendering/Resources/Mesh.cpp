#include <stdafx.h>
#include <Rendering/Resources/Mesh.h>

Rendering::Resources::Mesh::Mesh(std::vector<Geometry::Vertex>& p_vertices, std::vector<uint32_t>& p_indices) noexcept
	: m_vertexCount{ static_cast<uint32_t>(p_vertices.size()) }, m_indicesCount{ static_cast<uint32_t>(p_indices.size()) },
	m_vertices{ p_vertices }, m_indices{ p_indices }
{
	m_texture = new Texture();
}

Rendering::Resources::Mesh::~Mesh() noexcept
{
	delete m_vertexArray;
	delete m_vboPosition;
	delete m_vboTextCoords;
	delete m_vboNormal;
	delete m_indexBuffer;
	delete m_texture;
}

void Rendering::Resources::Mesh::AddTexture(const std::string& p_texturePath)
{
	m_texture->Load(p_texturePath);
}

void Rendering::Resources::Mesh::Bind() const noexcept
{
	if (m_texture)
		m_texture->Bind();
	if (m_vertexArray)
		m_vertexArray->Bind();
	if (m_indexBuffer)
		m_indexBuffer->Bind();
}

void Rendering::Resources::Mesh::Unbind() const noexcept
{
	m_indexBuffer->Unbind();
	m_vertexArray->Unbind();
	m_texture->Unbind();
}

const uint32_t Rendering::Resources::Mesh::GetVertexCount() const noexcept
{
	return m_vertexCount;
}

const uint32_t Rendering::Resources::Mesh::GetIndicesCount() const noexcept
{
	return m_indicesCount;
}

void Rendering::Resources::Mesh::CreateBuffers() noexcept
{
	m_vertexArray = new Buffers::VertexArray();
	m_vertexArray->Bind();

	std::vector<float> rawPositions{};
	std::vector<float> rawTextCoords{};
	std::vector<float> rawNormals{};

	for (const auto& vertex: m_vertices)
	{
		// Position
		rawPositions.push_back(vertex.m_position[0]);
		rawPositions.push_back(vertex.m_position[1]);
		rawPositions.push_back(vertex.m_position[2]);

		// TextCoord
		rawTextCoords.push_back(vertex.m_textCoords[0]);
		rawTextCoords.push_back(vertex.m_textCoords[1]);

		// Normal
		rawNormals.push_back(vertex.m_normal[0]);
		rawNormals.push_back(vertex.m_normal[1]);
		rawNormals.push_back(vertex.m_normal[2]);
	}

	// Buffer gen
	m_vboPosition = new Buffers::VertexBuffer(rawPositions);
	m_vboTextCoords = new Buffers::VertexBuffer(rawTextCoords);
	m_vboNormal = new Buffers::VertexBuffer(rawNormals);

	m_indexBuffer = new Buffers::IndexBuffer(m_indices);

	m_vertexArray->AddBuffer(m_vboPosition, 3, Buffers::GLType::FLOAT);
	m_vertexArray->AddBuffer(m_vboTextCoords, 2, Buffers::GLType::FLOAT);
	m_vertexArray->AddBuffer(m_vboNormal, 3, Buffers::GLType::FLOAT);

    m_vertexArray->Unbind();

}
