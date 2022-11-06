(define (caar x) (car (car x)))
(define (cadr x) (car (cdr x)))
(define (cdar x) (cdr (car x)))
(define (cddr x) (cdr (cdr x)))

; Некоторые вспомогательные функции, которые, может, пригодятся тебе.

(define (cons-all first rests)
  'replace-this-line)

(define (zip pairs)
  'replace-this-line)

;; Задача 17
;; Возвращает список двухэлементных списков
(define (enumerate s)
  (define (new_list index lst )    
    (cond
      ((null? lst)  nil   )
      ( else (cons (cons index (cons (car lst) nil)) (new_list (+ 1 index) (cdr lst) ) )                              )
    )
  )
  (new_list 0 s)
)


;; Задача 18
;; Возвращает список всех вариантов размена TOTAL на DENOMS
(define (list-change total denoms)
  ; НАЧАЛО ЗАДАЧИ 18
  'replace-this-line
  )
  ; КОНЕЦ ЗАДАЧИ 18

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
         ; НАЧАЛО ЗАДАЧИ 19
         'replace-this-line
         ; КОНЕЦ ЗАДАЧИ 19
         )
        ((quoted? expr)
         ; НАЧАЛО ЗАДАЧИ 19
         'replace-this-line
         ; КОНЕЦ ЗАДАЧИ 19
         )
        ((or (lambda? expr)
             (define? expr))
         (let ((form   (car expr))
               (params (cadr expr))
               (body   (cddr expr)))
           ; НАЧАЛО ЗАДАЧИ 19
           'replace-this-line
           ; КОНЕЦ ЗАДАЧИ 19
           ))
        ((let? expr)
         (let ((values (cadr expr))
               (body   (cddr expr)))
           ; НАЧАЛО ЗАДАЧИ 19
           'replace-this-line
           ; КОНЕЦ ЗАДАЧИ 19
           ))
        (else
         ; НАЧАЛО ЗАДАЧИ 19
         'replace-this-line
         ; КОНЕЦ ЗАДАЧИ 19
         )))
