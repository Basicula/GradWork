#include <iostream>

#include <Fluid.h>
#include <BoundingBox.h>
#include <Vector.h>

int main()
  {
  Fluid fluid(BoundingBox(Vector3d(-5), Vector3d(5)));
  for (int i = 0; i < 100; ++i)
    {
    fluid.ApplyPhysics();
    std::cout<<fluid.GetNumParticles()<<std::endl;
    }
  return 0;
  }