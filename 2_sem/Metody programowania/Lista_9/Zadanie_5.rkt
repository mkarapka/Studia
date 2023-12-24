#lang racket
(define morse-dict
  (make-hash '(("._" #\a ) ("_..." #\b) ("_._." #\c) ("_.." #\d)
               ("." #\e) (".._." #\f) ("__." #\g) ("...." #\h)
               (".." #\i) (".___" #\j) ("_._" #\k) ("._.." #\l)
               ("__" #\m) ("_." #\n) ("___" #\o) (".__." #\p)
               ("__._" #\q) ("._." #\r) ("..." #\s) ("_" #\t)
               (".._" #\u) ("..._" #\v) (".__" #\w) ("_.._" #\x)
               ("_.__" #\y ) ("__.." #\z ) (".____" #\1) ("..___" #\2)
               ("...__" #\3) ("...._" #\4) ("....." #\5) ("_...." #\6)
               ("__..." #\7) ("___.." #\8) ("____." #\9) ("_____" #\0))))

(define (morse-decode txt)
  (define (code xs)
    (car (hash-ref morse-dict (list->string (reverse xs)))))
  
  (define (morse-text txt xs)
    (cond [(null? txt) (cons (code xs) null)]
          [(equal? #\space (car txt))
           (if (null? xs)
               (cons #\space (morse-text (cdr txt) null))
                   (cons (code xs)
                         (morse-text (cdr txt) null)))]
          [else (morse-text (cdr txt) (cons (car txt) xs))]))
  
  (list->string (morse-text (string->list txt) null)))

;(string->list "__ .__. .. ___ _____ .. ___ .. ___")
;(list->string '(#\_ #\_))
(morse-decode "__ .__.  ..___ _____ ..___ ..___" )
