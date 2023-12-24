#lang racket
(require rackunit)
;Zbiór pusty
(define empty-set #f)
;zbiór sam singleton a
(define (singleton a)
  (lambda (x)
    (if(equal? x a)
     a null)) a)
(singleton 3)
;czy należy do zbioru
(define (s x) #t)
(define (in a s) (s a))
;suma zbiorów
(define (union s t)
  (or s t))
;iloczyn
(define (intersect s t)
  (and s t))

 