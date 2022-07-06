#pragma once
#include "Core.h"
#include "BaseComponent.h"
#include "Utils/Math.h"

namespace Zote
{
	struct ZOTE_API TransformComponent : public BaseComponent
	{
		TransformComponent() 
		{
			RotateGlobal(0, GetForward());
			RotateGlobal(0, GetRight());
			RotateGlobal(0, GetUp());
		}

		TransformComponent(const TransformComponent& other) = default;

		void SetParent(Entity parent)
		{
			this->parent = parent;
			hasParent = true;
		}

		void RemoveParent() { hasParent = false; }

		void SetPosition(const vec3& newPos) { position = newPos; }
		const vec3& GetPosition() const { return position; }

		void SetScale(const vec3& newScale) { scale = newScale; }
		const vec3& GetScale() const { return scale; }

		void SetRotation(const quat& newRot) { rotation = newRot; UpdateAxis(); }
		const quat& GetRotation() const { return rotation; }

		const vec3& GetForward() const { return forward; }
		const vec3& GetRight() const { return right; }
		const vec3& GetUp() const { return up; }

		void RotateLocal(const float& degrees, const vec3& axis)
		{
			rotation = rotation * glm::normalize(glm::angleAxis(glm::radians(degrees), axis));
			rotation = glm::normalize(rotation);
			UpdateAxis();
		}

		void RotateGlobal(const float& degrees, const vec3& axis)
		{
			rotation = glm::normalize(glm::angleAxis(glm::radians(degrees), axis)) * rotation;
			rotation = glm::normalize(rotation);
			UpdateAxis();
		}

		const mat4 GetModel()
		{
			mat4 model = mat4(1.0f);

			vec3 position = GetPosition();
			quat rotation = GetRotation();

			if (hasParent)
			{
				auto& parentTransform = parent.GetComponent<TransformComponent>();
				position += parentTransform.GetPosition();
				rotation += parentTransform.GetRotation();
			}			

			model = glm::translate(model, position);
			model = model * glm::toMat4(rotation);
			model = glm::scale(model, GetScale());
			return model;
		}

	private:
		Entity parent;
		bool hasParent = false;

		vec3 position = { 0, 0, 0 };
		quat rotation = { 1, 0, 0, 0 };
		vec3 scale = { 1, 1, 1 };

		vec3 right = { 1, 0, 0 };
		vec3 up = { 0, 1, 0 };
		vec3 forward = { 0, 0, 1 };

		void UpdateAxis()
		{
			mat4 axis = mat4(1.0f);

			axis = axis * glm::toMat4(rotation);

			forward = axis * vec4(0, 0, 1, 0);
			right = -axis * vec4(1, 0, 0, 0);
			up = axis * vec4(0, 1, 0, 0);
		}	
	};
}
