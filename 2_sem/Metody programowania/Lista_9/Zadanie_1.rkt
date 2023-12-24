#lang racket
; <exp> ::= <term> | <exp> "+" <term> | <exp> "-" <term>
; <term> ::= <fact> | <term> "*" <fact> | <term> "/" <fact>
; <fact> ::= <unary> | <unary> "^" <fact>
; <unary> ::= <pow> | <pow> "!" 
; <pow> ::= <num> | "-" <num> | "(" <exp> ")"
; <num> ::= <int> | <float>
; <float> ::= <int> "." <int>
; <int> ::= <digit> | <digit> <int>
; <digit> ::= "0" | "1" | "2" | ... | "9"


