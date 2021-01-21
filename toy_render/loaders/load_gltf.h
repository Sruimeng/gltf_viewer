#pragma once
#include <iostream>
#include "../scene/scene.h"
namespace  toy
{
    void loadGLTF(const std::string& filename, Scene& scene, const std::string& model_type);
} // namespace  toy
