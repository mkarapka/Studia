#lang plait
;; defining types
(define-type Op
  (add) (sub) (mult) (leq))

(define-type Exp
  (numE [n : Number])
  (varE [x : Symbol])
  (opE [op : Op] [e1 : Exp] [e2 : Exp])
  (ifzE [e0 : Exp] [e1 : Exp] [e2 : Exp])
  (letE [x : Symbol] [e1 : Exp] [e2 : Exp])
  (fE [xs : (Listof Symbol)] [e : Exp])
  (appE [x : Symbol] [xs : (Listof Exp)])
  (defE [fs : (Listof (Symbol * Exp))] [e : Exp]))

;; parser
(define (parse-start [s : S-Exp]) : Exp
  (cond
    [(s-exp-match? `{define {{fun SYMBOL {SYMBOL ...} = ANY} ...} for ANY} s)
     (defE (map fun-parse (s-exp->list (second (s-exp->list s)))) (parse (fourth (s-exp->list s))))]
    [else (error 'parse "invalid input")]))
     
(define (fun-parse [s : S-Exp]) : (Symbol * Exp)
   (let ([psd-fun (fE (map s-exp->symbol
        (s-exp->list (third (s-exp->list s))))
        (parse (fourth (rest (s-exp->list s)))))])
     (if (any-free?  (fE-xs psd-fun) (all-vars (fE-e psd-fun)))
         (error 'fun-parse "free variables")
         (pair (s-exp->symbol (second (s-exp->list s))) psd-fun))))
     
(define (any-free? [fun : (Listof Symbol)]  [lst :  (Listof Symbol)]) : Boolean
  (cond
    [(empty? lst) #t]
    [(member (first lst) fun) #f]
    [else (any-free? fun (rest lst))]))

(define (v-remove [x : 'a] [lst : (Listof 'a)]) : (Listof 'a)
  (filter (λ (elem) (not (equal? elem x))) lst))

(define (all-vars [e : Exp]) : (Listof Symbol)
    (type-case Exp e
      [(numE n) empty]
      [(varE x) (list x)]
      [(opE op e1 e2) (append (all-vars e1) (all-vars e2))]
      [(ifzE e0 e1 e2) (append (all-vars e0) (append (all-vars e1) (all-vars e2)))]
      [(appE x xs) (foldr (λ (x y) (append y (all-vars x))) empty xs)]
      [(letE x e1 e2) (append (all-vars e1) (v-remove x (all-vars e2)))]
      [else (error 'all-vars "invalid type")]))

(define (parse [s : S-Exp]) : Exp
  (cond
    [(s-exp-match? `NUMBER s)
     (numE (s-exp->number s))]
    
    [(s-exp-match? `{ANY SYMBOL ANY} s)
     (opE (parse-op (s-exp->symbol (second (s-exp->list s))))
          (parse (first (s-exp->list s)))
          (parse (third (s-exp->list s))))]
    [(s-exp-match? `{ifz ANY then ANY else ANY} s)
     (ifzE (parse (second (s-exp->list s)))
          (parse (fourth (s-exp->list s)))
          (parse (fourth (rest (rest (s-exp->list s))))))]
    [(s-exp-match? `{let SYMBOL be ANY in ANY} s)
     (letE (s-exp->symbol (second (s-exp->list s)))
           (parse (fourth (s-exp->list s)))
           (parse (fourth (rest (rest (s-exp->list s))))))]
    [(s-exp-match? `{SYMBOL {ANY ...}} s)
     (appE (s-exp->symbol (first (s-exp->list s)))
           (map parse (s-exp->list (second (s-exp->list s)))))]
    [(s-exp-match? `SYMBOL s)
     (varE (s-exp->symbol s))]
    [else (error 'parse "invalid input")]))

(define (parse-op [op : Symbol]) : Op
  (cond
    [(eq? op '+) (add)]
    [(eq? op '-) (sub)]
    [(eq? op '*) (mult)]
    [(eq? op '<=) (leq)]
    [else (error 'parse "unknown operator")]))

;; environments
(define-type Box
  (fB [xs : (Listof Symbol)] [e : Exp])
  (valB [v : Value]))

(define-type Binding
  (bind [name : Symbol]
        [bx : Box]))

(define-type-alias Env (Listof Binding))
(define mt-env empty)

(define (ex-lst [env : Env] [lst : (Listof (Symbol * Box))]) : Env
  (foldl (λ (pair acc) (extend-env acc
           (fst pair) (snd pair))) env lst))

(define (extend-env [env : Env] [x : Symbol] [bx : Box]) : Env
  (cons (bind x bx) env))

(define (lookup-env [n : Symbol] [env : Env]) : Box
  (type-case (Listof Binding) env
    [empty (error 'lookup "unbound variable")]
    [(cons b rst-env) (cond
                        [(eq? n (bind-name b))
                         (bind-bx b)]
                        [else (lookup-env n rst-env)])]))
;; eval
(define-type-alias Value Number)

(define (eval [e : Exp] [env : Env]) : Box
  (type-case Exp e
    [(numE n)
     (valB n)]
    [(varE x) (lookup-env x env)]
    [(defE fs e)
     (let ([lst (map (λ (x) (pair (fst x) (eval (snd x) env))) fs)])
     (eval e (ex-lst env lst)))]
    [(opE op e1 e2)
     (valB ((op->proc op) (valB-v (eval e1 env)) (valB-v (eval e2 env))))]
    [(ifzE e0 e1 e2)
     (if (= (valB-v (eval e0 env)) 0)
         (eval e1 env)
         (eval e2 env))]
    [(letE x e1 e2)
     (let ([v1 (eval e1 env)])
       (eval e2 (extend-env env x v1)))]
    [(fE xs e) (fB xs e)]
    [(appE x xs) (apply (lookup-env x env) xs env)]))

(define (apply [f : Box] [xs : (Listof Exp)] [env : Env]) : Box
  (eval (fB-e f) (ex-lst env (zip (fB-xs f)
         (map (λ (a) (eval a env)) xs)))))

(define (zip lst1 lst2)
  (if (empty? lst1) empty
      (cons (pair (first lst1) (first lst2))
            (zip (rest lst1) (rest lst2)))))

(define (leq-fun [v1 : Value] [v2 : Value]) : Value
  (if (<= v1 v2) 0 1))

(define (op->proc op) : (Value Value -> Value)
  (type-case Op op
    [(add) +]
    [(sub) -]
    [(mult) *]
    [(leq) (λ (x y) (leq-fun x y))]))


;; run
(define (run [s : S-Exp]) : Value
  (valB-v (eval (parse-start s) empty)))