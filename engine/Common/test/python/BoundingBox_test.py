import unittest

from engine.Math.Vector import Vector3d
from engine.Common import BoundingBox as bbox


class TestBoundingBoxConstructors(unittest.TestCase):
    def test_default_constructor(self):
        print("\nDefault constructor", end = "")
        bb = bbox()
        
        self.assertFalse(bb.isValid())

class TestBoundingBoxProperties(unittest.TestCase):
    def test_properties(self):
        print("\nProperties", end = "")
        bb = bbox()
        
        self.assertEqual(bb.min, Vector3d(2147483647))
        self.assertEqual(bb.max, Vector3d(-2147483648))

class TestBoundingBoxFunctionality(unittest.TestCase):
    def test_adding_point(self):
        print("\nAdd point", end = "")
        bb = bbox()
        
        bb.addPoint(Vector3d(1))
        self.assertFalse(bb.isValid())
        
        bb.addPoint(Vector3d(0))
        self.assertTrue(bb.isValid())
        
        bb.addPoint(Vector3d(0.5))
        
        self.assertEqual(bb.min, Vector3d(0))
        self.assertEqual(bb.max, Vector3d(1))

if __name__ == "__main__":
    print("\n----------------------")
    print("\n...Test BoundingBox...")
    unittest.main()