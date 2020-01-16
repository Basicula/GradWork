#include <iostream>

#include <Fluid.h>
#include <BoundingBox.h>
#include <Vector.h>
#include <KDTree.h>
#include <Sphere.h>

int main()
  {
  KDTree tree;
  Fluid fluid(BoundingBox(Vector3d(-5), Vector3d(5)));
  //tree.AddObject(std::shared_ptr<IObject>(&fluid));
  tree.AddObject(std::make_shared<Sphere>(Vector3d(0),10));
  tree.AddObject(std::make_shared<Sphere>(Vector3d(10),10));
  tree.AddObject(std::make_shared<Sphere>(Vector3d(20),10));
  tree.AddObject(std::make_shared<Sphere>(Vector3d(30),10));
  tree.AddObject(std::make_shared<Sphere>(Vector3d(40),10));
  tree.AddObject(std::make_shared<Sphere>(Vector3d(50),10));
  tree.AddObject(std::make_shared<Sphere>(Vector3d(60),10));
  tree.AddObject(std::make_shared<Sphere>(Vector3d(70),10));
  for (int i = 0; i < 100; ++i)
    {
    fluid.ApplyPhysics();
    std::cout<<fluid.GetNumParticles()<<std::endl;
    }
  return 0;
  }