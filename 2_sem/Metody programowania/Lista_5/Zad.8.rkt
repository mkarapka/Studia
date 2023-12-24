#lang plait
( define-type Prop
( var [ v : String ])
( conj [ l : Prop ] [ r : Prop ])
( disj [ l : Prop ] [ r : Prop ])
( neg [ f : Prop ]) )


(define (eval env f)
  (cond
    [(var? f) (hash-ref env (var-v f))]
    [(conj? f) (and (eval env (conj-l f)) (eval env (conj-r f)))]
    [(disj? f) (or (eval env (disj-l f)) (eval env (disj-r f)))]
    [(neg? f) (not (eval env (neg-f f)))]))

     