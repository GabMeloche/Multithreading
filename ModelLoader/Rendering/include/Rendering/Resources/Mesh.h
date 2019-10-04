#pragma once

#include <vector>

#include <Rendering/Export.h>

#include <Rendering/Buffers/VertexBuffer.h>
#include <Rendering/Buffers/VertexArray.h>
#include <Rendering/Buffers/IndexBuffer.h>

#include <Rendering/Geometry/Vertex.h>

#include <Rendering/Resources/Shader.h>
#include "Texture.h"

namespace Rendering::Resources
{
	class API_RENDERING Mesh
	{
	public:
		Mesh() = default;
		Mesh(std::vector<Geometry::Vertex>& p_vertices, std::vector<uint32_t>& p_indices) noexcept;
		~Mesh() noexcept;

		void AddTexture(const std::string & p_texturePath);

		void Bind() const noexcept;
		void Unbind() const noexcept;

		const uint32_t GetVertexCount() const noexcept;
		const uint32_t GetIndicesCount() const noexcept;
		const Buffers::VertexArray* GetVertexArray() const { return m_vertexArray; }
		bool GetQuad() const noexcept { return m_quad; }
		Texture* GetTexture() { return m_texture; };

		void CreateBuffers() noexcept;

		void SetVertexArray(Buffers::VertexArray* p_vertexArray) { m_vertexArray = p_vertexArray; }
		void SetQuad(bool p_quad) { m_quad = p_quad; }
		
	private:
		bool m_quad;
		const uint32_t m_vertexCount{};
		const uint32_t m_indicesCount{};

		Buffers::VertexArray* m_vertexArray;
		Buffers::VertexBuffer* m_vboPosition;
		Buffers::VertexBuffer* m_vboTextCoords;
		Buffers::VertexBuffer* m_vboNormal;
		Buffers::IndexBuffer* m_indexBuffer;
		std::vector<Geometry::Vertex> m_vertices;
		std::vector<uint32_t> m_indices;
		Texture* m_texture;
	};
}
