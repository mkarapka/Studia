#lang plait

(define-type (Form 'a)
  (var [x : 'a])
  (botF))

(define (bindM [x : (Form 'a)] f) : (Form 'a)
  (type-case (Form 'a) x
    [(var x) (f(var x))]
    [(botF) (botF)]))
(define (foo m)
  (bindM m (lambda (a) a)))
(define wyr
  (let ([x 2])
    (let ([x 3]) (display x))))