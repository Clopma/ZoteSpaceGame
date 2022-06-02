#include <Zote.h>

class Game : public Zote::Application
{
public:
	Game()
	{

	}
	~Game()
	{

	}
};

Zote::Application* Zote::CreateApplication()
{
	printf("Zote Game created!");
	return new Game();
}