#pragma once
#include "Core.h"

namespace Zote
{
	class Entity;

	struct ZOTE_API BaseComponent
	{
		friend class Entity;

		bool enabled = true;
		Entity* GetEntity() { return entity; }

	private:
		static constexpr auto in_place_delete = true;
		Entity* entity = nullptr;
	};
}