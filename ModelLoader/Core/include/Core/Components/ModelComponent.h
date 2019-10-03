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
		~ModelComponent();
		ModelComponent(const ModelComponent& p_other);

		const std::string& GetType() const override;
		void Update() override;
		Rendering::Resources::Mesh* GetMesh();
		Rendering::Resources::Model* GetModel();

	private:
		std::string m_type = "ModelComponent";
		Rendering::Resources::Model* m_model;
		Core::GameObject& m_gameObject;
	};
}
