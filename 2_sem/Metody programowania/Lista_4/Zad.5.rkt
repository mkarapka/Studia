#lang racket
(define-struct leaf () #:transparent)
(define-struct node (l elem r) #:transparent)
(define xs (list 1 5 2 3 8 6))
;modyfikacja kodu z wykładu
(define (insert-bst x t)
  (cond [(leaf? t) (node (leaf) x (leaf))]
        [(node? t)
         (cond   [(< x (node-elem t))
                 (node (insert-bst x (node-l t))
                       (node-elem t)
                       (node-r t))]
                [else
                 (node (node-l t)
                       (node-elem t)
                       (insert-bst x (node-r t)))])]))
;definicja treesort
(define (treesort xs)
  
  (define (create-tree xs)
    (define (step acc xs)
      (if (null? xs)
          acc
          (step (insert-bst
          (car xs) acc) (cdr xs))))
    (step (leaf) xs ))
  
  (define (fold-tree f x t)
    (cond [(leaf? t) x]
          [(node? t)
           (f (node-elem t)
              (fold-tree f x (node-l t))
              (fold-tree f x (node-r t)))]))
  
  (define (flatten tree)
    (fold-tree (lambda (x l r)
        (append l (cons x r))) '() tree))
  
  (let([drz (create-tree xs)])
     (flatten drz)))
(treesort xs)
        

    