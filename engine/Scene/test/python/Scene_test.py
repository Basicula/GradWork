import unittest

from engine import Scene
from engine.Math.Vector import Vector3d
from engine.Visual import *
from engine.Primitives import *
from engine.Visual.Light import *
from engine.Visual.Material import *

class TestSceneConstructor(unittest.TestCase):
    def test_constructor(self):
        print("\nConstructor without parameters ", end = "")
        scene = Scene()
        
        self.assertEqual(scene.name, "unnamed")
        
    def test_custom_constructor(self):
        print("\nConstructor with parameters ", end = "")
        scene = Scene("test")
        
        self.assertEqual(scene.name, "test")
        
class TestSceneExample(unittest.TestCase):
    def test_simple_example(self):
        print("\nSimple example ", end = "")
        scene = Scene("example")
        
        self.assertEqual(scene.name, "example")
        
        sphere = Sphere(Vector3d(0,0,0), 10)
        light = SpotLight(Vector3d(10,10,10))
        camera = Camera(Vector3d(0,0,-10),Vector3d(0,0,0),Vector3d(0,1,0),60,4/3,1)
        
        scene.addObject(sphere)
        self.assertEqual(scene.objCnt,1)
        scene.clearObjects()
        self.assertEqual(scene.objCnt,0)
        
        scene.addLight(light)
        self.assertEqual(scene.lightCnt,1)
        self.assertTrue(light.state)
        scene.setOnOffLight(0,False)
        self.assertFalse(light.state)
        scene.clearLights()
        self.assertEqual(scene.lightCnt,0)
        
        scene.addCamera(camera)
        self.assertEqual(scene.camCnt,1)
        scene.clearCameras()
        self.assertEqual(scene.camCnt,0)
    
if __name__ == "__main__":
    print("\n--------------")
    print("...Test Scene...")
    unittest.main()