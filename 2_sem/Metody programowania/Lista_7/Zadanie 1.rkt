#lang plait
;Zadanie 1
(define-type (Tree2-3 'a)
  (leaf)
  (node [l : (Tree2-3 'a)] [elem : 'a] [r : (Tree2-3 'a)])
  
  (node2 [l : (Tree2-3 'a)] [elem-l : 'a]
         [m : (Tree2-3 'a)]
         [elem-r : 'a] [r : (Tree2-3 'a)]))

(define (Tree23? t)
  (local ((define (count-r t sum)
            (cond [(leaf? t) 0]
                  [(node? t)
                   (if (and (equal? (count-r (node-l t) 0) (count-r (node-r t) 0))
                            (and (not (equal? (count-r (node-l t) 0) -1))
                                 (not (equal? (count-r (node-r t) 0) -1))))
                       (+ sum 1) -1)]
                  [(node2? t)
                   (if (and (and (equal? (count-r (node2-l t) 0) (count-r (node2-r t) 0))
                                 (equal? (count-r (node2-m t) 0) (count-r (node2-r t) 0)))
                            (and (and (not (equal? (count-r (node2-l t) 0) -1))
                                 (not (equal? (count-r (node2-r t) 0) -1)))
                                 (and (not (equal? (count-r (node2-m t) 0) -1))
                                      (not (equal? (count-r (node2-r t) 0) -1)))))
                       (+ sum 1) -1)])))
          (count-r t 0)))

  (define (bst? t)
  (local ((define (isbst max min t)
    (cond [(leaf? t) #t]
          [(node? t)
           (cond 
          [(or (< (node-elem t) min)
               (> (node-elem t) max))  #f]
          [(and (isbst (node-elem t) min (node-l t))
                (isbst max (node-elem t) (node-r t))) #t]
          [else #f])]
          [(node2? t)
           (cond
             [(> (node2-elem-r t) (node2-elem-l t)) #f]
             [(or (< (node2-elem-r t) min)
               (> (node2-elem-l t) max))  #f]
             [(and (and (isbst (node2-elem-r t) min (node2-l t))
                (isbst max (node2-elem-l t) (node2-r t)))
                   (isbst (node2-elem-l t) (node2-elem-r t) (node2-m t))) #t]
           [else #f])])))
  (isbst +inf.0 -inf.0 t)))
                                 
                                 