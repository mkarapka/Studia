#lang racket
(define-struct leaf () #:transparent)
(define-struct node (l elem r) #:transparent)
;exemplary tree
( define t
( node
( node ( leaf ) 2 ( leaf ) )
5
( node ( node ( leaf ) 6 ( leaf ) )
8
( node ( leaf ) 9 ( leaf ) ) ) ) )
;define fold-tree
(define (fold-tree f x t)
  (cond [(leaf? t) x]
        [(node? t)
         (f (node-elem t)
            (fold-tree f x (node-l t))
            (fold-tree f x (node-r t)))]))
;tree-sum
(define (tree-sum t)
  (define (tree-sum2 x y z)
    (+ x y z))  
  (fold-tree tree-sum2 0 t))
(tree-sum t)
;tree-flip
(define (tree-flip x left right)
  (node right x left))
(fold-tree tree-flip (leaf) t)
;tree-height
(define (tree-height t) 
  (define (tree-height2 x left right)
    (if (> left right)
        (+ 1 left)
        (+ 1 right)))
  (fold-tree tree-height2 0 t))
(tree-height t)
;tree-span
(define (tree-span t)
  (define (pick-x x left right) x)
  (define (tree-spanl t)
    (if (leaf? (node-l t))
        (fold-tree pick-x 0 t)
        (tree-spanl (node-l t))))
  (define (tree-spanr t)
    (if (leaf? (node-r t))
        (fold-tree pick-x 0 t)
        (tree-spanr (node-r t))))
  (cons (tree-spanl t) (tree-spanr t)))
(tree-span t)
;flatten
(define (flatten tree)
  (fold-tree (lambda (x l r) (append l (cons x r))) '() tree))
(flatten t)

(define (tree-span-2 t)
  (define (pick-min x t)
    (if (leaf? (node-l t))
        (node-elem t)
        (pick-min x (node-l t))))
 
(define (pick-max x t)
    (if (leaf? (node-r t))
        (node-elem t)
        (pick-min x (node-r t))))
  (let ([x (pick-max 0 t)] [y (pick-min 0 t)]) (cons y x)))
  
(tree-span-2 t)
