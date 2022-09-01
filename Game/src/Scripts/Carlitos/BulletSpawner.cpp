#include "BulletSpawner.h"
#include "BulletController.h"

void BulletSpawner::Start()
{
	balaIzq = crearBala(ship.GetComponent<TransformComponent>().GetPosition() + vec3(100.0, 100.0, 100.0), score);
	balaDer = crearBala(ship.GetComponent<TransformComponent>().GetPosition() + vec3(100.0, 100.0, 100.0), score);
}

void BulletSpawner::Update(float deltaTime)
{
	transcurridoDesdeUltimoMeteorito += deltaTime;
	
	if (transcurridoDesdeUltimoMeteorito > 0.4f && Input::GetKeyPressed(ZOTE_KEY_SPACE)) {
		
		transcurridoDesdeUltimoMeteorito = 0;
		recolocarBala(balaIzq, ship.GetComponent<TransformComponent>().GetPosition() + leftBulletSpawnOrigin);
		recolocarBala(balaDer, ship.GetComponent<TransformComponent>().GetPosition() + rightBulletSpawnOrigin);
	}
}
Entity BulletSpawner::crearBala(vec3 posicion, Entity score)
{
	BulletController* bulletController = new BulletController();
	bulletController->spawnerScriptId = spawnerId;
	bulletController->escena = escena;
	bulletController->score = score;
	//TODO meter todo esto en el controller start
	Entity bala = escena->CreateScriptableEntity(bulletController);
	TransformComponent& transform = bala.GetComponent<TransformComponent>();
	transform.SetPosition(posicion);
	transform.SetScale(vec3(0.15f, 0.15f, 0.0f));
	bala.AddComponent<SpriteComponent>("Textures/star.png").color = Color::red;
	auto& balaBody = bala.AddComponent<PBody2DComponent>();
	balaBody.SetIsTrigger(true);

	return bala;

}

void BulletSpawner::recolocarBala(Entity bala, vec3 posicion)
{
	TransformComponent& transform = bala.GetComponent<TransformComponent>();
	transform.SetPosition(posicion);
	bala.GetComponent<ScriptComponent>();
	//((BulletController*) GetEntity().GetComponent<ScriptComponent>().GetScript(spawnerId))-> = false;
}

