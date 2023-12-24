#lang racket
(define (sorted? xs)
  (define (sort x xs)
    (cond [(null? xs) #t]
          [(> x (car xs)) #f]
          [else (sort (car xs) (cdr xs))]))
  (sort (car xs) (cdr xs)))
(sorted? (list 1 2 5 4))