#include <ZoteApplication.h>

#include "Scripts/ScriptSystemExample/SwitchBetweenSprites.h"
#include "Scripts/PhysicSystemExample/PlayerController.h"

using namespace Zote;

namespace PhysicSystemExample
{
	class GameManager : public Script
	{
	public:
		float spawnRate = 2;
		Scene* scene = nullptr;

		void Update(float deltaTime) override
		{
			time += deltaTime;
			if (time < spawnRate) return;
			time = 0;
			CreateEnemy({ 0, 0 });
		}

		void CreateEnemy(vec2 spawn)
		{
			Entity enemy = scene->CreateEntity();
			enemy.name = "Enemy Entity";
			enemy.tag = "Enemy";

			enemy.AddComponent<SpriteComponent>().color = Color::red;
			auto& transform = enemy.GetComponent<TransformComponent>();
			transform.SetPosition({ spawn.x, spawn.y, 0 });
			transform.SetScale({ .5f, .5f, .5f });
			auto& pb = enemy.AddComponent<PBody2DComponent>();
			pb.SetMode(PBody2DComponent::Mode::dynamic);
			pb.SetGScale(0);
			pb.ApplyLinearImpulse({ 0, -5 });
		}

	private:	
		float time = 0;
	};
}

class Game : public Application
{

public:

	void Run() override
	{
		//ScriptSystemExample();
		//PhysicSystemExample();
		Test();
	}

	void ScriptSystemExample()
	{
		Ref<Window> window = MakeRef<Window>();
		if (!window->Init()) return;

		Scene scene(window);

		Entity myEntity = scene.CreateEntity();
		myEntity.AddComponent<SpriteComponent>();
		
		auto& myEntity_Scripts = myEntity.AddComponent<ScriptComponent>();
		
		auto* switchScript = new SwitchBetweenSprites();
		switchScript->pathA = "Textures/zote.png";
		switchScript->pathB = "Textures/sus.png";
		switchScript->timeToSwitch = 1;

		myEntity_Scripts.AddScript(switchScript);

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
		/*Entity gm = scene.CreateEntity();
		auto& gm_sc = gm.AddComponent<ScriptComponent>();
		auto* gmScript = new PhysicSystemExample::GameManager();
		gmScript->scene = &scene;
		gm_sc.AddScript(gmScript);*/

		Entity enemy = scene.CreateEntity();
		enemy.name = "Enemy Entity";
		enemy.tag = "Enemy";

		enemy.AddComponent<SpriteComponent>().color = Color::red;
		auto& transform = enemy.GetComponent<TransformComponent>();
		transform.SetPosition({ 0, 0, 0 });
		transform.SetScale({ .5f, .5f, .5f });
		auto& pb = enemy.AddComponent<PBody2DComponent>();
		pb.SetMode(PBody2DComponent::Mode::dynamic);
		pb.SetGScale(0);
		pb.ApplyLinearImpulse({ 0, -5 });

		//Player setup
		Entity player = scene.CreateEntity();
		auto& player_spc = player.AddComponent<SpriteComponent>();
		player_spc.color = Color::blue;

		auto& player_tc = player.GetComponent<TransformComponent>();
		player_tc.SetPosition({ 0, -6.5f, 0 });
		player_tc.SetScale({ 3, 1, 1 });

		player.AddComponent<PBody2DComponent>();
		auto& player_sc = player.AddComponent<ScriptComponent>();
		auto* playerController = new PlayerController();
		playerController->scene = &scene;
		player_sc.AddScript(playerController);

		window->StartLoop();
	}
	void Test()
	{
		Ref<Window> window = MakeRef<Window>();
		if (!window->Init()) return;
		Scene scene(window);

		Entity entity = scene.CreateEntity();
		entity.AddComponent<SpriteComponent>();
		auto& pb = entity.AddComponent<PBody2DComponent>();
		
		//pb.ApplyLinearImpulse({ 1, 0 });

		//pb.SetGScale(0);
		pb.SetMode(PBody2DComponent::Mode::dynamic);
		pb.SetGScale(0);
		pb.ApplyLinearImpulse({ 1, 0 });
		

		window->StartLoop();
	}
};

Zote::Application* Zote::CreateApplication()
{
	return new Game();
}