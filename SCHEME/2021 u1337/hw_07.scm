; Вопрос 1
(define (cddr s)
  (cdr (cdr s)))

(define (cadr s)
  (car (cdr s))
)

(define (caddr s)
  (car (cddr s))
)

; Вопрос 2
(define (sign x)
  (cond
    ((> x 0) 1)
    ((< x 0) -1)
    (else 0)
  )
)

; Вопрос 3
(define (square x) (* x x))

(define (pow b n)
  ( cond
    ((= n 0) 1)
    ((even? n) (* (square b) (pow b (- n 2))))
    ((odd? n) (* b (pow b (- n 1))))
    (else 1)
  )
)

; Вопрос 4
(define (ordered? s)
  ( cond
    ( (and (not (null? s)) (not (null? (cdr s))) (car s) (cadr s)) ( and (<= (car s) (cadr s)) (ordered? (cdr s)) ) )
    ( else #t)
  )
)

; Вопрос 5
(define (empty? s) (null? s))

(define (add s v)
  ( cond
    (    (null? s)        (cons v nil)                     ) ; если всё-таки дошёл до конца и не выпал раньше -> значит не было
    (    (< (car s) v)    (cons (car s) (add (cdr s) v))   ) ; если всё ещё не дошёл до места
    (    (> (car s) v)    (cons v (cons (car s) (cdr s)))  ) ; первое и единственное вхождение большего элемента
    ( else                (cons (car s) (cdr s))           ) ; если равен элементу
  )
)

; Вопрос 6
(define (contains? s v)
  ( cond
    (  (or (null? s) (> (car s) v ))     #f                     )
    (  (= (car s) v)                     #t                     )
    (  else                              (contains? (cdr s) v)  )

  )
)

; Эквивалентный код на Python:
;
; def empty(s):
;     return s is Link.empty
;
; def contains(s, v):
;     if empty(s):
;         return False
;     elif s.first > v:
;         return False
;     elif s.first == v:
;         return True
;     else:
;         return contains(s.rest, v)

; Вопрос 7
(define (intersect s t)
  (cond 
    (  (or (null? s) (null? t))    nil                                        )
    (  (= (car s) (car t))         (cons (car s) (intersect (cdr s) (cdr t))) )
    (  (< (car s) (car t))         (intersect (cdr s) t)                      )
    (  (> (car s) (car t))         (intersect s (cdr t))                      )
  )
)

; Эквивалентный код на Python:
;
; def intersect(set1, set2):
;     if empty(set1) or empty(set2):
;         return Link.empty
;     else:
;         e1, e2 = set1.first, set2.first
;         if e1 == e2:
;             return Link(e1, intersect(set1.rest, set2.rest))
;         elif e1 < e2:
;             return intersect(set1.rest, set2)
;         elif e2 < e1:
;             return intersect(set1, set2.rest)

(define (union s t)
  ( cond
    ( (null? s)                (cons (car t) (cdr t))                   )
    ( (null? t)                (cons (car s) (cdr s))                   )
    ( (< (car s) (car t))      (cons (car s) (union (cdr s) t))         )
    ( (> (car s) (car t))      (cons (car t) (union s (cdr t)))         )
    ( (= (car s) (car t))      (cons (car s) (union (cdr s) (cdr t)))   )
  )
)