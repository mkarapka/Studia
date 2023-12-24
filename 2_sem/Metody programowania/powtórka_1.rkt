#lang plait
(define (apply f a)
  (f a))
 ;(-> (-> a b c) (-> ( cons/c a b) c))

(define (fun f)
  (lambda (pair) (f (fst pair) (snd pair))))
(define-type Value
  (False)
  (consV [x : 'a] [b : Value]))

;(-> (-> b ( or/c false/c ( cons/c a b))) b ( listof a))



 ;(-> (-> a boolean?) ( listof a) ( cons/c ( listof a) ( listof a)))

(define (fun4 f as)
  (cons
   (foldl (lambda (x acc)
            (if (f x)
            (cons x acc)
            acc)) empty as)
   (foldl (lambda (x acc)
            (if (f x)
            acc
            (cons x acc))) empty as)))