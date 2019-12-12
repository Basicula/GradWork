import unittest

from engine.Math.Vector import Vector3d
from engine.Visual import Color
from engine.Visual.Light import SpotLight

class TestPotLightConstructor(unittest.TestCase):
    def test_default_constructor(self):
        light = SpotLight(Vector3d(0,0,0))
        
        self.assertEqual(light.location, Vector3d(0,0,0))
        self.assertEqual(light.color, Color(0xffffff))
        self.assertEqual(light.intensity, 1)
        
    def test_custom_construtor(self):
        light = SpotLight(Vector3d(1,2,3),Color(0xff00ff),23)
        
        self.assertEqual(light.location, Vector3d(1,2,3))
        self.assertEqual(light.color, Color(0xff00ff))
        self.assertEqual(light.intensity, 23)
        
class TestSpotLightProperties(unittest.TestCase):
    def test_properties(self):
        light = SpotLight(Vector3d(1))
        
        light.location = Vector3d(1,2,3)
        self.assertEqual(light.location, Vector3d(1,2,3))
        
        light.color = Color(0xff00ff)
        self.assertEqual(light.color, Color(0xff00ff))
        
        light.intensity = 23
        self.assertEqual(light.intensity, 23)
        
if __name__ == "__main__":
    unittest.main()