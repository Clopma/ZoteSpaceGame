 #include <ZoteApplication.h>
 #include "Scripts/Carlitos/MeteoriteSpawner.h"
 #include "Scripts/Carlitos/ShipController.h"
 #include "Scripts/Carlitos/StarSpawner.h"
 #include "Scripts/Carlitos/BulletSpawner.h"

 using namespace Zote;

 class Game : public Application
 {

 public:

 	void Run() override
 	{
 		Ref<Window> window = MakeRef<Window>("Principal", 1920, 1080, Color(0.1f, 0.1f, 0.1f, 1.f));
 		if (!window->Init()) return;
 		Scene scene(window);

 		Entity camera = scene.GetMainCamera();
 		camera.GetComponent<CameraComponent>().size = vec2(1920.f / 500.f, 1080.f / 500.f);

 		int spawnerId = createMeteoriteSpawner(&scene);
 		createStarSpawner(&scene);
 		Entity ship = createShip(&scene);
 		Entity score = createScore(&scene);
 		createBulletSpawner(&scene, ship, spawnerId, score);
 		createScoreOverlay(&scene);

 		window->StartLoop();
 	}

 	int createMeteoriteSpawner(Scene* scene) {
 		Entity meteoriteSpawnerEntity = scene->CreateEntity();
 		MeteoriteSpawner* meteoriteSpawner = new MeteoriteSpawner();
 		meteoriteSpawner->escena = scene;
 		int scriptSpawnerId = meteoriteSpawnerEntity.AddComponent<ScriptComponent>().AddScript(meteoriteSpawner);
 		meteoriteSpawner->spawnerId = scriptSpawnerId;
 		return scriptSpawnerId;
 	}

 	void createStarSpawner(Scene* scene) {
 		Entity starSpawnerEntity = scene->CreateEntity();
 		StarSpawner* starSpawner = new StarSpawner();
 		starSpawner->escena = scene;
 		starSpawnerEntity.AddComponent<ScriptComponent>().AddScript(starSpawner);
 	}

 	void createBulletSpawner(Scene* scene, Entity theShip, int spawnerId, Entity scoreEntity) {
 		Entity bulletSpawnerEntity = scene->CreateEntity();
 		BulletSpawner* bulletSpawner = new BulletSpawner();
 		bulletSpawner->spawnerId = spawnerId;
 		bulletSpawner->score = scoreEntity;
 		bulletSpawner->escena = scene;
 		bulletSpawner->ship = theShip;
 		bulletSpawnerEntity.AddComponent<ScriptComponent>().AddScript(bulletSpawner);
 	}

 	Entity createShip(Scene* scene) {
 		ShipController* shipController = new ShipController();
 		shipController->escena = scene;
 		//TODO meter todo esto en el controller start
 		Entity ship = scene->CreateScriptableEntity(shipController);
 		TransformComponent& transform = ship.GetComponent<TransformComponent>();
 		transform.SetPosition(vec3(0, 0, 0));
 		transform.SetScale(VEC3_ONE * 0.3f);
 		ship.AddComponent<SpriteComponent>("Textures/ship.png");
 		auto& body = ship.AddComponent<PBody2DComponent>();
 		body.SetMode(PBody2DComponent::Mode::dynamic);
 		body.SetGScale(0);
 		return ship;
 	}

 	Entity createScore(Scene* scene) {
 		Entity score = scene->CreateEntity();
 		TransformComponent& transform = score.GetComponent<TransformComponent>();
 		transform.SetPosition(vec3(2.95, 1.7, 0));
 		transform.SetScale(vec3(0.2f, 0.2f, 1.0f));
 		score.AddComponent<SpriteComponent>("Textures/score.png");
 		return score;
 	}

 	void createScoreOverlay(Scene* scene) {
 		Entity so = scene->CreateEntity();
 		TransformComponent& transform = so.GetComponent<TransformComponent>();
 		transform.SetPosition(vec3(3.5f, 1.7, 0));
 		transform.SetScale(vec3(1.0f, 0.8f, 1.0f));
 		so.AddComponent<SpriteComponent>("Textures/scoreOverlay.png");
 	}

 };

 Zote::Application* Zote::CreateApplication()
 {
 	return new Game();
 }