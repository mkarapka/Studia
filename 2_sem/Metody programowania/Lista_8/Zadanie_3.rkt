#lang racket

(provide
 mqueue?
 nonempty-mqueue/c
 double-list?
 (contract-out
  [mqueue-empty? (-> mqueue? boolean?)]
  [mqueue-make (-> mqueue?)]
  [mqueue-push-front (-> mqueue? any/c any/c)]
  [mqueue-push-back (-> mqueue? any/c any/c)]
  [mqueue-pop-front (-> nonempty-mqueue/c any/c )]
  [mqueue-pop-back (-> nonempty-mqueue/c any/c)]))

(struct mqueue
  ([front #:mutable]
   [back  #:mutable]))

(struct double-list
  ([prev #:mutable]
   [value #:mutable]
   [next #:mutable]))

(define (set-next! queue next)
  (set-double-list-next! queue next))

(define (set-prev! queue next)
  (set-double-list-prev! queue next))


 ;#1
(define (mqueue-empty? q)
  (and (null? (mqueue-front q))
       (null? (mqueue-back  q))))
(define nonempty-mqueue/c
  (and/c mqueue? (not/c mqueue-empty?)))

;#2
(define (mqueue-make)
  (mqueue null null))

;#3
(define (mqueue-push-front q x)
  (define p (double-list null x (mqueue-front q)))
  (if (mqueue-empty? q)
      (set-mqueue-back! q (double-list null x null))
      (set-next! (mqueue-front q) p))
  (set-mqueue-front! q p))

;#4
(define (mqueue-push-back q x)
  (define p (double-list (mqueue-back q) x null))
  (if (mqueue-empty? q)
      (set-mqueue-front! q (double-list null x null))
      (set-prev! (mqueue-back q) p))
  (set-mqueue-back! q p))

;#5
(define (mqueue-pop-front q)
  (define p (mqueue-front q))
  (set-mqueue-front! q (double-list-next p))
  (double-list-value p))

;#6
(define (mqueue-pop-back q)
  (define p (mqueue-back q))
  (set-mqueue-back! q (double-list-prev p))
  (double-list-value p))

