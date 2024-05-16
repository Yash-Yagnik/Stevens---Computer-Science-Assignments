#lang eopl

#|-------------------------------------------------------------------------------
 | Name: Yash Yagnik
 | Pledge: I pledge my honor that I have abided by the Stevens Honor System.
 |-------------------------------------------------------------------------------|#


#|-------------------------------------------------------------------------------|
 |                      Lab 8: Modular Operations (12 PTS)                       |
 |-------------------------------------------------------------------------------|#


#| This lab explores a few topics of number theory involving
 |   modular operations that have been covered in lecture thus far.
 |
 | The type "natural" refers to a nonnegative integer >= 0.
 | The type "posint" refers to a positive integer > 0.
 | You'll find the following functions built-in to EOPL useful:
 |   (modulo a b)   returns a mod b [a % b in Python].
 |   (quotient a b) returns the integer quotient of a ÷ b [a // b in Python].
 | Additionally, the gcd function implemented in the last lab is given below
 |   (gcd a b)
 |#

;; Type signature: (gcd natural natural) -> natural
;; returns the greatest common divisor of the inputs
(define (gcd a b)
  (cond ((= a 0) b)
        ((= b 0) a)
        (else (gcd b (modulo a b)))
  )
)


#|-------------------------------------------------------------------------------|
 |                     Part 1: Modular Congruence (3 PTS)                        |
 |-------------------------------------------------------------------------------|#


#| Here, we're going to implement a simple function in a unique way.
 | It may seem convoluted or unnecessary, but this implementation strategy
 |   is fundamental to functional programming.
 |
 | In past labs, we've seen that functions can be passed
 |   as parameters just like any other datatype;
 |   for instance, in (map zero? '(4 0 2 3 0 1)),
 |   the map function receives the "zero?" function as a parameter.
 | But in Racket and other functional languages,
 |   not only can functions receive functions as parameters,
 |   they can return functions as values too!
 |
 | The most direct way of returning a function
 |   is by constructing a lambda function as the return value.
 | Lambda functions are constructed similarly to regular functions,
 |   but they lack a name alongside their parameters.
 | A lambda is constructed like so:
 |   (lambda (<param1> <param2> ... <paramn>) <body>).
 |
 | An alternative way is to define a function with a subdefinition,
 |   and simply return the [unparenthesized] name of that subdefined function.
 | In the same way that you can pass a function using its name to another function,
 |   like "zero?" in the "map" example, you can return a function using its name.
 |#




#| Implement "cong-mod?" to accept a posint m
 |   and return a binary predicate representing
 |   the "congruence modulo m" equivalence relation.
 | In other words, the function that (cong-mod? m) returns
 |   should accept two naturals a and b, and return
 |   whether a and b are congruent modulo m.
 | You can choose how the return function computes whether a ≡ b (mod m),
 |   the two main ways being:
 |     1. a ≡ b (mod m) iff a mod m = b mod m.
 |     2. a ≡ b (mod m) iff m divides (a - b).
 |
 | Again, notice that "cong-mod?" only has the parameter m.
 | That's why the body of "cong-mod?" must construct
 |   a function that accepts the parameters a and b.
 | Also notice how the examples are written with an extra, but necessary,
 |   set of parentheses.
 | Also-also, observe the commented type signature of "cong-mod?".
 | It's admittedly confusing because it's not using a standard notation,
 |   but the signature indicates that the return type of the function
 |   is itself a function which accepts two naturals and returns a boolean.
 |
 | Examples:
 |   ((cong-mod? 1) 3 4)   -> #t
 |   ((cong-mod? 1) 5 0)   -> #t
 |   ((cong-mod? 2) 6 10)  -> #t
 |   ((cong-mod? 2) 13 7)  -> #t
 |   ((cong-mod? 2) 1 8)   -> #f
 |   ((cong-mod? 2) 0 0)   -> #t
 |   ((cong-mod? 3) 0 9)   -> #t
 |   ((cong-mod? 3) 7 0)   -> #f
 |   ((cong-mod? 3) 14 2)  -> #t
 |   ((cong-mod? 3) 8 19)  -> #f
 |   ((cong-mod? 8) 1 5)   -> #f
 |   ((cong-mod? 8) 9 12)  -> #f
 |   ((cong-mod? 8) 4 36)  -> #t
 |   ((cong-mod? 8) 25 25) -> #t
 |#

;; Type signature: (cong-mod? posint) -> (natural natural -> boolean)
;; 3 PTS
(define (cong-mod? m)
  (lambda (a b)
    (= (modulo (- a b) m) 0))
)




#| Constructing "cong-mod?" in this way is useful because
 |   it simplifies future usage of the function.
 | Consider this definition:
 |   (define cong-mod-3? (cong-mod? 3))
 |
 | Now we can easily and repeatedly compare two numbers modulo 3 like so:
 |  (cong-mod-3? 8 14).
 |
 | Also, if we wanted to write another function which accepted
 |   an arbitrary equivalence relation/function as input,
 |   we could easily pass it (cong-mod? 5), for instance, as a parameter.
 |#


#|-------------------------------------------------------------------------------|
 |                 Part 2: Extended Euclidean Algorithm (5 PTS)                  |
 |-------------------------------------------------------------------------------|#

#| Implement "pulverizer" to accept two integers a and b, where a > b,
 |   and return a list of values (s t) which represent the
 |   coefficients for the linear combination of a and b.
 |
 | The built in math function "quotient" may be useful here.
 |    This function returns only the whole number portion of a division.
 |
 | Follow the algorithm from class. A helper function may be helpful.
 |
 | Examples:
 |   (pulverizer 2 1)      -> '(0 1)
 |   (pulverizer 240 46)   -> '(-9 47)
 |   (pulverizer 356 252)  -> '(17 -24)
 |   (pulverizer 1147 899) -> '(11 -14)
 |#
;; Type signature: (pulverizer natural natural) -> (natural natural)
;; 5 PTS

(define (my-pulverizer a b)
  (if (zero? a)
      (list b 0 1)
      (let ([p (my-pulverizer (modulo b a) a)])
        (list (car p)
              (- (car (cdr (cdr p)))
                 (* (quotient b a) (car (cdr p))))
              (car (cdr p)))))
  )
(define (pulverizer a b)
  (cdr (my-pulverizer a b))
)



#|-------------------------------------------------------------------------------|
 
 |                       Part 3: Modular Inverses (4 PTS)                        |
 |-------------------------------------------------------------------------------|#

(define (error-inverse)  (eopl:error "Error computing inverse: a and m must be relatively prime"))

#| Implement "mod-inverse" to accept two integers a and m
 |    and return the modular inverse of a mod m.
 |
 | Use the Extended Euclidean Algorithm (pulverizer) method above
 |    to help you with this function.
 | Additionally, make sure to utilize the error above if the inverse does not exist.
 | 
 | Examples:
 |   (mod-inverse 3 5)      -> 2
 |   (mod-inverse 5 3)      -> 2
 |   (mod-inverse 7 26)     -> 15
 |   (mod-inverse 26 7)     -> 3
 |   (mod-inverse 41 201)   -> 152
 |   (mod-inverse 201 41)   -> 10
 |   (mod-inverse 201 42)   -> error
 |   (mod-inverse 1147 899)  -> error
 |#
;; Type signature: (mod-inverse natural natural) -> posint
;; 4 PTS
(define (mod-inverse a m)
  (cond
    [(not (equal? (gcd a m) 1)) (error-inverse)]
    [else (modulo (car (pulverizer a m)) m)])
)