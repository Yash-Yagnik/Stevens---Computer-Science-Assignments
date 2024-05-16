############################################################
# Name: Yash Yagnik
# Pledge: I pledge my honor that I have abided by the Stevens Honor System.
# CS115 Lab 1
#  
############################################################

from math import factorial
from functools import reduce

def add(x, y):
    # Function adds two numbers together
    return x+y
    
def inverse(x):
    # Function divides 1 over the user input 
    return 1/x

def e(n):
    # Function replicates the taylor polynomial for e and gives the total number after adding up the fractions before the users input
   return 1 + reduce(add, map(inverse, map(factorial, range(1, n+1))))


