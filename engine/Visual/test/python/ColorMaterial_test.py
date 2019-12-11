import unittest

from engine.Visual import ColorMaterial, Color
from engine.Math.Vector import Vector3d

class TestColorMaterialConstructors(unittest.TestCase):
    def test_simple_constructor(self):
        cm = ColorMaterial(Color(0x00ff00))
        
        self.assertEqual(cm.color, Color(0x00ff00))
        self.assertEqual(cm.ambient, Vector3d(1,1,1))
        self.assertEqual(cm.diffuse, Vector3d(1,1,1))
        self.assertEqual(cm.specular, Vector3d(1,1,1))
        self.assertEqual(cm.shinines, 1)
        self.assertEqual(cm.reflection, 0)
        self.assertEqual(cm.refraction, 0)
        
    def test_full_constructor(self):
        ruby_material = ColorMaterial(Color(255, 0, 0)
                                    , Vector3d(0.1745, 0.01175, 0.01175)
                                    , Vector3d(0.61424, 0.04136, 0.04136)
                                    , Vector3d(0.727811, 0.626959, 0.626959)
                                    , 76.8)
        
        self.assertEqual(ruby_material.color, Color(0xff0000))
        self.assertEqual(ruby_material.ambient, Vector3d(0.1745, 0.01175, 0.01175))
        self.assertEqual(ruby_material.diffuse, Vector3d(0.61424, 0.04136, 0.04136))
        self.assertEqual(ruby_material.specular, Vector3d(0.727811, 0.626959, 0.626959))
        self.assertEqual(ruby_material.shinines, 76.8)
        self.assertEqual(ruby_material.reflection, 0)
        self.assertEqual(ruby_material.refraction, 0)



if __name__ == "__main__":
    unittest.main()