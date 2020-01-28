#include <iostream>
#include <chrono>

#include <Fluid.h>
#include <BoundingBox.h>
#include <Vector.h>
#include <KDTree.h>
#include <Sphere.h>
#include <Scene.h>
#include <Image.h>

void test_fluid()
  {
  auto fluid = std::make_shared<Fluid>(BoundingBox(Vector3d(-5), Vector3d(5)));
  auto start = std::chrono::system_clock::now();
  for (int i = 0; i < 1024; ++i)
    {
    fluid->ApplyPhysics();
    }
  auto end = std::chrono::system_clock::now();
  std::cout<<std::chrono::duration_cast<std::chrono::milliseconds>
    (end - start).count()<<std::endl;
  }

void test_tree()
  {
  KDTree tree;
  tree.AddObject(std::make_shared<Sphere>(Vector3d(0), 10));
  tree.AddObject(std::make_shared<Sphere>(Vector3d(10), 10));
  tree.AddObject(std::make_shared<Sphere>(Vector3d(20), 10));
  tree.AddObject(std::make_shared<Sphere>(Vector3d(30), 10));
  tree.AddObject(std::make_shared<Sphere>(Vector3d(40), 10));
  tree.AddObject(std::make_shared<Sphere>(Vector3d(50), 10));
  tree.AddObject(std::make_shared<Sphere>(Vector3d(60), 10));
  tree.AddObject(std::make_shared<Sphere>(Vector3d(70), 10));
  }

void test_scene()
  {
  Scene scene;
  auto fluid = std::make_shared<Fluid>(BoundingBox(Vector3d(-5), Vector3d(5)));
  scene.AddCamera(
    Camera(
      Vector3d(0),
      Vector3d(0,0,1),
      Vector3d(0,1,0),
      75,
      1024/768,
      2));
  for (int i = 0; i < 16; ++i)
    {
    auto x = 10.0 * std::rand() / static_cast<double>(RAND_MAX) 
      - 5.0 * std::rand() / static_cast<double>(RAND_MAX);
    auto y = 10.0 * std::rand() / static_cast<double>(RAND_MAX) 
      - 5.0 * std::rand() / static_cast<double>(RAND_MAX);
    auto z = 10.0 * std::rand() / static_cast<double>(RAND_MAX) 
      - 5.0 * std::rand() / static_cast<double>(RAND_MAX);
    auto r = 2.0 * std::rand() / static_cast<double>(RAND_MAX);
    scene.AddObject(std::make_shared<Sphere>(Vector3d(x,y,z),r));
    }
  Image image(1024, 768);
  const int frame_cnt = 16;
  auto start = std::chrono::system_clock::now();
  auto temp = start;
  for (int i = 0; i < frame_cnt; ++i)
    {
    scene.RenderFrame(image);
    //fluid->ApplyPhysics();
    }
  auto end = std::chrono::system_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>
    (end - start).count();
  std::cout << "Elapsed : " <<elapsed<< 
    ", FPS : " << 1000.0 * frame_cnt / elapsed<< std::endl;
  }

int main()
  {
  test_fluid();
  test_tree();
  test_scene();
  return 0;
  }