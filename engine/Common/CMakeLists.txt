set(
  SOURCES
  
  src/BoundingBox.cpp
)

set(
  HEADERS
 
  include/BoundingBox.h
)

add_library(
  Common
  
  ${SOURCES}
  ${HEADERS}
)

target_include_directories(Common PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_include_directories(Common PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/py")

target_link_libraries(Common PRIVATE Math)