#lang racket
;Zadanie 3
;bez kontraktu
(define  (suffixes xs)
  (if (null? xs)
      null
      (cons xs (suffixes (cdr xs)))))
;(suffixes (list 'm 'i 'k 'o 'l 'a 'j))
;z kontraktem
(define/contract (suffixes2 xs)
  (parametric->/c [a] (-> (listof a) (listof (listof a))))
  (if (null? xs)
      (cons null null)
      (cons xs (suffixes2 (cdr xs)))))
(suffixes2 (list 'm 'i 'k 'o 'l 'a 'j))


;(time (suffixes2 (range 3000)))
;(time (suffixes (range 3000)))

;Zadanie 4
;parametric->/c [a b] (-> a b A))
;#1
(define/contract (function1 x y)
(parametric->/c [a b] (-> a b a)) x)
;prametric->/c [a b c] (-> (-> A B c) (-> A b) a C))
;#2
(define/contract (function2 f g x)
  (parametric->/c [a b c] (-> (-> a b c) (-> a b) a c))
  (f x (g x)))

;prametric->/c [a b c] (-> (-> B c) (-> A b) (-> a C))
;#3

(define/contract (function3 f g)
  (parametric->/c [a b c] (-> (-> b c ) (-> a b ) (-> a c )))
  (lambda (x)
    (f (g x))))

;paramtetric->/c [a] (->(-> (-> a A) a ) A))
;#4
(define (function4 f)
  (parametric->/c [a] (-> (-> (-> a a ) a ) a))
  (f (lambda (x)
       (f (lambda (x) x)))))

;Zadanie 5
(define (foldl-map f a xs)
  (parametric->/c [a b] (-> (-> a b (listof a b) b (listof a) (listof a b))))
   (define (it a xs ys)
      (if (null? xs)
          (cons (reverse ys) a)
          (let [(p (f (car xs) a))]
            ( it (cdr p)
                 (cdr xs)
                 (cons (car p) ys)))))
   (it a xs null))
(foldl-map (lambda (x a) (cons a (+ a x))) 0 '(1 2 3) )


