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
			vec2 spawn;
			spawn.x = RandomFloat(-3, 3);

			CreateEnemy({ spawn.x, 7 });
		}

		void CreateEnemy(vec2 spawn)
		{
			Entity enemy = scene->CreateEntity("Enemy Entity", "Enemy");

			enemy.AddComponent<SpriteComponent>().color = Color::red;
			auto& transform = enemy.GetComponent<TransformComponent>();
			transform.SetPosition({ spawn.x, spawn.y, 0 });
			transform.SetScale({ .5f, .5f, .5f });
			auto& pb = enemy.AddComponent<PBody2DComponent>();
			pb.SetMode(PBody2DComponent::Mode::dynamic);
			pb.SetGScale(0);
			pb.ApplyLinearImpulse({ 0, -1 });
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
		PhysicSystemExample();
		//Test();
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
		Entity gm = scene.CreateEntity();
		auto& gm_sc = gm.AddComponent<ScriptComponent>();
		auto* gmScript = new PhysicSystemExample::GameManager();
		gmScript->scene = &scene;
		gm_sc.AddScript(gmScript);

		//Player setup
		Entity player = scene.CreateEntity();
		auto& player_spc = player.AddComponent<SpriteComponent>();
		player_spc.color = Color::blue;

		auto& player_tc = player.GetComponent<TransformComponent>();
		player_tc.SetPosition({ 0, -6.5f, 0 });
		player_tc.SetScale({ 3, 1, 1 });
		player_tc.RotateLocal(10, { 0, 0, 1 });

		player.AddComponent<PBody2DComponent>();
		auto& player_sc = player.AddComponent<ScriptComponent>();
		auto* playerController = new PlayerController();
		playerController->scene = &scene;
		player_sc.AddScript(playerController);

		Entity detail = scene.CreateEntity();
		auto& detail_sc = detail.AddComponent<SpriteComponent>();
		detail_sc.color = Color::green;
		auto& detal_tc = detail.GetComponent<TransformComponent>();
		detal_tc.SetParent(player);
		detal_tc.SetPosition({ 0, 1, 0 });

		window->StartLoop();
	}


	void Test()
	{
		Ref<Window> window = MakeRef<Window>();
		if (!window->Init()) return;
		Scene scene(window);

		Entity a = scene.CreateEntity("A");
		a.AddComponent<PBody2DComponent>();

		Entity b = scene.CreateEntity("B");
		b.AddComponent<PBody2DComponent>();

		scene.DestroyEntity(a);

		window->StartLoop();
	}
};

Zote::Application* Zote::CreateApplication()
{
	return new Game();
}