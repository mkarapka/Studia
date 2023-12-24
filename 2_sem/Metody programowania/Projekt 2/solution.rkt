#lang racket
(require data/heap)
(provide sim? wire?
         (contract-out
          [make-sim        (-> sim?)]
          [sim-wait!       (-> sim? positive? void?)]
          [sim-time        (-> sim? real?)]
          [sim-add-action! (-> sim? positive? (-> any/c) void?)]

          [make-wire       (-> sim? wire?)]
          [wire-on-change! (-> wire? (-> any/c) void?)]
          [wire-value      (-> wire? boolean?)]
          [wire-set!       (-> wire? boolean? void?)]

          [bus-value (-> (listof wire?) natural?)]
          [bus-set!  (-> (listof wire?) natural? void?)]

          [gate-not  (-> wire? wire? void?)]
          [gate-and  (-> wire? wire? wire? void?)]
          [gate-nand (-> wire? wire? wire? void?)]
          [gate-or   (-> wire? wire? wire? void?)]
          [gate-nor  (-> wire? wire? wire? void?)]
          [gate-xor  (-> wire? wire? wire? void?)]

          [wire-not  (-> wire? wire?)]
          [wire-and  (-> wire? wire? wire?)]
          [wire-nand (-> wire? wire? wire?)]
          [wire-or   (-> wire? wire? wire?)]
          [wire-nor  (-> wire? wire? wire?)]
          [wire-xor  (-> wire? wire? wire?)]

          [flip-flop (-> wire? wire? wire? void?)]))


(struct sim ([time #:mutable] [queue #:mutable]))
(struct wire ([sim #:mutable] [value #:mutable] [events #:mutable]))


; ====Simulation======
(define (make-sim)
  (sim 0 (make-heap (lambda (x y) (<= (car x) (car y))))))

(define (sim-wait! smt time)
  (let ([heap (sim-queue smt)])
  (when (> (heap-count heap) 0)
    (when (<= (car (heap-min heap)) (+ (sim-time smt) time))
      (begin
        (set-sim-time! smt (car (heap-min heap)))
        ((cdr (heap-min heap)))
        (heap-remove-min! heap)
        (sim-wait! smt time))))
  (set-sim-time! smt (+ (sim-time smt) time))))

(define (sim-add-action! s time fun)
  (heap-add! (sim-queue s) (cons (+ (sim-time s) time) fun)))

;======Wires=functions=======
(define (make-wire s) (wire s #f '()))

(define (wire-on-change! wire fun)
  (begin
    (set-wire-events! wire
    (cons fun (wire-events wire)))
    (fun)))  

(define (wire-set! wire new-signal)
  (when (not (eq? (wire-value wire) new-signal))
    (begin
    (set-wire-value! wire new-signal)
    (for-each (lambda (fun) (fun))
              (wire-events wire)))))
;======Gates========

(define (r-signal op p q)
  (cond
    [(equal? op 'and) (and p q)]
    [(equal? op 'nand) (not (and p q))]
    [(equal? op 'or) (or p q)]
    [(equal? op 'nor) (not (or p q))]
    [(equal? op 'xor) (and (or p q) (not (and p q)))]))

(define (create-gate out in1 in2 wait fun)
  (define (event) (wire-set! out
                  (r-signal fun (wire-value in1) (wire-value in2))))
  (begin
    (wire-on-change! in1 (lambda ()
       (sim-add-action! (wire-sim out) wait event)))
    (wire-on-change! in2 (lambda ()
        (sim-add-action! (wire-sim out) wait event)))))

(define (gate-not out in)
  (define (event) (wire-set! out (not (wire-value in))))
  (wire-on-change! in (lambda ()
        (sim-add-action! (wire-sim out) 1 event))))

(define (gate-and out in1 in2)
  (create-gate out in1 in2 1 'and))

(define (gate-nand out in1 in2)
  (create-gate out in1 in2 1 'nand))
    

(define (gate-or out in1 in2)
  (create-gate out in1 in2 1 'or))


(define (gate-nor out in1 in2)
  (create-gate out in1 in2 1 'nor))


(define (gate-xor out in1 in2)
  (create-gate out in1 in2 2 'xor))

;====Wires=======
  (define (wire-not in)
    (define new-w (make-wire (wire-sim in)))
    (begin
              (gate-not new-w in)
              new-w))

  (define (wire-and in1 in2)
    (define new-w (make-wire (wire-sim in1)))
    (begin
           (gate-and new-w in1 in2)
           new-w))

  (define (wire-nand in1 in2)
    (define new-w (make-wire (wire-sim in1)))
    (begin
           (gate-nand new-w in1 in2)
           new-w))
  
  (define (wire-or in1 in2)
    (define new-w (make-wire (wire-sim in1)))
    (begin
           (gate-or new-w in1 in2)
           new-w))
  
  (define (wire-nor in1 in2)
    (define new-w (make-wire (wire-sim in1)))
    (begin
           (gate-nor new-w in1 in2)
           new-w))
  
  (define (wire-xor in1 in2)
    (define new-w (make-wire (wire-sim in1)))
    (begin
           (gate-xor new-w in1 in2)
           new-w))
;============================
(define (bus-set! wires value)
  (match wires
    ['() (void)]
    [(cons w wires)
     (begin
       (wire-set! w (= (modulo value 2) 1))
       (bus-set! wires (quotient value 2)))]))

(define (bus-value ws)
  (foldr (lambda (w value) (+ (if (wire-value w) 1 0) (* 2 value)))
         0
         ws))

(define (flip-flop out clk data)
  (define sim (wire-sim data))
  (define w1  (make-wire sim))
  (define w2  (make-wire sim))
  (define w3  (wire-nand (wire-and w1 clk) w2))
  (gate-nand w1 clk (wire-nand w2 w1))
  (gate-nand w2 w3 data)
  (gate-nand out w1 (wire-nand out w3)))
