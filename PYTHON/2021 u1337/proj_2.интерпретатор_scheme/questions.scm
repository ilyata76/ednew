(define (caar x) (car (car x)))
(define (cadr x) (car (cdr x)))
(define (cdar x) (cdr (car x)))
(define (cddr x) (cdr (cdr x)))

; Некоторые вспомогательные функции, которые, может, пригодятся тебе.

(define (cons-all first rests)
  (define (insert elem)
    (cons first elem)
  )
  (map insert rests)
)

(define (my-append list1 list2) 
; ((1) (2)) ((3) (4)) -> ((1 2) (3 4))
  (list
  ( append (car list1) (car list2) )
  ( append (car (cdr list1)) (car (cdr list2)) )
  )
)

(define (zip pairs)
  (cond 
    ((null? pairs) (list nil nil))
    ( else (   my-append (list (list (car (car pairs))) (cdr (car pairs)))
                         (zip (cdr pairs))                               )
    )
  )
)

; (define (zip pairs)
;   (define (get-cars lst)
;     (if (null? lst) nil (cons (car (car lst)) (get-cars (cdr lst)) ))
;   )
;   (define (get-cdrs lst)
;     (if (null? lst) nil (cons (car (cdr (car lst))) (get-cdrs (cdr lst)) ))
;   )
;   (list (get-cars pairs) (get-cdrs pairs))
; )

;; Задача 17
;; Возвращает список двухэлементных списков
(define (enumerate s)
  (define (new_list index lst )    
    (cond
      ( (null? lst)  nil                                                                       )
      (        else  (cons (cons index (cons (car lst) nil)) (new_list (+ 1 index) (cdr lst))) )
    )
  )
  (new_list 0 s)
)


;; Задача 18
;; Возвращает список всех вариантов размена TOTAL на DENOMS

(define (list-change total denoms)
  (cond ((null? denoms) nil)
        ((= 0 total) nil)
        ((= total (car denoms)) (append (list (list total)) (list-change total (cdr denoms))))
        ((< total (car denoms)) (list-change total (cdr denoms)))
        ;(null? (list-change (- total (car denoms)) denoms))
        (else (append 
                      (cons-all (car denoms) (list-change (- total (car denoms)) denoms))
                      (list-change total (cdr denoms))
              ) 
        )
  )
)
; КОНЕЦ ЗАДАЧ 18


;
;; Задача 19
;; Возвращает функцию, которая проверяет
;; является ли выражение особой формой FORM
(define (check-special form)
  (lambda (expr) (equal? form (car expr))))

(define lambda? (check-special 'lambda))
(define define? (check-special 'define))
(define quoted? (check-special 'quote))
(define let?    (check-special 'let))

;; Заменяет все особые формы let в выражении EXPR
;; на эквивалентные формы lambda
(define (let-to-lambda expr)
  (cond ((atom? expr)
         ; НАЧАЛО 19
         expr
         ; КОНЕЦ  19
         )
        ((quoted? expr)
         ; НАЧАЛО  19
         expr
         ; КОНЕЦ  19
         )
        ((or (lambda? expr)
             (define? expr))
         (let ((form   (car expr))
               (params (cadr expr))
               (body   (cddr expr)))
           ; НАЧАЛО  19
           (eval (list form params (let-to-lambda (car body))))
           ;(cons form (cons params (cons (let-to-lambda (car body)) nil)))
           ; КОНЕЦ  19
           ))
        ((let? expr)

         (let ((values (cadr expr))
               (body   (cddr expr)))
           ; НАЧАЛО  19
           (define ZIPA (zip values))
           (define (POPA list) 
              (cond 
                ((null? list) nil)
                (else (cons (car list) (POPA (cdr list))) 
                )
              )
           )
           (cons (cons 'lambda (cons (car ZIPA) (cons (let-to-lambda (car body)) nil))) (POPA (car (cdr ZIPA))) )

           ; КОНЕЦ  19
           ))
        (else
         ; НАЧАЛО  19
         expr
         ; КОНЕЦ  19
         )))
