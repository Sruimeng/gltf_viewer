
set(sources
    math/euler.h
    math/matirix.h
    math/quaternion.h
    math/vector.h 
)

add_library(toy SHARED
    math/euler.h
    math/matirix.h
    math/quaternion.h
    math/vector.h
    aabb.h
)