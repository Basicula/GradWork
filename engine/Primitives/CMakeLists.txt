set(
    SOURCES
	
	#src/Sphere.cpp
	src/Ray.cpp
	#src/Plane.cpp
	#src/Torus.cpp
	#src/Cylinder.cpp
)

set(
    HEADERS

	#include/Sphere.h
	include/Ray.h
	#include/Plane.h
	#include/Torus.h
	#include/Cylinder.h
  #
	#include/IObject.h
)

add_library(
	Primitives
    
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(Primitives PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_include_directories(Primitives PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/py")

target_link_libraries(Primitives PRIVATE Math)
target_link_libraries(Primitives PRIVATE Visual)