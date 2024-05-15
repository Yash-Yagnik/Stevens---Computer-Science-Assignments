
############################################################
# Name: Yash Yagnik
# Pledge: I have abided by the Stevens Honor System
# CS115 Lab 1
#
############################################################
def same(user_word):
    # This function sees if the first and last letter in a word is the same
    user_word = user_word.lower()
    if user_word[(len(user_word)-1)] == user_word[0]:
	    return True
    else:
	    return False
	    
def consecutiveSum(x, y):
                  # This function find the sum of consecutive integers between 2 numbers provided
	    return (((x + y)/2) * (y - x -1))
	    

	    
	    
