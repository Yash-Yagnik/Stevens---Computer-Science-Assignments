'''
Created on Sept 5, 2022

@author: Zumrut Akcam

CS115 - Lab 0 Test Script
'''
import unittest
import lab0 as lab0 #change lab0Solution with the name of your solution file

class Test(unittest.TestCase):

    def testSame1(self):
        self.assertTrue(lab0.same("test"))

    def testSame2(self):
        self.assertFalse(lab0.same("Not a correct one"))

    def testSame3(self):
        self.assertTrue(lab0.same("A"))

    def testSame4(self):
        self.assertTrue(lab0.same("Arachnophobia"))

    def testConsecutiveSum1(self):
        self.assertAlmostEqual(lab0.consecutiveSum(3, 5), 4, 10)

    def testConsecutiveSum2(self):
        self.assertAlmostEqual(lab0.consecutiveSum(4, 8), 18, 10)

    def testConsecutiveSum3(self):
        self.assertAlmostEqual(lab0.consecutiveSum(1, 10), 44, 10)

    def testConsecutiveSum4(self):
        self.assertAlmostEqual(lab0.consecutiveSum(3, 101),5044, 10)


if __name__ == "__main__":
    unittest.main()
    
