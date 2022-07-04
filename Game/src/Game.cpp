#include <ZoteApplication.h>

#include "Scripts/SwitchBetweenSprites.h"

using namespace Zote;

class Game : public Application
{

public:

	void Run() override
	{
		ScriptSystemExample();
	}

	void ScriptSystemExample()
	{
		Ref<Window> window = MakeRef<Window>();
		if (!window->Init()) return;

		Scene scene(window);

		Entity myEntity = scene.CreateEntity();
		myEntity.AddComponent<SpriteComponent>();
		
		auto& myEntity_Scripts = myEntity.AddComponent<ScriptComponent>();
		
		auto* switchScript = new SwitchBetweenSprites();
		switchScript->pathA = "Textures/zote.png";
		switchScript->pathB = "Textures/sus.png";
		switchScript->timeToSwitch = 1;

		myEntity_Scripts.AddScript(switchScript);

		window->StartLoop();
	}
};

Zote::Application* Zote::CreateApplication()
{
	return new Game();
}