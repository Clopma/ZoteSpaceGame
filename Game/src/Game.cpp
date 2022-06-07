#include <Zote.h>

using namespace Zote;

class Game : public Application
{
	Window* window;
	Scene* scene;

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

		scene = new Scene(*window);

		Entity testTriangle = scene->CreateEntity();

		MeshComponent& m = testTriangle.AddComponent<MeshComponent>();
		TransformComponent& t = testTriangle.GetTransform();

		t.position.z = -2.5f;
		t.position.y = 0.5f;

		window->StartLoop();
	}
};

Zote::Application* Zote::CreateApplication()
{
	LOG("Zote Game created!")
	return new Game();
}