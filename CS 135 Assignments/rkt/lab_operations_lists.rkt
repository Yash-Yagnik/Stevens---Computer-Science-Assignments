#lang eopl
;; Do not remove or change the line above!

#|-------------------------------------------------------------------------------
 | Name: Yash Yagnik
 | Pledge: I pledge my honor that I have abided by the Stevens Honor System.
 |-------------------------------------------------------------------------------|#

#| In each lab, you will implement a series of functions.
 | Each function you successfully implement will contribute
 |   some number of points to your total grade.
 | The point value of each function is stated above its declaration.
 | Each function will be assessed with a set of test cases which
 |   may NOT be the same as provided test cases.
 | Important note:  If your code does not compile you will receive a zero.
 | If you are unable to complete a function, please do not delete it, as
 |   that will cause our test scripts to malfunction.
 |#




#|-------------------------------------------------------------------------------|
 |                    Lab 1: Operations and Lists (20 PTS)                       |
 |-------------------------------------------------------------------------------|#

#| In this lab, you'll implement some basic operations on integers and booleans.
 | The following built-in functions will prove useful:
 |   (not p)   returns ¬p.
 |   (and p q) returns p ∧ q.
 |   (or p q)  returns p ∨ q.
 |   (+ x y)   returns x + y.
 |   (* x y)   returns x * y.
 |   (/ x y)   returns x / y.
 |   (sqrt x)  returns the square root of x.

 | Once you've successfully implemented a function,
 |   you can use it in subsequent functions too! 

 | True and false are written in Scheme as "#t" and "#f" respectively.
 |#



#|-------------------------------------------------------------------------------|
 |                          Part 1: Truth Tables (10 PTS)                        |
 |-------------------------------------------------------------------------------|#

#| Implement "nand" so that it accepts two booleans p and q
 |   and returns p ⊼ q [p nand q]:
 |
 | p q │ p ⊼ q
 | ────┼───────
 | T T │ F
 | T F │ T
 | F T │ T
 | F F │ T
 |
 | Example of testing this function:
 |   (nand #t #f) -> #t
 |#

;; Type signature: (nand boolean boolean) -> boolean
;; 2 PTS
(define (nand p q)
  (not (and p q))
  
)


#| Implement "implies" to accept two booleans p and q
 |   and return "p ⇒ q" [if p, then q]:
 |
 | p q │ p ⇒ q
 | ────┼───────
 | T T │ T
 | T F │ F
 | F T │ T
 | F F │ T
 |#

;; Type signature: (implies boolean boolean) -> boolean
;; 2 PTS
(define (implies p q)
  (or (not p) q)
)


#| Implement "xor" to accept two booleans p and q
 |   and return p ⊕ q [p exclusive or q]:
 |
 | p q │ p ⊕ q
 | ────┼───────
 | T T │ F
 | T F │ T
 | F T │ T
 | F F │ F
 |#

;; Type signature: (xor boolean boolean) -> boolean
;; 2 PTS
(define (xor p q)
  (and (or p q) (not (and p q)))
)


#| Implement "3majority" to return #t iff
 |   a majority of its three arguments are #t:
 |
 | p q r │ (3majority p q r)
 | ──────┼──────────────────
 | T T T │ T
 | T F T │ T
 | F T T │ T
 | F F T │ F
 | T T F │ T
 | T F F │ F
 | F T F │ F
 | F F F │ F
 |#

;; Type signature: (3majority boolean boolean boolean) -> boolean
;; 2 PTS
(define (3majority p q r)
  (or (and p q) (and q r) (and p r))
)


#| Implement "isosceles" to return #t when
 |   exactly two of its arguments are #t:
 |
 | p q r │ (isosceles p q r)
 | ──────┼──────────────────
 | T T T │ F
 | T F T │ T
 | F T T │ T
 | F F T │ F
 | T T F │ T
 | T F F │ F
 | F T F │ F
 | F F F │ F
 |#

;; Type signature: (isosceles boolean boolean boolean) -> boolean
;; 2 PTS
(define (isosceles p q r)
  "implement"
  (and (or (and p q) (and q r) (and p r)) (not(and p q r)))
)



#|-------------------------------------------------------------------------------|
 |                     Part 2: List Manipulation (10 PTS)                        |
 |-------------------------------------------------------------------------------|#

#| This part of the lab serves as an introduction to working with lists in Racket.
 | All lists in Racket are linked lists,
 |   meaning lists are either null [empty],
 |   or a pair of a head [the first element]
 |   and a tail [the rest of the list].
 | This means you can only directly access the first element of a list.
 | To access subsequent elements, you have to repeatedly access tails.
 |
 | Racket has the tick operator ' which is a shorthand for the "quote" function.
 | The tick operator tells the Racket interpreter to treat an expression as a literal
 |   rather than try to evaluate it.
 | By quoting a sequence of things in parentheses, a list is produced.
 | For example, (quote (+ 1 2)), or equivalently '(+ 1 2),
 |   will yield the list (+ 1 2), rather than 3.
 | When you quote a list, it quotes each sub-expression in the list,
 |   allowing you to create nested lists with just one tick mark.
 |#

#| The foundational building block of every list is the empty list,
 |   which is expressed in the following ways (the first is most common):
 |   '()
 |   empty
 |   (list)
 |
 | To construct a list of multiple values, use the "list" function.
 |   (list 1 2 3) -> (1 2 3)
 |   (list (+ 1 2)) -> (3)     <- notice how this differs from (quote (+ 1 2))
 |   (list 'a 'b) -> (a b)     <- '(a b) produces the same result
 |#

#| Here are some useful built-in list functions, where L is a list and E is some element:
 | (null? L) returns #t if L is empty, otherwise #f.
 | (length L) returns the number of elements in L.
 | (reverse L) returns L in reverse order.
 | (cons E L) returns L with E added to the front of the list.
 | (append L1 L2) returns a list of L1 followed by L2.
 | (car L) returns the first element of L. It throws an exception when given an empty list.
 | (cdr L) returns the tail [everything but the first element] of L. It throws an exception when given an empty list.
 |
 | You may not need all of these functions for this lab, but they may be useful in the future.
 |#



#| Implement "name" to accept a first and last name,
 |   and return a list of the first and last name.
 | Example:
 |   (name "Sandeep" "Bhatt") -> ("Sandeep" "Bhatt")
 |#

;; Type signature: (name string string) -> (string string)
;; 1 PTS
(define (name first last)
  (list first last)
)


#| Implement "last-name" to accept a list of a first and last name
 |   [like those constructed by the "name" function] and return the last name.
 | Example:
 |   (last-name '("Sandeep" "Bhatt"))    -> "Bhatt"
 |   (last-name (name "Jared" "Pincus")) -> "Pincus"
 |#

;; Type signature: (last-name (string string)) -> string
;; 1 PTS
(define (last-name name)
  (car (reverse name))
)


#| Implement "yoda" to take a three-part sentence [as a list]
 |   and return the sentence in Yoda-speak.
 | In other words, (w1 w2 w3) becomes (w3 w1 w2).
 | You may assume the input list has exactly 3 elements.
 |
 | Examples:
 |   (yoda '(I love Racket))                  -> (Racket I love)
 |   (yoda '(You are strong-with-the-force))  -> (strong-with-the-force You are)
 |   (yoda '(Sandeep-Bhatt has a-shiny-head)) -> (a-shiny-head Sandeep-Bhatt has)
 |#

;; Type signature: (yoda 3-element-list) -> 3-element-list
;; 2 PTS
(define (yoda words)
  (append (cddr words) (append (list (car words)) (list (cadr words))))
)


#| Implement "pig-latin" to accept a word as a list of characters
 |   and return that word following the rules of Pig Latin.
 | You translate a word into Pig Latin by relocating the first letter
 |   to the end of the word, then adding the suffix "ay".
 | The experienced Pig Latin speakers among you will know that sometimes
 |   you have to move more than one letter from the front of the word to the end,
 |   but here we'll ignore that rule. You merely need to move the first letter.
 | You may assume that the input word is at least one letter long.
 |
 | Examples:
 |   (pig-latin '(h a p p y))       -> (a p p y h a y)
 |   (pig-latin '(b i r t h d a y)) -> (i r t h d a y b a y)
 |   (pig-latin '(t r u e))         -> (r u e t a y)
 |#

;; Type signature: (pig-latin list) -> list
;; 3 PTS
(define (pig-latin word)
  (append (append (cdr word) (list (car word))) (list 'a 'y))
)


#| Implement "quad-roots" to accept integers a, b, and c,
 |   and return the two roots of the quadratic a*x^2 + b*x + c.
 | As a refresher, the two roots are equal to
 |   (-b ± sqrt(b^2 - 4*a*c)) / (2*a).
 | Format the function's output as a list of
 |   the root produced with minus, followed by
 |   the root produced with plus.
 |
 | While Racket does have support for complex numbers,
 |   you may assume that the roots of the input quadratic
 |   will not include imaginary components.
 | You may also assume that a ≠ 0.
 | Your output for the provided test cases may not exactly match
 |   the provided output. For example, decimals may be represented in fractional form.
 | As long as the values are equivalent mathematically, then your output is correct.
 |
 | Subdefinitions may help to make this function much cleaner!
 |
 | Examples:
 |   (quad-roots -3 0 0)    -> (0 0)
 |   (quad-roots 2 0 -2)    -> (-1 1)
 |   (quad-roots -3 15 -18) -> (3 2)
 |   (quad-roots 8 6 -5)    -> (-1.25 0.5)
 |   (quad-roots 1 -1 -1)   -> (-0.618... 1.618...)
 |   (quad-roots -5 2 2)    -> (0.863... -0.463...)
 |#

;; Type signature: (quad-roots nonzero-int int int) -> (real-number real-number)
;; 3 PTS
(define (quad-roots a b c)
  (list (/ (-(* b -1) (sqrt (- (* b b) (* 4 a c)))) (* 2 a)) (/ (+(* b -1) (sqrt (- (* b b) (* 4 a c)))) (* 2 a)))
    )