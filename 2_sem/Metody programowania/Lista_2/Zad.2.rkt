#lang racket
(define (fib n)
  (cond [(<= n 0) 0]
        [(= n 1) 1]
        [else (+ (fib (- n 1)) (fib (- n 2)))]))
(fib 8)

(define (fib-iter n)
  (define (it n acc a b)
    (cond [(= n 0) 0]
          [(= n 1) 1]
          [(if (= acc n) (+ a b) (it n (+ acc 1) b (+ a b)))]))
  (it n 2 0 1))
(fib-iter 8)
    
    