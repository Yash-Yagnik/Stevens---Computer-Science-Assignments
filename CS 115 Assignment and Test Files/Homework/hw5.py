'''
Created on 10/25/22
@author:   Yash Yagnik
Pledge:    I pledge my honor that I have abided by the Stevens Honor System

CS115 - Hw 5 
'''
memo1 = {0: 2, 1: 1}
def fast_lucas(n):
    '''Returns the nth Lucas number using the memoization technique
    shown in class and lab. The Lucas numbers are as follows:
    [2, 1, 3, 4, 7, 11, ...]'''

    if n in memo1:
        return memo1[n]
    else:
        answer = fast_lucas(n-1) + fast_lucas(n-2)
        memo1[n] = answer
        return answer 


memo = {}
def fast_change(amount, coins):
    '''Recieves an amount and the types differnet coins the currency has to offer.
    Returns the most effiecnt way to divide the amount with respect to the currancies coins'''
    if amount == 0:
        return 0
    elif ((amount, str(coins))) in memo:
        return memo[(amount, str(coins))]
    elif amount < 0 or coins == []:
        memo[(amount, str(coins))] = float("inf")
        return float("inf")
    else:
        useit = 1 + fast_change(amount - coins[0], coins)
        loseit = fast_change(amount, coins[1:])
        mini = min(useit, loseit)
        memo[(amount, str(coins))] = mini
        return mini
       



# If you did this correctly, the results should be nearly instantaneous.
print(fast_lucas(3))  # 4
print(fast_lucas(5))  # 11
print(fast_lucas(9))  # 76
print(fast_lucas(24))  # 103682
print(fast_lucas(40))  # 228826127
print(fast_lucas(50))  # 28143753123

print(fast_change(131, [1, 5, 10, 20, 50, 100]))
print(fast_change(292, [1, 5, 10, 20, 50, 100]))
print(fast_change(673, [1, 5, 10, 20, 50, 100]))
print(fast_change(724, [1, 5, 10, 20, 50, 100]))
print(fast_change(888, [1, 5, 10, 20, 50, 100]))


