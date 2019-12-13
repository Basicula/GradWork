set(
  SOURCES
    
  src/SpotLight.cpp
	src/Color.cpp
	src/ColorMaterial.cpp
)

set(
  HEADERS
    
  include/SpotLight.h
	include/Color.h
	include/ColorMaterial.h
)

add_library(
	Visual
	
  ${SOURCES}
  ${HEADERS}
)

target_include_directories(Visual PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_include_directories(Visual PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/py")

target_link_libraries(Visual PRIVATE Math)