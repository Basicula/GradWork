set(
  SOURCES
  
  src/BoundingBox.cpp
  src/Intersection.cpp
)

set(
  HEADERS
 
  include/BoundingBox.h
  include/Intersection.h
  
  include/IObject.h
  
  include/DefinesAndConstants.h
)

add_library(
  Common
  
  ${SOURCES}
  ${HEADERS}
)

target_include_directories(Common PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_include_directories(Common PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/py")

target_link_libraries(Common PRIVATE Math)