'''
Created on _11/1/22_______________
@author:   _Yash Yagnik and Vraj Patel____________
Pledge:    _I pledge my honor that I have abided by the Stevens Honor System___

CS115 - Hw 6
'''

# Number of bits for data in the run-length encoding format.
# The assignment refers to this as k.
COMPRESSED_BLOCK_SIZE = 5

 

# Number of bits for data in the original format.

MAX_RUN_LENGTH = 2 ** COMPRESSED_BLOCK_SIZE - 1

 

# Do not change the variables above.

# Write your functions here. You may use those variables in your code.

 

def numToBinary(n, x = ''):
    '''returns binary version of decimal number n in bits equivalent to COMPRESSED_BLOCK_SIZE'''
    if n >= MAX_RUN_LENGTH:
        return '1' * COMPRESSED_BLOCK_SIZE
    else:
        if n == 0:
            if len(x) < COMPRESSED_BLOCK_SIZE:
                return '0'*(COMPRESSED_BLOCK_SIZE - len(x)) + x
            else:
                return x
        else:
            if n % 2 == 0:
                return numToBinary(n//2, '0' + x)
            else:
                return numToBinary(n//2, '1' + x)
 

def binaryToNum(s):
    '''returns decimal number corresponding to binary s'''
    if s == '' or s == '0':
        return 0
    else:
        if s[-1] == '0':
            return int(binaryToNum(s[:-1])) * 2
        else:
            return int(binaryToNum(s[:-1])) * 2 + 1
 

def count1(s):
    """counts the number of consecutive ones at the beginning of the string"""
    if s == '' or s[0] != "1":
        return 0
    else:
        return 1 + count1(s[1:])
 
def count2(s):
    """counts the number of consecutive zeroes at the beginning of the string"""
    if s == '' or s[0] != '0':
        return 0
    else:
        return 1 + count2(s[1:])
   

def preCompress(s):
    '''Outputs a run-length encoding of the input string'''
    x = count2(s)
    if x > 31:
        x = 31
    y = count1(s[x:])
    if y > 31:
        y = 31
    z = numToBinary(x)
    a = numToBinary(y)
    if s == '':
        return ''
    else:
        return z + a + preCompress(s[(x + y):])
 

def compress(s):
    '''Sends the input into the preCompress function that does the real calculations for compressing the input'''
    # The largest amount of bits that this function can output to encode a 64 bit input is 325 bits 
    x = preCompress(s)
    if x[-5:] == '00000':
        return x[:-5]
    else:
        return x
   

def uncompress(s):
    '''inverts or undoes the compressing in your compress function'''
    if s == '':
        return ''
    x = binaryToNum(s[0:5])
    y = binaryToNum(s[5:10])
    return '0' * x + '1' * y + uncompress(s[10:])

 

def compression(s):
    '''returns the ratio of the compressed binary string to the original'''
    return len(compress(s)) / len(s)

    '''
>>> compression('10'*32)
5.078125
>>> compression('01'*32)
5.0
>>> compression('0100'*16)
2.578125
>>> compression('0'*64)
0.390625
>>> compression('1'*64)
0.46875
'''
# Above are the tests that were run, revealing the pattern that most of the compress outputs are longer than their inputs
# This will be key in proving the Laicompress function to be impossible in the next comment
    

 # Laicompress may work for some cases however it will not work for cases such as "10" * 32, "01" * 32, and etc.
 # You can see these results in the comments under the compression function, if the output is a whole number
 # Then that means that the output (the compressing of a 64 bit input) is longer than the input


