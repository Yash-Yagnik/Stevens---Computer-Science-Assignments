#lang eopl

#|-------------------------------------------------------------------------------
 | Name: Yash Yagnik 
 | Pledge: I pledge my honor that I have abided by the Stevens Honor System.
 |-------------------------------------------------------------------------------|#


#|-------------------------------------------------------------------------------|
 |                    Lab 4: Recursion and Sets (17 PTS +8 EC)                   |
 |-------------------------------------------------------------------------------|#

#| In this lab, we'll have some more recursion practice and then implement
 |  some basic set operations.
 |#

#|-------------------------------------------------------------------------------|
 |                      Part 1: Tail Recursion (7 PTS +4 EC)                     |
 |-------------------------------------------------------------------------------|#

#| First, we'll implement functions using tail recursion.
 | Tail recursion requires that the last operation done in 
 |   a method is the recursive call.
 | You MUST implement these functions using tail recursion
 |   or you will not receive credit.
 |#

#| Implement "length" to accept a list L
 |   and return X, where X equals the length of the list.
 | For example:
 |   If L = '(1 (3 2) (5 (9 4 8)) 6), then X = 4 since the outermost list has 4 elements.
 |
 | Examples:
 |   (length '(8))                        -> 1
 |   (length '(((((((17))))))))           -> 1
 |   (length '((b c) a (d (e f))))        -> 3
 |   (length '(s t v (u (x (y) z)) (w)))  -> 5
 |#

;; Type signature: (length list) -> int
;; 2 PTS
(define (length L)
  (define (myLength L X)
    (if (null? L)
        X 
        (myLength (cdr L) (+ 1 X))))
  (myLength L 0)
)

#| Implement "increase" to accept a list L and an integer n
 |   and return S, where S is a list of each element in L with n added to it.
 |
 | Examples:
 |   (increase '(8) 9)          -> '(17)
 |   (increase '(0 2 4 6) -2)   -> '(-2 0 2 4)
 |   (increase '(3 4 5 6 7) 5)  -> '(8 9 10 11 12)
 |#

;; Type signature: (increase list int) -> int
;; 2 PTS
(define (increase L n)
  (define (myIncrease L n S)
    (if (null? L)
         S
         (myIncrease (cdr L) n (append S (list (+ (car L) n))))))
 (myIncrease L n '())
)


#| This exercise serves to introduce the 'map' function.
 | Implement "dot" to accept two lists, A and B, of equal length
 |   and return C, where C is a list of the corresponding elements
 |   of A and B multiplied together.
 | Recursion is NOT required for this function.
 | Hint: use the built in 'map' function. This function takes an
 |   operation and at least one list and applies the operation to each element
 |
 | Examples:
 |   (dot '(8) '(3))                   -> '(24)
 |   (dot '(0 2 4 6) '(-2 -6 3 2))     -> '(0 -12 12 12)
 |   (dot '(3 4 5 6 7) '(5 4 3 2 1))   -> '(15 16 15 12 6)
 |#

;; Type signature: (dot list list) -> list
;; 3 PTS
(define (dot L S)
  (map * L S)
)

#| EXTRA CREDIT:
 | Implement "nest" to accept a list L
 |   and return X, where X equals the depth of nesting in the list.
 | For example:
 |   If L = '(1 (3 2) (5 (9 4 8)) (6)), then X = 3 since the list (9 4 8) is 3 levels deep.
 |
 | Examples:
 |   (nest '(8))                  -> 1
 |   (nest '((b c) a (d (e f))))  -> 3
 |   (nest '(((((((17))))))))     -> 7
 |#

;; Type signature: (nest list) -> int
;; 4 EC PTS
(define (nest L)
  "implement"
)



#| In the next part of the lab, we'll implement some basic functions
 |   which operate on sets.
 | These functions will come in handy in some subsequent labs.
 | EOPL lacks a built-in set datatype, so what we call a "set" will
 |   simply be a list which we ensure contains no duplicate elements.
 | And, when interacting with a "set", we won't care about
 |   the order of elements in the underlying list.
 | So throughout this lab, we can treat a set as a list,
 |   but we can't necessarily treat a list as a set.
 | Below is a helper function you'll need to construct a set from a list.
 | It simply eliminates duplicate elements from the input list.
 |#

;; Type signature: (make-set list) -> set
(define (make-set L)
  (cond [(null? L) '()]
        [(member (car L) (cdr L)) (make-set (cdr L))]
        [else (cons (car L) (make-set (cdr L)))]))


#| As you're working on each function, consider if you can
 |   take advantage of functions you've already implemented in this file.
 | Take particular note of the type signatures of each function.
 | If the output is expecting a set, make sure your
 |   output contains no duplicate values.
 | Additionally, your functions should be able to work with sets containing any type of data.
 |   Don't worry about nested sets, though.
 |   You'll see sets containing lists, but not sets containing sets.
 |   If a set contains lists, the order of items inside of the lists must matter.
 | Unless otherwise specified, the empty set/list is valid input to each function!
 | You may assume when the type of a function's input is "set" that
 |   the input will not contain duplicates.
 |#


#| IMPORTANT NOTE!!!
 | If the output of a function is of type "set", the order of elements
 |   in the output set does NOT need to match the order shown in the expected output.
 | If the set you output contains all the same elements of the expected set
 |   and contains no duplicate values, then it is correct.
 | If the output of a function is any other type than "set",
 |   the standard rule applies that its value must precisely match
 |   the expected output to be marked as correct.
 |#


#|-------------------------------------------------------------------------------|
 |                  Part 2: Unary Set Operations (10 PTS +4 EC)                  |
 |-------------------------------------------------------------------------------|#

#| Here, we'll implement functions which operate on one set.
 | Some functions may require recursion; others may not.
 |#


#| Implement "element?" to accept a set S and an element e
 |   and return #t if e is an element of S, and #f otherwise.
 | Use Racket's "equal?" function to compare data of arbitrary types.
 |
 | Examples:
 |   (element? '() 0)                     -> #f
 |   (element? '(7 8 9) 8)                -> #t
 |   (element? '("a" "b" "c") "ab")       -> #f
 |   (element? '(the man saw a dog) 'saw) -> #t
 |   (element? '((1 2) (3 4)) '(1 2))     -> #t
 |#

;; Type signature: (element? set any) -> boolean
;; 3 PTS
(define (element? S e)
  (cond [(null? S) #f]
        [(equal? (car S) e) #t]
        [else (element? (cdr S) e)])
)


#| Implement "insert" to accept a set S and an element e,
 |   and return the set of e and all the elements of S.
 | If S already contains e, the resultant set
 |   should not have any new elements.
 | Remember, the order of elements in the resultant set
 |   does not need to match the output shown below.
 |
 | Examples:
 |   (insert '(1 2 3) 0)            -> (0 1 2 3)
 |   (insert '(1 2 3) 1)            -> (1 2 3)
 |   (insert '("ab" "cd" "ba") "a") -> ("a" "ab" "cd" "ba")
 |   (insert '((y) (x z)) '(x y z)) -> ((y) (x z) (x y z))
 |#

;; Type signature: (insert set any) -> set
;; 2 PTS
(define (insert S e)
  (make-set (cons e S))
)


#| Implement "remove" to accept a set S and element e,
 |   and return the set of all elements in S except for e.
 | If e is not an element of S, the resultant set
 |   should be equivalent to S.
 |
 | Examples:
 |   (remove '(1 2 3) 2)          -> (1 3)
 |   (remove '(1 2 3 4) 3)        -> (1 2 4)
 |   (remove '("ab" "c") "a")     -> ("ab" "c")
 |   (remove '((x y z) (z)) '(x)) -> ((x y z) (z))
 |   (remove '((x y z) (z)) '(z)) -> ((x y z))
 |#

;; Type signature: (remove set any) -> set
;; 3 PTS
(define (remove S e)
  (define (myRemove S e L)
    (cond [(null? S) L]
          [(equal? (car S) e) (myRemove (cdr S) e L)]
          [else (myRemove (cdr S) e (append (list (car S)) L))]))
  (myRemove S e '())
)


#| Implement "cardinality" to accept a list L
 |   and return |L|, or the number of *unique*
 |   element in L.
 | Examples:
 |   (cardinality '(1 2 3))                   -> 3
 |   (cardinality '(1 1 2 3 3))               -> 3
 |   (cardinality '(a a a))                   -> 1
 |   (cardinality '((x y z) (x) (x y) (x z))) -> 4
 |#

;; Type signature: (cardinality list) -> int
;; 2 PTS
(define (cardinality L)
  (length (make-set L))
)


#| EXTRA CREDIT:
 | Implement "powerset" to accept a set S and return P(S),
 |   or the powerset of S.
 | P(S) is a set which contains every possible subset of S, including S.
 | This one is pretty challenging to implement!
 |
 | Hints:
 |   EOPL's "map" function may come in handy.
 |   You may want to use let-binding to reduce computation time.
 |   Consider writing helper functions or lambda functions.
 |
 | Because the output is a set of sets, the order of all the subsets,
 |   and the order of items in each subset, are arbitrary.
 |
 | Examples:
 |   (powerset '())            -> (())
 |   (powerset '(1))           -> (() (1))
 |   (powerset '(1 2))         -> (() (1) (2) (1 2))
 |   (powerset '(a b c))       -> (() (a) (b) (c) (a b) (a c) (b c) (a b c))
 |   (powerset '((A B) (C D))) -> (() ((C D)) ((A B)) ((A B) (C D)))
 |     -- In the above case, A needs to precede B and C needs to precede D,
 |        because we interpret (A B) and (C D) as ordered lists.
 |#

;; Type signature: (powerset set) -> set-of-sets
;; 4 EC PTS
(define (powerset S)
  "implement"
)
