set(SOURCE
    math/euler.h 
    math/matrix.h 
    math/quaternion.h 
    math/vector.h 
    
    scene/scene.h
    scene/scene.cpp
    loaders/load_gltf.h
    loaders/load_gltf.cpp
    cameras/camera.h
    cameras/camera.cpp
)

add_library(toy SHARED ${SOURCE})

add_executable(toy_example main.cpp)

target_link_libraries(toy_example
    PUBLIC
    toy
)