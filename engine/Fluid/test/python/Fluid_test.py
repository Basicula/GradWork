import unittest
import json

from engine.Fluid import Fluid
from engine.Common import BoundingBox
from engine.Math.Vector import Vector3d

class TestFluidConstructors(unittest.TestCase):
    def test_bbox_constructor(self):
        print("\nBoundingBox constructor", end = "")
        fluid = Fluid(BoundingBox(Vector3d(-5), Vector3d(5)))
        
        self.assertEqual(fluid.boundingBox.min, Vector3d(-5))
        self.assertEqual(fluid.boundingBox.max, Vector3d(5))
        
class TestFluidFunctionality(unittest.TestCase):
    def test_serialization(self):
        print("\nSerialization", end = "")
        fluid = Fluid(BoundingBox(Vector3d(-5), Vector3d(5)))
        
        dict = json.loads(repr(fluid))
        inner = dict["Fluid"]
        
        self.assertEqual(inner["Box"], json.loads(repr(BoundingBox(Vector3d(-5), Vector3d(5)))))
        
    def test_deserialization(self):
        print("\nDeserialization", end = "")
        fluid = Fluid(BoundingBox(Vector3d(-5), Vector3d(5)))
        
        dict = json.loads(repr(fluid))
        fluid_re = Fluid.fromDict(dict)
        
        self.assertEqual(fluid_re.boundingBox.min, fluid.boundingBox.min)
        self.assertEqual(fluid_re.boundingBox.max, fluid.boundingBox.max)

if __name__ == "__main__":
    print("\n--------------")
    print("...Test Fluid...")
    unittest.main()