'''
Created on 10/9/2022
@author:   Yash Yagnik
Pledge:    I pledge my honor that I have abided by the Stevens Honor System

CS115 - Hw 3
'''
# Be sure to submit hw3.py.  Remove the '_template' from the file name.

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' PROBLEM 0
' Implement the function giveChange() here:
' See the PDF in Canvas for more details.
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
# your code goes here
def giveChange(amount, coins):
    '''Returns the least amount of coins that it would take to
    make change the input money, it also prints out to the exact coins needed to get the change'''
    if amount==0:
        return [0, []]
    elif amount < 0 or coins == []:
        return [float("inf"), []]
    elif coins[0] > amount:
        return giveChange(amount, coins[1:])
    
    useit = giveChange(amount - coins[0], coins)
    loseit = giveChange(amount, coins[1:])
    useit2 = [1 + useit[0], useit[1] + [coins[0]]]
    if useit2[0] < loseit[0]:
        return useit2
    else:
        return loseit

       



# Here's the list of letter values and a small dictionary to use.
# Leave the following lists in place.
scrabbleScores = \
   [ ['a', 1], ['b', 3], ['c', 3], ['d', 2], ['e', 1], ['f', 4], ['g', 2],
     ['h', 4], ['i', 1], ['j', 8], ['k', 5], ['l', 1], ['m', 3], ['n', 1],
     ['o', 1], ['p', 3], ['q', 10], ['r', 1], ['s', 1], ['t', 1], ['u', 1],
     ['v', 4], ['w', 4], ['x', 8], ['y', 4], ['z', 10] ]

Dictionary = ['a', 'am', 'at', 'apple', 'bat', 'bar', 'babble', 'can', 'foo',
              'spam', 'spammy', 'zzyzva']

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' PROBLEM 1
' Implement wordsWithScore() which is specified below.

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''


# Implement your functions here.
def letterScore(letter, scorelist):
    #This will output the score attached to using a certain letter in scrabble word
    if scorelist == []:
        return 0
    elif scorelist[0][0] == letter:
        return scorelist[0][1]
    else:
        return letterScore(letter, scorelist[1:])

def wordScore(word, scorelist):
    #This outputs the addition of the points of all the letters in the word provided by the user
    if word == "":
        return 0
    else:
        return letterScore(word[0], scorelist) + wordScore(word[1:], scorelist)
    
def wordsWithScore(dct, scores):
    # This will output the score of the each word in a list based upon the scoring given by the user
    if dct == []:
        return []
    else:
        return [[dct[0]] + [wordScore(dct[0], scores)]] + wordsWithScore(dct[1:], scores)

    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' PROBLEM 2
' For the sake of an exercise, we will implement a function
' that does a kind of slice. You must use recursion for this
' one. Your code is allowed to refer to list index L[0] and
' also use slice notation L[1:] but no other slices.
' (Notice that you cannot assume anything about the length of the list.)
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
def take(n, L):
    '''Returns the list L[0:n], assuming L is a list and n is at least 0.'''
    if n <= 0 or L == []:
        return []
    else:
        return [L[0]] + take(n-1, L[1:])
    



'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' PROBLEM 3
' Similar to problem 2, will implement another function
' that does a kind of slice. You must use recursion for this
' one. Your code is allowed to refer to list index L[0] and
' also use slice notation L[1:] but no other slices.
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
def drop(n, L):
    '''Returns the list L[n:], assuming L is a list and n is at least 0.'''
    if n == 0:
        return L
    else:
        return drop(n-1, L[1:])        

    

