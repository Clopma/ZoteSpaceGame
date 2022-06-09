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

		MeshComponent& m = testTriangle.AddComponent<MeshComponent>();
		TransformComponent& t = testTriangle.GetTransform();
		ScriptComponent& s = testTriangle.AddComponent<ScriptComponent>();
		MoveTriangleScript script;

		s.AddScript(&script);

		window->StartLoop();
	}
};

Zote::Application* Zote::CreateApplication()
{
	return new Game();
}