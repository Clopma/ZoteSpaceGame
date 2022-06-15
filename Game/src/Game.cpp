#include <ZoteApplication.h>
#include "Scripts/MoveTriangle.h"
#include "Scripts/MoveCamera.h"

using namespace Zote;

class Game : public Application
{
	Window* window = nullptr;
	Scene* scene = nullptr;

public:

	Game()
	{
		window = new Window();
	}
	~Game()
	{
		if (scene != nullptr)
			delete scene;
		
		delete window;
	}

	void Run() override
	{
		if (!window->Init())
		{
			LOG("Zote Game window failed!")
			return;
		}

		GameContext();
	}

	void GameContext()
	{
		scene = new Scene(*window);

		Entity testTriangle = scene->CreateEntity();

		testTriangle.GetComponent<TransformComponent>().SetPosition( { 0, 0, 3 });

		testTriangle.AddComponent<MeshComponent>();

		auto& testTriangle_scripts = testTriangle.AddComponent<ScriptComponent>();
		testTriangle_scripts.AddScript(new MoveTriangleScript());

		auto& mainCamera_scripts = scene->GetMainCamera().AddComponent<ScriptComponent>();
		mainCamera_scripts.AddScript(new MoveCamera());

		window->StartLoop();
	}
};

Zote::Application* Zote::CreateApplication()
{
	return new Game();
}