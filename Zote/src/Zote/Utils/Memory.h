#pragma once

#include <memory>
template<typename T>
using Ref = std::shared_ptr<T>;
#define MakeRef std::make_shared