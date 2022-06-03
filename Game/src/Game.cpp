#include <Zote.h>

class Game : public Zote::Application
{
	Zote::Window* window;

public:
	Game()
	{
		window = new Zote::Window();
	}
	~Game()
	{
		delete window;
	}

	void Run() override
	{
		if (!window->Init())
		{
			LOG("Zote Game window failed!")
			return;
		}

		window->StartLoop();
	}
};

Zote::Application* Zote::CreateApplication()
{
	LOG("Zote Game created!")
	return new Game();
}