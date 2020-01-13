add_subdirectory(Math)
add_subdirectory(Common)
add_subdirectory(Visual)
add_subdirectory(Primitives)
add_subdirectory(Fluid)
add_subdirectory(Scene)

pybind11_add_module(engine engine_module.cpp)
target_link_libraries(
    engine
    
    PRIVATE
    
    Math
    Common
    Visual
    Primitives
    Fluid
    Scene
    
    pybind11)
    
set_target_properties(Primitives PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(Fluid PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(Visual PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(Scene PROPERTIES POSITION_INDEPENDENT_CODE TRUE)