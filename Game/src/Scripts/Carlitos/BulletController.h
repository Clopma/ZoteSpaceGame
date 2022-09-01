#pragma once
#include <ZoteCommon.h>
using namespace Zote;

class BulletController : public Script {


public:
	void Update(float deltaTime) override;
	void OnCollision(Entity entity) override;
	Scene* escena = nullptr;
	int spawnerScriptId;
	Entity score;
	float tiempoDesdeDisparo = 0.f;
};
