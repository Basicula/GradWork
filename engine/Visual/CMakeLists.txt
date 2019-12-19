set(
  SOURCES

  src/Camera.cpp
  src/Color.cpp
  src/ColorMaterial.cpp
  src/Image.cpp
  src/SpotLight.cpp
)

set(
  HEADERS
  
  include/ILight.h
  include/IMaterial.h

  include/Camera.h
  include/Color.h
  include/ColorMaterial.h
  include/Image.h
  include/SpotLight.h
)

add_library(
  Visual

  ${SOURCES}
  ${HEADERS}
)

target_include_directories(Visual PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_include_directories(Visual PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/py")

target_link_libraries(Visual PRIVATE Math)