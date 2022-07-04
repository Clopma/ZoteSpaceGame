#include <ZoteApplication.h>
#include "Scripts/MoveTriangle.h"
#include "Scripts/MoveCamera.h"
#include "ZoteCommon.h"
using namespace Zote;

class Game : public Application
{
	Ref<Window> window;
	Ref<Scene> scene;

public:

	Game()
	{
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
		testTriangle.AddComponent<MeshComponent>();*/
	
		Entity blackSquare = scene->CreateEntity();
		auto& blackSquareSprite = blackSquare.AddComponent<SpriteComponent>();
		blackSquareSprite.color = { 0.f, 0.f, 0.f, 1.f };
		auto& blackSquareTransform = blackSquare.GetComponent<TransformComponent>();
		blackSquareTransform.RotateGlobal(-15.f, {0, 0, 1});
		blackSquareTransform.SetPosition({ 0, -3, 0 });
		blackSquareTransform.SetScale({ 200.f, 1.f, 1.f });
		auto& blackSquare_rb = blackSquare.AddComponent<PBody2DComponent>();
		blackSquare_rb.SetGScale(0);
		blackSquare_rb.SetMode(PBody2DComponent::Mode::kinematic);

		/*auto& testTriangle_scripts = testTriangle.AddComponent<ScriptComponent>();
		testTriangle_scripts.AddScript(new MoveTriangleScript()); */

		auto& mainCamera_scripts = scene->GetMainCamera().AddComponent<ScriptComponent>();
		mainCamera_scripts.AddScript(new MoveCamera());

		Entity zote = scene->CreateEntity();
		zote.GetComponent<TransformComponent>().SetPosition({ 0, 1, 0 });
		auto& zoteSprite = zote.AddComponent<SpriteComponent>("Textures/zote.png");
		auto& zote_rb = zote.AddComponent<PBody2DComponent>();
		zote_rb.SetMode(PBody2DComponent::Mode::dynamic);

		auto& scComponent = zote.AddComponent<ScriptComponent>();
		scComponent.AddScript(new MoveTriangleScript());
		//zote_rb.SetShape(Rigidbody2DComponent::Shape::circle);
		//zote_rb.SetRadius(.5f);

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