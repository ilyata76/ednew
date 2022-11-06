;; Scheme ;;

; Вопрос 2
(define (over-or-under x y)
  ( car 
    ( cons
      ( cond
        ((> x y) 1)
        ((< x y) -1)
        (else 0)
      )
      nil 
    )
  )
)

;;; Тесты
;(over-or-under 1 2)
; -1
;(over-or-under 2 1)
; 1
;(over-or-under 1 1)
; 0

; Вопрос 3
(define (filter f lst)
  ( cond 
    ((= (length lst) 0) nil)
    ((f (car lst)) (cons (car lst) (filter f (cdr lst))))
    (else (filter f (cdr lst)))
  )
)


;;; Тесты
;(define (even? x)
;  (= (modulo x 2) 0))
;(filter even? '(0 1 1 2 3 5 8))
; (0 2 8)

; Вопрос 4
(define (make-adder num)
  (lambda (x) (+ num x))
)

;;; Тесты
;(define adder (make-adder 5))
;(adder 8)
; 13

; Вопрос 5
(define lst
  ( cons
    (cons 1 nil)
    (cons 2 (cons (cons 3 4) (cons 5 nil)))
  )
)

; Вопрос 6
(define (composed f g)
  (lambda (x) (f (g x)))
)

; Вопрос 7
(define (remove item lst)
  ( cond 
    ((null? lst) nil)
    ((= item (car lst)) (remove item (cdr lst)))
    (else (cons (car lst) (remove item (cdr lst))))
  
  )
)

;;; Тесты
;(remove 3 nil)
; ()
;(remove 3 '(1 3 5))
; (1 5)
;(remove 5 '(5 3 5 5 1 4 5 4))
; (3 1 4 4)

; Вопрос 8
(define (no-repeats s)
  ( if (null? s)
    nil
    ( cons 
      (car s) 
      (no-repeats (remove (car s) (cdr s)))
    )
  )
)

; Вопрос 9
(define (substitute s old new)
  ( cond 
    ((null? s) nil)
  
    ((pair? (car s))
      (cons
        (substitute (car s) old new)
        (substitute (cdr s) old new)
      )
    )
    ( else
      (if (equal? (car s) old) 
        (cons
          new
          (substitute (cdr s) old new)
        )
        ( cons
          (car s)
          (substitute (cdr s) old new)
        )
      )
    )
  )
)

; Вопрос 10
(define (sub-all s olds news)
  (if (null? olds)
    s
    (substitute (sub-all s (cdr olds) (cdr news)) (car olds) (car news))
  )
)