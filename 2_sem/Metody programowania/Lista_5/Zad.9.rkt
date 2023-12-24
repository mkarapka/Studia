#lang plait
(define-type (Tree 'a)
  (leaf)
  (node [l : (Tree 'a)] [elem : 'a] [r : (Tree 'a)]))

( define-type Prop
( var [ v : String ])
( conj [ l : Prop ] [ r : Prop ])
( disj [ l : Prop ] [ r : Prop ])
( neg [ f : Prop ]) )

(define (create-tr xs)
  (local
    ((define (tr b xs)
      (if (empty? xs)
          (leaf)
          (node (tr #t (rest xs)) b
                (tr #f (rest xs))))))
    (node (tr #t xs) #f (tr #f xs))))




;(define xg (list (cons "p" #t) (cons "q" #f) (cons "r" #t)))
;(define x (make-hash (first xg)))
;(define (m-hs xs env)
  ;(cond
   ; [(empty? xs) env]
   ; [else (m-hs (rest xs) (hash-set! env (first xs)))]))
  
  


   