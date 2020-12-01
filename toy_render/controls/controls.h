#pragma once

#include <iostream>

#include "track_ball.h"
#include "../supports/GLFW/include/GLFW/glfw3.h"
namespace toy {
    static void scrollCallback(GLFWwindow* window, double xscroll, double yscroll)
    {
        std::cerr << "yscroll: " << yscroll << ",xscroll: " << xscroll << "\n";
        // if (trackball.wheelEvent((int)yscroll))
        //     camera_changed = true;
    }
}