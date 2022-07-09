#pragma once
#include <ZoteCommon.h>

using namespace Zote;

class SwitchBetweenSprites : public Script
{
public:
	cstr pathA = "Textures/csharp.png";
	cstr pathB = "Textures/cpp.png";
	float timeToSwitch = 1;

	void Start() override;
	void Update(float deltaTime) override;

private:
	
	Entity thisEntity;
	bool change = false;
	float currentTime = 0;

};
