'''
Functions
CS 115 9/9/22

'''
import math
def quad(x):
    return dbl(dbl(x))

# print (quad(4))

def dbl(x):
    return (2 *x)

# print (dbl(4))

def MyFunc(x, y):
    return x + 42 * y

# print MyFunc(2, 4)
        
def area(r):
    return math.pi * (r**2)

from functools import reduce
# print area(5)


#Lists

fruits = ['Apple', 'Pear', 'Cherry']

# fruits[0:3]

L = [1, 2, 3, 4]



# Map  Function

def dbl(x):
     return 2 * x

def add(x, y):
	return x+y

#print(reduce (add, [1, 2, 3, 4]))
#print (list(map(dbl, L)))



# If Statements

def test(x):
    if ((x % 2) == 0):
        return ("Number is Even!")

    else:
        return ("Number is Odd!")

# print(test(5))


def span(l):
    mx = reduce(max, l)
    mn = reduce(min, l)
    return mx - mn

'''print(span([3, 1, 42, 7]))
print(span([42, 42, 42, 42]))'''

# Map and Reduce
def gauss(n):
    return reduce(add, range(n+1))

#print(gauss(5))

def sqrd(x, y):
     return x ** y

def sumOfSquares(n):
    return reduce(add, map(sqrd, range(n+1) ))

#print (sumOfSquares(5))

#If, elif statments
def special(x):
    if x>=42:
        print ("Hi")
        return "Great Number"
    elif True:
        print ("Hoho")
        return "Another Great Number"
    print ("Hey")
    return "Not So Great Number"

#print(special(43))

# List and Filter
def even(x):
    return x%2 == 0

#print (list(filter(even, [1, 2, 3, 4])))


# Recursion using factorial function

def factorial(n):
    if n==0:
        return 1
    else:
        return n*factorial(n-1)

def tower(x):
    if (x==0):
        return 1
    else:
        return (2 ** tower(x-1))

# Also can be written as
def tower1(x):
    if (x==1):
        return 2
    else:
        return (2 ** tower(x-1))
    
#Lambda
evn = lambda x: x%2 == 0

def prime(n):
    L = range(2, n)
    divisors = filter(lambda x: x%L[0] !=0, L)
    return list(divisors)

# Knapsack Problem, Use it or Lose it
def knapsack(capacity, items):
    if items == [] or capacity <= 0:
        return 0
    elif items[0][0] > capacity:
        return kanpsack(capacity[1:])
    else:
        useit = items[0][1] + knapsack(capacity - items[0][0], items[1:])
        loseit = kanpsack(capacity[1:])
        return max(useit, loseit)

# Edit Distance Example

def distance(w1, w2):
    if w1 == "":
        return len(w2)
    elif w2 == "":
        return len(w1)
    elif w1[0] == w2[0]:
        return distance(w1[1:], w2[1:])
    else:
        delete = 1 + distance(w1[1:], w2)
        sub = 1 + distance(w1[1:], w2[1:])
        insert = 1 + distance(w1, w2[1:])
        return min (delete, sub, insert)
        
# Longest Common Subset Example

def LCS(S1, S2):
    if S1 == "" or S2 == "":
        return 0
    elif S1[0] == S2[0]:
            return 1 + LCS(S1[1:], S2[1:])
    else:
        diff1 = LCS(S1[1:], S2)
        diff2 = LCS(S1, S2[1:])
        return max(diff1, diff2)

# Tail Recursion

def reverseString(s1, s2 = ""):
    if s1 == "":
        return s2
    else:
        return reverseString(s1[:-1], s2 + s1[-1])

def tailFactorial(n, a = 1):
    if n == 0:
        return a
    else:
        return tailFactorial(n-1, a * n)


# Palindrome Example

def isPalindrome(word):
    if  word == "":
        return True
    if word[0].lower() != word[-1].lower():
        return False
    else:
        return isPalindrome(word[1:-1])

memo = {1:1, 2:2, 3:4}

def KFP_fast(n):
    if n in memo:
        return memo[n]
    ans1 = KFP_fast(n-1)
    memo[n-1] = ans1
    ans2 = KFP_fast(n-2)
    memo[n-2] = ans2
    ans3 = KFP_fast(n-3)
    memo[n-3] = ans3
    return ans1 + ans2 + ans3
    

import time
def MesureTime(f, n):
    start = time.time()
    f(n)
    return time.time() - start

#print("KFP slow takes: " +  + "secs")
#print("KFP fast  takes: " +  + "secs")

# Memoization aka Faster Version
memo = {}
def fastLCS(s1, s2):
    if (s1, s2) in memo:
        return memo[(s1, s2)]
    if s1 == "" or s2 == "":
        memo[(s1, s2)] = 0
        return 0
    elif s1[0] == s2[0]:
        same = 1 + fastLCS(s1[1:], s2[1:])
        memo[(s1, s2)] = same
        return same
    else:
        chops1 = fastLCS(s1[1:], s2)
        chops2 = fastLCS(s1, s2[1:])
        answer = max(chops1, chops2)
        memo[(s1, s2)] = answer
        return answer
        

    

