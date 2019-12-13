import unittest

from engine.Primitives import Sphere, Ray, Intersection
from engine.Math.Vector import Vector3d
from engine.Visual import ColorMaterial, Color


class TestSphereConstructor(unittest.TestCase):
    def test_with_default(self):
        print("\nDefault constructor", end = "")
        sphere = Sphere(Vector3d(0,0,0), 10)
        
        self.assertEqual(sphere.center, Vector3d(0,0,0))
        self.assertEqual(sphere.radius, 10)
        self.assertEqual(sphere.material.color, Color(0xaaaaaa))
        
    def test_full_constructor(self):
        print("\nFull constructor", end = "")
        sphere = Sphere(Vector3d(0,0,0), 10, ColorMaterial(Color(0xff0000)))
        
        self.assertEqual(sphere.center, Vector3d(0,0,0))
        self.assertEqual(sphere.radius, 10)
        self.assertEqual(sphere.material.color, Color(0xff0000))
        
class TestSphereProperties(unittest.TestCase):
    def test_properties(self):
        print("\nProperties", end = "")
        sphere = Sphere(Vector3d(0,0,0), 10)
        
        sphere.center = Vector3d(1,2,3)
        self.assertEqual(sphere.center, Vector3d(1,2,3))
        
        sphere.radius = 123
        self.assertEqual(sphere.radius, 123)
        
        sphere.material = ColorMaterial(Color(0xff00ff))
        self.assertEqual(sphere.material.color, Color(0xff00ff))
        
class TestSphereRayIntersection(unittest.TestCase):
    def test_two_intersections(self):
        print("\nRay intersects Sphere", end = "")
        sphere = Sphere(Vector3d(0,0,30), 10)
        ray = Ray(Vector3d(0,0,0),Vector3d(0,0,1))
        intersection = Intersection()
        
        hitted = sphere.hitRay(intersection,ray)
        self.assertEqual(hitted, True)
        self.assertEqual(intersection.distance, 20)
        
if __name__ == "__main__":
    print("\n---------------")
    print("...Test Sphere...")
    unittest.main()