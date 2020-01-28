set(
    SOURCES
    
    src/BoundingBox.cpp
    src/Intersection.cpp
    src/Ray.cpp
    
    src/KDTree.cpp
    src/KDNode.cpp
    
    src/BFPointSearcher.cpp
    
    src/Simulation.cpp
)

set(
    HEADERS
    
    include/BoundingBox.h
    include/Intersection.h
    include/Ray.h
    
    include/KDTree.h
    include/KDNode.h

    include/PointNeighborSearcher.h
    include/BFPointSearcher.h
    
    include/Simulation.h
    
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