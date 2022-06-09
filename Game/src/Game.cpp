#include <ZoteApplication.h>
#include "MoveTriangle.h"

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

		testTriangle.AddComponent<MeshComponent>();
		auto& testTriangle_scripts = testTriangle.AddComponent<ScriptComponent>();
		testTriangle_scripts.AddScript(new MoveTriangleScript());

		window->StartLoop();
	}
};

Zote::Application* Zote::CreateApplication()
{
	return new Game();
}