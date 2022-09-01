#pragma once

#include "ZoteApplication.h"

using namespace Zote;

class Game final : public Application
{
    void Run() override
    {
        const Ref<Window> window = MakeRef<Window>();
        window->Init();
        Scene scene(window);
        
        CreateEntities(scene);
        
        window->StartLoop();
    }

    static void CreateEntities(Scene& scene)
    {
        Entity alex = scene.CreateEntity();
        alex.AddComponent<SpriteComponent>("Textures/alex.png");
        alex.GetComponent<TransformComponent>().SetScale(vec3(1, 1.3f, 1) * 2.0f);
    }
};

inline Zote::Application* Zote::CreateApplication()
{
    return new Game();
}