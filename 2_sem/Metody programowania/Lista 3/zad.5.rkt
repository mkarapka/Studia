#lang racket
(require rackunit)
(define (build-list n f)
  (define (it i acc)
    (if (equal? i -1)
        acc
        (it (- i 1) (cons (f i) acc))))
  (it (- n 1) '()))

;1
(define (f x) (+ 1 x))
(build-list 6 f)
;negatives
(define (negatives n)
  (build-list n
     (lambda (x) (* -1 (+ 1 x)))))
(negatives 6)
;reciprocals
(define (reciprocals n)
  (build-list n
     (lambda (x) (/ 1 (+ 1 x)))))
(reciprocals 6)
;even
(define (evens n)
  (build-list n
     (lambda (x) (* 2 x))))
(evens 6)

;identifyM
(define (identyfyM n)
  (build-list n
     (lambda (x) (string-append (make-string (- n (string-length (number->string x 2))) #\0)
                                (number->string x 2)))))
(identyfyM 6)
;make-string 3 #\a(string-append 
  

        
                
       