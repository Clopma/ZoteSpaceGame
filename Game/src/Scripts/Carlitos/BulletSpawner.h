#pragma once
#include <ZoteCommon.h>
using namespace Zote;

class BulletSpawner : public Script {


public:
	void Start() override;
	void Update(float deltaTime) override;
	Scene* escena = nullptr;
	float transcurridoDesdeUltimoMeteorito = 100000;
	int spawnerId;
	Entity ship;
	vec3 leftBulletSpawnOrigin = vec3(-0.1f, 0.1f, 0.f);
	vec3 rightBulletSpawnOrigin = vec3(0.1f, 0.1f, 0.f);
	Entity crearBala(vec3 posicion, Entity score);
	void recolocarBala(Entity bala, vec3 posicion);
	Entity balaIzq;
	Entity balaDer;
	Entity score;
	
};