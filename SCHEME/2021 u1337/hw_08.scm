; Вопрос 1
(define (reverse lst)
  ( define (rev_lst lst ost) 
    ( if (null? (cdr lst)) 
        (cons (car lst) ost)
        (rev_lst (cdr lst) (cons (car lst) ost))
    )    
  )
  ( if (null? lst) nil (rev_lst lst nil) )
)

; Вопрос 2 AASDFP;OGKDSFPOGKDFGPODFKGOPDFG
(define (longest-increasing-subsequence lst)
  ( define (lis lst prev)
    (cond 
      (    (and (null? (cdr lst)) (<= (car lst) prev))    nil                                          )
      (    (and (null? (cdr lst)) (> (car lst) prev))     (cons (car lst) nil)                         )
      (    (<= (car lst) prev)                            (lis (cdr lst) prev)                         )
      (    else                                           (cons (car lst) (lis (cdr lst) (car lst)))   )
    )
  )
  ( if (null? lst) nil (lis lst -1) )
)

(define (cadr s) (car (cdr s)))
(define (caddr s) (cadr (cdr s)))

; Дифференцирование
; derive возвращает производную EXPR по VAR
(define (derive expr var)
  (cond ((number? expr) 0)
        ((variable? expr) (if (same-variable? expr var) 1 0))
        ((sum? expr) (derive-sum expr var))
        ((product? expr) (derive-product expr var))
        ((exp? expr) (derive-exp expr var))
        (else 'Error)))

; переменные представляются символами
(define (variable? x) (symbol? x))
(define (same-variable? v1 v2)
  (and (variable? v1) (variable? v2) (eq? v1 v2)))

; числа сравниваются с помощью =
(define (=number? expr num)
  (and (number? expr) (= expr num)))

; суммы представляются списками, начинающимися с +.
(define (make-sum a1 a2)
  (cond ((=number? a1 0) a2)
        ((=number? a2 0) a1)
        ((and (number? a1) (number? a2)) (+ a1 a2))
        (else (list '+ a1 a2))))
(define (sum? x)
  (and (list? x) (eq? (car x) '+)))
(define (addend s) (cadr s))
(define (augend s) (caddr s))

; произведения представляются списками, начинающимися с *.
(define (make-product m1 m2)
  (cond ((or (=number? m1 0) (=number? m2 0)) 0)
        ((=number? m1 1) m2)
        ((=number? m2 1) m1)
        ((and (number? m1) (number? m2)) (* m1 m2))
        (else (list '* m1 m2))))
(define (product? x)
  (and (list? x) (eq? (car x) '*)))
(define (multiplier p) (cadr p))
(define (multiplicand p) (caddr p))

; Вопрос 3
(define (derive-sum expr var)
  (define A ( derive (cadr expr) var))
  (define B ( derive (caddr expr) var))
  (if (and (number? A) (number? B))   (+ A B)    (list '+ A B)       )
)

; Вопрос 4
(define (derive-product expr var)
  ( define lefo (derive (cadr expr) var) )
  ( define rigo (derive (caddr expr) var) )
  (cond 
        ((and (number? (cadr expr)) (number? (caddr expr)))     0                                  )
        ((and (number? lefo) (= lefo 0))      
            ( if (and (number? rigo) (= rigo 1)) (cadr expr) (list '* (cadr expr) rigo) )          )
        ((and (number? rigo) (= rigo 0))    
            ( if (and (number? lefo) (= lefo 1) ) (caddr expr) ( list '* lefo (caddr expr) ) )     )

        (else 
            (cond 
              ((and (number? lefo) (= lefo 1))    (list '+  (caddr expr) (list '* (cadr expr) rigo))                    )
              ((and (number? rigo) (= rigo 1))    (list '+ (list '* lefo (caddr expr)) (cadr expr))                     )
              (else                               (list '+ (list '* lefo (caddr expr)) (list '* (cadr expr) rigo))      )    
            )
        )
            
            
  )
)

; Вопрос 5
; возведение в степень представляется списком, начинающимся с ^.
(define (make-exp base exponent)
  (cond 
      ((number? base)      (if (number? exponent) (expt base exponent) (list '^ base exponent) )                  )
      ((number? exponent)  (if (= exponent 1)   base  
                          (if (= exponent 0)   1 (list '^ base exponent)   )  
                          )                 
      )
      (else                          (list '^ base exponent)         )
  
  )
)

(define (base exp)
  (if (and (list? exp) (eq? (car exp) '^)) (cadr exp) exp)
)

(define (exponent exp)
  (if (and (list? exp) (eq? (car exp) '^)) (caddr exp) 1)
)

(define (exp? exp)
  (if (and (list? exp) (eq? (car exp) '^)) #t #f)
)

(define x^2 (make-exp 'x 2))
(define x^3 (make-exp 'x 3))

; Вопрос 6
(define (derive-exp exp var)
  ( cond
    ((number? exp) 0)
    (else (list '* (exponent exp) (make-exp (base exp) (- (exponent exp) 1))    ))
  )
)