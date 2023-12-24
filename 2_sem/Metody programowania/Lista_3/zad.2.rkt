#lang racket
(define (product xs)
  (define (it xs acc)
    (if (null? xs)
        acc
        (it (cdr xs) (* (car xs) acc))))
    (it xs 1))
(define x '(1 2 3 4 5))
(product x)