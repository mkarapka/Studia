#lang plait
;Zadanie 1
;Definicja indukcji ($)
;Niech P będzie taką włanością list,że:
;i) P(empty)
;ii) Dla każdej wartości x i każdej listy xs
;jeśli P(xs), to P((cons x xs))
;Wtedy dla dowolnej listy xs zachodzi P(xs)

;Dowód

;i)P(empty)
;h := (lambda (x) (f (g x)))
;(map f (map g empty)) ≡ (map f empty) ≡ empty ≡ (map h empty)

;ii) Dla dowolnych x i xs t,że (map f (map g xs)) ≡ (map (lambda (x) (f (g x))) xs)
;zachodzi (map f (map g (cons x xs))) ≡ (map (lambda (x) (f (g x))) (cons x xs))

;L ≡ (map f (map g (cons x xs))) ≡ (map f (cons (g x) (map g xs))) ≡ (cons (f (g x)) (map f (map g xs)))
;P ≡ (map (lambda (x) (f (g x))) (cons x xs))  ≡  (cons (f (g x)) (map (lambda (x) (f (g x)) xs)) ≡
; ≡ (cons (f (g x)) (map f (map g xs))) ≡ P
;========================================================================================================

;Zadanie 2
;Bez straty ogólności będziemy robić indukcje strukturalną względem xs
;Skorzystamy z ($)

;i)dla xs := empty P(xs) zachodzi, ponieważ
;(append empty ys) ≡ ys , zatem istnieje takie zs,że ys ≡ zs

;ii) Załóżmy, że (append xs ys) ≡ zs, pokażmy,że
;(append (cons x xs) ys) ≡ (cons x zs):
;(append (cons x xs) ys) ≡ (cons x (append xs ys)) ≡ (cons x zs)
;Zatem dla dowolnych list xs i ys istnieje lista zs taka, że (append xs ys) ≡ zs
;=========================================================================================

;Zadanie 3
( define-type ( NNF 'v )
( nnf-lit [ polarity : Boolean ] [ var : 'v ])
( nnf-conj [ l : ( NNF 'v ) ] [ r : ( NNF 'v ) ])
( nnf-disj [ l : ( NNF 'v ) ] [ r : ( NNF 'v ) ]) )

; Zasada Indukcji dla NNF
; Niech P będzie własnością formuły φ typu NNF, taką że
; (i) Dla φ będącego lit zachodzi P(φ)
; (ii) Dla φ będącego conj zakładając P(l) i P(r) zachodzi P(φ)
; (iii) Dla φ będącego disj zakładając P(l) i P(r) zachodzi P(φ)
; Wówczas dla dowlnego φ zachodzi P(φ)

;Definicja zbioru
;Niech F będzie najmniejszym takim zbiorem nad NNF, że:
;*v ∈ F
;**dla dowolnych φ i ψ ∈ F zachodzi (φ ∧ ψ)∈ F oraz (φ v ψ)∈ F

;Zasada indukcji
;Niech X ⊂_ F t.że:
; v ∈ X
; dla dowolnego φ i ψ ∈ X
; jeśli zachodzi (φ ∧ ψ)∈ X oraz (φ v ψ)∈ X
; Wtedy X = F
;========================================================================================

;Zadanie 4
;Defincja neg-nnf
(define (neg-nnf f)
  (cond
    [(nnf-lit? f) (if (eq? (nnf-lit-polarity f) #t)
          (nnf-lit #f (nnf-lit-var f)) (nnf-lit #t (nnf-lit-var f)))]
    
    [(nnf-conj? f) (nnf-conj (neg-nnf (nnf-conj-l f)) (neg-nnf (nnf-conj-r f)))]
    [(nnf-disj? f) (nnf-disj (neg-nnf (nnf-disj-l f)) (neg-nnf (nnf-disj-r f)))]))

(define formula (nnf-disj (nnf-conj (nnf-lit #f 'p) (nnf-lit #t 'q)) (nnf-lit #t 'r)))

;Dowód:
; Niech X ⊂_ F , X = {φ ∈ F | (neg-nnf (neg-nnf φ)) ≡ φ}
;*1)'v ∈ X, bo (neg-nnf (neg-nnf 'v)) ≡ (neg-nnf ~'v) ≡ 'v
;** Weźmy dowolne  φ i ψ i załóżmy, że φ i ψ ∈ X
;Rozbijmy to na przypadki:

;2) (φ ∧ ψ)∈ X
;(neg-nnf (neg-nnf conj) ≡ (neg-nnf (disj (neg-nnf-l) (neg-nnf-r))) ≡
; ≡ (conj (neg-nnf (neg-nnf-l)) (neg-nnf (neg-nnf-r))) ≡ (conj l r)

;3) (φ v ψ)∈ X
;(neg-nnf (neg-nnf disj)) ≡ (neg-nnf ( conj (neg-nnf-l) (neg-nnf-r)))
;≡ (disj (neg-nnf (neg-nnf-l)) (neg-nnf (neg-nnf-r)) ≡ (disj l r)

;Zatem na mocy zasady indukcji (neg-nnf (neg-nnf φ)) ≡ φ
; zachodzi dla dowolnej formuły φ.
;==================================================================================

;Zadanie 5

(define (eval-nnf val f)
  (cond
    [(nnf-lit? f) (if (nnf-lit-polarity f) (val (nnf-lit-var f)) (not (val (nnf-lit-var f))))]
    [(nnf-conj? f) (and (eval-nnf val (nnf-conj-l f)) (eval-nnf val (nnf-conj-r f)))]
    [(nnf-disj? f) (or (eval-nnf val (nnf-disj-l f)) (eval-nnf val (nnf-disj-r f)))]))

(define (exp-val x)
  (cond [(equal? x 'p) #t]
        [(equal? x 'q) #f]
        [(equal? x 'r) #f]
        [(equal? x 't) #f]))

;Zasada indukcji 
;Niech P będzie własnością φ t.że:
;* dla lit v zachodzi P(v)
;** dla dowolnego  φ i ψ jeślli
;zachodzi P(φ ∧ ψ) oraz P(φ v ψ)
;to P zachodzi dla dowolnego φ

;Dowód:
;*) L ≡ (eval-nnf σ (neg-nnf lit)) ≡ (eval-nnf σ (not lit)≡
; ≡ (not (σ lit))
;P ≡ (not (eval-nnf σ lit)) ≡ (not (σ lit)) ≡ L

;**) Rozpatrzmy przypaki
;1) L ≡ (eval-nnf σ (neg-nnf conj) ≡ (eval-nnf σ (neg-nnf conj))≡
;≡ (eval-nnf σ (disj (neg-nnf l) (neg-nnf r)))
;≡ (disj (not (eval-nnf σ l)) (neg-nnf (eval-nnf σ r)) ≡
; (or (not (eval-nnf σ l)) (not (eval-nnf σ r))
; P ≡ ((not (eval-nnf σ conj)) ≡ (not (and (eval-nnf σ l) (eval-nnf σ r)))
; ≡ (or (not (eval-nnf σ l)) (not (eval-nnf σ l)))

;2) L ≡ (eval-nnf σ (neg-nnf disj)) ≡ (eval-nnf σ (conj (neg-nnf l) (neg-nnf r))) ≡
;≡ (and (eval-nnf σ (neg-nnf l)) (eval-nnf σ (neg-nnf r))) 
;P ≡ (not (eval-nnf σ disj)) ≡ (not (or (eval-nnf σ l) (eval-nnf σ  r)))
;≡ (and (not (eval-nnf σ l)) (not (eval-nnf σ r))) ≡
;≡ (and (eval-nnf σ (neg-nnf l)) (eval-nnf σ (neg-nnf r)))
;=====================================================================================

;Zadanie 6
( define-type ( Formula 'v )
( var [ var : 'v ])
( neg [ f : ( Formula 'v ) ])
( conj [ l : ( Formula 'v ) ] [ r : ( Formula 'v ) ])
( disj [ l : ( Formula 'v ) ] [ r : ( Formula 'v ) ]) )

;#t - wystąpiła negacja, #f - wpp
(define (to-nnf f)
  (local ((define (set-neg f val)
            (cond
              [(var? f) (if (equal? val #t) (neg f) f)]
              [(neg? f) (if (equal? val #t)
                            (set-neg (neg-f f) #f) (set-neg (neg-f f) #t))]
              [(conj? f) (if (equal? val #t)
                             (disj (set-neg (conj-l f) val) (set-neg (conj-r f) val))
                             (conj (set-neg (conj-l f) val) (set-neg (conj-r f) val)))]
              [(disj? f) (if (equal? val #t)
                             (conj (set-neg (disj-l f) val) (set-neg (disj-r f) val))
                             (disj (set-neg (disj-l f) val) (set-neg (disj-r f) val)))])))
    (set-neg f #f)))


;Przykłady
(define form (disj (var 'p) (neg (conj (var 'q) (var 'r)))))
(define form2 (conj (var 'p) (neg (disj (var 'q) (var 'r)))))
(to-nnf form)
(to-nnf form2)
;L ≡ (map f (map g (cons x xs))) ≡ (map f (map (lambda (x) (g x)) (cons x xs))) ≡
; ≡ (map (f (lambda (x) (g x))) (cons x xs)) ≡ (map (lambda (x) (f (g x))) (cons x xs)) ≡ P
;==========================================================================================


