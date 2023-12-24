#lang plait

(module+ test
  (print-only-errors #t))

;; abstract syntax -------------------------------
;ZAD_5 - typ
(define-type Op
  (add)
  (sub)
  (mul)
  (div)
  (eql)
  (leq))

(define-type List-Exp
  (consE [l : Exp] [r : Exp])
  (carE [ls : Exp])
  (cdrE [ls : Exp])
  (null?E [ls : Exp])
  (nullE )
  (listEx [elems : (Listof Exp)]))


(define-type Exp
  (numE [n : Number])
  (opE [op : Op]
       [l : Exp]
       [r : Exp])
  (ifE [b : Exp]
       [l : Exp]
       [r : Exp])
  (condE [cs : (Listof (Exp * Exp))])
  (listE [ls : List-Exp]))
;########################################
;; parse ----------------------------------------
;ZAD_5 - parser
(define (parse [s : S-Exp]) : Exp
  (cond
    [(s-exp-match? `NUMBER s)
     (numE (s-exp->number s))]
    [(s-exp-match? `{if ANY ANY ANY} s)
     (ifE (parse (second (s-exp->list s)))
          (parse (third (s-exp->list s)))
          (parse (fourth (s-exp->list s))))]
    [(s-exp-match? `{cond ANY ...} s)
     (condE (parse-cond (rest (s-exp->list s))))]
    ;; parsowanie list
    [(s-exp-match? `{cons ANY ANY} s)
     (listE (consE
             (parse (second (s-exp->list s)))
             (parse (third (s-exp->list s)))))]
    [(s-exp-match? `{car ANY} s)
     (listE (carE
             (parse (second (s-exp->list s)))))]
    [(s-exp-match? `{cdr ANY} s)
     (listE (cdrE
             (parse (second  (s-exp->list s)))))]
    [(s-exp-match? `{ null? ANY} s)
     (listE (null?E
             (parse (second (s-exp->list s)))))]
    [(s-exp-match? `null  s)
     (listE (nullE))]
    [(s-exp-match? `{list ANY ...} s)
     (listE (listEx (map parse (rest (s-exp->list s)))))]
    ;;
    [(s-exp-match? `{SYMBOL ANY ANY} s)
     (opE (parse-op (s-exp->symbol (first (s-exp->list s))))
          (parse (second (s-exp->list s)))
          (parse (third (s-exp->list s))))]
    [else (error 'parse "invalid input")]))
;############################################
(define (parse-cond [ss : (Listof S-Exp)]) : (Listof (Exp * Exp))
  (type-case (Listof S-Exp) ss
    [empty
     empty]
    [(cons s ss)
     (if (s-exp-match? `{ANY ANY} s)
         (cons (pair (parse (first (s-exp->list s)))
                     (parse (second (s-exp->list s))))
               (parse-cond ss))
         (error 'parse "invalid input: cond"))]))

(define (parse-op [op : Symbol]) : Op
  (cond
    [(eq? op '+) (add)]
    [(eq? op '-) (sub)]
    [(eq? op '*) (mul)]
    [(eq? op '/) (div)]
    [(eq? op '=) (eql)]
    [(eq? op '<=) (leq)]
    [else (error 'parse "unknown operator")]))
                
  
;; eval --------------------------------------

(define-type Value
  (numV [n : Number])
  (boolV [b : Boolean])
  (listV [ls : (Listof Value)])) 

(define (op-num-num->proc [f : (Number Number -> Number)]) : (Value Value -> Value)
  (λ (v1 v2)
    (type-case Value v1
      [(numV n1)
       (type-case Value v2
         [(numV n2)
          (numV (f n1 n2))]
         [else
          (error 'eval "type error")])]
      [else
       (error 'eval "type error")])))

(define (op-num-bool->proc [f : (Number Number -> Boolean)]) : (Value Value -> Value)
  (λ (v1 v2)
    (type-case Value v1
      [(numV n1)
       (type-case Value v2
         [(numV n2)
          (boolV (f n1 n2))]
         [else
          (error 'eval "type error")])]
      [else
       (error 'eval "type error")])))

(define (op->proc [op : Op]) : (Value Value -> Value)
  (type-case Op op
    [(add) (op-num-num->proc +)]
    [(sub) (op-num-num->proc -)]
    [(mul) (op-num-num->proc *)]
    [(div) (op-num-num->proc /)]
    [(eql) (op-num-bool->proc =)]
    [(leq) (op-num-bool->proc <=)]))

;ZAD_5 - Interpreter
(define (eval [e : Exp]) : Value
  (type-case Exp e
    [(numE n) (numV n)]
    [(opE o l r) ((op->proc o) (eval l) (eval r))]
    [(ifE b l r)
     (type-case Value (eval b)
       [(boolV v)
        (if v (eval l) (eval r))]
       [else
        (error 'eval "type error")])]
    [(condE cs)
     (eval (cond->if cs))]
    ;; lista
    [(listE ls)
     (type-case List-Exp ls  
       [(consE l r)
        (type-case Value (eval r) ;; drugi argument consa ma byc listą
          [(listV ls)
           (listV (cons (eval l) ls))]
          [else (error 'eval "type error")])]
         
       [(carE ls)
        (type-case Value (eval ls)
          [(listV ls)
           (first ls)]
          [else (error 'eval "type error")])]
         
       [(cdrE ls)
        (type-case Value (eval ls)
          [(listV ls)
           (listV (rest ls))]
          [else (error 'eval "type error")])]
         
       [(null?E ls)
        (type-case Value (eval ls)
          [(listV ls)
           (boolV (empty? ls))]
          [else (error 'eval "type error")])]
         
       [(nullE)
        (listV empty)]
       
       [(listEx ls)
        (listV (map eval ls))])]))
; ###################################
(define (cond->if [cs : (Listof (Exp * Exp))]) : Exp
  (type-case (Listof (Exp * Exp)) cs
    [empty
     (numE 42)]
    [(cons c cs)
     (ifE (fst c)
          (snd c )
          (cond->if cs))]))

(define (run [e : S-Exp]) : Value
  (eval (parse e)))

(module+ test
  (test (run `2)
        (numV 2))
  (test (run `{+ 2 1})
        (numV 3))
  (test (run `{* 2 1})
        (numV 2))
  (test (run `{+ {* 2 3} {+ 5 8}})
        (numV 19))
  (test (run `{= 0 1})
        (boolV #f))
  (test (run `{if {= 0 1} {* 3 4} 8})
        (numV 8))
  (test (run `{cond {{= 0 1} {* 3 4}}
                    {{= 1 1} 8}})
        (numV 8)))

;; printer ———————————————————————————————————-

(define (ListV->Listof-Symbol [ls : (Listof Value)]) : (Listof Symbol)
  (type-case (Listof Value) ls
    [empty empty]
    [(cons v ls)
     (cons (string->symbol (value->string v)) (ListV->Listof-Symbol ls))]))

(define (listV->string [ls : (Listof Value)]) : String
  (to-string (ListV->Listof-Symbol ls)))

(define (value->string [v : Value]) : String
  (type-case Value v
    [(numV n) (to-string n)]
    [(boolV b) (if b "true" "false")]
    [(listV ls) (listV->string ls)]))

(define (print-value [v : Value]) : Void
  (display (value->string v)))

(define (main [e : S-Exp]) : Void
  (print-value (eval (parse e))))
