; (define-macro (list-of map-expr for var in lst if filter-expr)
;   (list 'map (list 'lambda (list var) map-expr) (list 
;         'filter (list 'lambda (list var) filter-expr) lst)
;   )
; )

(define-macro (list-of map-expr for var in lst . predic)
  (define (my-predic lst-predic) (if (null? lst-predic) (list 'if #t) lst-predic     )            )
  (list 'map (list 'lambda (list var) map-expr) (list 
        'filter (list 'lambda (list var) (car (cdr (my-predic predic)))) lst)
  )
)