#lang plait
;#1
(define (f1 g a)
   g)
;#2
(define (f2 g h)
  (lambda (x) (g x (h x))))
;#3
(define (f3 f)
  (f (lambda (x)
       (f (lambda (x) x)))))
;#4
(define (f4 f g x)
  ((lambda (x) (pair (f x) (g x))) x))
  
;#5
(define (f5 [f : ('a -> (Optionof('a * 'b)))] [a : 'a])
  (list (snd (some-v (f a)))))
  