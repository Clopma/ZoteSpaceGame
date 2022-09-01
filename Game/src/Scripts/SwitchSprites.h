#pragma once
#include "ZoteCommon.h"
using namespace Zote;

class SwitchSprites final : public Script
{
public:
    SwitchSprites(const cstr a, const cstr b) { pathA = a; pathB = b; }

private:
    cstr pathA = "";
    cstr pathB = "";
    bool usePathA = false;
    bool wasPressed = false;

    void Update(float deltaTime) override
    {
        PerformIfSpacePressed([this]()
        {
            usePathA = !usePathA;
            const cstr path = usePathA ? pathA : pathB;
            GetEntity().GetComponent<SpriteComponent>().AddTexture(path);
        });
    }

    void PerformIfSpacePressed(const std::function<void()>& func)
    {
        if (Input::GetKeyPressed(ZOTE_KEY_SPACE) && !wasPressed)
        {
            wasPressed = true;
            func();
        }
        
        else if (Input::GetKeyReleased(ZOTE_KEY_SPACE) && wasPressed)
            wasPressed = false;
    }
};