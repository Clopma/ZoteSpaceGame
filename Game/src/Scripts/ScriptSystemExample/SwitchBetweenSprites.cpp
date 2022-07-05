#include "SwitchBetweenSprites.h"

void SwitchBetweenSprites::Start()
{
	LOG("Script SwitchBetweenSprites started");
	thisEntity = GetEntity();
}

void SwitchBetweenSprites::Update(float deltaTime)
{
	auto& spriteComponent = thisEntity.GetComponent<SpriteComponent>();
	
	currentTime += deltaTime;

	if (currentTime < timeToSwitch)
		return;

	currentTime = 0;

	cstr path = change ? pathA : pathB;
	spriteComponent.AddTexture(path);
	change = !change;

	LOG("Sprite texture updated to: " << path);
}
