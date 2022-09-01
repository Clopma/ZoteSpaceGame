#pragma once

#include "ZoteApplication.h"
#include "Scripts/SwitchSprites.h"
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
        Entity alex = scene.CreateScriptableEntity(new SwitchSprites("Textures/alex.png",
            "Textures/cpplogo.png"));
        alex.AddComponent<SpriteComponent>();
        alex.GetComponent<TransformComponent>().SetScale(vec3(1, 1.3f, 1) * 2.0f);
    }
};

inline Zote::Application* Zote::CreateApplication()
{
    return new Game();
}