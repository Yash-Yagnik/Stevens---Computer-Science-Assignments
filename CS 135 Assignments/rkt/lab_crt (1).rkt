#lang eopl

#|-------------------------------------------------------------------------------
 | Name: Yash Yagnik
 | Pledge: I pledge my honor that I ahve abided by the Stevens Honor System.
 |-------------------------------------------------------------------------------|#


#|-------------------------------------------------------------------------------|
 |                   Lab 9: Chinese Remainder Theorem (15 PTS)                   |
 |-------------------------------------------------------------------------------|#


#| This lab will make you code Chinese Remainder Theorem.
 |   It has split CRT into several small parts to make it more
 |   doable. Functions for gcd, pulverizer, and mod-inverse 
 |   have been provided for you.
 | 
 |#

;; Type signature: (gcd natural natural) -> natural
;; returns the greatest common divisor of the inputs
(define (gcd a b)
  (cond ((= a 0) b)
        ((= b 0) a)
        (else (gcd b (modulo a b)))
  )
)

;; Type signature: (pulverizer natural natural) -> (natural natural)
;; returns a pair of coefficients (x, y) such that ax + by = gcd(a, b)
(define (pulverizer a b)
  (define (pulverize a b q r)
    (if (zero? r)
        '()
        (append (pulverize b (modulo a b) (quotient b (modulo a b)) (modulo b (modulo a b)))  (list (list a b q r)))
    )
  )

  (define (back-sub l c)
    (if (null? l)
        c
        (back-sub (cdr l) (list (cadr c) (- (car c) (* (caddr (car l)) (cadr c)))))
    )
  )

  (back-sub (pulverize a b (quotient a b) (modulo a b)) '(0 1))
)

(define (error-inverse)  (eopl:error "Error computing inverse: a and m must be relatively prime"))

;; Type signature: (mod-inverse natural natural) -> posint
;; returns the multiplicative inverse of a modulo m
(define (mod-inverse a m)
  (if (= (gcd a m) 1)
      (if (> (car (pulverizer a m)) 0)
          (car (pulverizer a m))
          (+ (car (pulverizer a m)) m)
      )
      (error-inverse)
  )
)


#|-------------------------------------------------------------------------------|
 |                             Part 1: CRT (15 PTS)                              |
 |-------------------------------------------------------------------------------|#

#| Here, we're going to implement a few simple functions to break up the CRT algorithm.
 |   Lists of pairs will be used to represent the a and b of a mod b, so the list
 |   '((2 3) (3 5) (2 7))' represents the set of modulos 2 mod 3, 3 mod 5, and 2 mod 7.
 |#


#| Implement "find-m" to compute the product of all numbers inside the mod (b).
 |
 | Examples:
 |   (find-m '((2 3) (3 5) (2 7))) -> 105
 |   (find-m '((10 11) (4 12) (12 13))) -> 1716
 |   (find-m '((1 5) (2 14) (5 23) (26 27))) -> 43470
 |#
;; Type Signature: (find-m list-of-(a,b)-tuples) -> int
;; 2 PTS
(define (find-m L)
  (cond [(null? L) 1]
        [else ( * (car (cdr (car L))) (find-m (cdr L)))]
         ))



#| Implement "CRT-exists?" to return a boolean that represents if the CRT is possible.
 |   Remember that the CRT is possible if and only if all numbers inside the mod (b)
 |   are pairwise relatively prime.
 |
 | A helper function may be useful.
 |
 | Examples:
 |   (CRT-exists? '((2 3) (3 5) (2 6))) -> #f
 |   (CRT-exists? '((10 11) (4 12) (12 13))) -> #t
 |   (CRT-exists? '((1 5) (2 14) (5 23) (26 28))) -> #f
 |   (CRT-exists? '((1 2) (1 3) (1 5) (1 7) (1 11) (1 13))) -> #t
 |#
;; Type Signature: (CRT-exists? list-of-(a,b)-tuples) -> boolean
;; 4 PTS

(define (CRT-exists? L)
  (define list (strip L '()))
  (CRT-exists-helper? (find-m L) list)
)

(define (CRT-exists-helper? D L)
  (cond [(null? L) #t]
        [(equal? (modulo  (/ D (car L)) (car L)) 0) #f]
        [else (CRT-exists-helper? D (cdr L))])
)

(define (strip L a)
  (cond [(null? L) a]
        [else (strip (cdr L) (append a (cdr (car L)))) ])
)



#| Implement "CRT-helper" to compute unsimplified value of the CRT.
 |   This function will be used in the next part to compute the actual CRT.
 |   It is given a valid list of Ai and Mi values, and M (product of all b in the list).
 |   Ai is the first element of each tuple, Mi is m/b where b is the second element of each tuple.
 |   Remember you need to compute Ai*Mi*Mi^-1 for all i in the list and sum these values.
 |
 | Examples:
 |   (CRT-helper '((10 11) (4 12) (12 13)) 1716) -> 26740
 |   (CRT-helper '((2 3) (3 5) (2 7)) 105) -> 233
 |   (CRT-helper '((1 2) (2 3) (3 5) (4 7) (5 11) (6 13)) 30030) -> 299513
 |#
;; Type Signature: (CRT-helper list-of-(a,b)-tuples int) -> int
;; 5 PTS

(define (CRT-helper L m)
  (cond [(null? L) 0]
        [else (+ (* (car (car L)) (/ m (car (cdr (car L)))) (mod-inverse (/ m (car (cdr (car L)))) (/ m (/ m (car (cdr (car L))))))) (CRT-helper (cdr L) m))]
))






#| Implement "CRT" to compute the actual CRT algorithm.
 |   Use the previous functions to complete this function.
 |   You should first check if the CRT is possible to be computed.
 |   If it is possible to be computed you should return the smallest positive integer that fulfills
 |   the requirements by using CRT-helper and M. If it isn't possible you should return -1.
 |
 | Examples:
 |   (CRT '((10 11) (4 12) (12 13))) -> 1000
 |   (CRT '((2 3) (3 5) (2 7))) -> 23
 |   (CRT '((1 2) (2 3) (3 5) (4 7) (5 11) (6 13))) -> 29243
 |   (CRT '((1 2) (4 8) (8 9))) -> -1
 |#
;; Type Signature: (CRT list-of-(a,b)-tuples) -> int
;; 4 PTS
(define (CRT L)
  (cond [(not (CRT-exists? L)) -1]
        [else (modulo (CRT-helper L (find-m L)) (find-m L))])
 )
