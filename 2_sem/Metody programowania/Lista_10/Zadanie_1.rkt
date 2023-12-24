#lang plait

;; abstract syntax -------------------------------

(define-type Op
  (add)
  (sub)
  (mul)
  (div))

(define-type Exp
  (numE [n : Number])
  (opE [op : Op] [l : Exp] [r : Exp]))

;; parse ----------------------------------------

; ZAD_1 - początek
(define (parse [s : S-Exp]) : Exp
  (cond
    [(s-exp-match? `NUMBER s)
     (numE (s-exp->number s))]
    
    [(s-exp-match? `{SYMBOL ANY ...} s)
     (parse-list (parse-op (s-exp->symbol (first (s-exp->list s))))
                  (rest (s-exp->list s)))]
    [else (error 'parse "invalid input")]))

(define (parse-list oprt [xs : (Listof S-Exp)])
  (cond
    [(empty? xs) (numE 0)]
    [(= (length xs) 1) (parse (first xs))]
    [else (opE oprt (opE oprt (parse (first xs)) (parse (second xs)))
               (parse-list oprt (rest (rest xs))))]))
                   
; ZAD_1 - koniec
(define (parse-op [op : Symbol]) : Op
  (cond
    [(eq? op '+) (add)]
    [(eq? op '-) (sub)]
    [(eq? op '*) (mul)]
    [(eq? op '/) (div)]
    [else (error 'parse "unknown operator")]))

(module+ test
  (test (parse `2)
        (numE 2))
  (test (parse `{+ 2 1})
        (opE (add) (numE 2) (numE 1)))
  (test (parse `{* 3 4})
        (opE (mul) (numE 3) (numE 4)))
  (test (parse `{+ {* 3 4} 8})
        (opE (add)
             (opE (mul) (numE 3) (numE 4))
             (numE 8)))
  (test (parse `{+ 1})
            (numE 1))
  (test/exn (parse `{^ 1 2})
            "unknown operator"))
  
;; eval --------------------------------------

(define-type-alias Value Number)

(define (op->proc [op : Op]) : (Value Value -> Value)
  (type-case Op op
    [(add) +]
    [(sub) -]
    [(mul) *]
    [(div) /]))

(define (eval [e : Exp]) : Value
  (type-case Exp e
    [(numE n) n]
    [(opE o l r) ((op->proc o) (eval l) (eval r))]))

(define (run [e : S-Exp]) : Value
  (eval (parse e)))



;; printer ———————————————————————————————————-

(define (print-value [v : Value]) : Void
  (display v))

(define (main [e : S-Exp]) : Void
  (print-value (eval (parse e))))