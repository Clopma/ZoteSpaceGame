#include <ZoteApplication.h>

using namespace Zote;

class Game : public Application
{

public:

	void Run() override
	{
		Ref<Window> window = MakeRef<Window>();
		if (!window->Init()) return;

		Scene scene(window);

		Entity zote = scene.CreateEntity();
		zote.AddComponent<SpriteComponent>("Textures/zote.png");

		window->StartLoop();
	}
};

Zote::Application* Zote::CreateApplication()
{
	return new Game();
}