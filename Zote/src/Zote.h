#pragma once

//For use by Zote applications
#include <iostream>

#include "Zote/Application.h"
#include "Zote/EntryPoint.h"
#include "Zote/Event.h"

#include "Zote/Rendering/Window.h"
#include "Zote/Rendering/Shader.h"
#include "Zote/Rendering/Mesh.h"

#include "Zote/ECS/Scene.h"
#include "Zote/ECS/Entity.h"

#include "Zote/Input.h"
#include "Zote/KeyCodes.h"
#include "Zote/MouseButtonCodes.h"

#define LOG(a) std::cout << a << std::endl;