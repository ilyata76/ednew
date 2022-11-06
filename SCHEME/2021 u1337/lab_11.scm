; Вопрос 3
(define (repeatedly-cube n x)
    (if (zero? n)
        x
        (let
            ((y (repeatedly-cube (- n 1) x)))
            (* y y y))))

; Вопрос 4
(define-macro (def func bindings body)
    `(define (,func ,@bindings) ,body)
)

; Вопрос 5
(define-macro (switch expr cases)
    (if (eq? (eval expr) (car (car cases))) 
        `,(car (cdr (car cases)))
        (list 'switch expr (cdr cases))
    
    )
)

(define-macro (list-of map-expr for var in lst . predic)
  (define (my-predic lst-predic) (if (null? lst-predic) (list 'if #t) lst-predic     )            )
  (list 'map (list 'lambda (list var) map-expr) (list 
        'filter (list 'lambda (list var) (car (cdr (my-predic predic)))) lst)
  )
)

; Вопрос 6
; (define (flatmap f x . rest)
;     (cond 
;         ( (null? x) nil)
;         ( (list? (f (car x)))   `( ,@(f (car x))  ,@(flatmap f (cdr x))  )   )
;         (else (cons (f (car x)) (flatmap f (cdr x))))
;     )
; )



(define (flatmap f x . lstnak )
    ( if (null? x) 
        (if (null? lstnak) lstnak (car lstnak))
        (let ( (lst (f (car x)))  )
            ( if (list? lst)
                (if (null? lstnak) (flatmap f (cdr x) (append lstnak lst)) (flatmap f (cdr x) (append (car lstnak) lst)))
                (if (null? lstnak) (flatmap f (cdr x) (append lstnak (list lst))) (flatmap f x (cdr x) (append (car lstnak) (list lst)))) 

            )
        )

    )
)

(define (expand lst) 
    (flatmap (lambda (x)
        (cond
            ( (eq? x 'x)   (list 'x 'r 'y 'f 'r)   )
            ( (eq? x 'y)   (list 'l 'f 'x 'l 'y)   )
            (else  (list x) )
        )
    )
    lst)
)

(define (interpret instr dist)
    (if (null? instr) (penup)
        (cond
            ((or (eq? (car instr) 'x) (eq? (car instr) 'y)) ( interpret (cdr instr) dist                    )  )
            ((eq? (car instr) 'f)                           (begin (forward dist)  (interpret (cdr instr) dist)  )  )
            ((eq? (car instr) 'l)                           (begin (left 90)  (interpret (cdr instr) dist)       )  )
            ((eq? (car instr) 'r)                           (begin (right 90)  (interpret (cdr instr) dist)      )  )
        )
    ) 
)

(define (apply-many n f x)
  (if (zero? n)
      x
      (apply-many (- n 1) f (f x))))

(define (dragon n d)
  (interpret (apply-many n expand '(f x)) d))