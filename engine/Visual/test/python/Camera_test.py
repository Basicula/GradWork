import unittest

from engine.Visual import Camera
from engine.Math.Vector import Vector3d

class TestCameraConstructor(unittest.TestCase):
    def test_constructor(self):
        print("\nConstructor", end = "")
        camera = Camera(Vector3d(0,0,0), Vector3d(0,0,1), Vector3d(0,1,0), 60, 4/3, 1)
        
        self.assertEqual(camera.location, Vector3d(0,0,0))
        
class TestCameraFunctionality(unittest.TestCase):
    def test_get_direction(self):
        print("\nGet direction", end = "")
        camera = Camera(Vector3d(0,0,0), Vector3d(0,0,1), Vector3d(0,1,0), 60, 4/3, 1)
        
        width, height = 800, 600
        u, v = 400, 300
        actual = camera.direction(u/width,v/height)
        expected = Vector3d(0,0,1)
        self.assertEqual(actual, expected)
        
        temp = camera.direction(0,v/height)
        self.assertTrue(temp.y == 0)
        self.assertTrue(temp.x != 0)
        
        temp = camera.direction(u/width,0)
        self.assertTrue(temp.y != 0)
        self.assertTrue(temp.x == 0)

if __name__ == "__main__":
    print("\n---------------")
    print("...Test Camera...")
    unittest.main()