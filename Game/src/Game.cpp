#include <Zote.h>

using namespace Zote;

class MoveTriangleScript : public Script
{
	float speed = 5;

	virtual void Start() override
	{
		printf("Started Triangle");
	}

	virtual void Update(float deltaTime) override
	{
		GetEntity()->GetTransform().position.x += speed;
	}
};

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

		scene = new Scene(*window);

		Entity testTriangle = scene->CreateEntity();

		MeshComponent& m = testTriangle.AddComponent<MeshComponent>();
		TransformComponent& t = testTriangle.GetTransform();

		t.position.z = -2.5f;
		t.position.y = 0.5f;

		ScriptComponent& s = testTriangle.AddComponent<ScriptComponent>();
		MoveTriangleScript script;
		s.AddScript(&script);

		window->StartLoop();
	}
};

Zote::Application* Zote::CreateApplication()
{
	LOG("Zote Game created!")
	return new Game();
}