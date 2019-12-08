add_subdirectory(Math)
add_subdirectory(Visual)
add_subdirectory(Primitives)

pybind11_add_module(engine engine_module.cpp)
target_link_libraries(
    engine
    
    PRIVATE
    
    Math
    Visual
    Primitives
    
    pybind11)