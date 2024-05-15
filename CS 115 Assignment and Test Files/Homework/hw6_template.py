'''
Created on 11/01/22
@author:   Yash Yagnik
Pledge:    I pledge my honor that I have abided by the Stevens Honor System

CS115 - Hw 6
'''
# Number of bits for data in the run-length encoding format.
# The assignment refers to this as k.
COMPRESSED_BLOCK_SIZE = 5

# Number of bits for data in the original format.
MAX_RUN_LENGTH = 2 ** COMPRESSED_BLOCK_SIZE - 1

# Do not change the variables above.
# Write your functions here. You may use those variables in your code.

def numTo5Bit(n):
    '''Precondition: integer argument is non-negative.
    Returns the string with the binary representation of non-negative integer n.
    If n is 0, the empty string is returned. '''
    if n==0:
        return ""
    #elif n>=31:
        #return None
    elif n%2 == 1:
        ans1 = numTo5Bit(n//2) + "1"
        return ans1
    else:
        ans2 = numTo5Bit(n//2) + "0"
        return ans2
    
    
    
   
def compress1(s):
    '''A run-length encoding of the input string.'''
    if len(s) == 64:
        return None
    else:
        return "The string provided is not 64 characters"
    
def compression(S):
    return len(compress(S))/ len(S)

