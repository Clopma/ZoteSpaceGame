#pragma once
#include <ZoteCommon.h>
using namespace Zote;

class MeteoriteDestroyer : public Script {


public:
	void Update(float deltaTime) override;
	Scene* escena = nullptr;
	bool destruido = false;
	float tiempoDesdeImpakto = 0;
	float impaktado = false;
	int spawnerId;
};
