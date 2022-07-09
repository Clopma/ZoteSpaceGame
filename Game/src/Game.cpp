#include <ZoteApplication.h>

#include "Scripts/ScriptSystemExample/SwitchBetweenSprites.h"
#include "Scripts/PhysicSystemExample/PlayerController.h"
#include "Scripts/PhysicSystemExample/GameManager.h"

using namespace Zote;

class Game : public Application
{

public:

	void Run() override
	{
		//ScriptSystemExample();
		PhysicSystemExample();
	}

	void ScriptSystemExample()
	{
		Ref<Window> window = MakeRef<Window>();
		if (!window->Init()) return;

		Scene scene(window);

		Entity myEntity = scene.CreateEntity();
		myEntity.AddComponent<SpriteComponent>();

		auto& myEntity_Scripts = myEntity.AddComponent<ScriptComponent>();
		myEntity_Scripts.AddScript(new SwitchBetweenSprites());

		window->StartLoop();
	}
	void PhysicSystemExample()
	{
		Ref<Window> window = MakeRef<Window>();
		if (!window->Init()) return;
		
		Scene scene(window);

		//Camera setup
		Entity camera = scene.GetMainCamera();
		auto& camera_cc = camera.GetComponent<CameraComponent>();
		camera_cc.size *= 5;

		//Game Manager setup
		{
			auto* gameManager = new GameManager();
			gameManager->scene = &scene;
			Entity gm = scene.CreateScriptableEntity(gameManager);
		}

		//Player setup
		{
			auto playerController = new PlayerController();
			playerController->scene = &scene;
			Entity player = scene.CreateScriptableEntity(playerController, "Player Entity", "Player");
		}

		//Lose Trigger
		{
			Entity groundTrigger = scene.CreateEntity("Ground Trigger", "Ground");
			auto& transform = groundTrigger.GetComponent<TransformComponent>();
			transform.SetPosition({ 0, -7, 0 });
			transform.SetScale({ 20, 1, 0 });
			auto& body = groundTrigger.AddComponent<PBody2DComponent>();
			body.SetIsTrigger(true);
		}

		window->StartLoop();
	}
};

Zote::Application* Zote::CreateApplication()
{
	return new Game();
}