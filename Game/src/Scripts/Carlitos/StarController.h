#pragma once
#include <ZoteCommon.h>
using namespace Zote;

class StarController : public Script {


public:
	void Update(float deltaTime) override;
	Scene* escena = nullptr;
	float tiempoDesdeCreacion = 0;
};
