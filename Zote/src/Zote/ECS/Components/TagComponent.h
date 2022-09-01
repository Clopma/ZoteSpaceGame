#pragma once

#include "Core.h"
#include "ECS/Components/BaseComponent.h"

#include "Utils/String.h"

namespace Zote
{
	struct ZOTE_API TagComponent : public BaseComponent
	{
		str name = "Entity";
		str tag = "Default";

		TagComponent() {}
		TagComponent(const TagComponent& other) = default;

		bool CompareTag(str other)
		{
			return !tag.compare(other);
		}

		bool CompareName(str other)
		{
			return !name.compare(other);
		}
	};
}

