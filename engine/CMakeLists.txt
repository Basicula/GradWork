find_package(GLUT QUIET)

if(NOT GLUT_FOUND)
	message("Installing GLUT...")
	
	set(FreeglutPath ../ThirdParties/freeglut_mvc)
	
	set(GLUT_INCLUDE_DIRS ${FreeglutPath}/include)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(GLUT_LIBRARY_DIRS ${FreeglutPath}/lib/x64)
		file(	COPY ${FreeglutPath}/bin/x64/freeglut.dll
			DESTINATION ${CMAKE_BINARY_DIR}
		)
	else()
		set(GLUT_LIBRARY_DIRS ${FreeglutPath}/lib)
		file(	COPY ${FreeglutPath}/bin/freeglut.dll
			DESTINATION ${CMAKE_BINARY_DIR}
		)
	endif()
endif()

link_directories(${GLUT_LIBRARY_DIRS})
include_directories(${GLUT_INCLUDE_DIRS})

add_subdirectory(Math)
add_subdirectory(Common)
add_subdirectory(Visual)
add_subdirectory(Primitives)
add_subdirectory(Fluid)
add_subdirectory(Scene)
add_subdirectory(GLUTWindow)

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
set_target_properties(Common PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(Fluid PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(Visual PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(Scene PROPERTIES POSITION_INDEPENDENT_CODE TRUE)