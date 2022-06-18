#pragma once

#ifdef UTILS_MEMORY // #define UTILS_MEMORY
#include <memory>
template<typename T>
using Ref = std::shared_ptr<T>;
#define MakeRef std::make_shared
#endif

#ifdef UTILS_MATHS // #define UTILS_MATHS
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
#endif

#ifdef UTILS_LOG // #define UTILS_LOG
#include <iostream>
#define LOG(x) std::cout << x << std::endl
#endif 

#ifdef UTILS_CSTRING // #define UTILS_LOG
using cstr = const char*;
#endif

#ifdef UTILS_STRING // #define UTILS_STRING
#include <string>
#include <fstream>
using str = std::string;
#endif

#ifdef UTILS_UINT // #define UTILS_UINT
using uint = unsigned int;
#endif