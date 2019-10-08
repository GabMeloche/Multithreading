#include <stdafx.h>
#include <Rendering/Managers/Renderer.h>
#include <Rendering/Resources/Model.h>
#include "Rendering/LowRenderer/Camera.h"
#include "Rendering/Resources/Transform.h"


Rendering::Managers::Renderer::~Renderer() noexcept
{
	//delete m_driver;
}

void Rendering::Managers::Renderer::Clear() const noexcept
{
	m_driver->Clear();
}

void Rendering::Managers::Renderer::PolygonModeLine() noexcept
{
	m_fillDrawIsOn = false;
	m_driver->PolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Rendering::Managers::Renderer::PolygonModeFill() noexcept
{
	m_fillDrawIsOn = true;
	m_driver->PolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Rendering::Managers::Renderer::Draw(
	Resources::Model* p_model, Resources::Transform& p_transform) const noexcept
{
	if (p_model == nullptr)
		return;

	glm::mat4 projection = Rendering::LowRenderer::Camera::GetInstance()->GetProjectionMatrix();
	glm::mat4 view = Rendering::LowRenderer::Camera::GetInstance()->GetViewMatrix();

	glm::mat4 modelMatrix = p_transform.GetModelMatrix();
	
	if (p_model->GetShader() && p_model->GetMesh())
	{
		p_model->GetShader()->Bind();
		p_model->GetShader()->SetUniformMatrix4fv("modelMatrix", modelMatrix);
		p_model->GetShader()->SetUniformMatrix4fv("projectionMatrix", projection);
		p_model->GetShader()->SetUniformMatrix4fv("viewMatrix", view);
		p_model->GetShader()->Unbind();
	}
	
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	p_model->Bind();

	if (p_model->GetMesh()->GetIndicesCount() > 0)
	{
		glDrawElements(GL_TRIANGLES, p_model->GetMesh()->GetIndicesCount(),
			GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, p_model->GetMesh()->GetVertexCount());
	}

	p_model->Unbind();
}

bool Rendering::Managers::Renderer::IsDrawFilled() const
{
	return m_fillDrawIsOn;
}
