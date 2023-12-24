#lang racket
( define-struct table ( schema rows ) #:transparent )
( define-struct column-info ( name type ) #:transparent )

;tab1
( define cities
( table
( list ( column-info 'city 'string )
( column-info 'country 'string )
( column-info 'area 'number )
( column-info 'capital 'boolean ) )
( list ( list " Wroclaw " " Poland " 293 #f )
( list " Warsaw " " Poland " 517 #t )
( list " Poznan " " Poland " 262 #f )
( list " Berlin " " Germany " 892 #t )
( list " Munich " " Germany " 310 #f )
( list " Paris " " France " 105 #t )
( list " Rennes " " France " 50 #f ) ) ) )

;tab2
( define countries
( table
( list ( column-info 'country 'string )
( column-info 'population 'number ) )
( list ( list " Poland " 38)
( list " Germany " 83)
( list " France " 67)
( list " Spain " 47) ) ) )

;tab3
(define tab3 (table
 (list
  (column-info 'city 'string)
  (column-info 'country 'string)
  (column-info 'area 'number)
  (column-info 'capital 'boolean)
  (column-info 'country1 'string)
  (column-info 'population 'number))
 (list (list " Wroclaw " " Poland " 293 #f " Poland " 38)
   (list " Warsaw " " Poland " 517 #t " Poland " 38)
   (list " Poznan " " Poland " 262 #f " Poland " 38)
   (list " Berlin " " Germany " 892 #t " Germany " 83)
   (list " Munich " " Germany " 310 #f " Germany " 83)
   (list " Paris " " France " 105 #t " France " 67)
   (list " Rennes " " France " 50 #f " France " 67))))
;define type-of
(define (type-of x)
  (cond [(string? x) 'string]
        [(boolean? x) 'boolean]
        [(number? x) 'number]
        [(symbol? x) 'symbol]))

;table-insert
(define (table-insert row tab)
  (define (check-schema row t-schema)
    (cond
      [(and (empty? row) (empty? t-schema)) #t]
      [(or (empty? row) (empty? t-schema)) #f]
      [(equal? (type-of (first row)) (column-info-type (first t-schema)))
           (check-schema (rest row) (rest t-schema))]
      [else #f]))
  (if (check-schema row (table-schema tab))
      (table (table-schema tab) (append (table-rows tab) (list row)))
      (error "Błąd" row)))
(display "Zadanie 1\n") 
(table-rows ( table-insert ( list " Rzeszow " " Poland " 129 #f ) cities ))
;(check-schema ( list  " Poland " #f) (table-schema countries) )    
;(column-info-name (first (table-schema cities )))

;table-project
(define (table-project cols tab)
  
  (define (pom cols schema row)
    (cond
      [(empty? cols) null]
      [(equal? (first cols) (column-info-name (first schema)))
       (cons (first row) (pom (rest cols) (rest schema) (rest row)))]
      [else (pom cols (rest schema) (rest row))]))
   
  (define (create-rows cols schema rows xs)
    (if (empty? rows) xs
    (create-rows cols schema (rest rows)
      (cons (pom cols schema (first rows)) xs))))
  
  (define (create-schema cols schema)
    (cond
      [(empty? cols) null]
      [(equal? (first cols) (column-info-name (first schema)))
       (cons (first schema) (create-schema (rest cols) (rest schema)))]
      [else (create-schema cols (rest schema))]))
    
  (table (create-schema cols (table-schema tab))
         (reverse (create-rows cols (table-schema tab) (table-rows tab) '()))))
(display "Zadanie 2\n")
(table-project '( city country ) cities)
;(pom '() '( city country ) (table-schema cities) (first (table-rows cities)))

;table-rename
(define (table-rename col ncol tab)
  (define (pom col ncol schema)
  (cond
    [(empty? schema) null]
    [(equal? (column-info-name (first schema)) col)
     (cons (column-info ncol (column-info-type (first schema)))
           (pom col ncol (rest schema)))]
    [else (cons (first schema) (pom col ncol (rest schema)))]))
(table (pom col ncol (table-schema tab)) (table-rows tab)))

(display "Zadanie 3\n")
(table-rename 'city 'dupa cities)
;(pom 'city 'dupa (table-schema cities))

;table-sort
(define (table-sort cols tab)
  
  (define (key arg arg1)
  (define (boolean->int x)
    (if x 1 0))
  (cond [(string? arg) (string<? arg arg1)]
        [(boolean? arg) (< (boolean->int arg) (boolean->int arg1))]
        [(symbol? arg) (symbol<? arg arg1)]
        [(number? arg) (< arg arg1)]))
  
  (define (sml? ROW ROW1)
    (define (smaller? cols row row1 schema)
      (cond [(empty? cols)#t]
            [(equal? (column-info-name (first schema)) (first cols))
             (cond [(key (first row) (first row1)) #t]
                   [(key (first row1) (first row)) #f]
                   [else (smaller? (rest cols) ROW ROW1 (table-schema tab))])]
            [else (smaller? cols (rest row) (rest row1) (rest schema))]))
    (smaller? cols ROW ROW1 (table-schema tab)))
  
  (table (table-schema tab) (sort (table-rows tab) sml?)))

(display "Zadanie 4\n")
(table-sort '( country city ) cities)

;table-select
( define-struct and-f ( l r ) ) ; koniunkcja formuł
( define-struct or-f ( l r ) ) ; dysjunkcja formuł
( define-struct not-f ( e ) ) ; negacja formuły
( define-struct eq-f ( name val ) ) ; wartość kolumny name równa val
( define-struct eq2-f ( name name2 ) ) ; wartości kolumn name i name2 równe
( define-struct lt-f ( name val ) )

(define (table-select form tab)
  
  ;returnig value of searching column
  (define (val-row row schema name)
    (if (equal? (column-info-name (first schema)) name)
        (first row)
        (val-row (rest row) (rest schema) name)))
  
  ;execute function on searching value
  (define (search-column row schema name val f-cond)
    (f-cond val (val-row row schema name)))
  
  (define (pom row formula schema)
    (define (f-result formula)
      (cond [(and-f? formula)
             (and (f-result (and-f-l formula)) (f-result (and-f-r formula)))]
            [(or-f? formula)
             (or (f-result (or-f-l formula)) (f-result (or-f-r formula)))]
            [(not-f? formula) (not (f-result (not-f-e formula)))]
            
            [(eq-f? formula) (search-column row schema
             (eq-f-name formula) (eq-f-val formula) equal?)]
            [(eq2-f? formula) (search-column row schema (eq2-f-name formula)
             (val-row row schema (eq2-f-name2 formula)) equal?)]
            [(lt-f? formula)
             (search-column row schema (lt-f-name formula) (lt-f-val formula) >)]))
    (f-result formula))
  
(define (return-rows rows xs)
    (cond [(empty? rows) xs]
          [(pom (first rows) form (table-schema tab))
           (return-rows (rest rows) (cons (first rows) xs))]
          [else (return-rows (rest rows) xs)]))
  
  (table (table-schema tab) (return-rows (table-rows tab) null)))

(display "Zadanie 5\n")
(table-rows ( table-select ( and-f ( eq-f 'capital #t ) ( not-f ( lt-f 'area 300) ) ) cities ) )

;table-cross
(define (table-cross-join tab1 tab2)
  
  (define (new-rows row Rows xs)
    (if (empty? Rows) xs
        (new-rows row (rest Rows)
                  (cons (append row (first Rows)) xs))))

  (define (new-table-rows Rows1 Rows2 xs)
    (if (empty? Rows1) xs
        (new-table-rows (rest Rows1) Rows2
         (append (new-rows (first Rows1) Rows2 null) xs))))
(table (append (table-schema tab1) (table-schema tab2))
       (new-table-rows (table-rows tab1) (table-rows tab2) null)))


(display "Zadanie 6\n")
  ( table-cross-join cities
( table-rename 'country 'country2 countries ) )


;(new-table-rows (table-rows cities) (table-rows countries) null)
;(new-rows ( list " Spain " 47) (table-rows cities) null)

;table-natural-join
(display "Zadanie 7\n")
;tworzenie listy duplikatów
(define (create-cols tab1 tab2)
  
  (define (duplicated? word schema)
    (if (empty? schema) #f
        (if (equal? word (column-info-name (first schema))) #t
            (duplicated? word (rest schema)))))
  
  (define (pom schema1 schema2 xs)
    (cond [(empty? schema1) xs]
          [(duplicated? (column-info-name (first schema1)) schema2)
           (pom (rest schema1) schema2 (cons (column-info-name (first schema1)) xs))]
          [else (pom (rest schema1) schema2 xs)]))
  (pom (table-schema tab1) (table-schema tab2) null))

(define (table-natural-join tab1 tab2)

(define (duplicated? word schema)
    (if (empty? schema) #f
        (if (equal? word (column-info-name (first schema))) #t
            (duplicated? word (rest schema)))))
  
    (define (pom schema1 schema2)
      (cond [(empty? schema1) #f]
            [(duplicated? (column-info-name (first schema1)) schema2)
             (column-info-name (first schema1))]
            [else (pom (rest schema1) schema2)]))
    
  (define (add-number s-word)
    (string->symbol (string-append
                     (symbol->string s-word) "1")))

  (define (new-schema word schema)
    (cond [(empty? schema) null]
          [(equal? word (column-info-name (first schema)))
           (new-schema word (rest schema))]
          [else (cons (column-info-name (first schema))
                      (new-schema word (rest schema)))]))

  (define (word-natural word tab1 tab2)
    (define costam (table-select (eq2-f word (add-number word))
                                 (table-cross-join tab1
     (table-rename word (add-number word) tab2))))
    
    (define nowe (append (new-schema (string->symbol "") (table-schema tab1))
                       (new-schema word (table-schema tab2))))
   (table-project nowe costam))
  (define slowo (pom (table-schema tab1) (table-schema tab2)))
   
  
(word-natural slowo cities countries))
( table-natural-join cities countries )


  