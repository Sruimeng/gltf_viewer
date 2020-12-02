set(SOURCE
    cameras/camera.h
    cameras/camera.cpp
    math/euler.h 
    math/matrix.h 
    math/quaternion.h 
    math/vector.h 
)

add_library(toy SHARED ${SOURCE})

add_executable(toy_example main.cpp)

target_link_libraries(toy_example
    PUBLIC
    toy
)