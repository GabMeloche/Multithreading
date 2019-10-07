#pragma once
#include <memory>
#include <Core/GameObject.h>
#include <Core/Components/IComponent.h>
#include <Rendering/Resources/Model.h>

namespace Core::Components
{
	class ModelComponent : public IComponent
	{
	public:
		ModelComponent(GameObject& p_gameObject);
		ModelComponent(GameObject& p_gameObject, const char* p_path);
		ModelComponent(Core::GameObject& p_gameObject, Rendering::Resources::Model* p_model);
		~ModelComponent() = default;
		ModelComponent(const ModelComponent& p_other);

		const std::string& GetType() const override;
		void Update() override;
		Rendering::Resources::Mesh* GetMesh() const;
		Rendering::Resources::Model* GetModel() const;

	private:
		Core::GameObject& m_gameObject;
		Rendering::Resources::Model* m_model;
		std::string m_type = "ModelComponent";
	};
}
