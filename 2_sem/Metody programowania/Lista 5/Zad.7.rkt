#lang plait
( define-type Prop
( var [ v : String ])
( conj [ l : Prop ] [ r : Prop ])
( disj [ l : Prop ] [ r : Prop ])
( neg [ f : Prop ]) )

;(free-vars (conj (var "p") (disj (var "q") (neg (var "r")))))

(define p (list 1 2 2 2 3 4))

(define (member? x xs)
  (cond
    [(empty? xs) #f]
    [(string=? x (first xs)) #t]
    [else (member? x (rest xs))]))

(define (rm xs)
  (local
    ((define (rm-duplicates xs xp) 
       (cond
         [(empty? xs) xp]
         [(member? (first xs) (rest xs)) (rm-duplicates (rest xs) xp)]
         [else (rm-duplicates (rest xs) (cons (first xs) xp))])))
     (rm-duplicates xs '())))



(define (free-vars p)
  (local
  ((define (free p)
    (cond
      [(var? p) (list (var-v p))]
      [(conj? p) (append (free (conj-l p)) (free (conj-r p)))]
      [(disj? p) (append (free (disj-l p)) (free (disj-r p)))]
      [(neg? p) (free (neg-f p))])))
(rm (free p))))

(free-vars (conj (var "p") (disj (var "q") (neg (var "r")))))

(free-vars (disj (var "p") (conj (var "q") (var "p"))))