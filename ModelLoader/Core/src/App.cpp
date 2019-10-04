#pragma once

#include <iostream>
#include <cstdlib>
#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <Core/Components/PlayerComponent.h>
#include <Rendering/Context/OpenGL/GLFWDevice.h>
#include <Rendering/Context/OpenGL/GLEWDriver.h>
#include <Rendering/Managers/Renderer.h>
#include <Rendering/Resources/Model.h>
#include <Rendering/LowRenderer/Camera.h>
#include <Core/GameObject.h>
#include <Rendering/Managers/InputManager.h>
#include <Core/Scene.h>
#include <Core/GameManager.h>
#include <Core/Components/ModelComponent.h>
#include <Core/Components/CameraComponent.h>
#include <Core/ResourceManager.h>
#include <chrono>
#include <thread>

int main()
{
	auto device = std::make_unique<Rendering::Context::OpenGL::GLFWDevice>(1024, 768);
	std::unique_ptr<Rendering::Managers::Renderer> renderer = std::make_unique<Rendering::Managers::Renderer>();
	renderer->Initialize<Rendering::Context::OpenGL::GLEWDriver>();

	Rendering::Managers::InputManager::InitializeFirstInstance(device->GetWindow());

	Core::GameManager gameManager(renderer.get());
	Rendering::LowRenderer::Camera mainCamera;

	std::shared_ptr<Core::GameObject> statue = std::make_shared<Core::GameObject>();
	std::shared_ptr<Core::GameObject> table = std::make_shared<Core::GameObject>();
    std::shared_ptr<Core::GameObject> player = std::make_shared<Core::GameObject>();
    std::shared_ptr<Core::GameObject> gun = std::make_shared<Core::GameObject>();
	
	Core::Scene scene1{};
	ResourceManager resourceMgr{};
	auto start = std::chrono::high_resolution_clock::now();
	
	std::promise <Rendering::Resources::Model*> promise;
	// vector future
	// handshake
	
	resourceMgr.AddModel("../rsc/models/statue.obj");
	resourceMgr.AddModel("../rsc/models/TigerTank.obj");
	resourceMgr.AddModel("../rsc/models/BarrocMiniTable.obj");
	resourceMgr.WaitLoad();
	
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	
	resourceMgr.GetModels()[0]->GetMesh()->CreateBuffers();
	resourceMgr.GetModels()[0]->LoadShader();
	resourceMgr.GetModels()[1]->GetMesh()->CreateBuffers();
	resourceMgr.GetModels()[1]->LoadShader();
	resourceMgr.GetModels()[2]->GetMesh()->CreateBuffers();
	resourceMgr.GetModels()[2]->LoadShader();

	statue->AddComponent<Core::Components::ModelComponent>(resourceMgr.GetModels()[0]);
	player->AddComponent<Core::Components::ModelComponent>(resourceMgr.GetModels()[1]);
	table->AddComponent<Core::Components::ModelComponent>(resourceMgr.GetModels()[2]);


	std::cout << "time to load all objects: " << elapsed.count() << std::endl;
	
	glm::vec3 distanceFromPlayer(0.0f, 0.2f, 0.0f);
	player->AddComponent<Core::Components::CameraComponent>(distanceFromPlayer);

	player->AddTexture("../rsc/textures/brick.png");

	scene1.AddGameObject(statue, "statue");
	scene1.AddGameObject(player, "player");
	scene1.AddGameObject(table, "table");

	gameManager.AddScene(scene1);
	gameManager.SetActiveScene(0);

	glm::vec3 newPos = glm::vec3(-1.0f, 0, 0);
	glm::vec3 rota = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(0.01f, 0.01f, 0.01f);

	glm::vec3 newPos2 = glm::vec3(1.0f, 0, 0);
	glm::vec3 rota2 = glm::vec3(0, 0, 36);
	glm::vec3 scale2 = glm::vec3(0.005f, 0.005f, 0.005f);

	glm::vec3 newPos3 = glm::vec3(0.0f, 0, 3.0f);
	glm::vec3 rota3 = glm::vec3(0, 0, 0);
	glm::vec3 scale3 = glm::vec3(0.005f, 0.005f, 0.005f);

	gameManager.GetActiveScene().FindGameObject("statue")->SetTransform(newPos, rota, scale);
	gameManager.GetActiveScene().FindGameObject("player")->SetTransform(newPos3, rota3, scale3);
	gameManager.GetActiveScene().FindGameObject("table")->SetTransform(newPos2, rota2, scale2);

	//Core::Components::PlayerComponent& playerComp = *player->GetComponent<Core::Components::PlayerComponent>();

	while (!device->ShouldClose())
	{
		device->RefreshEvent();
		renderer->Clear();

		// ##### Game logic #####
		gameManager.HandleEvents();

		// ##### Update #####
		gameManager.Update();

		/*gameManager.GetActiveScene().FindGameObject("player")->SetTransform(newPos3, rota3, scale3);
		rota3.x += 1;
		rota3.y += 1;*/
		// ##### Drawing #####
		gameManager.DrawActiveScene(*renderer);
		device->Render();
	}

	//assert(Rendering::Resources::Loaders::MeshLoader::Destroy(mesh));

	return EXIT_SUCCESS;
}
