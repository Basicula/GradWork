import unittest
import math

from engine.Math.Vector import Vector3d
from engine.Primitives import Ray

class TestRayConstuctors(unittest.TestCase):
    def test_constructor(self):
        ray = Ray(Vector3d(0,0,0), Vector3d(0,0,1))
        
        self.assertEqual(ray.origin, Vector3d(0,0,0))
        self.assertEqual(ray.direction, Vector3d(0,0,1))
        
    def test_normalization_in_constructor(self):
        ray = Ray(Vector3d(0,0,0), Vector3d(0,0,111))
        
        self.assertEqual(ray.origin, Vector3d(0,0,0))
        self.assertEqual(ray.direction, Vector3d(0,0,1))
        
        ray = Ray(Vector3d(0,0,0), Vector3d(1,1,1))
        
        self.assertEqual(ray.origin, Vector3d(0,0,0))
        x = 1 / math.sqrt(3)
        self.assertEqual(ray.direction, Vector3d(x,x,x))
    
if __name__ == "__main__":
    unittest.main()