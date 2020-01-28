set(
    SOURCES
    
    src/BoundingBox.cpp
    src/Intersection.cpp
    src/Ray.cpp
    
    src/KDTree.cpp
    src/KDNode.cpp
    
    src/BFPointSearcher.cpp
    
    src/Simulation.cpp
    
    src/ParallelUtils.cpp
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
    
    include/ParallelUtils.h
    
    include/IObject.h
    
    include/DefinesAndConstants.h
)

set(
    TESTS
    
    test/c++/test_main.cpp
)

# Main library
add_library(
    Common
    
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(Common PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_include_directories(Common PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/py")

target_link_libraries(Common PRIVATE Math)

# Test library
add_executable(Common.Test ${TESTS})
target_link_libraries(Common.Test PRIVATE Common)