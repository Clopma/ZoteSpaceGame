#include <Zote.h>

using namespace Zote;

class MoveTriangleScript : public Script
{
	float speed = 0.5f;
	TransformComponent* transform;

	virtual void Start() override
	{
		printf("Started Triangle");
		transform = &GetEntity()->GetComponent<TransformComponent>();
		//transform = &GetEntity()->GetTransform();
	}

	virtual void Update(float deltaTime) override
	{
		float dir;

		bool aPressed = Input::GetKeyPressed(ZOTE_KEY_A);
		bool dPressed = Input::GetKeyPressed(ZOTE_KEY_D);

		if (aPressed)
			dir = -1;
		if (dPressed)
			dir = 1;
		if (aPressed && dPressed || !aPressed && !dPressed)
			dir = 0;

		transform->position.x += dir * speed * deltaTime;
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