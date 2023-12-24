#lang racket
(require rackunit)
(define (maximum xs)
  (define (max x xs)
    (cond [(null? xs) x]
          [(> (car xs) x) (max (car xs) (cdr xs))]
          [else (max x (cdr xs))]))
  (max -inf.0 xs))


( maximum ( list ) )
