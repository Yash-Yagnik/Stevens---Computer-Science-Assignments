#lang eopl

#|-------------------------------------------------------------------------------
 | Name: Yash Yagnik
 | Pledge: I pledge my honor that I ahve abided by the Stevens Honor System.
 |-------------------------------------------------------------------------------|#


#|-------------------------------------------------------------------------------|
 |                        Lab 4: Sets and Relations (28 PTS)                     |
 |-------------------------------------------------------------------------------|#


#| In this lab, we'll implement some basic functions which operate on multiple sets.
 | As you're working on each function, consider if you can
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

#| We'll also write functions which operate over relations in this lab.
 | A relation is a set of pairs, so as a continuation of the
 |   previous lab's representation of sets,
 |   we'll represent a relation as a set of pairs of integers.
 | (NOTE: references to the term "pair" in the lab refer to ordered lists
 |    of two integers, NOT the Racket data structure called a "pair").
 | The pair (x y) with integers x and y represents
 |   an "arrow" pointing from x to y in the relation.
 |
 | Every relation in this lab will have a subset of the positive integers as its domain,
 |   which will be notated in the instructions as [1, n] where n is an integer ≥ 1.
 | [1, n] represents the domain of values: 1, 2, ..., n.
 |
 | Like in the previous lab, we'll use lists to represent sets,
 |   but we won't let there be duplicate elements and
 |   we won't care about the elements' order.
 | If the output type of a function is a "relation",
 |   the order of the pairs in the output list doesn't
 |   need to match the test cases' output order to be correct.
 |
 | If the type of a function's input is a "relation",
 |   you may assume that the relation is correctly formed;
 |   that is, the relation only contains unique pairs of integers.
 |
 | *** The empty relation is always valid input for relation inputs! ***
 |
 | At the bottom of this file, you'll find many helper functions,
 |   all from the previous lab, which you may or may not need to help you complete this one.
 | Since a relation is a type of set, the helpers which operate on sets will come in handy!
 |
 | Also, an important note:
 |   If you want to skip a function, whether it's extra credit or otherwise,
 |   please don't comment out the function's declaration. Instead,
 |   keep the function there and have it return something useless,
 |   like the "TODO" strings which are in the function bodies by default.
 |
 | From this point forward with these lab assignments,
 |   you should be comfortable using recursion, lists, if/cond expressions,
 |   and sometimes writing subdefinitions/helper functions.
 | If you want to take the extra step to write more advanced/efficient code,
 |   let bindings and lambda functions are two highly useful
 |   but completely optional constructs worth learning.
 |#





#|-------------------------------------------------------------------------------|
 |                     Part 1: Binary Set Operations (14 PTS)                    |
 |-------------------------------------------------------------------------------|#

#| Now we'll implement functions which operate on two sets.
 | Some functions may require recursion; others may not.
 |#


#| Implement "union" to accept sets S1 and S2 and return S1 ⋃ S2,
 |   or the set of all elements which are in S1 or in S2.
 | Examples:
 |   (union '(1 2 3) '(4 5 6))         -> (1 2 3 4 5 6) 
 |   (union '(c b f d) '(b c a))       -> (a b c d f)
 |   (union '("abc") '())              -> ("abc")
 |   (union '((z) (x y)) '((y x) (z))) -> ((z) (x y) (y x))
 |#

;; Type signature: (union set set) -> set
;; 2 PTS
(define (union S1 S2)
  (make-set (append S1 S2))
)


#| Implement "intersection" to accept sets S1 and S2 and return S1 ⋂ S2,
 |   or the set of all elements which are in S1 and in S2.
 | You may want to write a helper function for this one!
 |
 | Examples:
 |   (intersection '(1 2 3 4) '(2 4 5))         -> (2 4)
 |   (intersection '(s a n d e p) '(b h a t))   -> (a)
 |   (intersection '("abc") '("ab"))            -> ()
 |   (intersection '((x y) (z)) '((x y) (y x))) -> ((x y))
 |#

;; Type signature: (intersection set set) -> set
;; 3 PTS
(define (intersection S1 S2)
  (define (myIntersection S1 S2 L) 
  (cond [(null? S1) L]
        [(null? S2) L]
        [(element? S1 (car S2)) (myIntersection S1 (cdr S2) (append (list(car S2)) L))]
        [else (myIntersection S1 (cdr S2) L)])
    )
  (myIntersection S1 S2 '())
)


#| Implement "disjoint" to accept sets S1 and S2 and return
 |   whether S1 and S2 are disjoint (in other words, whether
 |   they share no elements in common).
 |
 | Examples:
 |   (disjoint? '(1 2 3) '())          -> #t
 |   (disjoint? '(a b c) '(b))         -> #f
 |   (disjoint? '((x z)) '((x y) (z))) -> #t
 |#

;; Type signature: (disjoint? set set) -> boolean
;; 1 PTS
(define (disjoint? S1 S2)
  (cond [(null? (intersection S1 S2)) #t]
        [else #f]
    )
)


#| Implement "subset?" to accept sets S1 and S2 and return S1 ⊆ S2.
 | In other words, it returns #t if S1 is a subset of S2 (or the same as S2),
 |   and #f otherwise.
 | In other-other words, it returns #t if every element in S1 is also in S2.
 |
 | Examples:
 |   (subset? '() '())               -> #t
 |   (subset? '(1 2 3) '(4 1 3 5 2)) -> #t
 |   (subset? '(b a c) '(d f e a g)) -> #f
 |   (subset? '(1 3 2) '(3 2 1))     -> #t
 |#

;; Type signature: (subset? set set) -> boolean
;; 3 PTS
(define (subset? S1 S2)
  (cond [(equal? S1 S2) #t]
        [(null? S1) #t]
        [(element? S2 (car S1)) (subset? (cdr S1) S2)]
        [else #f]
        )
)


#| Implement "set-equal?" to accept sets S1 and S2 and return whether S1 and S2 are equal
 |   (in other words, all elements of S1 are in S2 and all elements of S2 are in S1).
 | Recall that two sets with the same elements but in a different order
 |   are still equivalent to one another.
 |
 | Examples:
 |   (set-equal? '() '())                           -> #t
 |   (set-equal? '(a b c) '(a b c))                 -> #t
 |   (set-equal? '(1 2 3 4) '(4 3 1 2))             -> #t
 |   (set-equal? '("c" "b" "d" "a") '("a" "c" "b")) -> #f
 |#

;; Type signature: (set-equal? set set) -> boolean
;; 1 PTS
(define (set-equal? S1 S2)
  (cond [(equal? S1 S2) #t]
        [(null? S1) #t]
        [(element? S2 (car S1)) (set-equal? (cdr S1) S2)]
        [else #f]

    )
)


#| Implement "difference" to accept sets S1 and S2
 |   and return S1 \ S2, or the set of all elements which
 |   are in S1 and not in S2.
 |
 | Examples:
 |   (difference '(1 2 3) '(2 3 4)) -> (1)
 |   (difference '(x y z) '(y x z)) -> ()
 |   (difference '(1 2 3) '(4 5 6)) -> (1 2 3)
 |   (difference '() '("x" "y"))    -> ()
 |   (difference '("xyz") '())      -> ("xyz")
 |#

;; Type signature: (difference set set) -> set
;; 3 PTS
(define (difference S1 S2)
  (define (myDifference S1 S2 L)
  (cond [(set-equal? S1 S2) L]
        [(null? S2) S1]
        [(null? S1) L]
        [(equal? (element? S2 (car S1)) #f) (myDifference (cdr S1) S2 (append L (list (car S1))) )]
        [else (myDifference (cdr S1) S2 L)]
        )
    )
  (myDifference S1 S2 '())
)


#| Implement "sym-diff" to accept sets S1 and S2 and
 |   return the symmetric difference of S1 and S2,
 |   which is the set of all items which are in exactly one of the sets.
 | In other words, the symmetric difference is the set of items
 |   which are in S1 and not in S2, or are in S2 and not in S1.
 |
 | Examples:
 |   (sym-diff '(1 2 3) '(3 4 5)) -> (1 2 4 5)
 |   (sym-diff '(a b c) '(d e f)) -> (a b c d e f)
 |   (sym-diff '(1 2 3) '(1 2 3)) -> ()
 |   (sym-diff '(1 2) '(1 2 3 4)) -> (3 4)
 |   (sym-diff '(1) '())          -> (1)
 |#

;; Type signature: (sym-diff list list) -> set
;; 1 PTS
(define (sym-diff S1 S2)
  (make-set (append (difference S1 S2) (difference S2 S1)))
)





#|-------------------------------------------------------------------------------|
 |                           Part II: Relations (14 PTS)                         |
 |-------------------------------------------------------------------------------|#

#| Implement "id" to accept a positive integer
 |   and return the "identity relation" over [1, n].
 | This means it should create a set
 |   containing the pairs (1 1), (2 2), ..., (n n).
 |
 | Examples:
 |   (id 1) -> ((1 1))
 |   (id 2) -> ((1 1) (2 2))
 |   (id 5) -> ((1 1) (2 2) (3 3) (4 4) (5 5))
 |#

;; Type signature: (id positive-int) -> relation
;; 3 PTS
(define (id n)
  (define (myId n L)
  (cond [(equal? n 1) (append '((1 1)) L)]
        [else (myId (- n 1) (append (list (list n n)) L))]
  )
    )
  (myId n '())
)


#| Implement "reflexive?" to accept a positive integer n and relation R,
 |   and return whether R is reflexive over the domain [1, n].
 | In other words, R is reflexive if it contains the identity relation up to n.
 | This can be implemented easily using "id" and one of the provided helper functions.
 |
 | Examples:
 |   (reflexive? 3 '())                              -> #f
 |   (reflexive? 2 '((3 3) (1 1) (2 2)))             -> #t
 |   (reflexive? 3 '((2 3) (1 1) (3 3) (3 4) (2 2))) -> #t
 |   (reflexive? 4 '((1 1) (2 2) (3 3)))             -> #f
 |   (reflexive? 1 '((1 4) (2 3) (3 1) (3 3) (4 4))) -> #f
 |   (reflexive? 2 '((4 3) (2 2) (1 3) (1 1)))       -> #t
 |#

;; Type signature: (reflexive? positive-int relation) -> boolean
;; 2 PTS
(define (reflexive? n R)
  (cond [(subset? (id n) R) #t]
        (else #f)
    )
)


#| Implement "reflexive-closure" to accept a positive integer n and a relation R,
 |   and return the reflexive closure of R over [1, n],
 |   which is the smallest relation that contains R and is reflexive over [1, n].
 | This can also be implemented easily using "id" and one of the provided helper functions.
 |
 | Examples:
 |   (reflexive-closure 3 '())                  -> ((1 1) (2 2) (3 3))
 |   (reflexive-closure 3 '((3 2) (2 3)))       -> ((1 1) (2 2) (3 3) (3 2) (2 3))
 |   (reflexive-closure 4 '((1 1) (2 2) (3 3))) -> ((1 1) (2 2) (3 3) (4 4))
 |   (reflexive-closure 1 '((1 1) (2 2) (3 3))) -> ((1 1) (2 2) (3 3))
 |   (reflexive-closure 2 '((1 3) (3 2) (3 3))) -> ((1 3) (3 2) (3 3) (1 1) (2 2))
 |   (reflexive-closure 1 '((2 4) (5 7) (4 3))) -> ( (5 7) (4 3) (2 4)  (1 1))
 |#

;; Type signature: (reflexive-closure positive-int relation) -> relation
;; 2 PTS
(define (reflexive-closure n R)
  (make-set (append (id n) R))
)


#| Implement "converse" to accept a relation R, and return the converse of R.
 | We can define R's converse in set-builder notation as { (y, x) | (x, y) ∈ R }.
 | In other words, the converse of R is the same as R but the inputs and outputs are flipped.
 | Hint: consider Racket's "map" and "reverse" functions for a really easy way to implement this!
 |
 | Examples:
 |   (converse '())                  -> ()
 |   (converse '((1 2) (3 2) (4 5))) -> ((2 1) (2 3) (5 4))
 |   (converse '((1 1) (1 2) (1 3))) -> ((1 1) (2 1) (3 1))
 |   (converse '((2 6) (4 3)))       -> ((6 2) (3 4))
 |#

;; Type signature: (converse relation) -> relation
;; 3 PTS
(define (converse R)
  (map reverse R)
  
)


#| Implement "symmetric?", which accepts a relation R and returns whether R is symmetric.
 | R is symmetric iff ∀(x, y) ∈ R : (y, x) ∈ R.
 | This can be implemented easily using "converse" and one of the provided helper functions.
 |
 | Examples:
 |   (symmetric? '())                              -> #t
 |   (symmetric? '((1 1) (2 1) (1 2)))             -> #t
 |   (symmetric? '((1 1) (2 4) (3 7) (3 5) (5 3))) -> #f
 |   (symmetric? '((2 4) (4 3) (3 4) (4 2)))       -> #t
 |   (symmetric? '((1 1) (4 4)))                   -> #t
 |   (symmetric? '((1 2) (2 1) (3 3) (2 3)))       -> #f
 |#

;; Type signature: (symmetric? relation) -> boolean
;; 2 PTS
(define (symmetric? R)
  (cond [(set-equal? (converse R) R) #t]
        [else #f]
         )
)


#| Implement "symmetric-closure" to accept a relation R and return the symmetric closure of R,
 |   which is the smallest relation which is symmetric and contains R.
 | This can be implemented easily using "converse" and one of the provided helper functions.
 |
 | Examples:
 |   (symmetric-closure '())                  -> ()
 |   (symmetric-closure '((3 2) (2 3)))       -> ((3 2) (2 3))
 |   (symmetric-closure '((1 2) (2 7) (3 4))) -> ((1 2) (2 7) (3 4) (2 1) (7 2) (4 3))
 |   (symmetric-closure '((1 1) (2 2) (1 3))) -> ((1 1) (2 2) (1 3) (3 1))
 |   (symmetric-closure '((3 3)))             -> ((3 3))
 |#

;; Type signature: (reflexive-closure relation) -> relation
;; 2 PTS
(define (symmetric-closure R)
  (make-set (append (converse R) R))
  
)




  

#|-------------------------------------------------------------------------------|
 |              Helper Functions: use them to your heart's content!              |
 |-------------------------------------------------------------------------------|#

;; "make-set" accepts a list and returns the list without duplicate elements.
;; Type signature: (make-set list) -> set
(define (make-set L)
  (cond [(null? L) '()]
        [(member (car L) (cdr L)) (make-set (cdr L))]
        [else (cons (car L) (make-set (cdr L)))]))


;; "element?" accepts a set S and an element e and returns #t iff e ∈ S.
;; Type signature: (element? set any) -> boolean
(define (element? S e)
  (cond [(null? S) #f]
        [(equal? e (car S)) #t]
        [else (element? (cdr S) e)]))


;; "insert" accepts a set S and an element e, and returns {e} ⋃ S.
;; Type signature: (insert set any) -> set
(define (insert S e)
  (make-set (cons e S)))


;; "remove" accepts a set S and element e and returns S – {e}.
;; Type signature: (remove set any) -> set
(define (remove S e)
  (cond [(null? S) S]
        [(equal? e (car S)) (cdr S)]
        [else (cons (car S) (remove (cdr S) e))]))


;; "cardinality" accepts a list L and returns the number of unique elements in L.
;; Type signature: (cardinality list) -> int
(define (cardinality L)
  (length (make-set L)))


;; "powerset" accepts a set S and returns the set { T | T ⊆ S }.
;; Type signature: (powerset set) -> set-of-sets
(define (powerset S)
  (if (null? S) '(())
      (let ([r (powerset (cdr S))])
        (append r (map (lambda (s) (cons (car S) s))
                       r)))))
