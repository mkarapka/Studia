#lang racket
(require rackunit)
(define (elem? x xs)
  (if (null? xs) #f
  (if (equal? (car xs) x) #t (elem? x (cdr xs)))))
(elem? 6 (list 1 4 5 2 6 7))
