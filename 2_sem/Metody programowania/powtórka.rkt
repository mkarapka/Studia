#lang racket
(require rackunit)

(define/contract (fun4 f as)
  (parametric->/c [a] (-> (-> a boolean?) (listof a) (cons/c (listof a) (listof a))))
  (cons
   (foldr (lambda (x acc)
            (if (f x)
                (cons x acc)
                acc)) null as)
   (foldr (lambda (x acc)
            (if (f x)
                acc
                (cons x acc))) null as)))
(check-equal? (fun4 number? (list 1 "1" 2 "2")) '((1 2) "1" "2"))

(define (pom xs acc)
      (cond
        [(null? xs) acc]
        [else (pom (cdr xs) (foldr (lambda (x y)
                                     (if (= (car x) 42)
                                         (cons (cons (car xs) (cdr x)) y)
                                         (cons x y))) null xs))]))
(define (zip as bs)
  (let ([space (foldr (lambda (x y)
           (cons (cons 42 x) y)) null as)])
    (pom bs null)))
(zip '(1 2 3) '(a b))