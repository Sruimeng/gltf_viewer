
set(SOURCE
    cameras/camera.h
    cameras/camera.cpp
    math/euler.h 
    math/matrix.h 
    math/quaternion.h 
    math/vector.h 
)

add_library(toy SHARED ${SOURCE})