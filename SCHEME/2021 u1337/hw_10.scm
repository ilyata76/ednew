
; Хвостовая рекурсия
; Вопрос 1
(define (replicate x n . rest)
  (if (= n 0) 
      ( if (null? rest) nil (car rest) )
      ( if (null? rest) (begin (define NEW_REST (append rest (list x))) (replicate x (- n 1) NEW_REST) ) 
                        (begin (define NEW_REST (append (car rest) (list x))) (replicate x (- n 1) NEW_REST) ) )
  )  
)

; Вопрос 2
(define (accumulate combiner start n term)
  (define (my_accumulate combiner start n term index)
    (if (= index 0)
      (combiner start (my_accumulate combiner start n term (+ index 1)))
      (if (= n 0)
        (if (eq? combiner *) 1 0)
        (combiner (term index) (my_accumulate combiner start (- n 1) term (+ index 1)))
      )
    )
  )
  (my_accumulate combiner start n term 0)
)

; Вопрос 3
(define (accumulate-tail combiner start n term)
  (define (my_accumulate combiner start n term index . rest)
    ( if (= index 0)
        (my_accumulate combiner start n term (+ index 1) start)
        (if (= n 0)
            ( if (null? rest) start (car rest) )
            ( if (null? rest)  
                      (begin ( define NEW_REST start ) (my_accumulate combiner start (- n 1) term (+ index 1) NEW_REST) )
                      (begin ( define NEW_REST (combiner (car rest) (term index)) ) (my_accumulate combiner start (- n 1) term (+ index 1) NEW_REST) ) )
        )
    )  
  )
  (my_accumulate combiner start n term 0 10)
)

; Потоки
; Вопрос 4
(define (map-stream f s)
    (if (null? s)
    	nil
    	(cons-stream (f (car s)) (map-stream f (cdr-stream s)))))

(define multiples-of-three
  (cons-stream 
      3 
      (map-stream (lambda (x) (+ x 3) ) multiples-of-three)
  )
)

; Вопрос 5
(define (nondecreastream s . rest)
    'sss
)


(define finite-test-stream
    (cons-stream 1
        (cons-stream 2
            (cons-stream 3
                (cons-stream 1
                    (cons-stream 2
                        (cons-stream 2
                            (cons-stream 1 nil))))))))

(define infinite-test-stream
    (cons-stream 1
        (cons-stream 2
            (cons-stream 2
                infinite-test-stream))))