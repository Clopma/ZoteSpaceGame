#include <Zote.h>

struct Args
{
	std::string message;
	int number;

public:
	Args(std::string message, int number)
		: message(message), number(number) {}
};

class Game : public Zote::Application
{
	Zote::Window* window;
	Zote::Event<Game, Args> gameEvent;

public:
	
	void OnGameEvent(Args args) const { LOG(args.message) }
	void OnGameEventPlus(Args args) const { LOG(args.number) }

	Game()
	{
		int funcIndex = gameEvent.ADD_LISTENER(Game, OnGameEvent);
		gameEvent.ADD_LISTENER(Game, OnGameEventPlus);
		window = new Zote::Window();
	}
	~Game()
	{
		delete window;
	}

	void Run() override
	{
		gameEvent.Invoke(*this, Args("Primer evento!!!", 3));
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