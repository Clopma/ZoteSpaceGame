#include <ZoteApplication.h>
#include "Scripts/MoveTriangle.h"
#include "Scripts/MoveCamera.h"

using namespace Zote;

class Game : public Application
{
	Ref<Window> window;
	Ref<Scene> scene;

public:

	Game()
	{
		//window = MakeRef<Window>("My Zote Game!", 1920, 1080, Color::Normalize(Color::grey));		
		window = MakeRef<Window>();
	}

	void Run() override
	{
		if (!window->Init())
		{
			LOG("Zote Game window failed!");
			return;
		}

		GameContext();
	}

	void GameContext()
	{
		scene = MakeRef<Scene>(window);

		scene->GetMainCamera().GetComponent<CameraComponent>().mode = CameraComponent::Mode::Perspective;
		scene->GetMainCamera().GetComponent<TransformComponent>().SetPosition({ 0, 0, -6 });

		/*Entity testTriangle = scene->CreateEntity();
		testTriangle.AddComponent<MeshComponent>();
		
		auto& testTriangle_rb = testTriangle.AddComponent<Rigidbody2DComponent>();
		testTriangle_rb.SetMode(Rigidbody2DComponent::Mode::dynamic);*/

		Entity blackSquare = scene->CreateEntity();
		auto& blackSquareSprite = blackSquare.AddComponent<SpriteComponent>();
		blackSquareSprite.color = { 0.f, 0.f, 0.f, 1.f };
		auto& blackSquareTransform = blackSquare.GetComponent<TransformComponent>();
		blackSquareTransform.RotateGlobal(-15.f, {0, 0, 1});
		blackSquareTransform.SetPosition({ 0, -3, 0 });
		blackSquareTransform.SetScale({ 5.f, 1.f, 1.f });
		auto& blackSquare_rb = blackSquare.AddComponent<Rigidbody2DComponent>();
		blackSquare_rb.SetGScale(0);
		blackSquare_rb.SetMode(Rigidbody2DComponent::Mode::kinematic);

		/*auto& testTriangle_scripts = testTriangle.AddComponent<ScriptComponent>();
		testTriangle_scripts.AddScript(new MoveTriangleScript()); */

		auto& mainCamera_scripts = scene->GetMainCamera().AddComponent<ScriptComponent>();
		mainCamera_scripts.AddScript(new MoveCamera());

		Entity zote = scene->CreateEntity();
		zote.GetComponent<TransformComponent>().SetPosition({ 0, 1, 0 });
		auto& zoteSprite = zote.AddComponent<SpriteComponent>("Textures/zote.png");
		auto& zote_rb = zote.AddComponent<Rigidbody2DComponent>();
		zote_rb.SetMode(Rigidbody2DComponent::Mode::dynamic);
		zote_rb.SetGScale(.2f);

		Entity redSquare = scene->CreateEntity();
		auto& redSquareSprite = redSquare.AddComponent<SpriteComponent>();
		redSquareSprite.color = Color::blue;

		Entity amogus = scene->CreateEntity();
		auto& amogusSprite = amogus.AddComponent<SpriteComponent>("Textures/sus.png");
		amogus.GetComponent<TransformComponent>().SetPosition({ -1, 0, 0 });
		window->StartLoop();
		
	}
};

Zote::Application* Zote::CreateApplication()
{
	return new Game();
}