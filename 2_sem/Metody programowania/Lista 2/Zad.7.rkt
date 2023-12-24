#lang racket
(define (suffixes xs)
  (define (suffixes-helper xs)
    (cond
      [(null? xs) '(())] ; 
      [else (cons xs (suffixes-helper (cdr xs)))])
  )
  (suffixes-helper xs)
)
( suffixes ( list 1 2 3 4) )
(cons ( list 1 2 3 4) '(2 3))