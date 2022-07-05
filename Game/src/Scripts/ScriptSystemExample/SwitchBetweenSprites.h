#pragma once
#include <ZoteCommon.h>

using namespace Zote;

class SwitchBetweenSprites : public Script
{
public:
	cstr pathA = "";
	cstr pathB = "";
	float timeToSwitch = 0;

	void Start() override;
	void Update(float deltaTime) override;

private:
	
	Entity thisEntity;
	bool change = false;
	float currentTime = 0;

};
