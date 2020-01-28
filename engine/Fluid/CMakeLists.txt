set(
  SOURCES
  
  src/Fluid.cpp
  
  src/StandartParticle.cpp
  src/Particle.cpp
  
  src/ParticleSystem.cpp
  src/SPHSystem.cpp
  
  src/SPHSimulation.cpp
)

set(
  HEADERS
  
  include/Fluid.h
  
  include/StandartParticle.h
  include/Particle.h
  
  include/ParticleSystem.h
  include/SPHSystem.h
  
  include/SPHSimulation.h
  
  include/FluidConstants.h
)

add_library(
  Fluid
  
  ${SOURCES}
  ${HEADERS}
)

target_include_directories(Fluid PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_include_directories(Fluid PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/py")

target_link_libraries(Fluid PRIVATE Math)
target_link_libraries(Fluid PRIVATE Common)
target_link_libraries(Fluid PRIVATE Visual)
target_link_libraries(Fluid PRIVATE Primitives)

add_executable(Fluidexe src/main.cpp)

target_include_directories(Fluidexe PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_include_directories(Fluidexe PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/py")

target_link_libraries(Fluidexe PRIVATE Math)
target_link_libraries(Fluidexe PRIVATE Common)
target_link_libraries(Fluidexe PRIVATE Visual)
target_link_libraries(Fluidexe PRIVATE Primitives)
target_link_libraries(Fluidexe PRIVATE Fluid)
target_link_libraries(Fluidexe PRIVATE Scene)