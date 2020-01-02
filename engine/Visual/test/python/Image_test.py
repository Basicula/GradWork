import unittest
import time

from engine.Visual import Image, Color

class TestImageConstructor(unittest.TestCase):
    def test_simple_constructor(self):
        print("\nDefault constructor", end = "")
        width = 10
        height = 20
        image = Image(width, height)
        
        self.assertEqual(image.width, width)
        self.assertEqual(image.height, height)
        
        default_color = Color(0)
        for x in range(width):
            for y in range(height):
                self.assertEqual(image.getPixel(x,y), default_color)
    
    def test_full_constructor(self):
        print("\nCustom constructor", end = "")
        width = 12
        height = 32
        image = Image(width, height, Color(0xffffff))
        
        self.assertEqual(image.width, width)
        self.assertEqual(image.height, height)
        
        custom_color = Color(0xffffff)
        for x in range(width):
            for y in range(height):
                self.assertEqual(image.getPixel(x,y), custom_color)
                
class TestImageProperties(unittest.TestCase):
    def test_properties(self):
        print("\nProperties", end = "")
        width = 123
        height = 321
        image = Image(width, height)
        
        with self.assertRaises(AttributeError):
            image.width = 123
            
        with self.assertRaises(AttributeError):
            image.height = 123
            
        self.assertEqual(image.width, width)
        self.assertEqual(image.height, height)
            
        with self.assertRaises(AttributeError):
            image.data = 123
            
        #with self.assertRaises(AttributeError):
        #    image.data[0][0] = Color(0)
            
        self.assertEqual(image.data[0][0], Color(0))
        
        with self.assertRaises(AttributeError):
            image.rawData = 123
            
        self.assertEqual(image.rawData[0], 0)
        
class TestImageFunctionality(unittest.TestCase):
    def test_pixel_manipulation(self):
        print("\nPixel manipulation", end = "")
        width = 22
        height = 33
        image = Image(width, height, Color(0xff0000))
        
        expected_color = Color(0x00ff00)
        image.setPixel(11,11,expected_color)
        self.assertEqual(image.getPixel(11,11), expected_color)
        
        self.assertEqual(image.getPixel(123,123), Color(0))
        
        image.setPixel(123,1312,Color(0))


if __name__ == "__main__":
    print("\n--------------")
    print("...Test Image...")
    unittest.main()