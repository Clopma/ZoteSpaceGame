#pragma once
#include <ZoteCommon.h>
using namespace Zote;

class StarSpawner : public Script {


public:
	void Update(float deltaTime) override;
	Scene* escena = nullptr;
	float transcurridoDesdeUltimaEstrella = 0;
	int estrellasCreadas = 0;
	void crearEstrella(vec3 posicion);
};