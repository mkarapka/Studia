#lang racket
(define morse-dict
  (make-hash '((#\a "._") (#\b "_...") (#\c "_._.") (#\d "_..")
               (#\e ".") (#\f ".._.") (#\g "__.") (#\h "....")
               (#\i "..") (#\j ".___") (#\k "_._") (#\l "._..")
               (#\m "__") (#\n "_.") (#\o "___") (#\p ".__.")
               (#\q "--.-") (#\r ".-.") (#\s "...") (#\t "-")
               (#\u ".._") (#\v "..._") (#\w ".__") (#\x "_.._")
               (#\y "_.__") (#\z "__..") (#\1 ".____") (#\2 "..___")
               (#\3 "...__") (#\4 "...._") (#\5 ".....") (#\6 "_....")
               (#\7 "__...") (#\8 "___..") (#\9 "____.") (#\0 "_____")))) 


(define (morse-code txt)
  (define (morse-text txt bool)
     (cond [(null? txt) null]
           [(char-whitespace? (car txt))
            (if bool
            (cons " "  (cons " " (morse-text (cdr txt) #f)))
            (morse-text (cdr txt) #f))]
           [else (cons (string-join (hash-ref morse-dict (car txt)))
                       (morse-text (cdr txt) #t))]))
    
  (string-join (morse-text (string->list (string-downcase txt)) #t)))
 (morse-code "Metody Programowania")
