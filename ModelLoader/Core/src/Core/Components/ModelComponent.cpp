#include <stdafx.h>
#include <Core/Components/ModelComponent.h>
//#include <Core/GameObject.h>
#include <Rendering/LowRenderer/Camera.h>

using namespace Core::Components;

ModelComponent::ModelComponent(Core::GameObject& p_gameObject) : m_gameObject{ p_gameObject }
{
	m_model = nullptr;
	m_type = "Model";
}

ModelComponent::ModelComponent(Core::GameObject& p_gameObject, const char* p_path) : m_gameObject { p_gameObject }
{
	//m_model = &Rendering::Resources::Model(p_path);
	m_model = new Rendering::Resources::Model(p_path);
}

ModelComponent::~ModelComponent()
{
	delete m_model;
}

ModelComponent::ModelComponent(const ModelComponent & p_other) : m_gameObject{ p_other.m_gameObject }
{
	m_type = p_other.m_type;
	m_model = p_other.m_model;
}

const std::string& ModelComponent::GetType() const
{
	return m_type;
}

void Core::Components::ModelComponent::Update()
{
	glm::mat4 projection = Rendering::LowRenderer::Camera::GetInstance()->GetProjectionMatrix();
	glm::mat4 view = Rendering::LowRenderer::Camera::GetInstance()->GetViewMatrix();

	glm::mat4 modelMatrix = m_gameObject.GetTransform().GetModelMatrix();

	m_model->GetShader()->Bind();
	m_model->GetShader()->SetUniformMatrix4fv("modelMatrix", modelMatrix);
	m_model->GetShader()->SetUniformMatrix4fv("projectionMatrix", projection);
	m_model->GetShader()->SetUniformMatrix4fv("viewMatrix", view);
	m_model->GetShader()->Unbind();
}

Rendering::Resources::Mesh* ModelComponent::GetMesh()
{
	return m_model->GetMesh();
}

Rendering::Resources::Model* ModelComponent::GetModel()
{
	return m_model;
}
