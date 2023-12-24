#lang racket
(define (square a b c)
  (cond [ (and (> a b) (> a c) (* a a))]
        [(and (> b a) (> b c) (* b b))]
        [(and (> c a) (> c b) (* c c))]))
(square 11 2 4)
