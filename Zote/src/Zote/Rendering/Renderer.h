#pragma once
#include "ECS/Components.h"

namespace Zote
{
	struct ZOTE_API Renderer
	{
		inline static Camera* currentCamera;
		inline static Transform* currentCameraTransform;

		static void DrawMesh(MeshRenderer& meshRenderer, Transform& transform, float windowAspect)
		{
			if (currentCamera == nullptr || currentCameraTransform == nullptr) return;

			meshRenderer.shader->Use();

			currentCamera->UpdateAxis();
			
			//Projection matrix
			currentCamera->CalculateProjection(windowAspect);
			int projectionLocation = meshRenderer.shader->GetProjectionLocation();
			meshRenderer.shader->SetUnfiformMat4(projectionLocation, currentCamera->GetProjection());

			//View matrix
			currentCamera->CalculateView(*currentCameraTransform);
			int viewLocation = meshRenderer.shader->GetViewLocation();
			meshRenderer.shader->SetUnfiformMat4(viewLocation, currentCamera->GetView());

			//Model matrix
			transform.CalculateModel();
			int modelLocation = meshRenderer.shader->GetModelLocation();
			meshRenderer.shader->SetUnfiformMat4(modelLocation, transform.GetModel());

			meshRenderer.mesh->Render();
			meshRenderer.shader->Unbind();

			transform.position.y += 0.005f;
			LOG(transform.position.y);
		}
	};
}
