import time
import unittest

from engine import Scene
from engine.Math.Vector import Vector3d
from engine.Visual import *
from engine.Primitives import *
from engine.Visual.Light import *
from engine.Visual.Material import *


class TestScenePerformance(unittest.TestCase):
    def test_frames_per_second(self):
        scene = Scene("example")
    
        ruby_material = ColorMaterial(Color(255, 0, 0)
                                , Vector3d(0.1745, 0.01175, 0.01175)
                                , Vector3d(0.61424, 0.04136, 0.04136)
                                , Vector3d(0.727811, 0.626959, 0.626959)
                                , 76.8)
        
        scene.addObject(Sphere(Vector3d(0,0,0), 3, ruby_material))
        scene.addObject(Sphere(Vector3d(4,4,-4), 1, ruby_material))
        
        scene.addLight(SpotLight(Vector3d(10,10,-10)))
        scene.addLight(SpotLight(Vector3d(0,10,-5)))
        
        scene.addCamera(Camera(Vector3d(0,0,-15),Vector3d(0,0,0),Vector3d(0,1,0),60,4/3,1))
        
        image = Image(scene.frameWidth, scene.frameHeight)
        
        frames_cnt = 30
        start = time.time()
        for i in range(frames_cnt):
            scene.getFrame(image)
        elapsed = time.time() - start
        print("\nFrames per second - Time = {}s, Frames = {}, FPS = {}".format(round(elapsed,4),frames_cnt,round(frames_cnt/elapsed,4)), end = "")
        
if __name__ == "__main__":
    print("\n-------------------------")
    print("...Test Scene Performane...")
    unittest.main()