#pragma once
#include "Core.h"
#include "BaseComponent.h"

#include "Rendering/Shader.h"
#include "Rendering/Sprite.h"

#include "Utils/Memory.h"

namespace Zote
{
	struct ZOTE_API SpriteComponent : public BaseComponent
	{
		Ref<Sprite> sprite;
		Ref<Shader> shader;

		SpriteComponent()
		{
			sprite = MakeRef<Sprite>();
			shader = MakeRef<Shader>(sprite->GetVertPath(), sprite->GetFragPath());
		}
	};
}