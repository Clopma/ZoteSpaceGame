#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <Maths/Color.h>

using vec3 = glm::vec3;
using vec2 = glm::vec2;
using vec4 = glm::vec4;
using mat4 = glm::mat4;
using quat = glm::quat;

#define VEC3_UP vec3(0, 1, 0)
#define VEC3_RIGHT vec3(1, 0, 0)
#define VEC3_FORWARD vec3(0, 0, 1)

#define VEC2_UP vec2(0, 1)
#define VEC2_RIGHT vec2(1, 0)

inline float RandomFloat(float a, float b) {
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}