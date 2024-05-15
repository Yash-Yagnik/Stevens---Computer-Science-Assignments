Python 3.9.13 (tags/v3.9.13:6de2ca5, May 17 2022, 16:36:42) [MSC v.1929 64 bit (AMD64)] on win32
Type "help", "copyright", "credits" or "license()" for more information.
>>> def same(user_word):
	user_word = user_word.lower()
	if user_word[(len(user_word)-1)] == user_word[0]:
		print("true")
	else:
		print("false")

		
>>> same("Stevens")

true
>>> def consecutiveSum(x, y):
	print(((x + y)/2) * (y - x -1))

	
>>> consecutiveSum(4, 5)
0.0
>>> consecutiveSum(4, 9)
26.0
>>> 