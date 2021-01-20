#include <iostream>

#include "scene/scene.h"
int main(int argc, char const *argv[])
{
    try
    {
        toy::Scene scene;
        toy::loadScene("jixiegui.glb",&scene);
        std::cerr << "this is a  toy render example"
                  << "\n";
        std::cerr << "this is a  toy render example"
                  << "\n";
        /* code */
        return 0;
        /* code */
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
