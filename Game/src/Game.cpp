#include <Zote.h>

struct Args
{
	std::string message;
	int number;

public:
	Args(std::string message, int number)
		: message(message), number(number) {}
};

struct Sender
{
	Zote::Event<Args> senderEvent;
	void Fire() { senderEvent.Invoke(Args("Primer evento!!!", 3)); }
	Sender() {}
};

struct Subscriber
{
	void OnGameEvent(Args args) { LOG(args.message) }
	void OnGameEventPlus(Args args) { LOG(args.number) }

	Subscriber() {}

	Subscriber(Sender* sender)
	{
		sender->senderEvent.AddListener(DELEGATE(Args, *this, Subscriber, OnGameEvent));
		sender->senderEvent.AddListener(DELEGATE(Args, *this, Subscriber, OnGameEventPlus));
	}
};

class Game : public Zote::Application
{
	Zote::Window* window;
	Sender* send;
	Subscriber* sub;

public:

	Game()
	{
		send = new Sender();
		sub = new Subscriber(send);
		window = new Zote::Window();
	}
	~Game()
	{
		delete window;
	}

	void Run() override
	{
		send->Fire();
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