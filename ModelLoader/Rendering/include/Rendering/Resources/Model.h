#pragma once
#include <Rendering/Export.h>
#include <Rendering/Resources/Mesh.h>
#include <Rendering/Resources/Shader.h>
#include <vector>
#include <string>
#include <memory>
#include <atomic>

namespace Rendering::Resources
{
    class API_RENDERING Model
    {
    public:
        Model() noexcept = default;
        Model(const char* p_path) noexcept;
        Model(const char* p_modelPath,
              const std::string& p_vertexFilepath,
              const std::string& p_fragmentFilepath) noexcept;
		Model(Mesh* p_mesh);
        Model(const Model& p_other) noexcept;

		void AddTexture(const std::string & p_texturePath) const;

        Mesh* GetMesh() noexcept { return m_mesh; }

        Shader* GetShader() noexcept { return m_shader; }

		Texture* GetTexture() noexcept { return m_mesh->GetTexture(); };

        void Bind() const noexcept;
        void Unbind() const noexcept;
		static Model StaticLoadModel(const char* path);

        void LoadShader(
            const std::string& p_vertexFilepath =
                    "../rsc/shaders/defaultShader.vert",
            const std::string& p_fragmentFilepath =
                    "../rsc/shaders/defaultShader.frag") noexcept;
    private:
        std::string m_directory;
        Shader* m_shader;
        Mesh*   m_mesh;

        void LoadModel(const char* path) noexcept;
    };
}
