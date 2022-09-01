#pragma once
#include <ZoteCommon.h>
using namespace Zote;

class MeteoriteSpawner : public Script {

	
public:
	void Update(float deltaTime) override;
	Scene* escena = nullptr;
	float transcurridoDesdeUltimaDificultad = 0;
	int numMeteoritosExtra = 0;
	inline static bool iniciando = true; //Aparentemente hay una instancia del spawner por cada meteorito que llama a esta clase así que lo he tenido que hacer estático
	int spawnerId;
	inline static Color badColor = Color::Normalize(Color(222.f, 117.f, 82.f, 1.f));
	inline static Color goodColor = Color::Normalize(Color(140.f, 240.f, 58.f, 1.f));
	Entity resetearMeteorito(Entity meteorito);
	float test = RandomFloat(0.2f, 0.45f);
	std::vector<Entity> meteoritos;
	



	bool debugUnMeteorito = false;
};