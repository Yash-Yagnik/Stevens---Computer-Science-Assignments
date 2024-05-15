'''
Created on 10/01/20222
@author:   Yash Yagnik and Vraj Patel
Pledge:    I pledge my honor that I have abided by the Stevens Honor System
CS115 - Hw 2
'''
import sys
from functools import reduce

# Be sure to submit hw2.py.  Remove the '_template' from the file name.

# Allows up to 10000 recursive calls.
# The maximum permitted limit varies from system to system.
sys.setrecursionlimit(10000)

# Leave the following lists in place.
scrabbleScores = \
   [ ['a', 1], ['b', 3], ['c', 3], ['d', 2], ['e', 1], ['f', 4], ['g', 2],
     ['h', 4], ['i', 1], ['j', 8], ['k', 5], ['l', 1], ['m', 3], ['n', 1],
     ['o', 1], ['p', 3], ['q', 10], ['r', 1], ['s', 1], ['t', 1], ['u', 1],
     ['v', 4], ['w', 4], ['x', 8], ['y', 4], ['z', 10] ]

Dictionary = ['a', 'am', 'at', 'apple', 'bat', 'bar', 'babble', 'can', 'foo',
              'spam', 'spammy', 'zzyzva']

# Implement your functions here.
def letterScore(letter, scorelist):
    #This will output the score attached to using a certain letter in scrabble word
    if scorelist == []:
        return 0
    elif scorelist[0][0] == letter:
        return scorelist[0][1]
    else:
        return letterScore(letter, scorelist[1:])

def wordScore(S, scorelist):
    #This outputs the addition of the points of all the letters in the word provided by the user
    if S == "":
        return 0
    else:
        return letterScore(S[0], scorelist) + wordScore(S[1:], scorelist)
def ind(e, L):
    #Returns the index at which the desired value/word is in a list. Both given by the user
    if L == []:
        return 0
    elif L == "":
        return 0
    elif L[0] == e:
        return 0
    else:
        return 1 + ind(e, L[1:])
    
def rem(s, L):
    #Removes all the instances of s in L
    index = ind(s, L)
    return L[0:index] + L[index + 1:]

def validWord(word, Rack):
    #Returns True if a word can be made using the list of words given by the user
    if word == "":
        return True
    elif word[0] in Rack:
        return validWord(word[1:], rem(word[0], Rack))
    else:
        return False
    
def scoreList(Rack):
    #Returns a list of the words the were made using the list of letter given by the user along their scores
    x = list(filter(lambda x:validWord(x, Rack), Dictionary))
    if x == []:
        return [' ', 0]
    else:
        return list(map((lambda x: [x, wordScore(x, scrabbleScores)]), x))

def bestWord(Rack):
    #Returns the word with the highest score that was made from thelist of letters provided by the user
    if scoreList(Rack) == [' ', 0]:
        return ["", 0]
    else:
        return list(scoreList(Rack)[-1]) 
    
